/*
 * Solaris driver for ethernet cards based on the ADMtek Centaur
 *
 * Copyright (c) 2007 by Garrett D'Amore <garrett@damore.org>.
 * All rights reserved.
 *
 * Redistribution and use in source and binary forms, with or without
 * modification, are permitted provided that the following conditions
 * are met:
 * 1. Redistributions of source code must retain the above copyright
 *    notice, this list of conditions and the following disclaimer.
 * 2. Redistributions in binary form must reproduce the above copyright
 *    notice, this list of conditions and the following disclaimer in the
 *    documentation and/or other materials provided with the distribution.
 * 3. Neither the name of the author nor the names of any co-contributors
 *    may be used to endorse or promote products derived from this software
 *    without specific prior written permission.
 *
 * THIS SOFTWARE IS PROVIDED BY THE COPYRIGHT HOLDER AND CONTRIBUTORS ``AS IS''
 * AND ANY EXPRESS OR IMPLIED WARRANTIES, INCLUDING, BUT NOT LIMITED TO, THE
 * IMPLIED WARRANTIES OF MERCHANTABILITY AND FITNESS FOR A PARTICULAR PURPOSE
 * ARE DISCLAIMED.  IN NO EVENT SHALL THE COPYRIGHT HOLDER OR CONTRIBUTORS BE
 * LIABLE FOR ANY DIRECT, INDIRECT, INCIDENTAL, SPECIAL, EXEMPLARY, OR
 * CONSEQUENTIAL DAMAGES (INCLUDING, BUT NOT LIMITED TO, PROCUREMENT OF
 * SUBSTITUTE GOODS OR SERVICES; LOSS OF USE, DATA, OR PROFITS; OR BUSINESS
 * INTERRUPTION) HOWEVER CAUSED AND ON ANY THEORY OF LIABILITY, WHETHER IN
 * CONTRACT, STRICT LIABILITY, OR TORT (INCLUDING NEGLIGENCE OR OTHERWISE)
 * ARISING IN ANY WAY OUT OF THE USE OF THIS SOFTWARE, EVEN IF ADVISED OF THE
 * POSSIBILITY OF SUCH DAMAGE.
 */
/*
 * Copyright 2008 Sun Microsystems, Inc.  All rights reserved.
 * Use is subject to license terms.
 */

#pragma ident	"%Z%%M%	%I%	%E% SMI"

#include <sys/varargs.h>
#include <sys/types.h>
#include <sys/modctl.h>
#include <sys/conf.h>
#include <sys/devops.h>
#include <sys/stream.h>
#include <sys/strsun.h>
#include <sys/cmn_err.h>
#include <sys/ethernet.h>
#include <sys/kmem.h>
#include <sys/time.h>
#include <sys/crc32.h>
#include <sys/miiregs.h>
#include <sys/mac.h>
#include <sys/mac_ether.h>
#include <sys/ddi.h>
#include <sys/sunddi.h>
#include <sys/vlan.h>

#include "afe.h"
#include "afeimpl.h"

/*
 * Driver globals.
 */

/* patchable debug flag ... must not be static! */
#ifdef	DEBUG
unsigned		afe_debug = DWARN;
#endif

/* table of supported devices */
static afe_card_t afe_cards[] = {

	/*
	 * ADMtek Centaur and Comet
	 */
	{ 0x1317, 0x0981, "ADMtek AL981", MODEL_COMET },
	{ 0x1317, 0x0985, "ADMtek AN983", MODEL_CENTAUR },
	{ 0x1317, 0x1985, "ADMtek AN985", MODEL_CENTAUR },
	{ 0x1317, 0x9511, "ADMtek ADM9511", MODEL_CENTAUR },
	{ 0x1317, 0x9513, "ADMtek ADM9513", MODEL_CENTAUR },
	/*
	 * Accton just relabels other companies' controllers
	 */
	{ 0x1113, 0x1216, "Accton EN5251", MODEL_CENTAUR },
	/*
	 * Models listed here.
	 */
	{ 0x10b7, 0x9300, "3Com 3CSOHO100B-TX", MODEL_CENTAUR },
	{ 0x1113, 0xec02, "SMC SMC1244TX", MODEL_CENTAUR },
	{ 0x10b8, 0x1255, "SMC SMC1255TX", MODEL_CENTAUR },
	{ 0x111a, 0x1020, "Siemens SpeedStream PCI 10/100", MODEL_CENTAUR },
	{ 0x1113, 0x1207, "Accton EN1207F", MODEL_CENTAUR },
	{ 0x1113, 0x2242, "Accton EN2242", MODEL_CENTAUR },
	{ 0x1113, 0x2220, "Accton EN2220", MODEL_CENTAUR },
	{ 0x1113, 0x9216, "3M VOL-N100VF+TX", MODEL_CENTAUR },
	{ 0x1317, 0x0574, "Linksys LNE100TX", MODEL_CENTAUR },
	{ 0x1317, 0x0570, "Linksys NC100", MODEL_CENTAUR },
	{ 0x1385, 0x511a, "Netgear FA511", MODEL_CENTAUR },
	{ 0x13d1, 0xab02, "AboCom FE2500", MODEL_CENTAUR },
	{ 0x13d1, 0xab03, "AboCom PCM200", MODEL_CENTAUR },
	{ 0x13d1, 0xab08, "AboCom FE2500MX", MODEL_CENTAUR },
	{ 0x1414, 0x0001, "Microsoft MN-120", MODEL_CENTAUR },
	{ 0x16ec, 0x00ed, "U.S. Robotics USR997900", MODEL_CENTAUR },
	{ 0x1734, 0x100c, "Fujitsu-Siemens D1961", MODEL_CENTAUR },
	{ 0x1737, 0xab08, "Linksys PCMPC200", MODEL_CENTAUR },
	{ 0x1737, 0xab09, "Linksys PCM200", MODEL_CENTAUR },
	{ 0x17b3, 0xab08, "Hawking PN672TX", MODEL_CENTAUR },
};

#define	ETHERVLANMTU	(ETHERMAX + 4)

/*
 * Function prototypes
 */
static int	afe_attach(dev_info_t *, ddi_attach_cmd_t);
static int	afe_detach(dev_info_t *, ddi_detach_cmd_t);
static int	afe_resume(dev_info_t *);
static int	afe_m_unicst(void *, const uint8_t *);
static int	afe_m_multicst(void *, boolean_t, const uint8_t *);
static int	afe_m_promisc(void *, boolean_t);
static mblk_t	*afe_m_tx(void *, mblk_t *);
static int	afe_m_stat(void *, uint_t, uint64_t *);
static int	afe_m_start(void *);
static void	afe_m_stop(void *);
static int	afe_m_getprop(void *, const char *, mac_prop_id_t, uint_t,
    uint_t, void *);
static int	afe_m_setprop(void *, const char *, mac_prop_id_t, uint_t,
    const void *);
static unsigned	afe_intr(caddr_t);
static void	afe_startmac(afe_t *);
static void	afe_stopmac(afe_t *);
static void	afe_resetrings(afe_t *);
static boolean_t	afe_initialize(afe_t *);
static void	afe_startall(afe_t *);
static void	afe_stopall(afe_t *);
static void	afe_resetall(afe_t *);
static afe_txbuf_t *afe_alloctxbuf(afe_t *);
static void	afe_destroytxbuf(afe_txbuf_t *);
static afe_rxbuf_t *afe_allocrxbuf(afe_t *);
static void	afe_destroyrxbuf(afe_rxbuf_t *);
static boolean_t	afe_send(afe_t *, mblk_t *);
static int	afe_allocrxring(afe_t *);
static void	afe_freerxring(afe_t *);
static int	afe_alloctxring(afe_t *);
static void	afe_freetxring(afe_t *);
static void	afe_error(dev_info_t *, char *, ...);
static void	afe_setrxfilt(afe_t *);
static uint8_t	afe_sromwidth(afe_t *);
static uint16_t	afe_readsromword(afe_t *, unsigned);
static void	afe_readsrom(afe_t *, unsigned, unsigned, char *);
static void	afe_getfactaddr(afe_t *, uchar_t *);
static uint8_t	afe_miireadbit(afe_t *);
static void	afe_miiwritebit(afe_t *, uint8_t);
static void	afe_miitristate(afe_t *);
static uint16_t	afe_miiread(afe_t *, int, int);
static void	afe_miiwrite(afe_t *, int, int, uint16_t);
static uint16_t	afe_miireadgeneral(afe_t *, int, int);
static void	afe_miiwritegeneral(afe_t *, int, int, uint16_t);
static uint16_t	afe_miireadcomet(afe_t *, int, int);
static void	afe_miiwritecomet(afe_t *, int, int, uint16_t);
static int	afe_getmiibit(afe_t *, uint16_t, uint16_t);
static void	afe_startphy(afe_t *);
static void	afe_stopphy(afe_t *);
static void	afe_reportlink(afe_t *);
static void	afe_checklink(afe_t *);
static void	afe_checklinkcomet(afe_t *);
static void	afe_checklinkcentaur(afe_t *);
static void	afe_checklinkmii(afe_t *);
static void	afe_disableinterrupts(afe_t *);
static void	afe_enableinterrupts(afe_t *);
static void	afe_reclaim(afe_t *);
static mblk_t	*afe_receive(afe_t *);

#ifdef	DEBUG
static void	afe_dprintf(afe_t *, const char *, int, char *, ...);
#endif

#define	KIOIP	KSTAT_INTR_PTR(afep->afe_intrstat)

static mac_callbacks_t afe_m_callbacks = {
	MC_SETPROP | MC_GETPROP,
	afe_m_stat,
	afe_m_start,
	afe_m_stop,
	afe_m_promisc,
	afe_m_multicst,
	afe_m_unicst,
	afe_m_tx,
	NULL,		/* mc_resources */
	NULL,		/* mc_ioctl */
	NULL,		/* mc_getcapab */
	NULL,		/* mc_open */
	NULL,		/* mc_close */
	afe_m_setprop,
	afe_m_getprop,
};


/*
 * Stream information
 */
DDI_DEFINE_STREAM_OPS(afe_devops, nulldev, nulldev, afe_attach, afe_detach,
    nodev, NULL, D_MP, NULL);

/*
 * Module linkage information.
 */

static struct modldrv afe_modldrv = {
	&mod_driverops,			/* drv_modops */
	"ADMtek Fast Ethernet",		/* drv_linkinfo */
	&afe_devops			/* drv_dev_ops */
};

static struct modlinkage afe_modlinkage = {
	MODREV_1,		/* ml_rev */
	{ &afe_modldrv, NULL }	/* ml_linkage */
};

/*
 * Device attributes.
 */
static ddi_device_acc_attr_t afe_devattr = {
	DDI_DEVICE_ATTR_V0,
	DDI_STRUCTURE_LE_ACC,
	DDI_STRICTORDER_ACC
};

static ddi_device_acc_attr_t afe_bufattr = {
	DDI_DEVICE_ATTR_V0,
	DDI_NEVERSWAP_ACC,
	DDI_STRICTORDER_ACC
};

static ddi_dma_attr_t afe_dma_attr = {
	DMA_ATTR_V0,		/* dma_attr_version */
	0,			/* dma_attr_addr_lo */
	0xFFFFFFFFU,		/* dma_attr_addr_hi */
	0x7FFFFFFFU,		/* dma_attr_count_max */
	4,			/* dma_attr_align */
	0x3F,			/* dma_attr_burstsizes */
	1,			/* dma_attr_minxfer */
	0xFFFFFFFFU,		/* dma_attr_maxxfer */
	0xFFFFFFFFU,		/* dma_attr_seg */
	1,			/* dma_attr_sgllen */
	1,			/* dma_attr_granular */
	0			/* dma_attr_flags */
};

/*
 * Tx buffers can be arbitrarily aligned.  Additionally, they can
 * cross a page boundary, so we use the two buffer addresses of the
 * chip to provide a two-entry scatter-gather list.
 */
static ddi_dma_attr_t afe_dma_txattr = {
	DMA_ATTR_V0,		/* dma_attr_version */
	0,			/* dma_attr_addr_lo */
	0xFFFFFFFFU,		/* dma_attr_addr_hi */
	0x7FFFFFFFU,		/* dma_attr_count_max */
	1,			/* dma_attr_align */
	0x3F,			/* dma_attr_burstsizes */
	1,			/* dma_attr_minxfer */
	0xFFFFFFFFU,		/* dma_attr_maxxfer */
	0xFFFFFFFFU,		/* dma_attr_seg */
	2,			/* dma_attr_sgllen */
	1,			/* dma_attr_granular */
	0			/* dma_attr_flags */
};

/*
 * Ethernet addresses.
 */
static uchar_t afe_broadcast[ETHERADDRL] = {
	0xff, 0xff, 0xff, 0xff, 0xff, 0xff
};

/*
 * DDI entry points.
 */
int
_init(void)
{
	int	rv;
	mac_init_ops(&afe_devops, "afe");
	if ((rv = mod_install(&afe_modlinkage)) != DDI_SUCCESS) {
		mac_fini_ops(&afe_devops);
	}
	return (rv);
}

int
_fini(void)
{
	int	rv;
	if ((rv = mod_remove(&afe_modlinkage)) == DDI_SUCCESS) {
		mac_fini_ops(&afe_devops);
	}
	return (rv);
}

int
_info(struct modinfo *modinfop)
{
	return (mod_info(&afe_modlinkage, modinfop));
}

int
afe_attach(dev_info_t *dip, ddi_attach_cmd_t cmd)
{
	afe_t			*afep;
	mac_register_t		*macp;
	int			inst = ddi_get_instance(dip);
	ddi_acc_handle_t	pci;
	uint16_t		venid;
	uint16_t		devid;
	uint16_t		svid;
	uint16_t		ssid;
	uint16_t		cachesize;
	afe_card_t		*cardp;
	int			i;

	switch (cmd) {
	case DDI_RESUME:
		return (afe_resume(dip));

	case DDI_ATTACH:
		break;

	default:
		return (DDI_FAILURE);
	}

	/* this card is a bus master, reject any slave-only slot */
	if (ddi_slaveonly(dip) == DDI_SUCCESS) {
		afe_error(dip, "slot does not support PCI bus-master");
		return (DDI_FAILURE);
	}
	/* PCI devices shouldn't generate hilevel interrupts */
	if (ddi_intr_hilevel(dip, 0) != 0) {
		afe_error(dip, "hilevel interrupts not supported");
		return (DDI_FAILURE);
	}
	if (pci_config_setup(dip, &pci) != DDI_SUCCESS) {
		afe_error(dip, "unable to setup PCI config handle");
		return (DDI_FAILURE);
	}

	venid = pci_config_get16(pci, PCI_VID);
	devid = pci_config_get16(pci, PCI_DID);
	svid = pci_config_get16(pci, PCI_SVID);
	ssid = pci_config_get16(pci, PCI_SSID);

	/*
	 * Note: ADMtek boards seem to misprogram themselves with bogus
	 * timings, which do not seem to work properly on SPARC.  We
	 * reprogram them zero (but only if they appear to be broken),
	 * which seems to at least work.  Its unclear that this is a
	 * legal or wise practice to me, but it certainly works better
	 * than the original values.  (I would love to hear
	 * suggestions for better values, or a better strategy.)
	 */
	if ((pci_config_get8(pci, PCI_MINGNT) == 0xff) &&
	    (pci_config_get8(pci, PCI_MAXLAT) == 0xff)) {
		pci_config_put8(pci, PCI_MINGNT, 0);
		pci_config_put8(pci, PCI_MAXLAT, 0);
	}

	/*
	 * the last entry in the card table matches every possible
	 * card, so the for-loop always terminates properly.
	 */
	cardp = NULL;
	for (i = 0; i < (sizeof (afe_cards) / sizeof (afe_card_t)); i++) {
		if ((venid == afe_cards[i].card_venid) &&
		    (devid == afe_cards[i].card_devid)) {
			cardp = &afe_cards[i];
		}
		if ((svid == afe_cards[i].card_venid) &&
		    (ssid == afe_cards[i].card_devid)) {
			cardp = &afe_cards[i];
			break;
		}
	}

	if (cardp == NULL) {
		pci_config_teardown(&pci);
		afe_error(dip, "Unable to identify PCI card");
		return (DDI_FAILURE);
	}

	if (ddi_prop_update_string(DDI_DEV_T_NONE, dip, "model",
	    cardp->card_cardname) != DDI_PROP_SUCCESS) {
		pci_config_teardown(&pci);
		afe_error(dip, "Unable to create model property");
		return (DDI_FAILURE);
	}

	/*
	 * Grab the PCI cachesize -- we use this to program the
	 * cache-optimization bus access bits.
	 */
	cachesize = pci_config_get8(pci, PCI_CLS);

	/* this cannot fail */
	afep = kmem_zalloc(sizeof (afe_t), KM_SLEEP);
	ddi_set_driver_private(dip, afep);

	/* get the interrupt block cookie */
	if (ddi_get_iblock_cookie(dip, 0, &afep->afe_icookie) != DDI_SUCCESS) {
		afe_error(dip, "ddi_get_iblock_cookie failed");
		pci_config_teardown(&pci);
		kmem_free(afep, sizeof (afe_t));
		return (DDI_FAILURE);
	}

	afep->afe_dip = dip;
	afep->afe_cardp = cardp;
	afep->afe_phyaddr = -1;
	afep->afe_cachesize = cachesize;

	/* default properties */
	afep->afe_adv_aneg = !!ddi_prop_get_int(DDI_DEV_T_ANY, dip, 0,
	    "adv_autoneg_cap", 1);
	afep->afe_adv_100T4 = !!ddi_prop_get_int(DDI_DEV_T_ANY, dip, 0,
	    "adv_100T4_cap", 1);
	afep->afe_adv_100fdx = !!ddi_prop_get_int(DDI_DEV_T_ANY, dip, 0,
	    "adv_100fdx_cap", 1);
	afep->afe_adv_100hdx = !!ddi_prop_get_int(DDI_DEV_T_ANY, dip, 0,
	    "adv_100hdx_cap", 1);
	afep->afe_adv_10fdx = !!ddi_prop_get_int(DDI_DEV_T_ANY, dip, 0,
	    "adv_10fdx_cap", 1);
	afep->afe_adv_10hdx = !!ddi_prop_get_int(DDI_DEV_T_ANY, dip, 0,
	    "adv_10hdx_cap", 1);

	afep->afe_forcefiber = ddi_prop_get_int(DDI_DEV_T_ANY, dip, 0,
	    "fiber", 0);

	DBG(DPCI, "PCI vendor id = %x", venid);
	DBG(DPCI, "PCI device id = %x", devid);
	DBG(DPCI, "PCI cachesize = %d", cachesize);
	DBG(DPCI, "PCI COMM = %x", pci_config_get8(pci, PCI_CMD));
	DBG(DPCI, "PCI STAT = %x", pci_config_get8(pci, PCI_STAT));

	mutex_init(&afep->afe_xmtlock, NULL, MUTEX_DRIVER, afep->afe_icookie);
	mutex_init(&afep->afe_intrlock, NULL, MUTEX_DRIVER, afep->afe_icookie);

	/*
	 * Enable bus master, IO space, and memory space accesses.
	 */
	pci_config_put16(pci, PCI_CMD,
	    pci_config_get16(pci, PCI_CMD) | PCI_CMD_BME | PCI_CMD_MAE);

	/* we're done with this now, drop it */
	pci_config_teardown(&pci);

	/*
	 * Initialize interrupt kstat.  This should not normally fail, since
	 * we don't use a persistent stat.  We do it this way to avoid having
	 * to test for it at run time on the hot path.
	 */
	afep->afe_intrstat = kstat_create("afe", inst, "intr", "controller",
	    KSTAT_TYPE_INTR, 1, 0);
	if (afep->afe_intrstat == NULL) {
		afe_error(dip, "kstat_create failed");
		goto failed;
	}
	kstat_install(afep->afe_intrstat);

	/*
	 * Map in the device registers.
	 */
	if (ddi_regs_map_setup(dip, 1, (caddr_t *)&afep->afe_regs,
	    0, 0, &afe_devattr, &afep->afe_regshandle)) {
		afe_error(dip, "ddi_regs_map_setup failed");
		goto failed;
	}

	/*
	 * Allocate DMA resources (descriptor rings and buffers).
	 */
	if ((afe_allocrxring(afep) != DDI_SUCCESS) ||
	    (afe_alloctxring(afep) != DDI_SUCCESS)) {
		afe_error(dip, "unable to allocate DMA resources");
		goto failed;
	}

	/* Initialize the chip. */
	mutex_enter(&afep->afe_intrlock);
	mutex_enter(&afep->afe_xmtlock);
	if (!afe_initialize(afep)) {
		mutex_exit(&afep->afe_xmtlock);
		mutex_exit(&afep->afe_intrlock);
		goto failed;
	}
	mutex_exit(&afep->afe_xmtlock);
	mutex_exit(&afep->afe_intrlock);

	/* Determine the number of address bits to our EEPROM. */
	afep->afe_sromwidth = afe_sromwidth(afep);

	/*
	 * Get the factory ethernet address.  This becomes the current
	 * ethernet address (it can be overridden later via ifconfig).
	 */
	afe_getfactaddr(afep, afep->afe_curraddr);
	afep->afe_promisc = B_FALSE;

	/* make sure we add configure the initial filter */
	(void) afe_m_unicst(afep, afep->afe_curraddr);
	(void) afe_m_multicst(afep, B_TRUE, afe_broadcast);

	/*
	 * Establish interrupt handler.
	 */
	if (ddi_add_intr(dip, 0, NULL, NULL, afe_intr, (caddr_t)afep) !=
	    DDI_SUCCESS) {
		afe_error(dip, "unable to add interrupt");
		goto failed;
	}

	/* TODO: do the power management stuff */

	if ((macp = mac_alloc(MAC_VERSION)) == NULL) {
		afe_error(dip, "mac_alloc failed");
		goto failed;
	}

	macp->m_type_ident = MAC_PLUGIN_IDENT_ETHER;
	macp->m_driver = afep;
	macp->m_dip = dip;
	macp->m_src_addr = afep->afe_curraddr;
	macp->m_callbacks = &afe_m_callbacks;
	macp->m_min_sdu = 0;
	macp->m_max_sdu = ETHERMTU;
	macp->m_margin = VLAN_TAGSZ;

	if (mac_register(macp, &afep->afe_mh) == DDI_SUCCESS) {
		mac_free(macp);
		return (DDI_SUCCESS);
	}

	/* failed to register with MAC */
	mac_free(macp);
failed:
	if (afep->afe_icookie != NULL) {
		ddi_remove_intr(dip, 0, afep->afe_icookie);
	}
	if (afep->afe_intrstat) {
		kstat_delete(afep->afe_intrstat);
	}
	mutex_destroy(&afep->afe_intrlock);
	mutex_destroy(&afep->afe_xmtlock);

	afe_freerxring(afep);
	afe_freetxring(afep);

	if (afep->afe_regshandle != NULL) {
		ddi_regs_map_free(&afep->afe_regshandle);
	}
	kmem_free(afep, sizeof (afe_t));
	return (DDI_FAILURE);
}

int
afe_detach(dev_info_t *dip, ddi_detach_cmd_t cmd)
{
	afe_t		*afep;

	afep = ddi_get_driver_private(dip);
	if (afep == NULL) {
		afe_error(dip, "no soft state in detach!");
		return (DDI_FAILURE);
	}

	switch (cmd) {
	case DDI_DETACH:

		if (mac_unregister(afep->afe_mh) != 0) {
			return (DDI_FAILURE);
		}

		/* make sure hardware is quiesced */
		mutex_enter(&afep->afe_intrlock);
		mutex_enter(&afep->afe_xmtlock);
		afep->afe_flags &= ~AFE_RUNNING;
		afe_stopall(afep);
		mutex_exit(&afep->afe_xmtlock);
		mutex_exit(&afep->afe_intrlock);

		/* clean up and shut down device */
		ddi_remove_intr(dip, 0, afep->afe_icookie);

		/* clean up kstats */
		kstat_delete(afep->afe_intrstat);

		ddi_prop_remove_all(dip);

		/* free up any left over buffers or DMA resources */
		afe_freerxring(afep);
		afe_freetxring(afep);

		ddi_regs_map_free(&afep->afe_regshandle);
		mutex_destroy(&afep->afe_intrlock);
		mutex_destroy(&afep->afe_xmtlock);

		kmem_free(afep, sizeof (afe_t));
		return (DDI_SUCCESS);

	case DDI_SUSPEND:
		/* quiesce the hardware */
		mutex_enter(&afep->afe_intrlock);
		mutex_enter(&afep->afe_xmtlock);
		afep->afe_flags |= AFE_SUSPENDED;
		afe_stopall(afep);
		mutex_exit(&afep->afe_xmtlock);
		mutex_exit(&afep->afe_intrlock);
		return (DDI_SUCCESS);
	default:
		return (DDI_FAILURE);
	}
}

int
afe_resume(dev_info_t *dip)
{
	afe_t	*afep;

	if ((afep = ddi_get_driver_private(dip)) == NULL) {
		return (DDI_FAILURE);
	}

	mutex_enter(&afep->afe_intrlock);
	mutex_enter(&afep->afe_xmtlock);

	afep->afe_flags &= ~AFE_SUSPENDED;

	/* re-initialize chip */
	if (!afe_initialize(afep)) {
		afe_error(afep->afe_dip, "unable to resume chip!");
		afep->afe_flags |= AFE_SUSPENDED;
		mutex_exit(&afep->afe_intrlock);
		mutex_exit(&afep->afe_xmtlock);
		return (DDI_SUCCESS);
	}

	/* start the chip */
	if (afep->afe_flags & AFE_RUNNING) {
		afe_startall(afep);
	}

	/* drop locks */
	mutex_exit(&afep->afe_xmtlock);
	mutex_exit(&afep->afe_intrlock);

	return (DDI_SUCCESS);
}

void
afe_setrxfilt(afe_t *afep)
{
	unsigned rxen, pa0, pa1;

	if (afep->afe_flags & AFE_SUSPENDED) {
		/* don't touch a suspended interface */
		return;
	}

	rxen = GETCSR(afep, CSR_NAR) & NAR_RX_ENABLE;

	/* stop receiver */
	if (rxen) {
		afe_stopmac(afep);
	}

	/* program promiscuous mode */
	if (afep->afe_promisc)
		SETBIT(afep, CSR_NAR, NAR_RX_PROMISC);
	else
		CLRBIT(afep, CSR_NAR, NAR_RX_PROMISC);

	/* program mac address */
	pa0 = (afep->afe_curraddr[3] << 24) | (afep->afe_curraddr[2] << 16) |
	    (afep->afe_curraddr[1] << 8) | afep->afe_curraddr[0];
	pa1 = (afep->afe_curraddr[5] << 8) | afep->afe_curraddr[4];

	DBG(DMACID, "programming PAR0 with %x", pa0);
	DBG(DMACID, "programming PAR1 with %x", pa1);
	PUTCSR(afep, CSR_PAR0, pa0);
	PUTCSR(afep, CSR_PAR1, pa1);
	if (rxen) {
		SETBIT(afep, CSR_NAR, rxen);
	}

	DBG(DMACID, "programming MAR0 = %x", afep->afe_mctab[0]);
	DBG(DMACID, "programming MAR1 = %x", afep->afe_mctab[1]);

	/* program multicast filter */
	if (AFE_MODEL(afep) == MODEL_COMET) {
		if (afep->afe_mctab[0] || afep->afe_mctab[1]) {
			SETBIT(afep, CSR_NAR, NAR_RX_MULTI);
		} else {
			CLRBIT(afep, CSR_NAR, NAR_RX_MULTI);
		}
	} else {
		CLRBIT(afep, CSR_NAR, NAR_RX_MULTI);
		PUTCSR(afep, CSR_MAR0, afep->afe_mctab[0]);
		PUTCSR(afep, CSR_MAR1, afep->afe_mctab[1]);
	}

	/* restart receiver */
	if (rxen) {
		afe_startmac(afep);
	}
}

int
afe_m_multicst(void *arg, boolean_t add, const uint8_t *macaddr)
{
	afe_t		*afep = arg;
	int		index;
	uint32_t	crc;
	uint32_t	bit;
	uint32_t	newval, oldval;

	CRC32(crc, macaddr, ETHERADDRL, -1U, crc32_table);
	crc %= AFE_MCHASH;

	/* bit within a 32-bit word */
	index = crc / 32;
	bit = (1 << (crc % 32));

	mutex_enter(&afep->afe_intrlock);
	mutex_enter(&afep->afe_xmtlock);
	newval = oldval = afep->afe_mctab[index];

	if (add) {
		afep->afe_mccount[crc]++;
		if (afep->afe_mccount[crc] == 1)
			newval |= bit;
	} else {
		afep->afe_mccount[crc]--;
		if (afep->afe_mccount[crc] == 0)
			newval &= ~bit;
	}
	if (newval != oldval) {
		afep->afe_mctab[index] = newval;
		afe_setrxfilt(afep);
	}

	mutex_exit(&afep->afe_xmtlock);
	mutex_exit(&afep->afe_intrlock);

	return (0);
}

int
afe_m_promisc(void *arg, boolean_t on)
{
	afe_t		*afep = arg;

	/* exclusive access to the card while we reprogram it */
	mutex_enter(&afep->afe_intrlock);
	mutex_enter(&afep->afe_xmtlock);
	/* save current promiscuous mode state for replay in resume */
	afep->afe_promisc = on;

	afe_setrxfilt(afep);
	mutex_exit(&afep->afe_xmtlock);
	mutex_exit(&afep->afe_intrlock);

	return (0);
}

int
afe_m_unicst(void *arg, const uint8_t *macaddr)
{
	afe_t		*afep = arg;

	/* exclusive access to the card while we reprogram it */
	mutex_enter(&afep->afe_intrlock);
	mutex_enter(&afep->afe_xmtlock);

	bcopy(macaddr, afep->afe_curraddr, ETHERADDRL);
	afe_setrxfilt(afep);

	mutex_exit(&afep->afe_xmtlock);
	mutex_exit(&afep->afe_intrlock);

	return (0);
}

mblk_t *
afe_m_tx(void *arg, mblk_t *mp)
{
	afe_t	*afep = arg;
	mblk_t	*nmp;

	mutex_enter(&afep->afe_xmtlock);

	if (afep->afe_flags & AFE_SUSPENDED) {
		while ((nmp = mp) != NULL) {
			afep->afe_carrier_errors++;
			mp = mp->b_next;
			freemsg(nmp);
		}
		mutex_exit(&afep->afe_xmtlock);
		return (NULL);
	}

	while (mp != NULL) {
		nmp = mp->b_next;
		mp->b_next = NULL;

		if (!afe_send(afep, mp)) {
			mp->b_next = nmp;
			break;
		}
		mp = nmp;
	}
	mutex_exit(&afep->afe_xmtlock);

	return (mp);
}

/*
 * Hardware management.
 */
static boolean_t
afe_initialize(afe_t *afep)
{
	int		i;
	unsigned	val;
	uint32_t	par, nar;

	ASSERT(mutex_owned(&afep->afe_intrlock));
	ASSERT(mutex_owned(&afep->afe_xmtlock));

	DBG(DCHATTY, "resetting!");
	SETBIT(afep, CSR_PAR, PAR_RESET);
	for (i = 1; i < 10; i++) {
		drv_usecwait(5);
		val = GETCSR(afep, CSR_PAR);
		if (!(val & PAR_RESET)) {
			break;
		}
	}
	if (i == 10) {
		afe_error(afep->afe_dip, "timed out waiting for reset!");
		return (B_FALSE);
	}

	/*
	 * Updated Centaur data sheets show that the Comet and Centaur are
	 * alike here (contrary to earlier versions of the data sheet).
	 */
	/* XXX:? chip problems */
	/* par = PAR_MRLE | PAR_MRME | PAR_MWIE; */
	par = 0;
	switch (afep->afe_cachesize) {
	case 8:
		par |= PAR_CALIGN_8 | PAR_BURST_8;
		break;
	case 16:
		par |= PAR_CALIGN_16 | PAR_BURST_16;
		break;
	case 32:
		par |= PAR_CALIGN_32 | PAR_BURST_32;
		break;
	default:
		par |= PAR_BURST_32;
		par &= ~(PAR_MWIE | PAR_MRLE | PAR_MRME);
		break;

	}

	PUTCSR(afep, CSR_PAR, par);

	/* enable transmit underrun auto-recovery */
	SETBIT(afep, CSR_CR, CR_TXURAUTOR);

	afe_resetrings(afep);

	/* clear the lost packet counter (cleared on read) */
	(void) GETCSR(afep, CSR_LPC);

	nar = GETCSR(afep, CSR_NAR);
	nar &= ~NAR_TR;		/* clear tx threshold */
	nar |= NAR_SF;		/* store-and-forward */
	nar |= NAR_HBD;		/* disable SQE test */
	PUTCSR(afep, CSR_NAR, nar);

	afe_setrxfilt(afep);

	return (B_TRUE);
}

/*
 * Serial EEPROM access - inspired by the FreeBSD implementation.
 */

uint8_t
afe_sromwidth(afe_t *afep)
{
	int		i;
	uint32_t	eeread;
	uint8_t		addrlen = 8;

	eeread = SPR_SROM_READ | SPR_SROM_SEL | SPR_SROM_CHIP;

	PUTCSR(afep, CSR_SPR, eeread & ~SPR_SROM_CHIP);
	drv_usecwait(1);
	PUTCSR(afep, CSR_SPR, eeread);

	/* command bits first */
	for (i = 4; i != 0; i >>= 1) {
		unsigned val = (SROM_READCMD & i) ? SPR_SROM_DIN : 0;

		PUTCSR(afep, CSR_SPR, eeread | val);
		drv_usecwait(1);
		PUTCSR(afep, CSR_SPR, eeread | val | SPR_SROM_CLOCK);
		drv_usecwait(1);
	}

	PUTCSR(afep, CSR_SPR, eeread);

	for (addrlen = 1; addrlen <= 12; addrlen++) {
		PUTCSR(afep, CSR_SPR, eeread | SPR_SROM_CLOCK);
		drv_usecwait(1);
		if (!(GETCSR(afep, CSR_SPR) & SPR_SROM_DOUT)) {
			PUTCSR(afep, CSR_SPR, eeread);
			drv_usecwait(1);
			break;
		}
		PUTCSR(afep, CSR_SPR, eeread);
		drv_usecwait(1);
	}

	/* turn off accesses to the EEPROM */
	PUTCSR(afep, CSR_SPR, eeread &~ SPR_SROM_CHIP);

	DBG(DSROM, "detected srom width = %d bits", addrlen);

	return ((addrlen < 4 || addrlen > 12) ? 6 : addrlen);
}

/*
 * The words in EEPROM are stored in little endian order.  We
 * shift bits out in big endian order, though.  This requires
 * a byte swap on some platforms.
 */
uint16_t
afe_readsromword(afe_t *afep, unsigned romaddr)
{
	int		i;
	uint16_t	word = 0;
	uint16_t	retval;
	int		eeread;
	uint8_t		addrlen;
	int		readcmd;
	uchar_t		*ptr;

	eeread = SPR_SROM_READ | SPR_SROM_SEL | SPR_SROM_CHIP;
	addrlen = afep->afe_sromwidth;
	readcmd = (SROM_READCMD << addrlen) | romaddr;

	if (romaddr >= (1 << addrlen)) {
		/* too big to fit! */
		return (0);
	}

	PUTCSR(afep, CSR_SPR, eeread & ~SPR_SROM_CHIP);
	PUTCSR(afep, CSR_SPR, eeread);

	/* command and address bits */
	for (i = 4 + addrlen; i >= 0; i--) {
		short val = (readcmd & (1 << i)) ? SPR_SROM_DIN : 0;

		PUTCSR(afep, CSR_SPR, eeread | val);
		drv_usecwait(1);
		PUTCSR(afep, CSR_SPR, eeread | val | SPR_SROM_CLOCK);
		drv_usecwait(1);
	}

	PUTCSR(afep, CSR_SPR, eeread);

	for (i = 0; i < 16; i++) {
		PUTCSR(afep, CSR_SPR, eeread | SPR_SROM_CLOCK);
		drv_usecwait(1);
		word <<= 1;
		if (GETCSR(afep, CSR_SPR) & SPR_SROM_DOUT) {
			word |= 1;
		}
		PUTCSR(afep, CSR_SPR, eeread);
		drv_usecwait(1);
	}

	/* turn off accesses to the EEPROM */
	PUTCSR(afep, CSR_SPR, eeread &~ SPR_SROM_CHIP);

	/*
	 * Fix up the endianness thing.  Note that the values
	 * are stored in little endian format on the SROM.
	 */
	ptr = (uchar_t *)&word;
	retval = (ptr[1] << 8) | ptr[0];
	return (retval);
}

void
afe_readsrom(afe_t *afep, unsigned romaddr, unsigned len, char *dest)
{
	int	i;
	uint16_t	word;
	uint16_t	*ptr = (uint16_t *)((void *)dest);
	for (i = 0; i < len; i++) {
		word = afe_readsromword(afep, romaddr + i);
		*ptr = word;
		ptr++;
	}
}

void
afe_getfactaddr(afe_t *afep, uchar_t *eaddr)
{
	afe_readsrom(afep, SROM_ENADDR, ETHERADDRL / 2, (char *)eaddr);

	DBG(DMACID,
	    "factory ethernet address = %02x:%02x:%02x:%02x:%02x:%02x",
	    eaddr[0], eaddr[1], eaddr[2], eaddr[3], eaddr[4], eaddr[5]);
}

/*
 * MII management.
 */
void
afe_startphy(afe_t *afep)
{
	unsigned	phyaddr;
	unsigned	bmcr;
	unsigned	bmsr;
	unsigned	anar;
	unsigned	phyidr1;
	unsigned	phyidr2;
	unsigned	nosqe = 0;
	int		retries;
	int		fiber;
	int		cnt;

	/* ADMtek devices just use the PHY at address 1 */
	afep->afe_phyaddr = phyaddr = 1;

	phyidr1 = afe_miiread(afep, phyaddr, MII_PHYIDH);
	phyidr2 = afe_miiread(afep, phyaddr, MII_PHYIDL);
	if ((phyidr1 == 0x0022) &&
	    ((phyidr2 & 0xfff0) ==  0x5410)) {
		nosqe = 1;
		/* only 983B has fiber support */
		afep->afe_flags |= AFE_HASFIBER;
	}
	afep->afe_phyid = (phyidr1 << 16) | phyidr2;

	DBG(DPHY, "phy at %d: %x,%x", phyaddr, phyidr1, phyidr2);
	DBG(DPHY, "bmsr = %x", afe_miiread(afep,
	    afep->afe_phyaddr, MII_STATUS));
	DBG(DPHY, "anar = %x", afe_miiread(afep,
	    afep->afe_phyaddr, MII_AN_ADVERT));
	DBG(DPHY, "anlpar = %x", afe_miiread(afep,
	    afep->afe_phyaddr, MII_AN_LPABLE));
	DBG(DPHY, "aner = %x", afe_miiread(afep,
	    afep->afe_phyaddr, MII_AN_EXPANSION));

	DBG(DPHY, "resetting phy");

	/* we reset the phy block */
	afe_miiwrite(afep, phyaddr, MII_CONTROL, MII_CONTROL_RESET);
	/*
	 * wait for it to complete -- 500usec is still to short to
	 * bother getting the system clock involved.
	 */
	drv_usecwait(500);
	for (retries = 0; retries < 10; retries++) {
		if (afe_miiread(afep, phyaddr, MII_CONTROL) &
		    MII_CONTROL_RESET) {
			drv_usecwait(500);
			continue;
		}
		break;
	}
	if (retries == 100) {
		afe_error(afep->afe_dip, "timeout waiting on phy to reset");
		return;
	}

	DBG(DPHY, "phy reset complete");

	bmsr = afe_miiread(afep, phyaddr, MII_STATUS);
	anar = afe_miiread(afep, phyaddr, MII_AN_ADVERT);

	anar &= ~(MII_ABILITY_100BASE_T4 |
	    MII_ABILITY_100BASE_TX_FD | MII_ABILITY_100BASE_TX |
	    MII_ABILITY_10BASE_T_FD | MII_ABILITY_10BASE_T);

	fiber = 0;

	/* if fiber is being forced, and device supports fiber... */
	if (afep->afe_flags & AFE_HASFIBER) {

		uint16_t	mcr;

		DBG(DPHY, "device supports 100BaseFX");
		mcr = afe_miiread(afep, phyaddr, PHY_MCR);
		switch (afep->afe_forcefiber) {
		case 0:
			/* UTP Port */
			DBG(DPHY, "forcing twpair");
			mcr &= ~MCR_FIBER;
			fiber = 0;
			break;
		case 1:
			/* Fiber Port */
			DBG(DPHY, "forcing 100BaseFX");
			mcr |= MCR_FIBER;
			bmcr = (MII_CONTROL_100MB | MII_CONTROL_FDUPLEX);
			fiber = 1;
			break;
		default:
			DBG(DPHY, "checking for 100BaseFX link");
			/* fiber is 100 Mb FDX */
			afe_miiwrite(afep, phyaddr, MII_CONTROL,
			    MII_CONTROL_100MB | MII_CONTROL_FDUPLEX);
			drv_usecwait(50);

			mcr = afe_miiread(afep, phyaddr, PHY_MCR);
			mcr |= MCR_FIBER;
			afe_miiwrite(afep, phyaddr, PHY_MCR, mcr);
			drv_usecwait(500);

			/* if fiber is active, use it */
			if ((afe_miiread(afep, phyaddr, MII_STATUS) &
			    MII_STATUS_LINKUP)) {
				bmcr = MII_CONTROL_100MB | MII_CONTROL_FDUPLEX;
				fiber = 1;
			} else {
				mcr &= ~MCR_FIBER;
				fiber = 0;
			}
			break;
		}
		afe_miiwrite(afep, phyaddr, PHY_MCR, mcr);
		drv_usecwait(500);
	}

	if (fiber) {
		/* fiber only supports 100FDX(?) */
		bmsr &= ~(MII_STATUS_100_BASE_T4 |
		    MII_STATUS_100_BASEX | MII_STATUS_10_FD | MII_STATUS_10);
		bmsr |= MII_STATUS_100_BASEX_FD;
	}

	/* assume full support for everything to start */
	afep->afe_cap_aneg = afep->afe_cap_100T4 =
	    afep->afe_cap_100fdx = afep->afe_cap_100hdx =
	    afep->afe_cap_10fdx = afep->afe_cap_10hdx = 1;

	/* disable modes not supported in hardware */
	if (!(bmsr & MII_STATUS_100_BASEX_FD)) {
		afep->afe_adv_100fdx = 0;
		afep->afe_cap_100fdx = 0;
	}
	if (!(bmsr & MII_STATUS_100_BASE_T4)) {
		afep->afe_adv_100T4 = 0;
		afep->afe_cap_100T4 = 0;
	}
	if (!(bmsr & MII_STATUS_100_BASEX)) {
		afep->afe_adv_100hdx = 0;
		afep->afe_cap_100hdx = 0;
	}
	if (!(bmsr & MII_STATUS_10_FD)) {
		afep->afe_adv_10fdx = 0;
		afep->afe_cap_10fdx = 0;
	}
	if (!(bmsr & MII_STATUS_10)) {
		afep->afe_adv_10hdx = 0;
		afep->afe_cap_10hdx = 0;
	}
	if (!(bmsr & MII_STATUS_CANAUTONEG)) {
		afep->afe_adv_aneg = 0;
		afep->afe_cap_aneg = 0;
	}

	cnt = 0;
	if (afep->afe_adv_100fdx) {
		anar |= MII_ABILITY_100BASE_TX_FD;
		cnt++;
	}
	if (afep->afe_adv_100T4) {
		anar |= MII_ABILITY_100BASE_T4;
		cnt++;
	}
	if (afep->afe_adv_100hdx) {
		anar |= MII_ABILITY_100BASE_TX;
		cnt++;
	}
	if (afep->afe_adv_10fdx) {
		anar |= MII_ABILITY_10BASE_T_FD;
		cnt++;
	}
	if (afep->afe_adv_10hdx) {
		anar |= MII_ABILITY_10BASE_T;
		cnt++;
	}

	/*
	 * Make certain at least one valid link mode is selected.
	 */
	if (!cnt) {
		afe_error(afep->afe_dip, "No valid link mode selected.");
		afe_error(afep->afe_dip, "Powering down PHY.");
		afe_stopphy(afep);
		afep->afe_linkup = LINK_STATE_DOWN;
		if (afep->afe_flags & AFE_RUNNING)
			afe_reportlink(afep);
		return;
	}

	if (fiber) {
		bmcr = MII_CONTROL_100MB | MII_CONTROL_FDUPLEX;
	} else if ((afep->afe_adv_aneg) && (bmsr & MII_STATUS_CANAUTONEG)) {
		DBG(DPHY, "using autoneg mode");
		bmcr = (MII_CONTROL_ANE | MII_CONTROL_RSAN);
	} else {
		DBG(DPHY, "using forced mode");
		if (afep->afe_adv_100fdx) {
			bmcr = (MII_CONTROL_100MB | MII_CONTROL_FDUPLEX);
		} else if (afep->afe_adv_100hdx) {
			bmcr = MII_CONTROL_100MB;
		} else if (afep->afe_adv_10fdx) {
			bmcr = MII_CONTROL_FDUPLEX;
		} else {
			/* 10HDX */
			bmcr = 0;
		}
	}

	DBG(DPHY, "programming anar to 0x%x", anar);
	afe_miiwrite(afep, phyaddr, MII_AN_ADVERT, anar);
	DBG(DPHY, "programming bmcr to 0x%x", bmcr);
	afe_miiwrite(afep, phyaddr, MII_CONTROL, bmcr);

	if (nosqe) {
		uint16_t	pilr;
		/*
		 * work around for errata 983B_0416 -- duplex light flashes
		 * in 10 HDX.  we just disable SQE testing on the device.
		 */
		pilr = afe_miiread(afep, phyaddr, PHY_PILR);
		pilr |= PILR_NOSQE;
		afe_miiwrite(afep, phyaddr, PHY_PILR, pilr);
	}

	/*
	 * schedule a query of the link status
	 */
	PUTCSR(afep, CSR_TIMER, TIMER_LOOP |
	    (AFE_LINKTIMER * 1000 / TIMER_USEC));
}

void
afe_stopphy(afe_t *afep)
{
	/* stop the phy timer */
	PUTCSR(afep, CSR_TIMER, 0);

	/*
	 * phy in isolate & powerdown mode...
	 */
	afe_miiwrite(afep, afep->afe_phyaddr, MII_CONTROL,
	    MII_CONTROL_PWRDN | MII_CONTROL_ISOLATE);

	/*
	 * mark the link state unknown
	 */
	if (!afep->afe_resetting) {
		afep->afe_linkup = LINK_STATE_UNKNOWN;
		afep->afe_ifspeed = 0;
		afep->afe_duplex = LINK_DUPLEX_UNKNOWN;
		if (afep->afe_flags & AFE_RUNNING)
			afe_reportlink(afep);
	}
}

void
afe_reportlink(afe_t *afep)
{
	int changed = 0;

	if (afep->afe_ifspeed != afep->afe_lastifspeed) {
		afep->afe_lastifspeed = afep->afe_ifspeed;
		changed++;
	}
	if (afep->afe_duplex != afep->afe_lastduplex) {
		afep->afe_lastduplex = afep->afe_duplex;
		changed++;
	}
	if (changed)
		mac_link_update(afep->afe_mh, afep->afe_linkup);
}

void
afe_checklink(afe_t *afep)
{
	if ((afep->afe_flags & AFE_RUNNING) == 0)
		return;

	if ((afep->afe_txstall_time != 0) &&
	    (gethrtime() > afep->afe_txstall_time) &&
	    (afep->afe_txavail != AFE_TXRING)) {
		afep->afe_txstall_time = 0;
		afe_error(afep->afe_dip, "TX stall detected!");
		afe_resetall(afep);
		return;
	}

	switch (AFE_MODEL(afep)) {
	case MODEL_COMET:
		afe_checklinkcomet(afep);
		break;
	case MODEL_CENTAUR:
		afe_checklinkcentaur(afep);
		break;
	}
}

void
afe_checklinkcomet(afe_t *afep)
{
	uint16_t	xciis;
	int		reinit = 0;

	xciis = GETCSR16(afep, CSR_XCIIS);
	if (xciis & XCIIS_PDF) {
		afe_error(afep->afe_dip, "Parallel detection fault detected!");
	}
	if (xciis & XCIIS_RF) {
		afe_error(afep->afe_dip, "Remote fault detected.");
	}
	if (xciis & XCIIS_LFAIL) {
		if (afep->afe_linkup == LINK_STATE_UP) {
			reinit++;
		}
		afep->afe_ifspeed = 0;
		afep->afe_linkup = LINK_STATE_DOWN;
		afep->afe_duplex = LINK_DUPLEX_UNKNOWN;
		afe_reportlink(afep);
		if (reinit) {
			afe_startphy(afep);
		}
		return;
	}

	afep->afe_linkup = LINK_STATE_UP;
	afep->afe_ifspeed = (xciis & XCIIS_SPEED) ? 100000000 : 10000000;
	if (xciis & XCIIS_DUPLEX) {
		afep->afe_duplex = LINK_DUPLEX_FULL;
	} else {
		afep->afe_duplex = LINK_DUPLEX_HALF;
	}

	afe_reportlink(afep);
}

void
afe_checklinkcentaur(afe_t *afep)
{
	unsigned	opmode;
	int		reinit = 0;

	opmode = GETCSR(afep, CSR_OPM);
	if ((opmode & OPM_MODE) == OPM_MACONLY) {
		DBG(DPHY, "Centaur running in MAC-only mode");
		afe_checklinkmii(afep);
		return;
	}
	DBG(DPHY, "Centaur running in single chip mode");
	if ((opmode & OPM_LINK) == 0) {
		if (afep->afe_linkup == LINK_STATE_UP) {
			reinit++;
		}
		afep->afe_ifspeed = 0;
		afep->afe_duplex = LINK_DUPLEX_UNKNOWN;
		afep->afe_linkup = LINK_STATE_DOWN;
		afe_reportlink(afep);
		if (reinit) {
			afe_startphy(afep);
		}
		return;
	}

	afep->afe_linkup = LINK_STATE_UP;
	afep->afe_ifspeed = (opmode & OPM_SPEED) ? 100000000 : 10000000;
	if (opmode & OPM_DUPLEX) {
		afep->afe_duplex = LINK_DUPLEX_FULL;
	} else {
		afep->afe_duplex = LINK_DUPLEX_HALF;
	}
	afe_reportlink(afep);
}

void
afe_checklinkmii(afe_t *afep)
{
	/* read MII state registers */
	uint16_t	bmsr;
	uint16_t	bmcr;
	uint16_t	anar;
	uint16_t	anlpar;
	int			reinit = 0;

	/* read this twice, to clear latched link state */
	bmsr = afe_miiread(afep, afep->afe_phyaddr, MII_STATUS);
	bmsr = afe_miiread(afep, afep->afe_phyaddr, MII_STATUS);
	bmcr = afe_miiread(afep, afep->afe_phyaddr, MII_CONTROL);
	anar = afe_miiread(afep, afep->afe_phyaddr, MII_AN_ADVERT);
	anlpar = afe_miiread(afep, afep->afe_phyaddr, MII_AN_LPABLE);

	if (bmsr & MII_STATUS_REMFAULT) {
		afe_error(afep->afe_dip, "Remote fault detected.");
	}
	if (bmsr & MII_STATUS_JABBERING) {
		afe_error(afep->afe_dip, "Jabber condition detected.");
	}
	if ((bmsr & MII_STATUS_LINKUP) == 0) {
		/* no link */
		if (afep->afe_linkup == LINK_STATE_UP) {
			reinit = 1;
		}
		afep->afe_ifspeed = 0;
		afep->afe_duplex = LINK_DUPLEX_UNKNOWN;
		afep->afe_linkup = LINK_STATE_DOWN;
		afe_reportlink(afep);
		if (reinit) {
			afe_startphy(afep);
		}
		return;
	}

	DBG(DCHATTY, "link up!");
	afep->afe_linkup = LINK_STATE_UP;

	if (!(bmcr & MII_CONTROL_ANE)) {
		/* forced mode */
		if (bmcr & MII_CONTROL_100MB) {
			afep->afe_ifspeed = 100000000;
		} else {
			afep->afe_ifspeed = 10000000;
		}
		if (bmcr & MII_CONTROL_FDUPLEX) {
			afep->afe_duplex = LINK_DUPLEX_FULL;
		} else {
			afep->afe_duplex = LINK_DUPLEX_HALF;
		}
	} else if ((!(bmsr & MII_STATUS_CANAUTONEG)) ||
	    (!(bmsr & MII_STATUS_ANDONE))) {
		afep->afe_ifspeed = 0;
		afep->afe_duplex = LINK_DUPLEX_UNKNOWN;
	} else if (anar & anlpar & MII_ABILITY_100BASE_TX_FD) {
		afep->afe_ifspeed = 100000000;
		afep->afe_duplex = LINK_DUPLEX_FULL;
	} else if (anar & anlpar & MII_ABILITY_100BASE_T4) {
		afep->afe_ifspeed = 100000000;
		afep->afe_duplex = LINK_DUPLEX_HALF;
	} else if (anar & anlpar & MII_ABILITY_100BASE_TX) {
		afep->afe_ifspeed = 100000000;
		afep->afe_duplex = LINK_DUPLEX_HALF;
	} else if (anar & anlpar & MII_ABILITY_10BASE_T_FD) {
		afep->afe_ifspeed = 10000000;
		afep->afe_duplex = LINK_DUPLEX_FULL;
	} else if (anar & anlpar & MII_ABILITY_10BASE_T) {
		afep->afe_ifspeed = 10000000;
		afep->afe_duplex = LINK_DUPLEX_HALF;
	} else {
		afep->afe_ifspeed = 0;
		afep->afe_duplex = LINK_DUPLEX_UNKNOWN;
	}

	afe_reportlink(afep);
}

void
afe_miitristate(afe_t *afep)
{
	uint32_t val = SPR_SROM_WRITE | SPR_MII_CTRL;

	PUTCSR(afep, CSR_SPR, val);
	drv_usecwait(1);
	PUTCSR(afep, CSR_SPR, val | SPR_MII_CLOCK);
	drv_usecwait(1);
}

void
afe_miiwritebit(afe_t *afep, uint8_t bit)
{
	uint32_t val = bit ? SPR_MII_DOUT : 0;

	PUTCSR(afep, CSR_SPR, val);
	drv_usecwait(1);
	PUTCSR(afep, CSR_SPR, val | SPR_MII_CLOCK);
	drv_usecwait(1);
}

uint8_t
afe_miireadbit(afe_t *afep)
{
	uint32_t	val = SPR_MII_CTRL | SPR_SROM_READ;
	uint8_t		bit;

	PUTCSR(afep, CSR_SPR, val);
	drv_usecwait(1);
	bit = (GETCSR(afep, CSR_SPR) & SPR_MII_DIN) ? 1 : 0;
	PUTCSR(afep, CSR_SPR, val | SPR_MII_CLOCK);
	drv_usecwait(1);
	return (bit);
}

uint16_t
afe_miiread(afe_t *afep, int phy, int reg)
{
	/*
	 * ADMtek bugs ignore address decode bits -- they only
	 * support PHY at 1.
	 */
	if (phy != 1) {
		return (0xffff);
	}
	switch (AFE_MODEL(afep)) {
	case MODEL_COMET:
		return (afe_miireadcomet(afep, phy, reg));
	case MODEL_CENTAUR:
		return (afe_miireadgeneral(afep, phy, reg));
	}
	return (0xffff);
}

uint16_t
afe_miireadgeneral(afe_t *afep, int phy, int reg)
{
	uint16_t	value = 0;
	int		i;

	/* send the 32 bit preamble */
	for (i = 0; i < 32; i++) {
		afe_miiwritebit(afep, 1);
	}

	/* send the start code - 01b */
	afe_miiwritebit(afep, 0);
	afe_miiwritebit(afep, 1);

	/* send the opcode for read, - 10b */
	afe_miiwritebit(afep, 1);
	afe_miiwritebit(afep, 0);

	/* next we send the 5 bit phy address */
	for (i = 0x10; i > 0; i >>= 1) {
		afe_miiwritebit(afep, (phy & i) ? 1 : 0);
	}

	/* the 5 bit register address goes next */
	for (i = 0x10; i > 0; i >>= 1) {
		afe_miiwritebit(afep, (reg & i) ? 1 : 0);
	}

	/* turnaround - tristate followed by logic 0 */
	afe_miitristate(afep);
	afe_miiwritebit(afep, 0);

	/* read the 16 bit register value */
	for (i = 0x8000; i > 0; i >>= 1) {
		value <<= 1;
		value |= afe_miireadbit(afep);
	}
	afe_miitristate(afep);
	return (value);
}

uint16_t
afe_miireadcomet(afe_t *afep, int phy, int reg)
{
	if (phy != 1) {
		return (0xffff);
	}
	switch (reg) {
	case MII_CONTROL:
		reg = CSR_BMCR;
		break;
	case MII_STATUS:
		reg = CSR_BMSR;
		break;
	case MII_PHYIDH:
		reg = CSR_PHYIDR1;
		break;
	case MII_PHYIDL:
		reg = CSR_PHYIDR2;
		break;
	case MII_AN_ADVERT:
		reg = CSR_ANAR;
		break;
	case MII_AN_LPABLE:
		reg = CSR_ANLPAR;
		break;
	case MII_AN_EXPANSION:
		reg = CSR_ANER;
		break;
	default:
		return (0);
	}
	return (GETCSR16(afep, reg) & 0xFFFF);
}

void
afe_miiwrite(afe_t *afep, int phy, int reg, uint16_t val)
{
	/*
	 * ADMtek bugs ignore address decode bits -- they only
	 * support PHY at 1.
	 */
	if (phy != 1) {
		return;
	}
	switch (AFE_MODEL(afep)) {
	case MODEL_COMET:
		afe_miiwritecomet(afep, phy, reg, val);
		break;
	case MODEL_CENTAUR:
		afe_miiwritegeneral(afep, phy, reg, val);
		break;
	}
}

void
afe_miiwritegeneral(afe_t *afep, int phy, int reg, uint16_t val)
{
	int i;

	/* send the 32 bit preamble */
	for (i = 0; i < 32; i++) {
		afe_miiwritebit(afep, 1);
	}

	/* send the start code - 01b */
	afe_miiwritebit(afep, 0);
	afe_miiwritebit(afep, 1);

	/* send the opcode for write, - 01b */
	afe_miiwritebit(afep, 0);
	afe_miiwritebit(afep, 1);

	/* next we send the 5 bit phy address */
	for (i = 0x10; i > 0; i >>= 1) {
		afe_miiwritebit(afep, (phy & i) ? 1 : 0);
	}

	/* the 5 bit register address goes next */
	for (i = 0x10; i > 0; i >>= 1) {
		afe_miiwritebit(afep, (reg & i) ? 1 : 0);
	}

	/* turnaround - tristate followed by logic 0 */
	afe_miitristate(afep);
	afe_miiwritebit(afep, 0);

	/* now write out our data (16 bits) */
	for (i = 0x8000; i > 0; i >>= 1) {
		afe_miiwritebit(afep, (val & i) ? 1 : 0);
	}

	/* idle mode */
	afe_miitristate(afep);
}

void
afe_miiwritecomet(afe_t *afep, int phy, int reg, uint16_t val)
{
	if (phy != 1) {
		return;
	}
	switch (reg) {
	case MII_CONTROL:
		reg = CSR_BMCR;
		break;
	case MII_STATUS:
		reg = CSR_BMSR;
		break;
	case MII_PHYIDH:
		reg = CSR_PHYIDR1;
		break;
	case MII_PHYIDL:
		reg = CSR_PHYIDR2;
		break;
	case MII_AN_ADVERT:
		reg = CSR_ANAR;
		break;
	case MII_AN_LPABLE:
		reg = CSR_ANLPAR;
		break;
	case MII_AN_EXPANSION:
		reg = CSR_ANER;
		break;
	default:
		return;
	}
	PUTCSR16(afep, reg, val);
}

int
afe_m_start(void *arg)
{
	afe_t	*afep = arg;

	/* grab exclusive access to the card */
	mutex_enter(&afep->afe_intrlock);
	mutex_enter(&afep->afe_xmtlock);

	afe_startall(afep);
	afep->afe_flags |= AFE_RUNNING;

	mutex_exit(&afep->afe_xmtlock);
	mutex_exit(&afep->afe_intrlock);
	return (0);
}

void
afe_m_stop(void *arg)
{
	afe_t	*afep = arg;

	/* exclusive access to the hardware! */
	mutex_enter(&afep->afe_intrlock);
	mutex_enter(&afep->afe_xmtlock);

	afe_stopall(afep);
	afep->afe_flags &= ~AFE_RUNNING;

	mutex_exit(&afep->afe_xmtlock);
	mutex_exit(&afep->afe_intrlock);
}

void
afe_startmac(afe_t *afep)
{
	/* verify exclusive access to the card */
	ASSERT(mutex_owned(&afep->afe_intrlock));
	ASSERT(mutex_owned(&afep->afe_xmtlock));

	/* start the card */
	SETBIT(afep, CSR_NAR, NAR_TX_ENABLE | NAR_RX_ENABLE);

	if (afep->afe_txavail != AFE_TXRING)
		PUTCSR(afep, CSR_TDR, 0);

	/* tell the mac that we are ready to go! */
	if (afep->afe_flags & AFE_RUNNING)
		mac_tx_update(afep->afe_mh);
}

void
afe_stopmac(afe_t *afep)
{
	int		i;

	/* exclusive access to the hardware! */
	ASSERT(mutex_owned(&afep->afe_intrlock));
	ASSERT(mutex_owned(&afep->afe_xmtlock));

	CLRBIT(afep, CSR_NAR, NAR_TX_ENABLE | NAR_RX_ENABLE);

	/*
	 * A 1518 byte frame at 10Mbps takes about 1.2 msec to drain.
	 * We just add up to the nearest msec (2), which should be
	 * plenty to complete.
	 *
	 * Note that some chips never seem to indicate the transition to
	 * the stopped state properly.  Experience shows that we can safely
	 * proceed anyway, after waiting the requisite timeout.
	 */
	for (i = 2000; i != 0; i -= 10) {
		if ((GETCSR(afep, CSR_SR) & (SR_TX_STATE | SR_RX_STATE)) == 0)
			break;
		drv_usecwait(10);
	}

	/* prevent an interrupt */
	PUTCSR(afep, CSR_SR2, INT_RXSTOPPED | INT_TXSTOPPED);
}

void
afe_resetrings(afe_t *afep)
{
	int	i;

	/* now we need to reset the pointers... */
	PUTCSR(afep, CSR_RDB, 0);
	PUTCSR(afep, CSR_TDB, 0);

	/* reset the descriptor ring pointers */
	afep->afe_rxhead = 0;
	afep->afe_txreclaim = 0;
	afep->afe_txsend = 0;
	afep->afe_txavail = AFE_TXRING;

	/* set up transmit descriptor ring */
	for (i = 0; i < AFE_TXRING; i++) {
		afe_desc_t	*tmdp = &afep->afe_txdescp[i];
		unsigned	control = 0;
		if (i == (AFE_TXRING - 1)) {
			control |= TXCTL_ENDRING;
		}
		PUTTXDESC(afep, tmdp->desc_status, 0);
		PUTTXDESC(afep, tmdp->desc_control, control);
		PUTTXDESC(afep, tmdp->desc_buffer1, 0);
		PUTTXDESC(afep, tmdp->desc_buffer2, 0);
		SYNCTXDESC(afep, i, DDI_DMA_SYNC_FORDEV);
	}
	PUTCSR(afep, CSR_TDB, afep->afe_txdesc_paddr);

	/* make the receive buffers available */
	for (i = 0; i < AFE_RXRING; i++) {
		afe_rxbuf_t	*rxb = afep->afe_rxbufs[i];
		afe_desc_t	*rmdp = &afep->afe_rxdescp[i];
		unsigned	control;

		control = AFE_BUFSZ & RXCTL_BUFLEN1;
		if (i == (AFE_RXRING - 1)) {
			control |= RXCTL_ENDRING;
		}
		PUTRXDESC(afep, rmdp->desc_buffer1, rxb->rxb_paddr);
		PUTRXDESC(afep, rmdp->desc_buffer2, 0);
		PUTRXDESC(afep, rmdp->desc_control, control);
		PUTRXDESC(afep, rmdp->desc_status, RXSTAT_OWN);
		SYNCRXDESC(afep, i, DDI_DMA_SYNC_FORDEV);
	}
	PUTCSR(afep, CSR_RDB, afep->afe_rxdesc_paddr);
}

void
afe_stopall(afe_t *afep)
{
	afe_disableinterrupts(afep);

	afe_stopmac(afep);

	/* stop the phy */
	afe_stopphy(afep);
}

void
afe_startall(afe_t *afep)
{
	ASSERT(mutex_owned(&afep->afe_intrlock));
	ASSERT(mutex_owned(&afep->afe_xmtlock));

	/* make sure interrupts are disabled to begin */
	afe_disableinterrupts(afep);

	/* initialize the chip */
	(void) afe_initialize(afep);

	/* now we can enable interrupts */
	afe_enableinterrupts(afep);

	/* start up the phy */
	afe_startphy(afep);

	/* start up the mac */
	afe_startmac(afep);
}

void
afe_resetall(afe_t *afep)
{
	afep->afe_resetting = B_TRUE;
	afe_stopall(afep);
	afep->afe_resetting = B_FALSE;
	afe_startall(afep);
}

afe_txbuf_t *
afe_alloctxbuf(afe_t *afep)
{
	ddi_dma_cookie_t	dmac;
	unsigned		ncookies;
	afe_txbuf_t		*txb;
	size_t			len;

	txb = kmem_zalloc(sizeof (*txb), KM_SLEEP);

	if (ddi_dma_alloc_handle(afep->afe_dip, &afe_dma_txattr,
	    DDI_DMA_SLEEP, NULL, &txb->txb_dmah) != DDI_SUCCESS) {
		return (NULL);
	}

	if (ddi_dma_mem_alloc(txb->txb_dmah, AFE_BUFSZ, &afe_bufattr,
	    DDI_DMA_STREAMING, DDI_DMA_SLEEP, NULL, &txb->txb_buf, &len,
	    &txb->txb_acch) != DDI_SUCCESS) {
		return (NULL);
	}
	if (ddi_dma_addr_bind_handle(txb->txb_dmah, NULL, txb->txb_buf,
	    len, DDI_DMA_WRITE | DDI_DMA_STREAMING, DDI_DMA_SLEEP, NULL,
	    &dmac, &ncookies) != DDI_DMA_MAPPED) {
		return (NULL);
	}
	txb->txb_paddr = dmac.dmac_address;

	return (txb);
}

void
afe_destroytxbuf(afe_txbuf_t *txb)
{
	if (txb != NULL) {
		if (txb->txb_paddr)
			(void) ddi_dma_unbind_handle(txb->txb_dmah);
		if (txb->txb_acch)
			ddi_dma_mem_free(&txb->txb_acch);
		if (txb->txb_dmah)
			ddi_dma_free_handle(&txb->txb_dmah);
		kmem_free(txb, sizeof (*txb));
	}
}

afe_rxbuf_t *
afe_allocrxbuf(afe_t *afep)
{
	afe_rxbuf_t		*rxb;
	size_t			len;
	unsigned		ccnt;
	ddi_dma_cookie_t	dmac;

	rxb = kmem_zalloc(sizeof (*rxb), KM_SLEEP);

	if (ddi_dma_alloc_handle(afep->afe_dip, &afe_dma_attr,
	    DDI_DMA_SLEEP, NULL, &rxb->rxb_dmah) != DDI_SUCCESS) {
		kmem_free(rxb, sizeof (*rxb));
		return (NULL);
	}
	if (ddi_dma_mem_alloc(rxb->rxb_dmah, AFE_BUFSZ, &afe_bufattr,
	    DDI_DMA_STREAMING, DDI_DMA_SLEEP, NULL, &rxb->rxb_buf, &len,
	    &rxb->rxb_acch) != DDI_SUCCESS) {
		ddi_dma_free_handle(&rxb->rxb_dmah);
		kmem_free(rxb, sizeof (*rxb));
		return (NULL);
	}
	if (ddi_dma_addr_bind_handle(rxb->rxb_dmah, NULL, rxb->rxb_buf, len,
	    DDI_DMA_READ | DDI_DMA_STREAMING, DDI_DMA_SLEEP, NULL, &dmac,
	    &ccnt) != DDI_DMA_MAPPED) {
		ddi_dma_mem_free(&rxb->rxb_acch);
		ddi_dma_free_handle(&rxb->rxb_dmah);
		kmem_free(rxb, sizeof (*rxb));
		return (NULL);
	}
	rxb->rxb_paddr = dmac.dmac_address;

	return (rxb);
}

void
afe_destroyrxbuf(afe_rxbuf_t *rxb)
{
	if (rxb) {
		(void) ddi_dma_unbind_handle(rxb->rxb_dmah);
		ddi_dma_mem_free(&rxb->rxb_acch);
		ddi_dma_free_handle(&rxb->rxb_dmah);
		kmem_free(rxb, sizeof (*rxb));
	}
}

/*
 * Allocate receive resources.
 */
int
afe_allocrxring(afe_t *afep)
{
	int			rval;
	int			i;
	size_t			size;
	size_t			len;
	ddi_dma_cookie_t	dmac;
	unsigned		ncookies;
	caddr_t			kaddr;

	size = AFE_RXRING * sizeof (afe_desc_t);

	rval = ddi_dma_alloc_handle(afep->afe_dip, &afe_dma_attr,
	    DDI_DMA_SLEEP, NULL, &afep->afe_rxdesc_dmah);
	if (rval != DDI_SUCCESS) {
		afe_error(afep->afe_dip,
		    "unable to allocate DMA handle for rx descriptors");
		return (DDI_FAILURE);
	}

	rval = ddi_dma_mem_alloc(afep->afe_rxdesc_dmah, size, &afe_devattr,
	    DDI_DMA_CONSISTENT, DDI_DMA_SLEEP, NULL, &kaddr, &len,
	    &afep->afe_rxdesc_acch);
	if (rval != DDI_SUCCESS) {
		afe_error(afep->afe_dip,
		    "unable to allocate DMA memory for rx descriptors");
		return (DDI_FAILURE);
	}

	rval = ddi_dma_addr_bind_handle(afep->afe_rxdesc_dmah, NULL, kaddr,
	    size, DDI_DMA_RDWR | DDI_DMA_CONSISTENT, DDI_DMA_SLEEP, NULL,
	    &dmac, &ncookies);
	if (rval != DDI_DMA_MAPPED) {
		afe_error(afep->afe_dip,
		    "unable to bind DMA for rx descriptors");
		return (DDI_FAILURE);
	}

	/* because of afe_dma_attr */
	ASSERT(ncookies == 1);

	/* we take the 32-bit physical address out of the cookie */
	afep->afe_rxdesc_paddr = dmac.dmac_address;
	afep->afe_rxdescp = (void *)kaddr;

	/* allocate buffer pointers (not the buffers themselves, yet) */
	afep->afe_rxbufs = kmem_zalloc(AFE_RXRING * sizeof (afe_rxbuf_t *),
	    KM_SLEEP);

	/* now allocate rx buffers */
	for (i = 0; i < AFE_RXRING; i++) {
		afe_rxbuf_t *rxb = afe_allocrxbuf(afep);
		if (rxb == NULL)
			return (DDI_FAILURE);
		afep->afe_rxbufs[i] = rxb;
	}

	return (DDI_SUCCESS);
}

/*
 * Allocate transmit resources.
 */
int
afe_alloctxring(afe_t *afep)
{
	int			rval;
	int			i;
	size_t			size;
	size_t			len;
	ddi_dma_cookie_t	dmac;
	unsigned		ncookies;
	caddr_t			kaddr;

	size = AFE_TXRING * sizeof (afe_desc_t);

	rval = ddi_dma_alloc_handle(afep->afe_dip, &afe_dma_attr,
	    DDI_DMA_SLEEP, NULL, &afep->afe_txdesc_dmah);
	if (rval != DDI_SUCCESS) {
		afe_error(afep->afe_dip,
		    "unable to allocate DMA handle for tx descriptors");
		return (DDI_FAILURE);
	}

	rval = ddi_dma_mem_alloc(afep->afe_txdesc_dmah, size, &afe_devattr,
	    DDI_DMA_CONSISTENT, DDI_DMA_SLEEP, NULL, &kaddr, &len,
	    &afep->afe_txdesc_acch);
	if (rval != DDI_SUCCESS) {
		afe_error(afep->afe_dip,
		    "unable to allocate DMA memory for tx descriptors");
		return (DDI_FAILURE);
	}

	rval = ddi_dma_addr_bind_handle(afep->afe_txdesc_dmah, NULL, kaddr,
	    size, DDI_DMA_RDWR | DDI_DMA_CONSISTENT, DDI_DMA_SLEEP, NULL,
	    &dmac, &ncookies);
	if (rval != DDI_DMA_MAPPED) {
		afe_error(afep->afe_dip,
		    "unable to bind DMA for tx descriptors");
		return (DDI_FAILURE);
	}

	/* because of afe_dma_attr */
	ASSERT(ncookies == 1);

	/* we take the 32-bit physical address out of the cookie */
	afep->afe_txdesc_paddr = dmac.dmac_address;
	afep->afe_txdescp = (void *)kaddr;

	/* allocate buffer pointers (not the buffers themselves, yet) */
	afep->afe_txbufs = kmem_zalloc(AFE_TXRING * sizeof (afe_txbuf_t *),
	    KM_SLEEP);

	/* now allocate tx buffers */
	for (i = 0; i < AFE_TXRING; i++) {
		afe_txbuf_t *txb = afe_alloctxbuf(afep);
		if (txb == NULL)
			return (DDI_FAILURE);
		afep->afe_txbufs[i] = txb;
	}

	return (DDI_SUCCESS);
}

void
afe_freerxring(afe_t *afep)
{
	int		i;

	for (i = 0; i < AFE_RXRING; i++) {
		afe_destroyrxbuf(afep->afe_rxbufs[i]);
	}

	if (afep->afe_rxbufs) {
		kmem_free(afep->afe_rxbufs,
		    AFE_RXRING * sizeof (afe_rxbuf_t *));
	}

	if (afep->afe_rxdesc_paddr)
		(void) ddi_dma_unbind_handle(afep->afe_rxdesc_dmah);
	if (afep->afe_rxdesc_acch)
		ddi_dma_mem_free(&afep->afe_rxdesc_acch);
	if (afep->afe_rxdesc_dmah)
		ddi_dma_free_handle(&afep->afe_rxdesc_dmah);
}

void
afe_freetxring(afe_t *afep)
{
	int			i;

	for (i = 0; i < AFE_TXRING; i++) {
		afe_destroytxbuf(afep->afe_txbufs[i]);
	}

	if (afep->afe_txbufs) {
		kmem_free(afep->afe_txbufs,
		    AFE_TXRING * sizeof (afe_txbuf_t *));
	}
	if (afep->afe_txdesc_paddr)
		(void) ddi_dma_unbind_handle(afep->afe_txdesc_dmah);
	if (afep->afe_txdesc_acch)
		ddi_dma_mem_free(&afep->afe_txdesc_acch);
	if (afep->afe_txdesc_dmah)
		ddi_dma_free_handle(&afep->afe_txdesc_dmah);
}

/*
 * Interrupt service routine.
 */
unsigned
afe_intr(caddr_t arg)
{
	afe_t		*afep = (void *)arg;
	uint32_t	status;
	mblk_t		*mp = NULL;

	mutex_enter(&afep->afe_intrlock);

	if (afep->afe_flags & AFE_SUSPENDED) {
		/* we cannot receive interrupts! */
		mutex_exit(&afep->afe_intrlock);
		return (DDI_INTR_UNCLAIMED);
	}

	/* check interrupt status bits, did we interrupt? */
	status = GETCSR(afep, CSR_SR2) & INT_ALL;

	if (status == 0) {
		KIOIP->intrs[KSTAT_INTR_SPURIOUS]++;
		mutex_exit(&afep->afe_intrlock);
		return (DDI_INTR_UNCLAIMED);
	}
	/* ack the interrupt */
	PUTCSR(afep, CSR_SR2, status);
	KIOIP->intrs[KSTAT_INTR_HARD]++;

	if (!(afep->afe_flags & AFE_RUNNING)) {
		/* not running, don't touch anything */
		mutex_exit(&afep->afe_intrlock);
		return (DDI_INTR_CLAIMED);
	}

	if (status & (INT_RXOK|INT_RXNOBUF)) {
		/* receive packets */
		mp = afe_receive(afep);
		if (status & INT_RXNOBUF)
			PUTCSR(afep, CSR_RDR, 0);	/* wake up chip */
	}

	if (status & INT_TXOK) {
		/* transmit completed */
		mutex_enter(&afep->afe_xmtlock);
		afe_reclaim(afep);
		mutex_exit(&afep->afe_xmtlock);
	}

	if (status & (INT_LINKCHG|INT_TIMER)) {
		mutex_enter(&afep->afe_xmtlock);
		afe_checklink(afep);
		mutex_exit(&afep->afe_xmtlock);
	}

	if (status & (INT_RXSTOPPED|INT_TXSTOPPED|
	    INT_RXJABBER|INT_TXJABBER|INT_TXUNDERFLOW)) {

		if (status & (INT_RXJABBER | INT_TXJABBER)) {
			afep->afe_jabber++;
		}
		DBG(DWARN, "resetting mac, status %x", status);
		mutex_enter(&afep->afe_xmtlock);
		afe_resetall(afep);
		mutex_exit(&afep->afe_xmtlock);
	}

	if (status & INT_BUSERR) {
		switch (GETCSR(afep, CSR_SR) & SR_BERR_TYPE) {
		case SR_BERR_PARITY:
			afe_error(afep->afe_dip, "PCI parity error");
			break;
		case SR_BERR_TARGET_ABORT:
			afe_error(afep->afe_dip, "PCI target abort");
			break;
		case SR_BERR_MASTER_ABORT:
			afe_error(afep->afe_dip, "PCI master abort");
			break;
		default:
			afe_error(afep->afe_dip, "Unknown PCI error");
			break;
		}

		/* reset the chip in an attempt to fix things */
		mutex_enter(&afep->afe_xmtlock);
		afe_resetall(afep);
		mutex_exit(&afep->afe_xmtlock);
	}

	mutex_exit(&afep->afe_intrlock);

	/*
	 * Send up packets.  We do this outside of the intrlock.
	 */
	if (mp) {
		mac_rx(afep->afe_mh, NULL, mp);
	}

	return (DDI_INTR_CLAIMED);
}

void
afe_enableinterrupts(afe_t *afep)
{
	unsigned mask = INT_WANTED;

	if (afep->afe_wantw)
		mask |= INT_TXOK;

	PUTCSR(afep, CSR_IER2, mask);

	if (AFE_MODEL(afep) == MODEL_COMET) {
		/*
		 * On the Comet, this is the internal transceiver
		 * interrupt.  We program the Comet's built-in PHY to
		 * enable certain interrupts.
		 */
		PUTCSR16(afep, CSR_XIE, XIE_LDE | XIE_ANCE);
	}
}

void
afe_disableinterrupts(afe_t *afep)
{
	/* disable further interrupts */
	PUTCSR(afep, CSR_IER2, INT_NONE);

	/* clear any pending interrupts */
	PUTCSR(afep, CSR_SR2, INT_ALL);
}

boolean_t
afe_send(afe_t *afep, mblk_t *mp)
{
	size_t			len;
	afe_txbuf_t		*txb;
	afe_desc_t		*tmd;
	uint32_t		control;
	int			txsend;

	ASSERT(mutex_owned(&afep->afe_xmtlock));
	ASSERT(mp != NULL);

	len = msgsize(mp);
	if (len > ETHERVLANMTU) {
		DBG(DXMIT, "frame too long: %d", len);
		afep->afe_macxmt_errors++;
		freemsg(mp);
		return (B_TRUE);
	}

	if (afep->afe_txavail < AFE_TXRECLAIM)
		afe_reclaim(afep);

	if (afep->afe_txavail == 0) {
		/* no more tmds */
		afep->afe_wantw = B_TRUE;
		/* enable TX interrupt */
		afe_enableinterrupts(afep);
		return (B_FALSE);
	}

	txsend = afep->afe_txsend;

	/*
	 * For simplicity, we just do a copy into a preallocated
	 * DMA buffer.
	 */

	txb = afep->afe_txbufs[txsend];
	mcopymsg(mp, txb->txb_buf);	/* frees mp! */

	/*
	 * Statistics.
	 */
	afep->afe_opackets++;
	afep->afe_obytes += len;
	if (txb->txb_buf[0] & 0x1) {
		if (bcmp(txb->txb_buf, afe_broadcast, ETHERADDRL) != 0)
			afep->afe_multixmt++;
		else
			afep->afe_brdcstxmt++;
	}

	/* note len is already known to be a small unsigned */
	control = len | TXCTL_FIRST | TXCTL_LAST | TXCTL_INTCMPLTE;

	if (txsend == (AFE_TXRING - 1))
		control |= TXCTL_ENDRING;

	tmd = &afep->afe_txdescp[txsend];

	SYNCTXBUF(txb, len, DDI_DMA_SYNC_FORDEV);
	PUTTXDESC(afep, tmd->desc_control, control);
	PUTTXDESC(afep, tmd->desc_buffer1, txb->txb_paddr);
	PUTTXDESC(afep, tmd->desc_buffer2, 0);
	PUTTXDESC(afep, tmd->desc_status, TXSTAT_OWN);
	/* sync the descriptor out to the device */
	SYNCTXDESC(afep, txsend, DDI_DMA_SYNC_FORDEV);

	/*
	 * Note the new values of txavail and txsend.
	 */
	afep->afe_txavail--;
	afep->afe_txsend = (txsend + 1) % AFE_TXRING;

	/*
	 * It should never, ever take more than 5 seconds to drain
	 * the ring.  If it happens, then we are stuck!
	 */
	afep->afe_txstall_time = gethrtime() + (5 * 1000000000ULL);

	/*
	 * wake up the chip ... inside the lock to protect against DR suspend,
	 * etc.
	 */
	PUTCSR(afep, CSR_TDR, 0);

	return (B_TRUE);
}

/*
 * Reclaim buffers that have completed transmission.
 */
void
afe_reclaim(afe_t *afep)
{
	afe_desc_t	*tmdp;

	while (afep->afe_txavail != AFE_TXRING) {
		uint32_t	status;
		uint32_t	control;
		int		index = afep->afe_txreclaim;

		tmdp = &afep->afe_txdescp[index];

		/* sync it before we read it */
		SYNCTXDESC(afep, index, DDI_DMA_SYNC_FORKERNEL);

		control = GETTXDESC(afep, tmdp->desc_control);
		status = GETTXDESC(afep, tmdp->desc_status);

		if (status & TXSTAT_OWN) {
			/* chip is still working on it, we're done */
			break;
		}

		afep->afe_txavail++;
		afep->afe_txreclaim = (index + 1) % AFE_TXRING;

		/* in the most common successful case, all bits are clear */
		if (status == 0)
			continue;

		if ((control & TXCTL_LAST) == 0)
			continue;

		if (status & TXSTAT_TXERR) {
			afep->afe_errxmt++;

			if (status & TXSTAT_JABBER) {
				/* transmit jabber timeout */
				afep->afe_macxmt_errors++;
			}
			if (status &
			    (TXSTAT_CARRLOST | TXSTAT_NOCARR)) {
				afep->afe_carrier_errors++;
			}
			if (status & TXSTAT_UFLOW) {
				afep->afe_underflow++;
			}
			if (status & TXSTAT_LATECOL) {
				afep->afe_tx_late_collisions++;
			}
			if (status & TXSTAT_EXCOLL) {
				afep->afe_ex_collisions++;
				afep->afe_collisions += 16;
			}
		}

		if (status & TXSTAT_DEFER) {
			afep->afe_defer_xmts++;
		}

		/* collision counting */
		if (TXCOLLCNT(status) == 1) {
			afep->afe_collisions++;
			afep->afe_first_collisions++;
		} else if (TXCOLLCNT(status)) {
			afep->afe_collisions += TXCOLLCNT(status);
			afep->afe_multi_collisions += TXCOLLCNT(status);
		}
	}

	if (afep->afe_txavail >= AFE_TXRESCHED) {
		if (afep->afe_wantw) {
			/*
			 * we were able to reclaim some packets, so
			 * disable tx interrupts
			 */
			afep->afe_wantw = B_FALSE;
			afe_enableinterrupts(afep);
			mac_tx_update(afep->afe_mh);
		}
	}
}

mblk_t *
afe_receive(afe_t *afep)
{
	unsigned		len;
	afe_rxbuf_t		*rxb;
	afe_desc_t		*rmd;
	uint32_t		status;
	mblk_t			*mpchain, **mpp, *mp;
	int			head, cnt;

	mpchain = NULL;
	mpp = &mpchain;
	head = afep->afe_rxhead;

	/* limit the number of packets we process to a half ring size */
	for (cnt = 0; cnt < AFE_RXRING / 2; cnt++) {

		DBG(DRECV, "receive at index %d", head);

		rmd = &afep->afe_rxdescp[head];
		rxb = afep->afe_rxbufs[head];

		SYNCRXDESC(afep, head, DDI_DMA_SYNC_FORKERNEL);
		status = GETRXDESC(afep, rmd->desc_status);
		if (status & RXSTAT_OWN) {
			/* chip is still chewing on it */
			break;
		}

		/* discard the ethernet frame checksum */
		len = RXLENGTH(status) - ETHERFCSL;

		DBG(DRECV, "recv length %d, status %x", len, status);

		if ((status & (RXSTAT_ERRS | RXSTAT_FIRST | RXSTAT_LAST)) !=
		    (RXSTAT_FIRST | RXSTAT_LAST)) {

			afep->afe_errrcv++;

			/*
			 * Abnormal status bits detected, analyze further.
			 */
			if ((status & (RXSTAT_LAST|RXSTAT_FIRST)) !=
			    (RXSTAT_LAST|RXSTAT_FIRST)) {
				DBG(DRECV, "rx packet overspill");
				if (status & RXSTAT_FIRST) {
					afep->afe_toolong_errors++;
				}
			} else if (status & RXSTAT_DESCERR) {
				afep->afe_macrcv_errors++;

			} else if (status & RXSTAT_RUNT) {
				afep->afe_runt++;

			} else if (status & RXSTAT_COLLSEEN) {
				/* this should really be rx_late_collisions */
				afep->afe_macrcv_errors++;

			} else if (status & RXSTAT_DRIBBLE) {
				afep->afe_align_errors++;

			} else if (status & RXSTAT_CRCERR) {
				afep->afe_fcs_errors++;

			} else if (status & RXSTAT_OFLOW) {
				afep->afe_overflow++;
			}
		}

		else if (len > ETHERVLANMTU) {
			afep->afe_errrcv++;
			afep->afe_toolong_errors++;
		}

		/*
		 * At this point, the chip thinks the packet is OK.
		 */
		else {
			mp = allocb(len + AFE_HEADROOM, 0);
			if (mp == NULL) {
				afep->afe_errrcv++;
				afep->afe_norcvbuf++;
				goto skip;
			}

			/* sync the buffer before we look at it */
			SYNCRXBUF(rxb, len, DDI_DMA_SYNC_FORKERNEL);
			mp->b_rptr += AFE_HEADROOM;
			mp->b_wptr = mp->b_rptr + len;
			bcopy((char *)rxb->rxb_buf, mp->b_rptr, len);

			afep->afe_ipackets++;
			afep->afe_rbytes += len;
			if (status & RXSTAT_GROUP) {
				if (bcmp(mp->b_rptr, afe_broadcast,
				    ETHERADDRL) == 0)
					afep->afe_brdcstrcv++;
				else
					afep->afe_multircv++;
			}
			*mpp = mp;
			mpp = &mp->b_next;
		}

skip:
		/* return ring entry to the hardware */
		PUTRXDESC(afep, rmd->desc_status, RXSTAT_OWN);
		SYNCRXDESC(afep, head, DDI_DMA_SYNC_FORDEV);

		/* advance to next RMD */
		head = (head + 1) % AFE_RXRING;
	}

	afep->afe_rxhead = head;

	return (mpchain);
}

int
afe_getmiibit(afe_t *afep, uint16_t reg, uint16_t bit)
{
	unsigned	val;

	mutex_enter(&afep->afe_xmtlock);
	if (afep->afe_flags & AFE_SUSPENDED) {
		mutex_exit(&afep->afe_xmtlock);
		/* device is suspended */
		return (0);
	}
	val = afe_miiread(afep, afep->afe_phyaddr, reg);
	mutex_exit(&afep->afe_xmtlock);

	return (val & bit ? 1 : 0);
}
#define	GETMIIBIT(reg, bit) afe_getmiibit(afep, reg, bit)

int
afe_m_stat(void *arg, uint_t stat, uint64_t *val)
{
	afe_t	*afep = arg;

	mutex_enter(&afep->afe_xmtlock);
	if ((afep->afe_flags & (AFE_RUNNING|AFE_SUSPENDED)) == AFE_RUNNING)
		afe_reclaim(afep);
	mutex_exit(&afep->afe_xmtlock);

	switch (stat) {
	case MAC_STAT_IFSPEED:
		*val = afep->afe_ifspeed;
		break;

	case MAC_STAT_MULTIRCV:
		*val = afep->afe_multircv;
		break;

	case MAC_STAT_BRDCSTRCV:
		*val = afep->afe_brdcstrcv;
		break;

	case MAC_STAT_MULTIXMT:
		*val = afep->afe_multixmt;
		break;

	case MAC_STAT_BRDCSTXMT:
		*val = afep->afe_brdcstxmt;
		break;

	case MAC_STAT_IPACKETS:
		*val = afep->afe_ipackets;
		break;

	case MAC_STAT_RBYTES:
		*val = afep->afe_rbytes;
		break;

	case MAC_STAT_OPACKETS:
		*val = afep->afe_opackets;
		break;

	case MAC_STAT_OBYTES:
		*val = afep->afe_obytes;
		break;

	case MAC_STAT_NORCVBUF:
		*val = afep->afe_norcvbuf;
		break;

	case MAC_STAT_NOXMTBUF:
		*val = 0;
		break;

	case MAC_STAT_COLLISIONS:
		*val = afep->afe_collisions;
		break;

	case MAC_STAT_IERRORS:
		*val = afep->afe_errrcv;
		break;

	case MAC_STAT_OERRORS:
		*val = afep->afe_errxmt;
		break;

	case ETHER_STAT_LINK_DUPLEX:
		*val = afep->afe_duplex;
		break;

	case ETHER_STAT_ALIGN_ERRORS:
		*val = afep->afe_align_errors;
		break;

	case ETHER_STAT_FCS_ERRORS:
		*val = afep->afe_fcs_errors;
		break;

	case ETHER_STAT_SQE_ERRORS:
		*val = afep->afe_sqe_errors;
		break;

	case ETHER_STAT_DEFER_XMTS:
		*val = afep->afe_defer_xmts;
		break;

	case ETHER_STAT_FIRST_COLLISIONS:
		*val = afep->afe_first_collisions;
		break;

	case ETHER_STAT_MULTI_COLLISIONS:
		*val = afep->afe_multi_collisions;
		break;

	case ETHER_STAT_TX_LATE_COLLISIONS:
		*val = afep->afe_tx_late_collisions;
		break;

	case ETHER_STAT_EX_COLLISIONS:
		*val = afep->afe_ex_collisions;
		break;

	case ETHER_STAT_MACXMT_ERRORS:
		*val = afep->afe_macxmt_errors;
		break;

	case ETHER_STAT_CARRIER_ERRORS:
		*val = afep->afe_carrier_errors;
		break;

	case ETHER_STAT_TOOLONG_ERRORS:
		*val = afep->afe_toolong_errors;
		break;

	case ETHER_STAT_MACRCV_ERRORS:
		*val = afep->afe_macrcv_errors;
		break;

	case MAC_STAT_OVERFLOWS:
		*val = afep->afe_overflow;
		break;

	case MAC_STAT_UNDERFLOWS:
		*val = afep->afe_underflow;
		break;

	case ETHER_STAT_TOOSHORT_ERRORS:
		*val = afep->afe_runt;
		break;

	case ETHER_STAT_JABBER_ERRORS:
		*val = afep->afe_jabber;
		break;

	case ETHER_STAT_CAP_100T4:
		*val = afep->afe_cap_100T4;
		break;

	case ETHER_STAT_CAP_100FDX:
		*val = afep->afe_cap_100fdx;
		break;

	case ETHER_STAT_CAP_100HDX:
		*val = afep->afe_cap_100hdx;
		break;

	case ETHER_STAT_CAP_10FDX:
		*val = afep->afe_cap_10fdx;
		break;

	case ETHER_STAT_CAP_10HDX:
		*val = afep->afe_cap_10hdx;
		break;

	case ETHER_STAT_CAP_AUTONEG:
		*val = afep->afe_cap_aneg;
		break;

	case ETHER_STAT_LINK_AUTONEG:
		*val = ((afep->afe_adv_aneg != 0) &&
		    (GETMIIBIT(MII_AN_LPABLE, MII_AN_EXP_LPCANAN) != 0));
		break;

	case ETHER_STAT_ADV_CAP_100T4:
		*val = afep->afe_adv_100T4;
		break;

	case ETHER_STAT_ADV_CAP_100FDX:
		*val = afep->afe_adv_100fdx;
		break;

	case ETHER_STAT_ADV_CAP_100HDX:
		*val = afep->afe_adv_100hdx;
		break;

	case ETHER_STAT_ADV_CAP_10FDX:
		*val = afep->afe_adv_10fdx;
		break;

	case ETHER_STAT_ADV_CAP_10HDX:
		*val = afep->afe_adv_10hdx;
		break;

	case ETHER_STAT_ADV_CAP_AUTONEG:
		*val = afep->afe_adv_aneg;
		break;

	case ETHER_STAT_LP_CAP_100T4:
		*val = GETMIIBIT(MII_AN_LPABLE, MII_ABILITY_100BASE_T4);
		break;

	case ETHER_STAT_LP_CAP_100FDX:
		*val = GETMIIBIT(MII_AN_LPABLE, MII_ABILITY_100BASE_TX_FD);
		break;

	case ETHER_STAT_LP_CAP_100HDX:
		*val = GETMIIBIT(MII_AN_LPABLE, MII_ABILITY_100BASE_TX);
		break;

	case ETHER_STAT_LP_CAP_10FDX:
		*val = GETMIIBIT(MII_AN_LPABLE, MII_ABILITY_10BASE_T_FD);
		break;

	case ETHER_STAT_LP_CAP_10HDX:
		*val = GETMIIBIT(MII_AN_LPABLE, MII_ABILITY_10BASE_T);
		break;

	case ETHER_STAT_LP_CAP_AUTONEG:
		*val = GETMIIBIT(MII_AN_EXPANSION, MII_AN_EXP_LPCANAN);
		break;

	case ETHER_STAT_XCVR_ADDR:
		*val = afep->afe_phyaddr;
		break;

	case ETHER_STAT_XCVR_ID:
		*val = afep->afe_phyid;
		break;

	default:
		return (ENOTSUP);
	}
	return (0);
}

/*ARGSUSED*/
int
afe_m_getprop(void *arg, const char *name, mac_prop_id_t num, uint_t flags,
    uint_t sz, void *val)
{
	afe_t		*afep = arg;
	int		err = 0;
	boolean_t	dfl = flags & DLD_DEFAULT;

	if (sz == 0)
		return (EINVAL);

	switch (num) {
	case DLD_PROP_DUPLEX:
		if (sz >= sizeof (link_duplex_t)) {
			bcopy(&afep->afe_duplex, val, sizeof (link_duplex_t));
		} else {
			err = EINVAL;
		}
		break;

	case DLD_PROP_SPEED:
		if (sz >= sizeof (uint64_t)) {
			bcopy(&afep->afe_ifspeed, val, sizeof (uint64_t));
		} else {
			err = EINVAL;
		}
		break;

	case DLD_PROP_AUTONEG:
		*(uint8_t *)val =
		    dfl ? afep->afe_cap_aneg : afep->afe_adv_aneg;
		break;

#if 0
	case DLD_PROP_ADV_1000FDX_CAP:
	case DLD_PROP_EN_1000FDX_CAP:
	case DLD_PROP_ADV_1000HDX_CAP:
	case DLD_PROP_EN_1000HDX_CAP:
		/* We don't support gigabit! */
		*(uint8_t *)val = 0;
		break;
#endif

	case DLD_PROP_ADV_100FDX_CAP:
	case DLD_PROP_EN_100FDX_CAP:
		*(uint8_t *)val =
		    dfl ? afep->afe_cap_100fdx : afep->afe_adv_100fdx;
		break;

	case DLD_PROP_ADV_100HDX_CAP:
	case DLD_PROP_EN_100HDX_CAP:
		*(uint8_t *)val =
		    dfl ? afep->afe_cap_100hdx : afep->afe_adv_100hdx;
		break;

	case DLD_PROP_ADV_10FDX_CAP:
	case DLD_PROP_EN_10FDX_CAP:
		*(uint8_t *)val =
		    dfl ? afep->afe_cap_10fdx : afep->afe_adv_10fdx;
		break;

	case DLD_PROP_ADV_10HDX_CAP:
	case DLD_PROP_EN_10HDX_CAP:
		*(uint8_t *)val =
		    dfl ? afep->afe_cap_10hdx : afep->afe_adv_10hdx;
		break;

	case DLD_PROP_ADV_100T4_CAP:
	case DLD_PROP_EN_100T4_CAP:
		*(uint8_t *)val =
		    dfl ? afep->afe_cap_100T4 : afep->afe_adv_100T4;
		break;

	default:
		err = ENOTSUP;
	}

	return (err);
}

/*ARGSUSED*/
int
afe_m_setprop(void *arg, const char *name, mac_prop_id_t num, uint_t sz,
    const void *val)
{
	afe_t		*afep = arg;
	uint8_t		*advp;
	uint8_t		*capp;

	switch (num) {
	case DLD_PROP_EN_100FDX_CAP:
		advp = &afep->afe_adv_100fdx;
		capp = &afep->afe_cap_100fdx;
		break;

	case DLD_PROP_EN_100HDX_CAP:
		advp = &afep->afe_adv_100hdx;
		capp = &afep->afe_cap_100hdx;
		break;

	case DLD_PROP_EN_10FDX_CAP:
		advp = &afep->afe_adv_10fdx;
		capp = &afep->afe_cap_10fdx;
		break;

	case DLD_PROP_EN_10HDX_CAP:
		advp = &afep->afe_adv_10hdx;
		capp = &afep->afe_cap_10hdx;
		break;

	case DLD_PROP_EN_100T4_CAP:
		advp = &afep->afe_adv_100T4;
		capp = &afep->afe_cap_100T4;
		break;

	case DLD_PROP_AUTONEG:
		advp = &afep->afe_adv_aneg;
		capp = &afep->afe_cap_aneg;
		break;

	default:
		return (ENOTSUP);
	}

	if (*capp == 0)		/* ensure phy can support value */
		return (ENOTSUP);

	mutex_enter(&afep->afe_intrlock);
	mutex_enter(&afep->afe_xmtlock);

	if (*advp != *(const uint8_t *)val) {
		*advp = *(const uint8_t *)val;

		if ((afep->afe_flags & (AFE_RUNNING|AFE_SUSPENDED)) ==
		    AFE_RUNNING) {
			/*
			 * This re-initializes the phy, but it also
			 * restarts transmit and receive rings.
			 * Needless to say, changing the link
			 * parameters is destructive to traffic in
			 * progress.
			 */
			afe_resetall(afep);
		}
	}
	mutex_exit(&afep->afe_xmtlock);
	mutex_exit(&afep->afe_intrlock);

	return (0);
}

/*
 * Debugging and error reporting.
 */
void
afe_error(dev_info_t *dip, char *fmt, ...)
{
	va_list	ap;
	char	buf[256];

	va_start(ap, fmt);
	(void) vsnprintf(buf, sizeof (buf), fmt, ap);
	va_end(ap);

	if (dip) {
		cmn_err(CE_WARN, "%s%d: %s",
		    ddi_driver_name(dip), ddi_get_instance(dip), buf);
	} else {
		cmn_err(CE_WARN, "afe: %s", buf);
	}
}

#ifdef	DEBUG

void
afe_dprintf(afe_t *afep, const char *func, int level, char *fmt, ...)
{
	va_list	ap;

	va_start(ap, fmt);
	if (afe_debug & level) {
		char	tag[64];
		char	buf[256];

		if (afep && afep->afe_dip) {
			(void) snprintf(tag, sizeof (tag), "%s%d",
			    ddi_driver_name(afep->afe_dip),
			    ddi_get_instance(afep->afe_dip));
		} else {
			(void) snprintf(tag, sizeof (tag), "afe");
		}

		(void) snprintf(buf, sizeof (buf), "%s: %s: %s\n",
		    tag, func, fmt);

		vcmn_err(CE_CONT, buf, ap);
	}
	va_end(ap);
}

#endif

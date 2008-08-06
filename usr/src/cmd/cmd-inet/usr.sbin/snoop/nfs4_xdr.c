/*
 * CDDL HEADER START
 *
 * The contents of this file are subject to the terms of the
 * Common Development and Distribution License (the "License").
 * You may not use this file except in compliance with the License.
 *
 * You can obtain a copy of the license at usr/src/OPENSOLARIS.LICENSE
 * or http://www.opensolaris.org/os/licensing.
 * See the License for the specific language governing permissions
 * and limitations under the License.
 *
 * When distributing Covered Code, include this CDDL HEADER in each
 * file and include the License file at usr/src/OPENSOLARIS.LICENSE.
 * If applicable, add the following below this CDDL HEADER, with the
 * fields enclosed by brackets "[]" replaced with your own identifying
 * information: Portions Copyright [yyyy] [name of copyright owner]
 *
 * CDDL HEADER END
 */
/*
 * Copyright 2008 Sun Microsystems, Inc.  All rights reserved.
 * Use is subject to license terms.
 */

#include "nfs4_prot.h"

#ifndef _KERNEL
#include <stdlib.h>
#endif /* !_KERNEL */

#ifndef _AUTH_SYS_DEFINE_FOR_NFSv41
#define	_AUTH_SYS_DEFINE_FOR_NFSv41
#include <rpc/auth_sys.h>
typedef struct authsys_parms authsys_parms;
#endif /* _AUTH_SYS_DEFINE_FOR_NFSv41 */

#define	IGNORE_RDWR_DATA

extern int nfs4_skip_bytes;

bool_t
xdr_nfs_ftype4(XDR *xdrs, nfs_ftype4 *objp)
{

	rpc_inline_t *buf;

	if (!xdr_enum(xdrs, (enum_t *)objp))
		return (FALSE);
	return (TRUE);
}

bool_t
xdr_nfsstat4(XDR *xdrs, nfsstat4 *objp)
{

	rpc_inline_t *buf;

	if (!xdr_enum(xdrs, (enum_t *)objp))
		return (FALSE);
	return (TRUE);
}

bool_t
xdr_attrlist4(XDR *xdrs, attrlist4 *objp)
{

	rpc_inline_t *buf;

	if (!xdr_bytes(xdrs, (char **)&objp->attrlist4_val,
	    (uint_t *)&objp->attrlist4_len, ~0))
		return (FALSE);
	return (TRUE);
}

bool_t
xdr_bitmap4(XDR *xdrs, bitmap4 *objp)
{

	rpc_inline_t *buf;

	if (!xdr_array(xdrs, (char **)&objp->bitmap4_val,
	    (uint_t *)&objp->bitmap4_len, ~0,
	    sizeof (uint32_t), (xdrproc_t)xdr_uint32_t))
		return (FALSE);
	return (TRUE);
}

bool_t
xdr_changeid4(XDR *xdrs, changeid4 *objp)
{

	rpc_inline_t *buf;

	if (!xdr_uint64_t(xdrs, objp))
		return (FALSE);
	return (TRUE);
}

bool_t
xdr_clientid4(XDR *xdrs, clientid4 *objp)
{

	rpc_inline_t *buf;

	if (!xdr_uint64_t(xdrs, objp))
		return (FALSE);
	return (TRUE);
}

bool_t
xdr_count4(XDR *xdrs, count4 *objp)
{

	rpc_inline_t *buf;

	if (!xdr_uint32_t(xdrs, objp))
		return (FALSE);
	return (TRUE);
}

bool_t
xdr_length4(XDR *xdrs, length4 *objp)
{

	rpc_inline_t *buf;

	if (!xdr_uint64_t(xdrs, objp))
		return (FALSE);
	return (TRUE);
}

bool_t
xdr_mode4(XDR *xdrs, mode4 *objp)
{

	rpc_inline_t *buf;

	if (!xdr_uint32_t(xdrs, objp))
		return (FALSE);
	return (TRUE);
}

bool_t
xdr_nfs_cookie4(XDR *xdrs, nfs_cookie4 *objp)
{

	rpc_inline_t *buf;

	if (!xdr_uint64_t(xdrs, objp))
		return (FALSE);
	return (TRUE);
}

bool_t
xdr_nfs_fh4(XDR *xdrs, nfs_fh4 *objp)
{

	rpc_inline_t *buf;

	if (!xdr_bytes(xdrs, (char **)&objp->nfs_fh4_val,
	    (uint_t *)&objp->nfs_fh4_len, NFS4_FHSIZE))
		return (FALSE);
	return (TRUE);
}

bool_t
xdr_offset4(XDR *xdrs, offset4 *objp)
{

	rpc_inline_t *buf;

	if (!xdr_uint64_t(xdrs, objp))
		return (FALSE);
	return (TRUE);
}

bool_t
xdr_qop4(XDR *xdrs, qop4 *objp)
{

	rpc_inline_t *buf;

	if (!xdr_uint32_t(xdrs, objp))
		return (FALSE);
	return (TRUE);
}

bool_t
xdr_sec_oid4(XDR *xdrs, sec_oid4 *objp)
{

	rpc_inline_t *buf;

	if (!xdr_bytes(xdrs, (char **)&objp->sec_oid4_val,
	    (uint_t *)&objp->sec_oid4_len, ~0))
		return (FALSE);
	return (TRUE);
}

bool_t
xdr_sequenceid4(XDR *xdrs, sequenceid4 *objp)
{

	rpc_inline_t *buf;

	if (!xdr_uint32_t(xdrs, objp))
		return (FALSE);
	return (TRUE);
}

bool_t
xdr_seqid4(XDR *xdrs, seqid4 *objp)
{

	rpc_inline_t *buf;

	if (!xdr_uint32_t(xdrs, objp))
		return (FALSE);
	return (TRUE);
}

bool_t
xdr_sessionid4(XDR *xdrs, sessionid4 objp)
{

	rpc_inline_t *buf;

	if (!xdr_opaque(xdrs, objp, NFS4_SESSIONID_SIZE))
		return (FALSE);
	return (TRUE);
}

bool_t
xdr_slotid4(XDR *xdrs, slotid4 *objp)
{

	rpc_inline_t *buf;

	if (!xdr_uint32_t(xdrs, objp))
		return (FALSE);
	return (TRUE);
}

bool_t
xdr_utf8string(XDR *xdrs, utf8string *objp)
{

	rpc_inline_t *buf;

	if (!xdr_bytes(xdrs, (char **)&objp->utf8string_val,
	    (uint_t *)&objp->utf8string_len, ~0))
		return (FALSE);
	return (TRUE);
}

bool_t
xdr_utf8str_cis(XDR *xdrs, utf8str_cis *objp)
{

	rpc_inline_t *buf;

	if (!xdr_utf8string(xdrs, objp))
		return (FALSE);
	return (TRUE);
}

bool_t
xdr_utf8str_cs(XDR *xdrs, utf8str_cs *objp)
{

	rpc_inline_t *buf;

	if (!xdr_utf8string(xdrs, objp))
		return (FALSE);
	return (TRUE);
}

bool_t
xdr_utf8str_mixed(XDR *xdrs, utf8str_mixed *objp)
{

	rpc_inline_t *buf;

	if (!xdr_utf8string(xdrs, objp))
		return (FALSE);
	return (TRUE);
}

bool_t
xdr_component4(XDR *xdrs, component4 *objp)
{

	rpc_inline_t *buf;

	if (!xdr_utf8str_cs(xdrs, objp))
		return (FALSE);
	return (TRUE);
}

bool_t
xdr_linktext4(XDR *xdrs, linktext4 *objp)
{

	rpc_inline_t *buf;

	if (!xdr_utf8str_cs(xdrs, objp))
		return (FALSE);
	return (TRUE);
}

bool_t
xdr_pathname4(XDR *xdrs, pathname4 *objp)
{

	rpc_inline_t *buf;

	if (!xdr_array(xdrs, (char **)&objp->pathname4_val,
	    (uint_t *)&objp->pathname4_len, ~0,
	    sizeof (component4), (xdrproc_t)xdr_component4))
		return (FALSE);
	return (TRUE);
}

bool_t
xdr_verifier4(XDR *xdrs, verifier4 objp)
{

	rpc_inline_t *buf;

	if (!xdr_opaque(xdrs, objp, NFS4_VERIFIER_SIZE))
		return (FALSE);
	return (TRUE);
}

bool_t
xdr_nfstime4(XDR *xdrs, nfstime4 *objp)
{

	rpc_inline_t *buf;

	if (!xdr_int64_t(xdrs, &objp->seconds))
		return (FALSE);
	if (!xdr_uint32_t(xdrs, &objp->nseconds))
		return (FALSE);
	return (TRUE);
}

bool_t
xdr_time_how4(XDR *xdrs, time_how4 *objp)
{

	rpc_inline_t *buf;

	if (!xdr_enum(xdrs, (enum_t *)objp))
		return (FALSE);
	return (TRUE);
}

bool_t
xdr_settime4(XDR *xdrs, settime4 *objp)
{

	rpc_inline_t *buf;

	if (!xdr_time_how4(xdrs, &objp->set_it))
		return (FALSE);
	switch (objp->set_it) {
	case SET_TO_CLIENT_TIME4:
		if (!xdr_nfstime4(xdrs, &objp->settime4_u.time))
			return (FALSE);
		break;
	}
	return (TRUE);
}

bool_t
xdr_nfs_lease4(XDR *xdrs, nfs_lease4 *objp)
{

	rpc_inline_t *buf;

	if (!xdr_uint32_t(xdrs, objp))
		return (FALSE);
	return (TRUE);
}

bool_t
xdr_fsid4(XDR *xdrs, fsid4 *objp)
{

	rpc_inline_t *buf;

	if (!xdr_uint64_t(xdrs, &objp->major))
		return (FALSE);
	if (!xdr_uint64_t(xdrs, &objp->minor))
		return (FALSE);
	return (TRUE);
}

bool_t
xdr_change_policy4(XDR *xdrs, change_policy4 *objp)
{

	rpc_inline_t *buf;

	if (!xdr_uint64_t(xdrs, &objp->cp_major))
		return (FALSE);
	if (!xdr_uint64_t(xdrs, &objp->cp_minor))
		return (FALSE);
	return (TRUE);
}

bool_t
xdr_fs_location4(XDR *xdrs, fs_location4 *objp)
{

	rpc_inline_t *buf;

	if (!xdr_array(xdrs, (char **)&objp->server.server_val,
	    (uint_t *)&objp->server.server_len, ~0,
	    sizeof (utf8str_cis), (xdrproc_t)xdr_utf8str_cis))
		return (FALSE);
	if (!xdr_pathname4(xdrs, &objp->rootpath))
		return (FALSE);
	return (TRUE);
}

bool_t
xdr_fs_locations4(XDR *xdrs, fs_locations4 *objp)
{

	rpc_inline_t *buf;

	if (!xdr_pathname4(xdrs, &objp->fs_root))
		return (FALSE);
	if (!xdr_array(xdrs, (char **)&objp->locations.locations_val,
	    (uint_t *)&objp->locations.locations_len, ~0,
	    sizeof (fs_location4), (xdrproc_t)xdr_fs_location4))
		return (FALSE);
	return (TRUE);
}

bool_t
xdr_acetype4(XDR *xdrs, acetype4 *objp)
{

	rpc_inline_t *buf;

	if (!xdr_uint32_t(xdrs, objp))
		return (FALSE);
	return (TRUE);
}

bool_t
xdr_aceflag4(XDR *xdrs, aceflag4 *objp)
{

	rpc_inline_t *buf;

	if (!xdr_uint32_t(xdrs, objp))
		return (FALSE);
	return (TRUE);
}

bool_t
xdr_acemask4(XDR *xdrs, acemask4 *objp)
{

	rpc_inline_t *buf;

	if (!xdr_uint32_t(xdrs, objp))
		return (FALSE);
	return (TRUE);
}

bool_t
xdr_nfsace4(XDR *xdrs, nfsace4 *objp)
{

	rpc_inline_t *buf;

	if (!xdr_acetype4(xdrs, &objp->type))
		return (FALSE);
	if (!xdr_aceflag4(xdrs, &objp->flag))
		return (FALSE);
	if (!xdr_acemask4(xdrs, &objp->access_mask))
		return (FALSE);
	if (!xdr_utf8str_mixed(xdrs, &objp->who))
		return (FALSE);
	return (TRUE);
}

bool_t
xdr_aclflag4(XDR *xdrs, aclflag4 *objp)
{

	rpc_inline_t *buf;

	if (!xdr_uint32_t(xdrs, objp))
		return (FALSE);
	return (TRUE);
}

bool_t
xdr_nfsacl41(XDR *xdrs, nfsacl41 *objp)
{

	rpc_inline_t *buf;

	if (!xdr_aclflag4(xdrs, &objp->na41_flag))
		return (FALSE);
	if (!xdr_array(xdrs, (char **)&objp->na41_aces.na41_aces_val,
	    (uint_t *)&objp->na41_aces.na41_aces_len, ~0,
	    sizeof (nfsace4), (xdrproc_t)xdr_nfsace4))
		return (FALSE);
	return (TRUE);
}

bool_t
xdr_mode_masked4(XDR *xdrs, mode_masked4 *objp)
{

	rpc_inline_t *buf;

	if (!xdr_mode4(xdrs, &objp->mm_value_to_set))
		return (FALSE);
	if (!xdr_mode4(xdrs, &objp->mm_mask_bits))
		return (FALSE);
	return (TRUE);
}

bool_t
xdr_specdata4(XDR *xdrs, specdata4 *objp)
{

	rpc_inline_t *buf;

	if (!xdr_uint32_t(xdrs, &objp->specdata1))
		return (FALSE);
	if (!xdr_uint32_t(xdrs, &objp->specdata2))
		return (FALSE);
	return (TRUE);
}

bool_t
xdr_netaddr4(XDR *xdrs, netaddr4 *objp)
{

	rpc_inline_t *buf;

	if (!xdr_string(xdrs, &objp->na_r_netid, ~0))
		return (FALSE);
	if (!xdr_string(xdrs, &objp->na_r_addr, ~0))
		return (FALSE);
	return (TRUE);
}

bool_t
xdr_nfs_impl_id4(XDR *xdrs, nfs_impl_id4 *objp)
{

	rpc_inline_t *buf;

	if (!xdr_utf8str_cis(xdrs, &objp->nii_domain))
		return (FALSE);
	if (!xdr_utf8str_cs(xdrs, &objp->nii_name))
		return (FALSE);
	if (!xdr_nfstime4(xdrs, &objp->nii_date))
		return (FALSE);
	return (TRUE);
}

bool_t
xdr_stateid4(XDR *xdrs, stateid4 *objp)
{

	rpc_inline_t *buf;

	if (!xdr_uint32_t(xdrs, &objp->seqid))
		return (FALSE);
	if (!xdr_opaque(xdrs, objp->other, 12))
		return (FALSE);
	return (TRUE);
}

bool_t
xdr_layouttype4(XDR *xdrs, layouttype4 *objp)
{

	rpc_inline_t *buf;

	if (!xdr_enum(xdrs, (enum_t *)objp))
		return (FALSE);
	return (TRUE);
}

bool_t
xdr_layout_content4(XDR *xdrs, layout_content4 *objp)
{

	rpc_inline_t *buf;

	if (!xdr_layouttype4(xdrs, &objp->loc_type))
		return (FALSE);
	if (!xdr_bytes(xdrs, (char **)&objp->loc_body.loc_body_val,
	    (uint_t *)&objp->loc_body.loc_body_len, ~0))
		return (FALSE);
	return (TRUE);
}
/*
 * LAYOUT4_OSD2_OBJECTS loc_body description
 * is in a separate .x file
 */

/*
 * LAYOUT4_BLOCK_VOLUME loc_body description
 * is in a separate .x file
 */

bool_t
xdr_layouthint4(XDR *xdrs, layouthint4 *objp)
{

	rpc_inline_t *buf;

	if (!xdr_layouttype4(xdrs, &objp->loh_type))
		return (FALSE);
	if (!xdr_bytes(xdrs, (char **)&objp->loh_body.loh_body_val,
	    (uint_t *)&objp->loh_body.loh_body_len, ~0))
		return (FALSE);
	return (TRUE);
}

bool_t
xdr_layoutiomode4(XDR *xdrs, layoutiomode4 *objp)
{

	rpc_inline_t *buf;

	if (!xdr_enum(xdrs, (enum_t *)objp))
		return (FALSE);
	return (TRUE);
}

bool_t
xdr_layout4(XDR *xdrs, layout4 *objp)
{

	rpc_inline_t *buf;

	if (!xdr_offset4(xdrs, &objp->lo_offset))
		return (FALSE);
	if (!xdr_length4(xdrs, &objp->lo_length))
		return (FALSE);
	if (!xdr_layoutiomode4(xdrs, &objp->lo_iomode))
		return (FALSE);
	if (!xdr_layout_content4(xdrs, &objp->lo_content))
		return (FALSE);
	return (TRUE);
}

bool_t
xdr_deviceid4(XDR *xdrs, deviceid4 objp)
{

	rpc_inline_t *buf;

	if (!xdr_opaque(xdrs, objp, NFS4_DEVICEID4_SIZE))
		return (FALSE);
	return (TRUE);
}

bool_t
xdr_device_addr4(XDR *xdrs, device_addr4 *objp)
{

	rpc_inline_t *buf;

	if (!xdr_layouttype4(xdrs, &objp->da_layout_type))
		return (FALSE);
	if (!xdr_bytes(xdrs, (char **)&objp->da_addr_body.da_addr_body_val,
	    (uint_t *)&objp->da_addr_body.da_addr_body_len, ~0))
		return (FALSE);
	return (TRUE);
}

bool_t
xdr_layoutupdate4(XDR *xdrs, layoutupdate4 *objp)
{

	rpc_inline_t *buf;

	if (!xdr_layouttype4(xdrs, &objp->lou_type))
		return (FALSE);
	if (!xdr_bytes(xdrs, (char **)&objp->lou_body.lou_body_val,
	    (uint_t *)&objp->lou_body.lou_body_len, ~0))
		return (FALSE);
	return (TRUE);
}



bool_t
xdr_layoutreturn_type4(XDR *xdrs, layoutreturn_type4 *objp)
{

	rpc_inline_t *buf;

	if (!xdr_enum(xdrs, (enum_t *)objp))
		return (FALSE);
	return (TRUE);
}
/* layouttype4 specific data */

bool_t
xdr_layoutreturn_file4(XDR *xdrs, layoutreturn_file4 *objp)
{

	rpc_inline_t *buf;

	if (!xdr_offset4(xdrs, &objp->lrf_offset))
		return (FALSE);
	if (!xdr_length4(xdrs, &objp->lrf_length))
		return (FALSE);
	if (!xdr_stateid4(xdrs, &objp->lrf_stateid))
		return (FALSE);
	if (!xdr_bytes(xdrs, (char **)&objp->lrf_body.lrf_body_val,
	    (uint_t *)&objp->lrf_body.lrf_body_len, ~0))
		return (FALSE);
	return (TRUE);
}

bool_t
xdr_layoutreturn4(XDR *xdrs, layoutreturn4 *objp)
{

	rpc_inline_t *buf;

	if (!xdr_layoutreturn_type4(xdrs, &objp->lr_returntype))
		return (FALSE);
	switch (objp->lr_returntype) {
	case LAYOUTRETURN4_FILE:
		if (!xdr_layoutreturn_file4(xdrs,
		    &objp->layoutreturn4_u.lr_layout))
			return (FALSE);
		break;
	}
	return (TRUE);
}


bool_t
xdr_fs4_status_type(XDR *xdrs, fs4_status_type *objp)
{

	rpc_inline_t *buf;

	if (!xdr_enum(xdrs, (enum_t *)objp))
		return (FALSE);
	return (TRUE);
}

bool_t
xdr_fs4_status(XDR *xdrs, fs4_status *objp)
{

	rpc_inline_t *buf;

	if (!xdr_bool(xdrs, &objp->fss_absent))
		return (FALSE);
	if (!xdr_fs4_status_type(xdrs, &objp->fss_type))
		return (FALSE);
	if (!xdr_utf8str_cs(xdrs, &objp->fss_source))
		return (FALSE);
	if (!xdr_utf8str_cs(xdrs, &objp->fss_current))
		return (FALSE);
	if (!xdr_int32_t(xdrs, &objp->fss_age))
		return (FALSE);
	if (!xdr_nfstime4(xdrs, &objp->fss_version))
		return (FALSE);
	return (TRUE);
}

bool_t
xdr_threshold4_read_size(XDR *xdrs, threshold4_read_size *objp)
{

	rpc_inline_t *buf;

	if (!xdr_length4(xdrs, objp))
		return (FALSE);
	return (TRUE);
}

bool_t
xdr_threshold4_write_size(XDR *xdrs, threshold4_write_size *objp)
{

	rpc_inline_t *buf;

	if (!xdr_length4(xdrs, objp))
		return (FALSE);
	return (TRUE);
}

bool_t
xdr_threshold4_read_iosize(XDR *xdrs, threshold4_read_iosize *objp)
{

	rpc_inline_t *buf;

	if (!xdr_length4(xdrs, objp))
		return (FALSE);
	return (TRUE);
}

bool_t
xdr_threshold4_write_iosize(XDR *xdrs, threshold4_write_iosize *objp)
{

	rpc_inline_t *buf;

	if (!xdr_length4(xdrs, objp))
		return (FALSE);
	return (TRUE);
}

bool_t
xdr_threshold_item4(XDR *xdrs, threshold_item4 *objp)
{

	rpc_inline_t *buf;

	if (!xdr_layouttype4(xdrs, &objp->thi_layout_type))
		return (FALSE);
	if (!xdr_bitmap4(xdrs, &objp->thi_hintset))
		return (FALSE);
	if (!xdr_bytes(xdrs, (char **)&objp->thi_hintlist.thi_hintlist_val,
	    (uint_t *)&objp->thi_hintlist.thi_hintlist_len, ~0))
		return (FALSE);
	return (TRUE);
}

bool_t
xdr_mdsthreshold4(XDR *xdrs, mdsthreshold4 *objp)
{

	rpc_inline_t *buf;

	if (!xdr_array(xdrs, (char **)&objp->mth_hints.mth_hints_val,
	    (uint_t *)&objp->mth_hints.mth_hints_len, ~0,
	    sizeof (threshold_item4), (xdrproc_t)xdr_threshold_item4))
		return (FALSE);
	return (TRUE);
}

bool_t
xdr_retention_get4(XDR *xdrs, retention_get4 *objp)
{

	rpc_inline_t *buf;

	if (!xdr_uint64_t(xdrs, &objp->rg_duration))
		return (FALSE);
	if (!xdr_array(xdrs, (char **)&objp->rg_begin_time.rg_begin_time_val,
	    (uint_t *)&objp->rg_begin_time.rg_begin_time_len, 1,
	    sizeof (nfstime4), (xdrproc_t)xdr_nfstime4))
		return (FALSE);
	return (TRUE);
}

bool_t
xdr_retention_set4(XDR *xdrs, retention_set4 *objp)
{

	rpc_inline_t *buf;

	if (!xdr_bool(xdrs, &objp->rs_enable))
		return (FALSE);
	if (!xdr_array(xdrs, (char **)&objp->rs_duration.rs_duration_val,
	    (uint_t *)&objp->rs_duration.rs_duration_len, 1,
	    sizeof (uint64_t), (xdrproc_t)xdr_uint64_t))
		return (FALSE);
	return (TRUE);
}

bool_t
xdr_fs_charset_cap4(XDR *xdrs, fs_charset_cap4 *objp)
{

	rpc_inline_t *buf;

	if (!xdr_uint32_t(xdrs, objp))
		return (FALSE);
	return (TRUE);
}

bool_t
xdr_fattr4_supported_attrs(XDR *xdrs, fattr4_supported_attrs *objp)
{

	rpc_inline_t *buf;

	if (!xdr_bitmap4(xdrs, objp))
		return (FALSE);
	return (TRUE);
}

bool_t
xdr_fattr4_suppattr_exclcreat(XDR *xdrs, fattr4_suppattr_exclcreat *objp)
{

	rpc_inline_t *buf;

	if (!xdr_bitmap4(xdrs, objp))
		return (FALSE);
	return (TRUE);
}

bool_t
xdr_fattr4_type(XDR *xdrs, fattr4_type *objp)
{

	rpc_inline_t *buf;

	if (!xdr_nfs_ftype4(xdrs, objp))
		return (FALSE);
	return (TRUE);
}

bool_t
xdr_fattr4_fh_expire_type(XDR *xdrs, fattr4_fh_expire_type *objp)
{

	rpc_inline_t *buf;

	if (!xdr_uint32_t(xdrs, objp))
		return (FALSE);
	return (TRUE);
}

bool_t
xdr_fattr4_change(XDR *xdrs, fattr4_change *objp)
{

	rpc_inline_t *buf;

	if (!xdr_changeid4(xdrs, objp))
		return (FALSE);
	return (TRUE);
}

bool_t
xdr_fattr4_size(XDR *xdrs, fattr4_size *objp)
{

	rpc_inline_t *buf;

	if (!xdr_uint64_t(xdrs, objp))
		return (FALSE);
	return (TRUE);
}

bool_t
xdr_fattr4_link_support(XDR *xdrs, fattr4_link_support *objp)
{

	rpc_inline_t *buf;

	if (!xdr_bool(xdrs, objp))
		return (FALSE);
	return (TRUE);
}

bool_t
xdr_fattr4_symlink_support(XDR *xdrs, fattr4_symlink_support *objp)
{

	rpc_inline_t *buf;

	if (!xdr_bool(xdrs, objp))
		return (FALSE);
	return (TRUE);
}

bool_t
xdr_fattr4_named_attr(XDR *xdrs, fattr4_named_attr *objp)
{

	rpc_inline_t *buf;

	if (!xdr_bool(xdrs, objp))
		return (FALSE);
	return (TRUE);
}

bool_t
xdr_fattr4_fsid(XDR *xdrs, fattr4_fsid *objp)
{

	rpc_inline_t *buf;

	if (!xdr_fsid4(xdrs, objp))
		return (FALSE);
	return (TRUE);
}

bool_t
xdr_fattr4_unique_handles(XDR *xdrs, fattr4_unique_handles *objp)
{

	rpc_inline_t *buf;

	if (!xdr_bool(xdrs, objp))
		return (FALSE);
	return (TRUE);
}

bool_t
xdr_fattr4_lease_time(XDR *xdrs, fattr4_lease_time *objp)
{

	rpc_inline_t *buf;

	if (!xdr_nfs_lease4(xdrs, objp))
		return (FALSE);
	return (TRUE);
}

bool_t
xdr_fattr4_rdattr_error(XDR *xdrs, fattr4_rdattr_error *objp)
{

	rpc_inline_t *buf;

	if (!xdr_nfsstat4(xdrs, objp))
		return (FALSE);
	return (TRUE);
}

bool_t
xdr_fattr4_acl(XDR *xdrs, fattr4_acl *objp)
{

	rpc_inline_t *buf;

	if (!xdr_array(xdrs, (char **)&objp->fattr4_acl_val,
	    (uint_t *)&objp->fattr4_acl_len, ~0,
	    sizeof (nfsace4), (xdrproc_t)xdr_nfsace4))
		return (FALSE);
	return (TRUE);
}

bool_t
xdr_fattr4_aclsupport(XDR *xdrs, fattr4_aclsupport *objp)
{

	rpc_inline_t *buf;

	if (!xdr_uint32_t(xdrs, objp))
		return (FALSE);
	return (TRUE);
}

bool_t
xdr_fattr4_archive(XDR *xdrs, fattr4_archive *objp)
{

	rpc_inline_t *buf;

	if (!xdr_bool(xdrs, objp))
		return (FALSE);
	return (TRUE);
}

bool_t
xdr_fattr4_cansettime(XDR *xdrs, fattr4_cansettime *objp)
{

	rpc_inline_t *buf;

	if (!xdr_bool(xdrs, objp))
		return (FALSE);
	return (TRUE);
}

bool_t
xdr_fattr4_case_insensitive(XDR *xdrs, fattr4_case_insensitive *objp)
{

	rpc_inline_t *buf;

	if (!xdr_bool(xdrs, objp))
		return (FALSE);
	return (TRUE);
}

bool_t
xdr_fattr4_case_preserving(XDR *xdrs, fattr4_case_preserving *objp)
{

	rpc_inline_t *buf;

	if (!xdr_bool(xdrs, objp))
		return (FALSE);
	return (TRUE);
}

bool_t
xdr_fattr4_chown_restricted(XDR *xdrs, fattr4_chown_restricted *objp)
{

	rpc_inline_t *buf;

	if (!xdr_bool(xdrs, objp))
		return (FALSE);
	return (TRUE);
}

bool_t
xdr_fattr4_fileid(XDR *xdrs, fattr4_fileid *objp)
{

	rpc_inline_t *buf;

	if (!xdr_uint64_t(xdrs, objp))
		return (FALSE);
	return (TRUE);
}

bool_t
xdr_fattr4_files_avail(XDR *xdrs, fattr4_files_avail *objp)
{

	rpc_inline_t *buf;

	if (!xdr_uint64_t(xdrs, objp))
		return (FALSE);
	return (TRUE);
}

bool_t
xdr_fattr4_filehandle(XDR *xdrs, fattr4_filehandle *objp)
{

	rpc_inline_t *buf;

	if (!xdr_nfs_fh4(xdrs, objp))
		return (FALSE);
	return (TRUE);
}

bool_t
xdr_fattr4_files_free(XDR *xdrs, fattr4_files_free *objp)
{

	rpc_inline_t *buf;

	if (!xdr_uint64_t(xdrs, objp))
		return (FALSE);
	return (TRUE);
}

bool_t
xdr_fattr4_files_total(XDR *xdrs, fattr4_files_total *objp)
{

	rpc_inline_t *buf;

	if (!xdr_uint64_t(xdrs, objp))
		return (FALSE);
	return (TRUE);
}

bool_t
xdr_fattr4_fs_locations(XDR *xdrs, fattr4_fs_locations *objp)
{

	rpc_inline_t *buf;

	if (!xdr_fs_locations4(xdrs, objp))
		return (FALSE);
	return (TRUE);
}

bool_t
xdr_fattr4_hidden(XDR *xdrs, fattr4_hidden *objp)
{

	rpc_inline_t *buf;

	if (!xdr_bool(xdrs, objp))
		return (FALSE);
	return (TRUE);
}

bool_t
xdr_fattr4_homogeneous(XDR *xdrs, fattr4_homogeneous *objp)
{

	rpc_inline_t *buf;

	if (!xdr_bool(xdrs, objp))
		return (FALSE);
	return (TRUE);
}

bool_t
xdr_fattr4_maxfilesize(XDR *xdrs, fattr4_maxfilesize *objp)
{

	rpc_inline_t *buf;

	if (!xdr_uint64_t(xdrs, objp))
		return (FALSE);
	return (TRUE);
}

bool_t
xdr_fattr4_maxlink(XDR *xdrs, fattr4_maxlink *objp)
{

	rpc_inline_t *buf;

	if (!xdr_uint32_t(xdrs, objp))
		return (FALSE);
	return (TRUE);
}

bool_t
xdr_fattr4_maxname(XDR *xdrs, fattr4_maxname *objp)
{

	rpc_inline_t *buf;

	if (!xdr_uint32_t(xdrs, objp))
		return (FALSE);
	return (TRUE);
}

bool_t
xdr_fattr4_maxread(XDR *xdrs, fattr4_maxread *objp)
{

	rpc_inline_t *buf;

	if (!xdr_uint64_t(xdrs, objp))
		return (FALSE);
	return (TRUE);
}

bool_t
xdr_fattr4_maxwrite(XDR *xdrs, fattr4_maxwrite *objp)
{

	rpc_inline_t *buf;

	if (!xdr_uint64_t(xdrs, objp))
		return (FALSE);
	return (TRUE);
}

bool_t
xdr_fattr4_mimetype(XDR *xdrs, fattr4_mimetype *objp)
{

	rpc_inline_t *buf;

	if (!xdr_utf8str_cs(xdrs, objp))
		return (FALSE);
	return (TRUE);
}

bool_t
xdr_fattr4_mode(XDR *xdrs, fattr4_mode *objp)
{

	rpc_inline_t *buf;

	if (!xdr_mode4(xdrs, objp))
		return (FALSE);
	return (TRUE);
}

bool_t
xdr_fattr4_mode_set_masked(XDR *xdrs, fattr4_mode_set_masked *objp)
{

	rpc_inline_t *buf;

	if (!xdr_mode_masked4(xdrs, objp))
		return (FALSE);
	return (TRUE);
}

bool_t
xdr_fattr4_mounted_on_fileid(XDR *xdrs, fattr4_mounted_on_fileid *objp)
{

	rpc_inline_t *buf;

	if (!xdr_uint64_t(xdrs, objp))
		return (FALSE);
	return (TRUE);
}

bool_t
xdr_fattr4_no_trunc(XDR *xdrs, fattr4_no_trunc *objp)
{

	rpc_inline_t *buf;

	if (!xdr_bool(xdrs, objp))
		return (FALSE);
	return (TRUE);
}

bool_t
xdr_fattr4_numlinks(XDR *xdrs, fattr4_numlinks *objp)
{

	rpc_inline_t *buf;

	if (!xdr_uint32_t(xdrs, objp))
		return (FALSE);
	return (TRUE);
}

bool_t
xdr_fattr4_owner(XDR *xdrs, fattr4_owner *objp)
{

	rpc_inline_t *buf;

	if (!xdr_utf8str_mixed(xdrs, objp))
		return (FALSE);
	return (TRUE);
}

bool_t
xdr_fattr4_owner_group(XDR *xdrs, fattr4_owner_group *objp)
{

	rpc_inline_t *buf;

	if (!xdr_utf8str_mixed(xdrs, objp))
		return (FALSE);
	return (TRUE);
}

bool_t
xdr_fattr4_quota_avail_hard(XDR *xdrs, fattr4_quota_avail_hard *objp)
{

	rpc_inline_t *buf;

	if (!xdr_uint64_t(xdrs, objp))
		return (FALSE);
	return (TRUE);
}

bool_t
xdr_fattr4_quota_avail_soft(XDR *xdrs, fattr4_quota_avail_soft *objp)
{

	rpc_inline_t *buf;

	if (!xdr_uint64_t(xdrs, objp))
		return (FALSE);
	return (TRUE);
}

bool_t
xdr_fattr4_quota_used(XDR *xdrs, fattr4_quota_used *objp)
{

	rpc_inline_t *buf;

	if (!xdr_uint64_t(xdrs, objp))
		return (FALSE);
	return (TRUE);
}

bool_t
xdr_fattr4_rawdev(XDR *xdrs, fattr4_rawdev *objp)
{

	rpc_inline_t *buf;

	if (!xdr_specdata4(xdrs, objp))
		return (FALSE);
	return (TRUE);
}

bool_t
xdr_fattr4_space_avail(XDR *xdrs, fattr4_space_avail *objp)
{

	rpc_inline_t *buf;

	if (!xdr_uint64_t(xdrs, objp))
		return (FALSE);
	return (TRUE);
}

bool_t
xdr_fattr4_space_free(XDR *xdrs, fattr4_space_free *objp)
{

	rpc_inline_t *buf;

	if (!xdr_uint64_t(xdrs, objp))
		return (FALSE);
	return (TRUE);
}

bool_t
xdr_fattr4_space_total(XDR *xdrs, fattr4_space_total *objp)
{

	rpc_inline_t *buf;

	if (!xdr_uint64_t(xdrs, objp))
		return (FALSE);
	return (TRUE);
}

bool_t
xdr_fattr4_space_used(XDR *xdrs, fattr4_space_used *objp)
{

	rpc_inline_t *buf;

	if (!xdr_uint64_t(xdrs, objp))
		return (FALSE);
	return (TRUE);
}

bool_t
xdr_fattr4_system(XDR *xdrs, fattr4_system *objp)
{

	rpc_inline_t *buf;

	if (!xdr_bool(xdrs, objp))
		return (FALSE);
	return (TRUE);
}

bool_t
xdr_fattr4_time_access(XDR *xdrs, fattr4_time_access *objp)
{

	rpc_inline_t *buf;

	if (!xdr_nfstime4(xdrs, objp))
		return (FALSE);
	return (TRUE);
}

bool_t
xdr_fattr4_time_access_set(XDR *xdrs, fattr4_time_access_set *objp)
{

	rpc_inline_t *buf;

	if (!xdr_settime4(xdrs, objp))
		return (FALSE);
	return (TRUE);
}

bool_t
xdr_fattr4_time_backup(XDR *xdrs, fattr4_time_backup *objp)
{

	rpc_inline_t *buf;

	if (!xdr_nfstime4(xdrs, objp))
		return (FALSE);
	return (TRUE);
}

bool_t
xdr_fattr4_time_create(XDR *xdrs, fattr4_time_create *objp)
{

	rpc_inline_t *buf;

	if (!xdr_nfstime4(xdrs, objp))
		return (FALSE);
	return (TRUE);
}

bool_t
xdr_fattr4_time_delta(XDR *xdrs, fattr4_time_delta *objp)
{

	rpc_inline_t *buf;

	if (!xdr_nfstime4(xdrs, objp))
		return (FALSE);
	return (TRUE);
}

bool_t
xdr_fattr4_time_metadata(XDR *xdrs, fattr4_time_metadata *objp)
{

	rpc_inline_t *buf;

	if (!xdr_nfstime4(xdrs, objp))
		return (FALSE);
	return (TRUE);
}

bool_t
xdr_fattr4_time_modify(XDR *xdrs, fattr4_time_modify *objp)
{

	rpc_inline_t *buf;

	if (!xdr_nfstime4(xdrs, objp))
		return (FALSE);
	return (TRUE);
}

bool_t
xdr_fattr4_time_modify_set(XDR *xdrs, fattr4_time_modify_set *objp)
{

	rpc_inline_t *buf;

	if (!xdr_settime4(xdrs, objp))
		return (FALSE);
	return (TRUE);
}

bool_t
xdr_fattr4_dir_notif_delay(XDR *xdrs, fattr4_dir_notif_delay *objp)
{

	rpc_inline_t *buf;

	if (!xdr_nfstime4(xdrs, objp))
		return (FALSE);
	return (TRUE);
}

bool_t
xdr_fattr4_dirent_notif_delay(XDR *xdrs, fattr4_dirent_notif_delay *objp)
{

	rpc_inline_t *buf;

	if (!xdr_nfstime4(xdrs, objp))
		return (FALSE);
	return (TRUE);
}

bool_t
xdr_fattr4_absent(XDR *xdrs, fattr4_absent *objp)
{

	rpc_inline_t *buf;

	if (!xdr_bool(xdrs, objp))
		return (FALSE);
	return (TRUE);
}

bool_t
xdr_fattr4_fs_layout_types(XDR *xdrs, fattr4_fs_layout_types *objp)
{

	rpc_inline_t *buf;

	if (!xdr_array(xdrs, (char **)&objp->fattr4_fs_layout_types_val,
	    (uint_t *)&objp->fattr4_fs_layout_types_len, ~0,
	    sizeof (layouttype4), (xdrproc_t)xdr_layouttype4))
		return (FALSE);
	return (TRUE);
}

bool_t
xdr_fattr4_fs_status(XDR *xdrs, fattr4_fs_status *objp)
{

	rpc_inline_t *buf;

	if (!xdr_fs4_status(xdrs, objp))
		return (FALSE);
	return (TRUE);
}

bool_t
xdr_fattr4_fs_charset_cap4(XDR *xdrs, fattr4_fs_charset_cap4 *objp)
{

	rpc_inline_t *buf;

	if (!xdr_fs_charset_cap4(xdrs, objp))
		return (FALSE);
	return (TRUE);
}

bool_t
xdr_fattr4_layout_alignment(XDR *xdrs, fattr4_layout_alignment *objp)
{

	rpc_inline_t *buf;

	if (!xdr_uint32_t(xdrs, objp))
		return (FALSE);
	return (TRUE);
}

bool_t
xdr_fattr4_layout_blksize(XDR *xdrs, fattr4_layout_blksize *objp)
{

	rpc_inline_t *buf;

	if (!xdr_uint32_t(xdrs, objp))
		return (FALSE);
	return (TRUE);
}

bool_t
xdr_fattr4_layout_hint(XDR *xdrs, fattr4_layout_hint *objp)
{

	rpc_inline_t *buf;

	if (!xdr_layouthint4(xdrs, objp))
		return (FALSE);
	return (TRUE);
}

bool_t
xdr_fattr4_layout_types(XDR *xdrs, fattr4_layout_types *objp)
{

	rpc_inline_t *buf;

	if (!xdr_array(xdrs, (char **)&objp->fattr4_layout_types_val,
	    (uint_t *)&objp->fattr4_layout_types_len, ~0,
	    sizeof (layouttype4), (xdrproc_t)xdr_layouttype4))
		return (FALSE);
	return (TRUE);
}

bool_t
xdr_fattr4_mdsthreshold(XDR *xdrs, fattr4_mdsthreshold *objp)
{

	rpc_inline_t *buf;

	if (!xdr_mdsthreshold4(xdrs, objp))
		return (FALSE);
	return (TRUE);
}

bool_t
xdr_fattr4_retention_get(XDR *xdrs, fattr4_retention_get *objp)
{

	rpc_inline_t *buf;

	if (!xdr_retention_get4(xdrs, objp))
		return (FALSE);
	return (TRUE);
}

bool_t
xdr_fattr4_retention_set(XDR *xdrs, fattr4_retention_set *objp)
{

	rpc_inline_t *buf;

	if (!xdr_retention_set4(xdrs, objp))
		return (FALSE);
	return (TRUE);
}

bool_t
xdr_fattr4_retentevt_get(XDR *xdrs, fattr4_retentevt_get *objp)
{

	rpc_inline_t *buf;

	if (!xdr_retention_get4(xdrs, objp))
		return (FALSE);
	return (TRUE);
}

bool_t
xdr_fattr4_retentevt_set(XDR *xdrs, fattr4_retentevt_set *objp)
{

	rpc_inline_t *buf;

	if (!xdr_retention_set4(xdrs, objp))
		return (FALSE);
	return (TRUE);
}

bool_t
xdr_fattr4_retention_hold(XDR *xdrs, fattr4_retention_hold *objp)
{

	rpc_inline_t *buf;

	if (!xdr_uint64_t(xdrs, objp))
		return (FALSE);
	return (TRUE);
}

bool_t
xdr_fattr4_dacl(XDR *xdrs, fattr4_dacl *objp)
{

	rpc_inline_t *buf;

	if (!xdr_nfsacl41(xdrs, objp))
		return (FALSE);
	return (TRUE);
}

bool_t
xdr_fattr4_sacl(XDR *xdrs, fattr4_sacl *objp)
{

	rpc_inline_t *buf;

	if (!xdr_nfsacl41(xdrs, objp))
		return (FALSE);
	return (TRUE);
}

bool_t
xdr_fattr4(XDR *xdrs, fattr4 *objp)
{

	rpc_inline_t *buf;

	if (!xdr_bitmap4(xdrs, &objp->attrmask))
		return (FALSE);
	if (!xdr_attrlist4(xdrs, &objp->attr_vals))
		return (FALSE);
	return (TRUE);
}

bool_t
xdr_change_info4(XDR *xdrs, change_info4 *objp)
{

	rpc_inline_t *buf;

	if (!xdr_bool(xdrs, &objp->atomic))
		return (FALSE);
	if (!xdr_changeid4(xdrs, &objp->before))
		return (FALSE);
	if (!xdr_changeid4(xdrs, &objp->after))
		return (FALSE);
	return (TRUE);
}

bool_t
xdr_clientaddr4(XDR *xdrs, clientaddr4 *objp)
{

	rpc_inline_t *buf;

	if (!xdr_netaddr4(xdrs, objp))
		return (FALSE);
	return (TRUE);
}

bool_t
xdr_cb_client4(XDR *xdrs, cb_client4 *objp)
{

	rpc_inline_t *buf;

	if (!xdr_uint32_t(xdrs, &objp->cb_program))
		return (FALSE);
	if (!xdr_netaddr4(xdrs, &objp->cb_location))
		return (FALSE);
	return (TRUE);
}

bool_t
xdr_nfs_client_id4(XDR *xdrs, nfs_client_id4 *objp)
{

	rpc_inline_t *buf;

	if (!xdr_verifier4(xdrs, objp->verifier))
		return (FALSE);
	if (!xdr_bytes(xdrs, (char **)&objp->id.id_val,
	    (uint_t *)&objp->id.id_len, NFS4_OPAQUE_LIMIT))
		return (FALSE);
	return (TRUE);
}

bool_t
xdr_client_owner4(XDR *xdrs, client_owner4 *objp)
{

	rpc_inline_t *buf;

	if (!xdr_verifier4(xdrs, objp->co_verifier))
		return (FALSE);
	if (!xdr_bytes(xdrs, (char **)&objp->co_ownerid.co_ownerid_val,
	    (uint_t *)&objp->co_ownerid.co_ownerid_len, NFS4_OPAQUE_LIMIT))
		return (FALSE);
	return (TRUE);
}

bool_t
xdr_server_owner4(XDR *xdrs, server_owner4 *objp)
{

	rpc_inline_t *buf;

	if (!xdr_uint64_t(xdrs, &objp->so_minor_id))
		return (FALSE);
	if (!xdr_bytes(xdrs, (char **)&objp->so_major_id.so_major_id_val,
	    (uint_t *)&objp->so_major_id.so_major_id_len, NFS4_OPAQUE_LIMIT))
		return (FALSE);
	return (TRUE);
}

bool_t
xdr_state_owner4(XDR *xdrs, state_owner4 *objp)
{

	rpc_inline_t *buf;

	if (!xdr_clientid4(xdrs, &objp->clientid))
		return (FALSE);
	if (!xdr_bytes(xdrs, (char **)&objp->owner.owner_val,
	    (uint_t *)&objp->owner.owner_len, NFS4_OPAQUE_LIMIT))
		return (FALSE);
	return (TRUE);
}

bool_t
xdr_open_owner4(XDR *xdrs, open_owner4 *objp)
{

	rpc_inline_t *buf;

	if (!xdr_state_owner4(xdrs, objp))
		return (FALSE);
	return (TRUE);
}

bool_t
xdr_lock_owner4(XDR *xdrs, lock_owner4 *objp)
{

	rpc_inline_t *buf;

	if (!xdr_state_owner4(xdrs, objp))
		return (FALSE);
	return (TRUE);
}

bool_t
xdr_nfs_lock_type4(XDR *xdrs, nfs_lock_type4 *objp)
{

	rpc_inline_t *buf;

	if (!xdr_enum(xdrs, (enum_t *)objp))
		return (FALSE);
	return (TRUE);
}

/* Input for computing subkeys */

bool_t
xdr_ssv_subkey4(XDR *xdrs, ssv_subkey4 *objp)
{

	rpc_inline_t *buf;

	if (!xdr_enum(xdrs, (enum_t *)objp))
		return (FALSE);
	return (TRUE);
}


/* Input for computing smt_hmac */

bool_t
xdr_ssv_mic_plain_tkn4(XDR *xdrs, ssv_mic_plain_tkn4 *objp)
{

	rpc_inline_t *buf;

	if (!xdr_uint32_t(xdrs, &objp->smpt_ssv_seq))
		return (FALSE);
	if (!xdr_bytes(xdrs,
	    (char **)&objp->smpt_orig_plain.smpt_orig_plain_val,
	    (uint_t *)&objp->smpt_orig_plain.smpt_orig_plain_len, ~0))
		return (FALSE);
	return (TRUE);
}


/* SSV GSS PerMsgToken token */

bool_t
xdr_ssv_mic_tkn4(XDR *xdrs, ssv_mic_tkn4 *objp)
{

	rpc_inline_t *buf;

	if (!xdr_uint32_t(xdrs, &objp->smt_ssv_seq))
		return (FALSE);
	if (!xdr_bytes(xdrs, (char **)&objp->smt_hmac.smt_hmac_val,
	    (uint_t *)&objp->smt_hmac.smt_hmac_len, ~0))
		return (FALSE);
	return (TRUE);
}


/* Input for computing ssct_encr_data and ssct_hmac */

bool_t
xdr_ssv_seal_plain_tkn4(XDR *xdrs, ssv_seal_plain_tkn4 *objp)
{

	rpc_inline_t *buf;

	if (!xdr_bytes(xdrs,
	    (char **)&objp->sspt_confounder.sspt_confounder_val,
	    (uint_t *)&objp->sspt_confounder.sspt_confounder_len, ~0))
		return (FALSE);
	if (!xdr_uint32_t(xdrs, &objp->sspt_ssv_seq))
		return (FALSE);
	if (!xdr_bytes(xdrs,
	    (char **)&objp->sspt_orig_plain.sspt_orig_plain_val,
	    (uint_t *)&objp->sspt_orig_plain.sspt_orig_plain_len, ~0))
		return (FALSE);
	if (!xdr_bytes(xdrs, (char **)&objp->sspt_pad.sspt_pad_val,
	    (uint_t *)&objp->sspt_pad.sspt_pad_len, ~0))
		return (FALSE);
	return (TRUE);
}


/* SSV GSS SealedMessage token */

bool_t
xdr_ssv_seal_cipher_tkn4(XDR *xdrs, ssv_seal_cipher_tkn4 *objp)
{

	rpc_inline_t *buf;

	if (!xdr_uint32_t(xdrs, &objp->ssct_ssv_seq))
		return (FALSE);
	if (!xdr_bytes(xdrs, (char **)&objp->ssct_iv.ssct_iv_val,
	    (uint_t *)&objp->ssct_iv.ssct_iv_len, ~0))
		return (FALSE);
	if (!xdr_bytes(xdrs,
	    (char **)&objp->ssct_encr_data.ssct_encr_data_val,
	    (uint_t *)&objp->ssct_encr_data.ssct_encr_data_len, ~0))
		return (FALSE);
	if (!xdr_bytes(xdrs, (char **)&objp->ssct_hmac.ssct_hmac_val,
	    (uint_t *)&objp->ssct_hmac.ssct_hmac_len, ~0))
		return (FALSE);
	return (TRUE);
}


bool_t
xdr_fs_locations_server4(XDR *xdrs, fs_locations_server4 *objp)
{

	rpc_inline_t *buf;

	if (!xdr_int32_t(xdrs, &objp->fls_currency))
		return (FALSE);
	if (!xdr_bytes(xdrs, (char **)&objp->fls_info.fls_info_val,
	    (uint_t *)&objp->fls_info.fls_info_len, ~0))
		return (FALSE);
	if (!xdr_utf8str_cis(xdrs, &objp->fls_server))
		return (FALSE);
	return (TRUE);
}

bool_t
xdr_fs_locations_item4(XDR *xdrs, fs_locations_item4 *objp)
{

	rpc_inline_t *buf;

	if (!xdr_array(xdrs, (char **)&objp->fli_entries.fli_entries_val,
	    (uint_t *)&objp->fli_entries.fli_entries_len, ~0,
	    sizeof (fs_locations_server4), (xdrproc_t)xdr_fs_locations_server4))
		return (FALSE);
	if (!xdr_pathname4(xdrs, &objp->fli_rootpath))
		return (FALSE);
	return (TRUE);
}

bool_t
xdr_fs_locations_info4(XDR *xdrs, fs_locations_info4 *objp)
{

	rpc_inline_t *buf;

	if (!xdr_uint32_t(xdrs, &objp->fli_flags))
		return (FALSE);
	if (!xdr_int32_t(xdrs, &objp->fli_valid_for))
		return (FALSE);
	if (!xdr_pathname4(xdrs, &objp->fli_fs_root))
		return (FALSE);
	if (!xdr_array(xdrs, (char **)&objp->fli_items.fli_items_val,
	    (uint_t *)&objp->fli_items.fli_items_len, ~0,
	    sizeof (fs_locations_item4), (xdrproc_t)xdr_fs_locations_item4))
		return (FALSE);
	return (TRUE);
}

bool_t
xdr_fattr4_fs_locations_info(XDR *xdrs, fattr4_fs_locations_info *objp)
{

	rpc_inline_t *buf;

	if (!xdr_fs_locations_info4(xdrs, objp))
		return (FALSE);
	return (TRUE);
}

bool_t
xdr_nfl_util4(XDR *xdrs, nfl_util4 *objp)
{

	rpc_inline_t *buf;

	if (!xdr_uint32_t(xdrs, objp))
		return (FALSE);
	return (TRUE);
}


bool_t
xdr_filelayout_hint_care4(XDR *xdrs, filelayout_hint_care4 *objp)
{

	rpc_inline_t *buf;

	if (!xdr_enum(xdrs, (enum_t *)objp))
		return (FALSE);
	return (TRUE);
}

/* Encoded in the loh_body field of type layouthint4: */


bool_t
xdr_nfsv4_1_file_layouthint4(XDR *xdrs, nfsv4_1_file_layouthint4 *objp)
{

	rpc_inline_t *buf;

	if (!xdr_uint32_t(xdrs, &objp->nflh_care))
		return (FALSE);
	if (!xdr_nfl_util4(xdrs, &objp->nflh_util))
		return (FALSE);
	if (!xdr_count4(xdrs, &objp->nflh_stripe_count))
		return (FALSE);
	return (TRUE);
}



bool_t
xdr_multipath_list4(XDR *xdrs, multipath_list4 *objp)
{

	rpc_inline_t *buf;

	if (!xdr_array(xdrs, (char **)&objp->multipath_list4_val,
	    (uint_t *)&objp->multipath_list4_len, ~0,
	    sizeof (netaddr4), (xdrproc_t)xdr_netaddr4))
		return (FALSE);
	return (TRUE);
}

/* Encoded in the da_addr_body field of type device_addr4: */

bool_t
xdr_nfsv4_1_file_layout_ds_addr4(XDR *xdrs, nfsv4_1_file_layout_ds_addr4 *objp)
{

	rpc_inline_t *buf;

	if (!xdr_array(xdrs,
	    (char **)&objp->nflda_stripe_indices.nflda_stripe_indices_val,
	    (uint_t *)&objp->nflda_stripe_indices.nflda_stripe_indices_len, ~0,
	    sizeof (uint32_t), (xdrproc_t)xdr_uint32_t))
		return (FALSE);
	if (!xdr_array(xdrs,
	    (char **)&objp->nflda_multipath_ds_list.
	    nflda_multipath_ds_list_val,
	    (uint_t *)&objp->nflda_multipath_ds_list.
	    nflda_multipath_ds_list_len, ~0,
	    sizeof (multipath_list4), (xdrproc_t)xdr_multipath_list4))
		return (FALSE);
	return (TRUE);
}


/* Encoded in the loc_body field of type layout_content4: */

bool_t
xdr_nfsv4_1_file_layout4(XDR *xdrs, nfsv4_1_file_layout4 *objp)
{

	rpc_inline_t *buf;

	if (!xdr_deviceid4(xdrs, objp->nfl_deviceid))
		return (FALSE);
	if (!xdr_nfl_util4(xdrs, &objp->nfl_util))
		return (FALSE);
	if (!xdr_uint32_t(xdrs, &objp->nfl_first_stripe_index))
		return (FALSE);
	if (!xdr_offset4(xdrs, &objp->nfl_pattern_offset))
		return (FALSE);
	if (!xdr_array(xdrs, (char **)&objp->nfl_fh_list.nfl_fh_list_val,
	    (uint_t *)&objp->nfl_fh_list.nfl_fh_list_len, ~0,
	    sizeof (nfs_fh4), (xdrproc_t)xdr_nfs_fh4))
		return (FALSE);
	return (TRUE);
}

/*
 * Encoded in the lou_body field of type layoutupdate4:
 *      Nothing. lou_body is a zero length array of octets.
 */


bool_t
xdr_ACCESS4args(XDR *xdrs, ACCESS4args *objp)
{

	rpc_inline_t *buf;

	if (!xdr_uint32_t(xdrs, &objp->access))
		return (FALSE);
	return (TRUE);
}

bool_t
xdr_ACCESS4resok(XDR *xdrs, ACCESS4resok *objp)
{

	rpc_inline_t *buf;

	if (!xdr_uint32_t(xdrs, &objp->supported))
		return (FALSE);
	if (!xdr_uint32_t(xdrs, &objp->access))
		return (FALSE);
	return (TRUE);
}

bool_t
xdr_ACCESS4res(XDR *xdrs, ACCESS4res *objp)
{

	rpc_inline_t *buf;

	if (!xdr_nfsstat4(xdrs, &objp->status))
		return (FALSE);
	switch (objp->status) {
	case NFS4_OK:
		if (!xdr_ACCESS4resok(xdrs, &objp->ACCESS4res_u.resok4))
			return (FALSE);
		break;
	}
	return (TRUE);
}

bool_t
xdr_CLOSE4args(XDR *xdrs, CLOSE4args *objp)
{

	rpc_inline_t *buf;

	if (!xdr_seqid4(xdrs, &objp->seqid))
		return (FALSE);
	if (!xdr_stateid4(xdrs, &objp->open_stateid))
		return (FALSE);
	return (TRUE);
}

bool_t
xdr_CLOSE4res(XDR *xdrs, CLOSE4res *objp)
{

	rpc_inline_t *buf;

	if (!xdr_nfsstat4(xdrs, &objp->status))
		return (FALSE);
	switch (objp->status) {
	case NFS4_OK:
		if (!xdr_stateid4(xdrs, &objp->CLOSE4res_u.open_stateid))
			return (FALSE);
		break;
	}
	return (TRUE);
}

bool_t
xdr_COMMIT4args(XDR *xdrs, COMMIT4args *objp)
{

	rpc_inline_t *buf;

	if (!xdr_offset4(xdrs, &objp->offset))
		return (FALSE);
	if (!xdr_count4(xdrs, &objp->count))
		return (FALSE);
	return (TRUE);
}

bool_t
xdr_COMMIT4resok(XDR *xdrs, COMMIT4resok *objp)
{

	rpc_inline_t *buf;

	if (!xdr_verifier4(xdrs, objp->writeverf))
		return (FALSE);
	return (TRUE);
}

bool_t
xdr_COMMIT4res(XDR *xdrs, COMMIT4res *objp)
{

	rpc_inline_t *buf;

	if (!xdr_nfsstat4(xdrs, &objp->status))
		return (FALSE);
	switch (objp->status) {
	case NFS4_OK:
		if (!xdr_COMMIT4resok(xdrs, &objp->COMMIT4res_u.resok4))
			return (FALSE);
		break;
	}
	return (TRUE);
}

bool_t
xdr_createtype4(XDR *xdrs, createtype4 *objp)
{

	rpc_inline_t *buf;

	if (!xdr_nfs_ftype4(xdrs, &objp->type))
		return (FALSE);
	switch (objp->type) {
	case NF4LNK:
		if (!xdr_linktext4(xdrs, &objp->createtype4_u.linkdata))
			return (FALSE);
		break;
	case NF4BLK:
	case NF4CHR:
		if (!xdr_specdata4(xdrs, &objp->createtype4_u.devdata))
			return (FALSE);
		break;
	case NF4SOCK:
	case NF4FIFO:
	case NF4DIR:
		break;
	}
	return (TRUE);
}

bool_t
xdr_CREATE4args(XDR *xdrs, CREATE4args *objp)
{

	rpc_inline_t *buf;

	if (!xdr_createtype4(xdrs, &objp->objtype))
		return (FALSE);
	if (!xdr_component4(xdrs, &objp->objname))
		return (FALSE);
	if (!xdr_fattr4(xdrs, &objp->createattrs))
		return (FALSE);
	return (TRUE);
}

bool_t
xdr_CREATE4resok(XDR *xdrs, CREATE4resok *objp)
{

	rpc_inline_t *buf;

	if (!xdr_change_info4(xdrs, &objp->cinfo))
		return (FALSE);
	if (!xdr_bitmap4(xdrs, &objp->attrset))
		return (FALSE);
	return (TRUE);
}

bool_t
xdr_CREATE4res(XDR *xdrs, CREATE4res *objp)
{

	rpc_inline_t *buf;

	if (!xdr_nfsstat4(xdrs, &objp->status))
		return (FALSE);
	switch (objp->status) {
	case NFS4_OK:
		if (!xdr_CREATE4resok(xdrs, &objp->CREATE4res_u.resok4))
			return (FALSE);
		break;
	}
	return (TRUE);
}

bool_t
xdr_DELEGPURGE4args(XDR *xdrs, DELEGPURGE4args *objp)
{

	rpc_inline_t *buf;

	if (!xdr_clientid4(xdrs, &objp->clientid))
		return (FALSE);
	return (TRUE);
}

bool_t
xdr_DELEGPURGE4res(XDR *xdrs, DELEGPURGE4res *objp)
{

	rpc_inline_t *buf;

	if (!xdr_nfsstat4(xdrs, &objp->status))
		return (FALSE);
	return (TRUE);
}

bool_t
xdr_DELEGRETURN4args(XDR *xdrs, DELEGRETURN4args *objp)
{

	rpc_inline_t *buf;

	if (!xdr_stateid4(xdrs, &objp->deleg_stateid))
		return (FALSE);
	return (TRUE);
}

bool_t
xdr_DELEGRETURN4res(XDR *xdrs, DELEGRETURN4res *objp)
{

	rpc_inline_t *buf;

	if (!xdr_nfsstat4(xdrs, &objp->status))
		return (FALSE);
	return (TRUE);
}

bool_t
xdr_GETATTR4args(XDR *xdrs, GETATTR4args *objp)
{

	rpc_inline_t *buf;

	if (!xdr_bitmap4(xdrs, &objp->attr_request))
		return (FALSE);
	return (TRUE);
}

bool_t
xdr_GETATTR4resok(XDR *xdrs, GETATTR4resok *objp)
{

	rpc_inline_t *buf;

	if (!xdr_fattr4(xdrs, &objp->obj_attributes))
		return (FALSE);
	return (TRUE);
}

bool_t
xdr_GETATTR4res(XDR *xdrs, GETATTR4res *objp)
{

	rpc_inline_t *buf;

	if (!xdr_nfsstat4(xdrs, &objp->status))
		return (FALSE);
	switch (objp->status) {
	case NFS4_OK:
		if (!xdr_GETATTR4resok(xdrs, &objp->GETATTR4res_u.resok4))
			return (FALSE);
		break;
	}
	return (TRUE);
}

bool_t
xdr_GETFH4resok(XDR *xdrs, GETFH4resok *objp)
{

	rpc_inline_t *buf;

	if (!xdr_nfs_fh4(xdrs, &objp->object))
		return (FALSE);
	return (TRUE);
}

bool_t
xdr_GETFH4res(XDR *xdrs, GETFH4res *objp)
{

	rpc_inline_t *buf;

	if (!xdr_nfsstat4(xdrs, &objp->status))
		return (FALSE);
	switch (objp->status) {
	case NFS4_OK:
		if (!xdr_GETFH4resok(xdrs, &objp->GETFH4res_u.resok4))
			return (FALSE);
		break;
	}
	return (TRUE);
}

bool_t
xdr_LINK4args(XDR *xdrs, LINK4args *objp)
{

	rpc_inline_t *buf;

	if (!xdr_component4(xdrs, &objp->newname))
		return (FALSE);
	return (TRUE);
}

bool_t
xdr_LINK4resok(XDR *xdrs, LINK4resok *objp)
{

	rpc_inline_t *buf;

	if (!xdr_change_info4(xdrs, &objp->cinfo))
		return (FALSE);
	return (TRUE);
}

bool_t
xdr_LINK4res(XDR *xdrs, LINK4res *objp)
{

	rpc_inline_t *buf;

	if (!xdr_nfsstat4(xdrs, &objp->status))
		return (FALSE);
	switch (objp->status) {
	case NFS4_OK:
		if (!xdr_LINK4resok(xdrs, &objp->LINK4res_u.resok4))
			return (FALSE);
		break;
	}
	return (TRUE);
}

bool_t
xdr_open_to_lock_owner4(XDR *xdrs, open_to_lock_owner4 *objp)
{

	rpc_inline_t *buf;

	if (!xdr_seqid4(xdrs, &objp->open_seqid))
		return (FALSE);
	if (!xdr_stateid4(xdrs, &objp->open_stateid))
		return (FALSE);
	if (!xdr_seqid4(xdrs, &objp->lock_seqid))
		return (FALSE);
	if (!xdr_lock_owner4(xdrs, &objp->lock_owner))
		return (FALSE);
	return (TRUE);
}

bool_t
xdr_exist_lock_owner4(XDR *xdrs, exist_lock_owner4 *objp)
{

	rpc_inline_t *buf;

	if (!xdr_stateid4(xdrs, &objp->lock_stateid))
		return (FALSE);
	if (!xdr_seqid4(xdrs, &objp->lock_seqid))
		return (FALSE);
	return (TRUE);
}

bool_t
xdr_locker4(XDR *xdrs, locker4 *objp)
{

	rpc_inline_t *buf;

	if (!xdr_bool(xdrs, &objp->new_lock_owner))
		return (FALSE);
	switch (objp->new_lock_owner) {
	case TRUE:
		if (!xdr_open_to_lock_owner4(xdrs, &objp->locker4_u.open_owner))
			return (FALSE);
		break;
	case FALSE:
		if (!xdr_exist_lock_owner4(xdrs, &objp->locker4_u.lock_owner))
			return (FALSE);
		break;
	default:
		return (FALSE);
	}
	return (TRUE);
}

bool_t
xdr_LOCK4args(XDR *xdrs, LOCK4args *objp)
{

	rpc_inline_t *buf;

	if (!xdr_nfs_lock_type4(xdrs, &objp->locktype))
		return (FALSE);
	if (!xdr_bool(xdrs, &objp->reclaim))
		return (FALSE);
	if (!xdr_offset4(xdrs, &objp->offset))
		return (FALSE);
	if (!xdr_length4(xdrs, &objp->length))
		return (FALSE);
	if (!xdr_locker4(xdrs, &objp->locker))
		return (FALSE);
	return (TRUE);
}

bool_t
xdr_LOCK4denied(XDR *xdrs, LOCK4denied *objp)
{

	rpc_inline_t *buf;

	if (!xdr_offset4(xdrs, &objp->offset))
		return (FALSE);
	if (!xdr_length4(xdrs, &objp->length))
		return (FALSE);
	if (!xdr_nfs_lock_type4(xdrs, &objp->locktype))
		return (FALSE);
	if (!xdr_lock_owner4(xdrs, &objp->owner))
		return (FALSE);
	return (TRUE);
}

bool_t
xdr_LOCK4resok(XDR *xdrs, LOCK4resok *objp)
{

	rpc_inline_t *buf;

	if (!xdr_stateid4(xdrs, &objp->lock_stateid))
		return (FALSE);
	return (TRUE);
}

bool_t
xdr_LOCK4res(XDR *xdrs, LOCK4res *objp)
{

	rpc_inline_t *buf;

	if (!xdr_nfsstat4(xdrs, &objp->status))
		return (FALSE);
	switch (objp->status) {
	case NFS4_OK:
		if (!xdr_LOCK4resok(xdrs, &objp->LOCK4res_u.resok4))
			return (FALSE);
		break;
	case NFS4ERR_DENIED:
		if (!xdr_LOCK4denied(xdrs, &objp->LOCK4res_u.denied))
			return (FALSE);
		break;
	}
	return (TRUE);
}

bool_t
xdr_LOCKT4args(XDR *xdrs, LOCKT4args *objp)
{

	rpc_inline_t *buf;

	if (!xdr_nfs_lock_type4(xdrs, &objp->locktype))
		return (FALSE);
	if (!xdr_offset4(xdrs, &objp->offset))
		return (FALSE);
	if (!xdr_length4(xdrs, &objp->length))
		return (FALSE);
	if (!xdr_lock_owner4(xdrs, &objp->owner))
		return (FALSE);
	return (TRUE);
}

bool_t
xdr_LOCKT4res(XDR *xdrs, LOCKT4res *objp)
{

	rpc_inline_t *buf;

	if (!xdr_nfsstat4(xdrs, &objp->status))
		return (FALSE);
	switch (objp->status) {
	case NFS4ERR_DENIED:
		if (!xdr_LOCK4denied(xdrs, &objp->LOCKT4res_u.denied))
			return (FALSE);
		break;
	case NFS4_OK:
		break;
	}
	return (TRUE);
}

bool_t
xdr_LOCKU4args(XDR *xdrs, LOCKU4args *objp)
{

	rpc_inline_t *buf;

	if (!xdr_nfs_lock_type4(xdrs, &objp->locktype))
		return (FALSE);
	if (!xdr_seqid4(xdrs, &objp->seqid))
		return (FALSE);
	if (!xdr_stateid4(xdrs, &objp->lock_stateid))
		return (FALSE);
	if (!xdr_offset4(xdrs, &objp->offset))
		return (FALSE);
	if (!xdr_length4(xdrs, &objp->length))
		return (FALSE);
	return (TRUE);
}

bool_t
xdr_LOCKU4res(XDR *xdrs, LOCKU4res *objp)
{

	rpc_inline_t *buf;

	if (!xdr_nfsstat4(xdrs, &objp->status))
		return (FALSE);
	switch (objp->status) {
	case NFS4_OK:
		if (!xdr_stateid4(xdrs, &objp->LOCKU4res_u.lock_stateid))
			return (FALSE);
		break;
	}
	return (TRUE);
}

bool_t
xdr_LOOKUP4args(XDR *xdrs, LOOKUP4args *objp)
{

	rpc_inline_t *buf;

	if (!xdr_component4(xdrs, &objp->objname))
		return (FALSE);
	return (TRUE);
}

bool_t
xdr_LOOKUP4res(XDR *xdrs, LOOKUP4res *objp)
{

	rpc_inline_t *buf;

	if (!xdr_nfsstat4(xdrs, &objp->status))
		return (FALSE);
	return (TRUE);
}

bool_t
xdr_LOOKUPP4res(XDR *xdrs, LOOKUPP4res *objp)
{

	rpc_inline_t *buf;

	if (!xdr_nfsstat4(xdrs, &objp->status))
		return (FALSE);
	return (TRUE);
}

bool_t
xdr_NVERIFY4args(XDR *xdrs, NVERIFY4args *objp)
{

	rpc_inline_t *buf;

	if (!xdr_fattr4(xdrs, &objp->obj_attributes))
		return (FALSE);
	return (TRUE);
}

bool_t
xdr_NVERIFY4res(XDR *xdrs, NVERIFY4res *objp)
{

	rpc_inline_t *buf;

	if (!xdr_nfsstat4(xdrs, &objp->status))
		return (FALSE);
	return (TRUE);
}

bool_t
xdr_createmode4(XDR *xdrs, createmode4 *objp)
{

	rpc_inline_t *buf;

	if (!xdr_enum(xdrs, (enum_t *)objp))
		return (FALSE);
	return (TRUE);
}

bool_t
xdr_creatverfattr(XDR *xdrs, creatverfattr *objp)
{

	rpc_inline_t *buf;

	if (!xdr_verifier4(xdrs, objp->cva_verf))
		return (FALSE);
	if (!xdr_fattr4(xdrs, &objp->cva_attrs))
		return (FALSE);
	return (TRUE);
}

bool_t
xdr_createhow4(XDR *xdrs, createhow4 *objp)
{

	rpc_inline_t *buf;

	if (!xdr_createmode4(xdrs, &objp->mode))
		return (FALSE);
	switch (objp->mode) {
	case UNCHECKED4:
	case GUARDED4:
		if (!xdr_fattr4(xdrs, &objp->createhow4_u.createattrs))
			return (FALSE);
		break;
	case EXCLUSIVE4:
		if (!xdr_verifier4(xdrs, objp->createhow4_u.createverf))
			return (FALSE);
		break;
	case EXCLUSIVE4_1:
		if (!xdr_creatverfattr(xdrs, &objp->createhow4_u.ch_createboth))
			return (FALSE);
		break;
	default:
		return (FALSE);
	}
	return (TRUE);
}

bool_t
xdr_opentype4(XDR *xdrs, opentype4 *objp)
{

	rpc_inline_t *buf;

	if (!xdr_enum(xdrs, (enum_t *)objp))
		return (FALSE);
	return (TRUE);
}

bool_t
xdr_openflag4(XDR *xdrs, openflag4 *objp)
{

	rpc_inline_t *buf;

	if (!xdr_opentype4(xdrs, &objp->opentype))
		return (FALSE);
	switch (objp->opentype) {
	case OPEN4_CREATE:
		if (!xdr_createhow4(xdrs, &objp->openflag4_u.how))
			return (FALSE);
		break;
	}
	return (TRUE);
}

bool_t
xdr_limit_by4(XDR *xdrs, limit_by4 *objp)
{

	rpc_inline_t *buf;

	if (!xdr_enum(xdrs, (enum_t *)objp))
		return (FALSE);
	return (TRUE);
}

bool_t
xdr_nfs_modified_limit4(XDR *xdrs, nfs_modified_limit4 *objp)
{

	rpc_inline_t *buf;

	if (!xdr_uint32_t(xdrs, &objp->num_blocks))
		return (FALSE);
	if (!xdr_uint32_t(xdrs, &objp->bytes_per_block))
		return (FALSE);
	return (TRUE);
}

bool_t
xdr_nfs_space_limit4(XDR *xdrs, nfs_space_limit4 *objp)
{

	rpc_inline_t *buf;

	if (!xdr_limit_by4(xdrs, &objp->limitby))
		return (FALSE);
	switch (objp->limitby) {
	case NFS_LIMIT_SIZE:
		if (!xdr_uint64_t(xdrs, &objp->nfs_space_limit4_u.filesize))
			return (FALSE);
		break;
	case NFS_LIMIT_BLOCKS:
		if (!xdr_nfs_modified_limit4(xdrs,
		    &objp->nfs_space_limit4_u.mod_blocks))
			return (FALSE);
		break;
	default:
		return (FALSE);
	}
	return (TRUE);
}

bool_t
xdr_open_delegation_type4(XDR *xdrs, open_delegation_type4 *objp)
{

	rpc_inline_t *buf;

	if (!xdr_enum(xdrs, (enum_t *)objp))
		return (FALSE);
	return (TRUE);
}

bool_t
xdr_open_claim_type4(XDR *xdrs, open_claim_type4 *objp)
{

	rpc_inline_t *buf;

	if (!xdr_enum(xdrs, (enum_t *)objp))
		return (FALSE);
	return (TRUE);
}

bool_t
xdr_open_claim_delegate_cur4(XDR *xdrs, open_claim_delegate_cur4 *objp)
{

	rpc_inline_t *buf;

	if (!xdr_stateid4(xdrs, &objp->delegate_stateid))
		return (FALSE);
	if (!xdr_component4(xdrs, &objp->file))
		return (FALSE);
	return (TRUE);
}

bool_t
xdr_open_claim4(XDR *xdrs, open_claim4 *objp)
{

	rpc_inline_t *buf;

	if (!xdr_open_claim_type4(xdrs, &objp->claim))
		return (FALSE);
	switch (objp->claim) {
	case CLAIM_NULL:
		if (!xdr_component4(xdrs,
		    &objp->open_claim4_u.file))
			return (FALSE);
		break;
	case CLAIM_PREVIOUS:
		if (!xdr_open_delegation_type4(xdrs,
		    &objp->open_claim4_u.delegate_type))
			return (FALSE);
		break;
	case CLAIM_DELEGATE_CUR:
		if (!xdr_open_claim_delegate_cur4(xdrs,
		    &objp->open_claim4_u.delegate_cur_info))
			return (FALSE);
		break;
	case CLAIM_DELEGATE_PREV:
		if (!xdr_component4(xdrs,
		    &objp->open_claim4_u.file_delegate_prev))
			return (FALSE);
		break;
	case CLAIM_FH:
		break;
	case CLAIM_DELEG_PREV_FH:
		break;
	case CLAIM_DELEG_CUR_FH:
		if (!xdr_stateid4(xdrs,
		    &objp->open_claim4_u.oc_delegate_stateid))
			return (FALSE);
		break;
	default:
		return (FALSE);
	}
	return (TRUE);
}

bool_t
xdr_OPEN4args(XDR *xdrs, OPEN4args *objp)
{

	rpc_inline_t *buf;

	if (!xdr_seqid4(xdrs, &objp->seqid))
		return (FALSE);
	if (!xdr_uint32_t(xdrs, &objp->share_access))
		return (FALSE);
	if (!xdr_uint32_t(xdrs, &objp->share_deny))
		return (FALSE);
	if (!xdr_open_owner4(xdrs, &objp->owner))
		return (FALSE);
	if (!xdr_openflag4(xdrs, &objp->openhow))
		return (FALSE);
	if (!xdr_open_claim4(xdrs, &objp->claim))
		return (FALSE);
	return (TRUE);
}

bool_t
xdr_open_read_delegation4(XDR *xdrs, open_read_delegation4 *objp)
{

	rpc_inline_t *buf;

	if (!xdr_stateid4(xdrs, &objp->stateid))
		return (FALSE);
	if (!xdr_bool(xdrs, &objp->recall))
		return (FALSE);
	if (!xdr_nfsace4(xdrs, &objp->permissions))
		return (FALSE);
	return (TRUE);
}

bool_t
xdr_open_write_delegation4(XDR *xdrs, open_write_delegation4 *objp)
{

	rpc_inline_t *buf;

	if (!xdr_stateid4(xdrs, &objp->stateid))
		return (FALSE);
	if (!xdr_bool(xdrs, &objp->recall))
		return (FALSE);
	if (!xdr_nfs_space_limit4(xdrs, &objp->space_limit))
		return (FALSE);
	if (!xdr_nfsace4(xdrs, &objp->permissions))
		return (FALSE);
	return (TRUE);
}

bool_t
xdr_why_no_delegation4(XDR *xdrs, why_no_delegation4 *objp)
{

	rpc_inline_t *buf;

	if (!xdr_enum(xdrs, (enum_t *)objp))
		return (FALSE);
	return (TRUE);
}

bool_t
xdr_open_none_delegation4(XDR *xdrs, open_none_delegation4 *objp)
{

	rpc_inline_t *buf;

	if (!xdr_why_no_delegation4(xdrs, &objp->ond_why))
		return (FALSE);
	switch (objp->ond_why) {
	case WND4_CONTENTION:
		if (!xdr_bool(xdrs,
		    &objp->open_none_delegation4_u.ond_server_will_push_deleg))
			return (FALSE);
		break;
	case WND4_RESOURCE:
		if (!xdr_bool(xdrs,
		    &objp->open_none_delegation4_u.
		    ond_server_will_signal_avail))
			return (FALSE);
		break;
	}
	return (TRUE);
}

bool_t
xdr_open_delegation4(XDR *xdrs, open_delegation4 *objp)
{

	rpc_inline_t *buf;

	if (!xdr_open_delegation_type4(xdrs, &objp->delegation_type))
		return (FALSE);
	switch (objp->delegation_type) {
	case OPEN_DELEGATE_NONE:
		break;
	case OPEN_DELEGATE_READ:
		if (!xdr_open_read_delegation4(xdrs,
		    &objp->open_delegation4_u.read))
			return (FALSE);
		break;
	case OPEN_DELEGATE_WRITE:
		if (!xdr_open_write_delegation4(xdrs,
		    &objp->open_delegation4_u.write))
			return (FALSE);
		break;
	case OPEN_DELEGATE_NONE_EXT:
		if (!xdr_open_none_delegation4(xdrs,
		    &objp->open_delegation4_u.od_whynone))
			return (FALSE);
		break;
	default:
		return (FALSE);
	}
	return (TRUE);
}

bool_t
xdr_OPEN4resok(XDR *xdrs, OPEN4resok *objp)
{

	rpc_inline_t *buf;

	if (!xdr_stateid4(xdrs, &objp->stateid))
		return (FALSE);
	if (!xdr_change_info4(xdrs, &objp->cinfo))
		return (FALSE);
	if (!xdr_uint32_t(xdrs, &objp->rflags))
		return (FALSE);
	if (!xdr_bitmap4(xdrs, &objp->attrset))
		return (FALSE);
	if (!xdr_open_delegation4(xdrs, &objp->delegation))
		return (FALSE);
	return (TRUE);
}

bool_t
xdr_OPEN4res(XDR *xdrs, OPEN4res *objp)
{

	rpc_inline_t *buf;

	if (!xdr_nfsstat4(xdrs, &objp->status))
		return (FALSE);
	switch (objp->status) {
	case NFS4_OK:
		if (!xdr_OPEN4resok(xdrs, &objp->OPEN4res_u.resok4))
			return (FALSE);
		break;
	}
	return (TRUE);
}

bool_t
xdr_OPENATTR4args(XDR *xdrs, OPENATTR4args *objp)
{

	rpc_inline_t *buf;

	if (!xdr_bool(xdrs, &objp->createdir))
		return (FALSE);
	return (TRUE);
}

bool_t
xdr_OPENATTR4res(XDR *xdrs, OPENATTR4res *objp)
{

	rpc_inline_t *buf;

	if (!xdr_nfsstat4(xdrs, &objp->status))
		return (FALSE);
	return (TRUE);
}

bool_t
xdr_OPEN_CONFIRM4args(XDR *xdrs, OPEN_CONFIRM4args *objp)
{

	rpc_inline_t *buf;

	if (!xdr_stateid4(xdrs, &objp->open_stateid))
		return (FALSE);
	if (!xdr_seqid4(xdrs, &objp->seqid))
		return (FALSE);
	return (TRUE);
}

bool_t
xdr_OPEN_CONFIRM4resok(XDR *xdrs, OPEN_CONFIRM4resok *objp)
{

	rpc_inline_t *buf;

	if (!xdr_stateid4(xdrs, &objp->open_stateid))
		return (FALSE);
	return (TRUE);
}

bool_t
xdr_OPEN_CONFIRM4res(XDR *xdrs, OPEN_CONFIRM4res *objp)
{

	rpc_inline_t *buf;

	if (!xdr_nfsstat4(xdrs, &objp->status))
		return (FALSE);
	switch (objp->status) {
	case NFS4_OK:
		if (!xdr_OPEN_CONFIRM4resok(xdrs,
		    &objp->OPEN_CONFIRM4res_u.resok4))
			return (FALSE);
		break;
	}
	return (TRUE);
}

bool_t
xdr_OPEN_DOWNGRADE4args(XDR *xdrs, OPEN_DOWNGRADE4args *objp)
{

	rpc_inline_t *buf;

	if (!xdr_stateid4(xdrs, &objp->open_stateid))
		return (FALSE);
	if (!xdr_seqid4(xdrs, &objp->seqid))
		return (FALSE);
	if (!xdr_uint32_t(xdrs, &objp->share_access))
		return (FALSE);
	if (!xdr_uint32_t(xdrs, &objp->share_deny))
		return (FALSE);
	return (TRUE);
}

bool_t
xdr_OPEN_DOWNGRADE4resok(XDR *xdrs, OPEN_DOWNGRADE4resok *objp)
{

	rpc_inline_t *buf;

	if (!xdr_stateid4(xdrs, &objp->open_stateid))
		return (FALSE);
	return (TRUE);
}

bool_t
xdr_OPEN_DOWNGRADE4res(XDR *xdrs, OPEN_DOWNGRADE4res *objp)
{

	rpc_inline_t *buf;

	if (!xdr_nfsstat4(xdrs, &objp->status))
		return (FALSE);
	switch (objp->status) {
	case NFS4_OK:
		if (!xdr_OPEN_DOWNGRADE4resok(xdrs,
		    &objp->OPEN_DOWNGRADE4res_u.resok4))
			return (FALSE);
		break;
	}
	return (TRUE);
}

bool_t
xdr_PUTFH4args(XDR *xdrs, PUTFH4args *objp)
{

	rpc_inline_t *buf;

	if (!xdr_nfs_fh4(xdrs, &objp->object))
		return (FALSE);
	return (TRUE);
}

bool_t
xdr_PUTFH4res(XDR *xdrs, PUTFH4res *objp)
{

	rpc_inline_t *buf;

	if (!xdr_nfsstat4(xdrs, &objp->status))
		return (FALSE);
	return (TRUE);
}

bool_t
xdr_PUTPUBFH4res(XDR *xdrs, PUTPUBFH4res *objp)
{

	rpc_inline_t *buf;

	if (!xdr_nfsstat4(xdrs, &objp->status))
		return (FALSE);
	return (TRUE);
}

bool_t
xdr_PUTROOTFH4res(XDR *xdrs, PUTROOTFH4res *objp)
{

	rpc_inline_t *buf;

	if (!xdr_nfsstat4(xdrs, &objp->status))
		return (FALSE);
	return (TRUE);
}

bool_t
xdr_READ4args(XDR *xdrs, READ4args *objp)
{

	rpc_inline_t *buf;

	if (!xdr_stateid4(xdrs, &objp->stateid))
		return (FALSE);
	if (!xdr_offset4(xdrs, &objp->offset))
		return (FALSE);
	if (!xdr_count4(xdrs, &objp->count))
		return (FALSE);
	return (TRUE);
}

bool_t
xdr_READ4resok(XDR *xdrs, READ4resok *objp)
{

	rpc_inline_t *buf;

	if (!xdr_bool(xdrs, &objp->eof))

#ifdef  IGNORE_RDWR_DATA
	/*
	 * Try to get length of read, and if that
	 * fails, default to 0.  Don't return FALSE
	 * because the other read info will not be
	 * displayed.
	 */
	objp->data.data_val = NULL;
	if (!xdr_u_int(xdrs, &objp->data.data_len))
		objp->data.data_len = 0;
		nfs4_skip_bytes = objp->data.data_len;
#else
	if (!xdr_bytes(xdrs, (char **)&objp->data.data_val,
	    (uint_t *)&objp->data.data_len, ~0))
		return (FALSE);
#endif
	return (TRUE);
}

bool_t
xdr_READ4res(XDR *xdrs, READ4res *objp)
{

	rpc_inline_t *buf;

	if (!xdr_nfsstat4(xdrs, &objp->status))
		return (FALSE);
	switch (objp->status) {
	case NFS4_OK:
		if (!xdr_READ4resok(xdrs, &objp->READ4res_u.resok4))
			return (FALSE);
		break;
	}
	return (TRUE);
}

bool_t
xdr_READDIR4args(XDR *xdrs, READDIR4args *objp)
{

	rpc_inline_t *buf;

	if (!xdr_nfs_cookie4(xdrs, &objp->cookie))
		return (FALSE);
	if (!xdr_verifier4(xdrs, objp->cookieverf))
		return (FALSE);
	if (!xdr_count4(xdrs, &objp->dircount))
		return (FALSE);
	if (!xdr_count4(xdrs, &objp->maxcount))
		return (FALSE);
	if (!xdr_bitmap4(xdrs, &objp->attr_request))
		return (FALSE);
	return (TRUE);
}

bool_t
xdr_entry4(XDR *xdrs, entry4 *objp)
{

	rpc_inline_t *buf;

	entry4 *tmp_entry4;
	bool_t more_data = TRUE;
	bool_t first_objp = TRUE;


	if (xdrs->x_op == XDR_DECODE) {

		while (more_data) {

			void bzero();

			if (!xdr_nfs_cookie4(xdrs, &objp->cookie))
				return (FALSE);
			if (!xdr_component4(xdrs, &objp->name))
				return (FALSE);
			if (!xdr_fattr4(xdrs, &objp->attrs))
				return (FALSE);
			if (!xdr_bool(xdrs, &more_data))
				return (FALSE);

			if (!more_data) {
				objp->nextentry = NULL;
				break;
			}

			if (objp->nextentry == NULL) {
				objp->nextentry = (entry4 *)
				    mem_alloc(sizeof (entry4));
				if (objp->nextentry == NULL)
					return (FALSE);
				bzero(objp->nextentry, sizeof (entry4));
			}
			objp = objp->nextentry;
		}

	} else if (xdrs->x_op == XDR_ENCODE) {

		while (more_data) {
			if (!xdr_nfs_cookie4(xdrs, &objp->cookie))
				return (FALSE);
			if (!xdr_component4(xdrs, &objp->name))
				return (FALSE);
			if (!xdr_fattr4(xdrs, &objp->attrs))
				return (FALSE);
			objp = objp->nextentry;
			if (objp == NULL)
				more_data = FALSE;
			if (!xdr_bool(xdrs, &more_data))
				return (FALSE);
		}

	} else {

		while (more_data) {
			if (!xdr_nfs_cookie4(xdrs, &objp->cookie))
				return (FALSE);
			if (!xdr_component4(xdrs, &objp->name))
				return (FALSE);
			if (!xdr_fattr4(xdrs, &objp->attrs))
				return (FALSE);
			tmp_entry4 = objp;
			objp = objp->nextentry;
			if (objp == NULL)
				more_data = FALSE;
			if (!first_objp)
				mem_free(tmp_entry4, sizeof (entry4));
			else
				first_objp = FALSE;
		}

	}
	return (TRUE);
}

bool_t
xdr_dirlist4(XDR *xdrs, dirlist4 *objp)
{

	rpc_inline_t *buf;

	if (!xdr_pointer(xdrs, (char **)&objp->entries,
	    sizeof (entry4), (xdrproc_t)xdr_entry4))
		return (FALSE);
	if (!xdr_bool(xdrs, &objp->eof))
		return (FALSE);
	return (TRUE);
}

bool_t
xdr_READDIR4resok(XDR *xdrs, READDIR4resok *objp)
{

	rpc_inline_t *buf;

	if (!xdr_verifier4(xdrs, objp->cookieverf))
		return (FALSE);
	if (!xdr_dirlist4(xdrs, &objp->reply))
		return (FALSE);
	return (TRUE);
}

bool_t
xdr_READDIR4res(XDR *xdrs, READDIR4res *objp)
{

	rpc_inline_t *buf;

	if (!xdr_nfsstat4(xdrs, &objp->status))
		return (FALSE);
	switch (objp->status) {
	case NFS4_OK:
		if (!xdr_READDIR4resok(xdrs, &objp->READDIR4res_u.resok4))
			return (FALSE);
		break;
	}
	return (TRUE);
}

bool_t
xdr_READLINK4resok(XDR *xdrs, READLINK4resok *objp)
{

	rpc_inline_t *buf;

	if (!xdr_linktext4(xdrs, &objp->link))
		return (FALSE);
	return (TRUE);
}

bool_t
xdr_READLINK4res(XDR *xdrs, READLINK4res *objp)
{

	rpc_inline_t *buf;

	if (!xdr_nfsstat4(xdrs, &objp->status))
		return (FALSE);
	switch (objp->status) {
	case NFS4_OK:
		if (!xdr_READLINK4resok(xdrs, &objp->READLINK4res_u.resok4))
			return (FALSE);
		break;
	}
	return (TRUE);
}

bool_t
xdr_REMOVE4args(XDR *xdrs, REMOVE4args *objp)
{

	rpc_inline_t *buf;

	if (!xdr_component4(xdrs, &objp->target))
		return (FALSE);
	return (TRUE);
}

bool_t
xdr_REMOVE4resok(XDR *xdrs, REMOVE4resok *objp)
{

	rpc_inline_t *buf;

	if (!xdr_change_info4(xdrs, &objp->cinfo))
		return (FALSE);
	return (TRUE);
}

bool_t
xdr_REMOVE4res(XDR *xdrs, REMOVE4res *objp)
{

	rpc_inline_t *buf;

	if (!xdr_nfsstat4(xdrs, &objp->status))
		return (FALSE);
	switch (objp->status) {
	case NFS4_OK:
		if (!xdr_REMOVE4resok(xdrs, &objp->REMOVE4res_u.resok4))
			return (FALSE);
		break;
	}
	return (TRUE);
}

bool_t
xdr_RENAME4args(XDR *xdrs, RENAME4args *objp)
{

	rpc_inline_t *buf;

	if (!xdr_component4(xdrs, &objp->oldname))
		return (FALSE);
	if (!xdr_component4(xdrs, &objp->newname))
		return (FALSE);
	return (TRUE);
}

bool_t
xdr_RENAME4resok(XDR *xdrs, RENAME4resok *objp)
{

	rpc_inline_t *buf;

	if (!xdr_change_info4(xdrs, &objp->source_cinfo))
		return (FALSE);
	if (!xdr_change_info4(xdrs, &objp->target_cinfo))
		return (FALSE);
	return (TRUE);
}

bool_t
xdr_RENAME4res(XDR *xdrs, RENAME4res *objp)
{

	rpc_inline_t *buf;

	if (!xdr_nfsstat4(xdrs, &objp->status))
		return (FALSE);
	switch (objp->status) {
	case NFS4_OK:
		if (!xdr_RENAME4resok(xdrs, &objp->RENAME4res_u.resok4))
			return (FALSE);
		break;
	}
	return (TRUE);
}

bool_t
xdr_RENEW4args(XDR *xdrs, RENEW4args *objp)
{

	rpc_inline_t *buf;

	if (!xdr_clientid4(xdrs, &objp->clientid))
		return (FALSE);
	return (TRUE);
}

bool_t
xdr_RENEW4res(XDR *xdrs, RENEW4res *objp)
{

	rpc_inline_t *buf;

	if (!xdr_nfsstat4(xdrs, &objp->status))
		return (FALSE);
	return (TRUE);
}

bool_t
xdr_RESTOREFH4res(XDR *xdrs, RESTOREFH4res *objp)
{

	rpc_inline_t *buf;

	if (!xdr_nfsstat4(xdrs, &objp->status))
		return (FALSE);
	return (TRUE);
}

bool_t
xdr_SAVEFH4res(XDR *xdrs, SAVEFH4res *objp)
{

	rpc_inline_t *buf;

	if (!xdr_nfsstat4(xdrs, &objp->status))
		return (FALSE);
	return (TRUE);
}

bool_t
xdr_SECINFO4args(XDR *xdrs, SECINFO4args *objp)
{

	rpc_inline_t *buf;

	if (!xdr_component4(xdrs, &objp->name))
		return (FALSE);
	return (TRUE);
}

bool_t
xdr_rpc_gss_svc_t(XDR *xdrs, rpc_gss_svc_t *objp)
{

	rpc_inline_t *buf;

	if (!xdr_enum(xdrs, (enum_t *)objp))
		return (FALSE);
	return (TRUE);
}

bool_t
xdr_rpcsec_gss_info(XDR *xdrs, rpcsec_gss_info *objp)
{

	rpc_inline_t *buf;

	if (!xdr_sec_oid4(xdrs, &objp->oid))
		return (FALSE);
	if (!xdr_qop4(xdrs, &objp->qop))
		return (FALSE);
	if (!xdr_rpc_gss_svc_t(xdrs, &objp->service))
		return (FALSE);
	return (TRUE);
}

bool_t
xdr_secinfo4(XDR *xdrs, secinfo4 *objp)
{

	rpc_inline_t *buf;

	if (!xdr_uint32_t(xdrs, &objp->flavor))
		return (FALSE);
	switch (objp->flavor) {
	case RPCSEC_GSS:
		if (!xdr_rpcsec_gss_info(xdrs, &objp->secinfo4_u.flavor_info))
			return (FALSE);
		break;
	}
	return (TRUE);
}

bool_t
xdr_SECINFO4resok(XDR *xdrs, SECINFO4resok *objp)
{

	rpc_inline_t *buf;

	if (!xdr_array(xdrs, (char **)&objp->SECINFO4resok_val,
	    (uint_t *)&objp->SECINFO4resok_len, ~0,
	    sizeof (secinfo4), (xdrproc_t)xdr_secinfo4))
		return (FALSE);
	return (TRUE);
}

bool_t
xdr_SECINFO4res(XDR *xdrs, SECINFO4res *objp)
{

	rpc_inline_t *buf;

	if (!xdr_nfsstat4(xdrs, &objp->status))
		return (FALSE);
	switch (objp->status) {
	case NFS4_OK:
		if (!xdr_SECINFO4resok(xdrs, &objp->SECINFO4res_u.resok4))
			return (FALSE);
		break;
	}
	return (TRUE);
}

bool_t
xdr_SETATTR4args(XDR *xdrs, SETATTR4args *objp)
{

	rpc_inline_t *buf;

	if (!xdr_stateid4(xdrs, &objp->stateid))
		return (FALSE);
	if (!xdr_fattr4(xdrs, &objp->obj_attributes))
		return (FALSE);
	return (TRUE);
}

bool_t
xdr_SETATTR4res(XDR *xdrs, SETATTR4res *objp)
{

	rpc_inline_t *buf;

	if (!xdr_nfsstat4(xdrs, &objp->status))
		return (FALSE);
	if (!xdr_bitmap4(xdrs, &objp->attrsset))
		return (FALSE);
	return (TRUE);
}

bool_t
xdr_SETCLIENTID4args(XDR *xdrs, SETCLIENTID4args *objp)
{

	rpc_inline_t *buf;

	if (!xdr_nfs_client_id4(xdrs, &objp->client))
		return (FALSE);
	if (!xdr_cb_client4(xdrs, &objp->callback))
		return (FALSE);
	if (!xdr_uint32_t(xdrs, &objp->callback_ident))
		return (FALSE);
	return (TRUE);
}

bool_t
xdr_SETCLIENTID4resok(XDR *xdrs, SETCLIENTID4resok *objp)
{

	rpc_inline_t *buf;

	if (!xdr_clientid4(xdrs, &objp->clientid))
		return (FALSE);
	if (!xdr_verifier4(xdrs, objp->setclientid_confirm))
		return (FALSE);
	return (TRUE);
}

bool_t
xdr_SETCLIENTID4res(XDR *xdrs, SETCLIENTID4res *objp)
{

	rpc_inline_t *buf;

	if (!xdr_nfsstat4(xdrs, &objp->status))
		return (FALSE);
	switch (objp->status) {
	case NFS4_OK:
		if (!xdr_SETCLIENTID4resok(xdrs,
		    &objp->SETCLIENTID4res_u.resok4))
			return (FALSE);
		break;
	case NFS4ERR_CLID_INUSE:
		if (!xdr_clientaddr4(xdrs,
		    &objp->SETCLIENTID4res_u.client_using))
			return (FALSE);
		break;
	}
	return (TRUE);
}

bool_t
xdr_SETCLIENTID_CONFIRM4args(XDR *xdrs, SETCLIENTID_CONFIRM4args *objp)
{

	rpc_inline_t *buf;

	if (!xdr_clientid4(xdrs, &objp->clientid))
		return (FALSE);
	if (!xdr_verifier4(xdrs, objp->setclientid_confirm))
		return (FALSE);
	return (TRUE);
}

bool_t
xdr_SETCLIENTID_CONFIRM4res(XDR *xdrs, SETCLIENTID_CONFIRM4res *objp)
{

	rpc_inline_t *buf;

	if (!xdr_nfsstat4(xdrs, &objp->status))
		return (FALSE);
	return (TRUE);
}

bool_t
xdr_VERIFY4args(XDR *xdrs, VERIFY4args *objp)
{

	rpc_inline_t *buf;

	if (!xdr_fattr4(xdrs, &objp->obj_attributes))
		return (FALSE);
	return (TRUE);
}

bool_t
xdr_VERIFY4res(XDR *xdrs, VERIFY4res *objp)
{

	rpc_inline_t *buf;

	if (!xdr_nfsstat4(xdrs, &objp->status))
		return (FALSE);
	return (TRUE);
}

bool_t
xdr_stable_how4(XDR *xdrs, stable_how4 *objp)
{

	rpc_inline_t *buf;

	if (!xdr_enum(xdrs, (enum_t *)objp))
		return (FALSE);
	return (TRUE);
}

bool_t
xdr_WRITE4args(XDR *xdrs, WRITE4args *objp)
{

	rpc_inline_t *buf;

	if (!xdr_stateid4(xdrs, &objp->stateid))
		return (FALSE);
	if (!xdr_offset4(xdrs, &objp->offset))
		return (FALSE);
	if (!xdr_stable_how4(xdrs, &objp->stable))

#ifdef IGNORE_RDWR_DATA
	/*
	 * try to get length of write, and if that
	 * fails, default to 0.  Don't return FALSE
	 * because the other write info will not be
	 * displayed (write stateid).
	 */
	objp->data.data_val = NULL;
	if (!xdr_u_int(xdrs, &objp->data.data_len))
		objp->data.data_len = 0;
	nfs4_skip_bytes = objp->data.data_len;
#else
	if (!xdr_bytes(xdrs, (char **)&objp->data.data_val,
	    (uint_t *)&objp->data.data_len, ~0))
		return (FALSE);
#endif
	return (TRUE);
}

bool_t
xdr_WRITE4resok(XDR *xdrs, WRITE4resok *objp)
{

	rpc_inline_t *buf;

	if (!xdr_count4(xdrs, &objp->count))
		return (FALSE);
	if (!xdr_stable_how4(xdrs, &objp->committed))
		return (FALSE);
	if (!xdr_verifier4(xdrs, objp->writeverf))
		return (FALSE);
	return (TRUE);
}

bool_t
xdr_WRITE4res(XDR *xdrs, WRITE4res *objp)
{

	rpc_inline_t *buf;

	if (!xdr_nfsstat4(xdrs, &objp->status))
		return (FALSE);
	switch (objp->status) {
	case NFS4_OK:
		if (!xdr_WRITE4resok(xdrs, &objp->WRITE4res_u.resok4))
			return (FALSE);
		break;
	}
	return (TRUE);
}

bool_t
xdr_RELEASE_LOCKOWNER4args(XDR *xdrs, RELEASE_LOCKOWNER4args *objp)
{

	rpc_inline_t *buf;

	if (!xdr_lock_owner4(xdrs, &objp->lock_owner))
		return (FALSE);
	return (TRUE);
}

bool_t
xdr_RELEASE_LOCKOWNER4res(XDR *xdrs, RELEASE_LOCKOWNER4res *objp)
{

	rpc_inline_t *buf;

	if (!xdr_nfsstat4(xdrs, &objp->status))
		return (FALSE);
	return (TRUE);
}

bool_t
xdr_ILLEGAL4res(XDR *xdrs, ILLEGAL4res *objp)
{

	rpc_inline_t *buf;

	if (!xdr_nfsstat4(xdrs, &objp->status))
		return (FALSE);
	return (TRUE);
}

bool_t
xdr_gsshandle4_t(XDR *xdrs, gsshandle4_t *objp)
{

	rpc_inline_t *buf;

	if (!xdr_bytes(xdrs, (char **)&objp->gsshandle4_t_val,
	    (uint_t *)&objp->gsshandle4_t_len, ~0))
		return (FALSE);
	return (TRUE);
}

bool_t
xdr_gss_cb_handles4(XDR *xdrs, gss_cb_handles4 *objp)
{

	rpc_inline_t *buf;

	if (!xdr_rpc_gss_svc_t(xdrs, &objp->gcbp_service))
		return (FALSE);
	if (!xdr_gsshandle4_t(xdrs, &objp->gcbp_handle_from_server))
		return (FALSE);
	if (!xdr_gsshandle4_t(xdrs, &objp->gcbp_handle_from_client))
		return (FALSE);
	return (TRUE);
}

bool_t
xdr_callback_sec_parms4(XDR *xdrs, callback_sec_parms4 *objp)
{

	rpc_inline_t *buf;

	if (!xdr_uint32_t(xdrs, &objp->cb_secflavor))
		return (FALSE);
	switch (objp->cb_secflavor) {
	case AUTH_NONE:
		break;
	case AUTH_SYS:
		if (!xdr_authsys_parms(xdrs,
		    &objp->callback_sec_parms4_u.cbsp_sys_cred))
			return (FALSE);
		break;
	case RPCSEC_GSS:
		if (!xdr_gss_cb_handles4(xdrs,
		    &objp->callback_sec_parms4_u.cbsp_gss_handles))
			return (FALSE);
		break;
	default:
		return (FALSE);
	}
	return (TRUE);
}

bool_t
xdr_BACKCHANNEL_CTL4args(XDR *xdrs, BACKCHANNEL_CTL4args *objp)
{

	rpc_inline_t *buf;

	if (!xdr_uint32_t(xdrs, &objp->bca_cb_program))
		return (FALSE);
	if (!xdr_array(xdrs, (char **)&objp->bca_sec_parms.bca_sec_parms_val,
	    (uint_t *)&objp->bca_sec_parms.bca_sec_parms_len, ~0,
	    sizeof (callback_sec_parms4), (xdrproc_t)xdr_callback_sec_parms4))
		return (FALSE);
	return (TRUE);
}

bool_t
xdr_BACKCHANNEL_CTL4res(XDR *xdrs, BACKCHANNEL_CTL4res *objp)
{

	rpc_inline_t *buf;

	if (!xdr_nfsstat4(xdrs, &objp->bcr_status))
		return (FALSE);
	return (TRUE);
}

bool_t
xdr_channel_dir_from_client4(XDR *xdrs, channel_dir_from_client4 *objp)
{

	rpc_inline_t *buf;

	if (!xdr_enum(xdrs, (enum_t *)objp))
		return (FALSE);
	return (TRUE);
}

bool_t
xdr_BIND_CONN_TO_SESSION4args(XDR *xdrs, BIND_CONN_TO_SESSION4args *objp)
{

	rpc_inline_t *buf;

	if (!xdr_sessionid4(xdrs, objp->bctsa_sessid))
		return (FALSE);
	if (!xdr_channel_dir_from_client4(xdrs, &objp->bctsa_dir))
		return (FALSE);
	if (!xdr_bool(xdrs, &objp->bctsa_use_conn_in_rdma_mode))
		return (FALSE);
	return (TRUE);
}

bool_t
xdr_channel_dir_from_server4(XDR *xdrs, channel_dir_from_server4 *objp)
{

	rpc_inline_t *buf;

	if (!xdr_enum(xdrs, (enum_t *)objp))
		return (FALSE);
	return (TRUE);
}

bool_t
xdr_BIND_CONN_TO_SESSION4resok(XDR *xdrs, BIND_CONN_TO_SESSION4resok *objp)
{

	rpc_inline_t *buf;

	if (!xdr_sessionid4(xdrs, objp->bctsr_sessid))
		return (FALSE);
	if (!xdr_channel_dir_from_server4(xdrs, &objp->bctsr_dir))
		return (FALSE);
	if (!xdr_bool(xdrs, &objp->bctsr_use_conn_in_rdma_mode))
		return (FALSE);
	return (TRUE);
}

bool_t
xdr_BIND_CONN_TO_SESSION4res(XDR *xdrs, BIND_CONN_TO_SESSION4res *objp)
{

	rpc_inline_t *buf;

	if (!xdr_nfsstat4(xdrs, &objp->bctsr_status))
		return (FALSE);
	switch (objp->bctsr_status) {
	case NFS4_OK:
		if (!xdr_BIND_CONN_TO_SESSION4resok(xdrs,
		    &objp->BIND_CONN_TO_SESSION4res_u.bctsr_resok4))
			return (FALSE);
		break;
	}
	return (TRUE);
}

bool_t
xdr_state_protect_ops4(XDR *xdrs, state_protect_ops4 *objp)
{

	rpc_inline_t *buf;

	if (!xdr_bitmap4(xdrs, &objp->spo_must_enforce))
		return (FALSE);
	if (!xdr_bitmap4(xdrs, &objp->spo_must_allow))
		return (FALSE);
	return (TRUE);
}

bool_t
xdr_ssv_sp_parms4(XDR *xdrs, ssv_sp_parms4 *objp)
{

	rpc_inline_t *buf;

	if (!xdr_state_protect_ops4(xdrs, &objp->ssp_ops))
		return (FALSE);
	if (!xdr_array(xdrs,
	    (char **)&objp->ssp_hash_algs.ssp_hash_algs_val,
	    (uint_t *)&objp->ssp_hash_algs.ssp_hash_algs_len, ~0,
	    sizeof (sec_oid4), (xdrproc_t)xdr_sec_oid4))
		return (FALSE);
	if (!xdr_array(xdrs,
	    (char **)&objp->ssp_encr_algs.ssp_encr_algs_val,
	    (uint_t *)&objp->ssp_encr_algs.ssp_encr_algs_len, ~0,
	    sizeof (sec_oid4), (xdrproc_t)xdr_sec_oid4))
		return (FALSE);
	if (!xdr_uint32_t(xdrs, &objp->ssp_window))
		return (FALSE);
	if (!xdr_uint32_t(xdrs, &objp->ssp_num_gss_handles))
		return (FALSE);
	return (TRUE);
}

bool_t
xdr_state_protect_how4(XDR *xdrs, state_protect_how4 *objp)
{

	rpc_inline_t *buf;

	if (!xdr_enum(xdrs, (enum_t *)objp))
		return (FALSE);
	return (TRUE);
}

bool_t
xdr_state_protect4_a(XDR *xdrs, state_protect4_a *objp)
{

	rpc_inline_t *buf;

	if (!xdr_state_protect_how4(xdrs, &objp->spa_how))
		return (FALSE);
	switch (objp->spa_how) {
	case SP4_NONE:
		break;
	case SP4_MACH_CRED:
		if (!xdr_state_protect_ops4(xdrs,
		    &objp->state_protect4_a_u.spa_mach_ops))
			return (FALSE);
		break;
	case SP4_SSV:
		if (!xdr_ssv_sp_parms4(xdrs,
		    &objp->state_protect4_a_u.spa_ssv_parms))
			return (FALSE);
		break;
	default:
		return (FALSE);
	}
	return (TRUE);
}

bool_t
xdr_EXCHANGE_ID4args(XDR *xdrs, EXCHANGE_ID4args *objp)
{

	rpc_inline_t *buf;

	if (!xdr_client_owner4(xdrs, &objp->eia_clientowner))
		return (FALSE);
	if (!xdr_uint32_t(xdrs, &objp->eia_flags))
		return (FALSE);
	if (!xdr_state_protect4_a(xdrs, &objp->eia_state_protect))
		return (FALSE);
	if (!xdr_array(xdrs,
	    (char **)&objp->eia_client_impl_id.eia_client_impl_id_val,
	    (uint_t *)&objp->eia_client_impl_id.eia_client_impl_id_len, 1,
	    sizeof (nfs_impl_id4), (xdrproc_t)xdr_nfs_impl_id4))
		return (FALSE);
	return (TRUE);
}

bool_t
xdr_ssv_prot_info4(XDR *xdrs, ssv_prot_info4 *objp)
{

	rpc_inline_t *buf;

	if (!xdr_state_protect_ops4(xdrs, &objp->spi_ops))
		return (FALSE);
	if (!xdr_uint32_t(xdrs, &objp->spi_hash_alg))
		return (FALSE);
	if (!xdr_uint32_t(xdrs, &objp->spi_encr_alg))
		return (FALSE);
	if (!xdr_uint32_t(xdrs, &objp->spi_ssv_len))
		return (FALSE);
	if (!xdr_uint32_t(xdrs, &objp->spi_window))
		return (FALSE);
	if (!xdr_array(xdrs, (char **)&objp->spi_handles.spi_handles_val,
	    (uint_t *)&objp->spi_handles.spi_handles_len, ~0,
	    sizeof (gsshandle4_t), (xdrproc_t)xdr_gsshandle4_t))
		return (FALSE);
	return (TRUE);
}

bool_t
xdr_state_protect4_r(XDR *xdrs, state_protect4_r *objp)
{

	rpc_inline_t *buf;

	if (!xdr_state_protect_how4(xdrs, &objp->spr_how))
		return (FALSE);
	switch (objp->spr_how) {
	case SP4_NONE:
		break;
	case SP4_MACH_CRED:
		if (!xdr_state_protect_ops4(xdrs,
		    &objp->state_protect4_r_u.spr_mach_ops))
			return (FALSE);
		break;
	case SP4_SSV:
		if (!xdr_ssv_prot_info4(xdrs,
		    &objp->state_protect4_r_u.spr_ssv_info))
			return (FALSE);
		break;
	default:
		return (FALSE);
	}
	return (TRUE);
}

bool_t
xdr_EXCHANGE_ID4resok(XDR *xdrs, EXCHANGE_ID4resok *objp)
{

	rpc_inline_t *buf;

	if (!xdr_clientid4(xdrs, &objp->eir_clientid))
		return (FALSE);
	if (!xdr_sequenceid4(xdrs, &objp->eir_sequenceid))
		return (FALSE);
	if (!xdr_uint32_t(xdrs, &objp->eir_flags))
		return (FALSE);
	if (!xdr_state_protect4_r(xdrs, &objp->eir_state_protect))
		return (FALSE);
	if (!xdr_server_owner4(xdrs, &objp->eir_server_owner))
		return (FALSE);
	if (!xdr_bytes(xdrs,
	    (char **)&objp->eir_server_scope.eir_server_scope_val,
	    (uint_t *)&objp->eir_server_scope.eir_server_scope_len,
	    NFS4_OPAQUE_LIMIT))
		return (FALSE);
	if (!xdr_array(xdrs,
	    (char **)&objp->eir_server_impl_id.eir_server_impl_id_val,
	    (uint_t *)&objp->eir_server_impl_id.eir_server_impl_id_len, 1,
	    sizeof (nfs_impl_id4), (xdrproc_t)xdr_nfs_impl_id4))
		return (FALSE);
	return (TRUE);
}

bool_t
xdr_EXCHANGE_ID4res(XDR *xdrs, EXCHANGE_ID4res *objp)
{

	rpc_inline_t *buf;

	if (!xdr_nfsstat4(xdrs, &objp->eir_status))
		return (FALSE);
	switch (objp->eir_status) {
	case NFS4_OK:
		if (!xdr_EXCHANGE_ID4resok(xdrs,
		    &objp->EXCHANGE_ID4res_u.eir_resok4))
			return (FALSE);
		break;
	}
	return (TRUE);
}

bool_t
xdr_channel_attrs4(XDR *xdrs, channel_attrs4 *objp)
{

	rpc_inline_t *buf;

	if (!xdr_count4(xdrs, &objp->ca_headerpadsize))
		return (FALSE);
	if (!xdr_count4(xdrs, &objp->ca_maxrequestsize))
		return (FALSE);
	if (!xdr_count4(xdrs, &objp->ca_maxresponsesize))
		return (FALSE);
	if (!xdr_count4(xdrs, &objp->ca_maxresponsesize_cached))
		return (FALSE);
	if (!xdr_count4(xdrs, &objp->ca_maxoperations))
		return (FALSE);
	if (!xdr_count4(xdrs, &objp->ca_maxrequests))
		return (FALSE);
	if (!xdr_array(xdrs, (char **)&objp->ca_rdma_ird.ca_rdma_ird_val,
	    (uint_t *)&objp->ca_rdma_ird.ca_rdma_ird_len, 1,
	    sizeof (uint32_t), (xdrproc_t)xdr_uint32_t))
		return (FALSE);
	return (TRUE);
}

bool_t
xdr_CREATE_SESSION4args(XDR *xdrs, CREATE_SESSION4args *objp)
{

	rpc_inline_t *buf;

	if (!xdr_clientid4(xdrs, &objp->csa_clientid))
		return (FALSE);
	if (!xdr_sequenceid4(xdrs, &objp->csa_sequence))
		return (FALSE);
	if (!xdr_uint32_t(xdrs, &objp->csa_flags))
		return (FALSE);
	if (!xdr_channel_attrs4(xdrs, &objp->csa_fore_chan_attrs))
		return (FALSE);
	if (!xdr_channel_attrs4(xdrs, &objp->csa_back_chan_attrs))
		return (FALSE);
	if (!xdr_uint32_t(xdrs, &objp->csa_cb_program))
		return (FALSE);
	if (!xdr_array(xdrs, (char **)&objp->csa_sec_parms.csa_sec_parms_val,
	    (uint_t *)&objp->csa_sec_parms.csa_sec_parms_len, ~0,
	    sizeof (callback_sec_parms4), (xdrproc_t)xdr_callback_sec_parms4))
		return (FALSE);
	return (TRUE);
}

bool_t
xdr_CREATE_SESSION4resok(XDR *xdrs, CREATE_SESSION4resok *objp)
{

	rpc_inline_t *buf;

	if (!xdr_sessionid4(xdrs, objp->csr_sessionid))
		return (FALSE);
	if (!xdr_sequenceid4(xdrs, &objp->csr_sequence))
		return (FALSE);
	if (!xdr_uint32_t(xdrs, &objp->csr_flags))
		return (FALSE);
	if (!xdr_channel_attrs4(xdrs, &objp->csr_fore_chan_attrs))
		return (FALSE);
	if (!xdr_channel_attrs4(xdrs, &objp->csr_back_chan_attrs))
		return (FALSE);
	return (TRUE);
}

bool_t
xdr_CREATE_SESSION4res(XDR *xdrs, CREATE_SESSION4res *objp)
{

	rpc_inline_t *buf;

	if (!xdr_nfsstat4(xdrs, &objp->csr_status))
		return (FALSE);
	switch (objp->csr_status) {
	case NFS4_OK:
		if (!xdr_CREATE_SESSION4resok(xdrs,
		    &objp->CREATE_SESSION4res_u.csr_resok4))
			return (FALSE);
		break;
	}
	return (TRUE);
}

bool_t
xdr_DESTROY_SESSION4args(XDR *xdrs, DESTROY_SESSION4args *objp)
{

	rpc_inline_t *buf;

	if (!xdr_sessionid4(xdrs, objp->dsa_sessionid))
		return (FALSE);
	return (TRUE);
}

bool_t
xdr_DESTROY_SESSION4res(XDR *xdrs, DESTROY_SESSION4res *objp)
{

	rpc_inline_t *buf;

	if (!xdr_nfsstat4(xdrs, &objp->dsr_status))
		return (FALSE);
	return (TRUE);
}

bool_t
xdr_FREE_STATEID4args(XDR *xdrs, FREE_STATEID4args *objp)
{

	rpc_inline_t *buf;

	if (!xdr_stateid4(xdrs, &objp->fsa_stateid))
		return (FALSE);
	return (TRUE);
}

bool_t
xdr_FREE_STATEID4res(XDR *xdrs, FREE_STATEID4res *objp)
{

	rpc_inline_t *buf;

	if (!xdr_nfsstat4(xdrs, &objp->fsr_status))
		return (FALSE);
	return (TRUE);
}

bool_t
xdr_attr_notice4(XDR *xdrs, attr_notice4 *objp)
{

	rpc_inline_t *buf;

	if (!xdr_nfstime4(xdrs, objp))
		return (FALSE);
	return (TRUE);
}

bool_t
xdr_GET_DIR_DELEGATION4args(XDR *xdrs, GET_DIR_DELEGATION4args *objp)
{

	rpc_inline_t *buf;

	if (!xdr_bool(xdrs, &objp->gdda_signal_deleg_avail))
		return (FALSE);
	if (!xdr_bitmap4(xdrs, &objp->gdda_notification_types))
		return (FALSE);
	if (!xdr_attr_notice4(xdrs, &objp->gdda_child_attr_delay))
		return (FALSE);
	if (!xdr_attr_notice4(xdrs, &objp->gdda_dir_attr_delay))
		return (FALSE);
	if (!xdr_bitmap4(xdrs, &objp->gdda_child_attributes))
		return (FALSE);
	if (!xdr_bitmap4(xdrs, &objp->gdda_dir_attributes))
		return (FALSE);
	return (TRUE);
}

bool_t
xdr_GET_DIR_DELEGATION4resok(XDR *xdrs, GET_DIR_DELEGATION4resok *objp)
{

	rpc_inline_t *buf;

	if (!xdr_verifier4(xdrs, objp->gddr_cookieverf))
		return (FALSE);
	if (!xdr_stateid4(xdrs, &objp->gddr_stateid))
		return (FALSE);
	if (!xdr_bitmap4(xdrs, &objp->gddr_notification))
		return (FALSE);
	if (!xdr_bitmap4(xdrs, &objp->gddr_child_attributes))
		return (FALSE);
	if (!xdr_bitmap4(xdrs, &objp->gddr_dir_attributes))
		return (FALSE);
	return (TRUE);
}

bool_t
xdr_gddrnf4_status(XDR *xdrs, gddrnf4_status *objp)
{

	rpc_inline_t *buf;

	if (!xdr_enum(xdrs, (enum_t *)objp))
		return (FALSE);
	return (TRUE);
}

bool_t
xdr_GET_DIR_DELEGATION4res_non_fatal(XDR *xdrs,
    GET_DIR_DELEGATION4res_non_fatal *objp)
{

	rpc_inline_t *buf;

	if (!xdr_gddrnf4_status(xdrs, &objp->gddrnf_status))
		return (FALSE);
	switch (objp->gddrnf_status) {
	case GDD4_OK:
		if (!xdr_GET_DIR_DELEGATION4resok(xdrs,
		    &objp->GET_DIR_DELEGATION4res_non_fatal_u.gddrnf_resok4))
			return (FALSE);
		break;
	case GDD4_UNAVAIL:
		if (!xdr_bool(xdrs,
		    &objp->GET_DIR_DELEGATION4res_non_fatal_u.
		    gddrnf_will_signal_deleg_avail))
			return (FALSE);
		break;
	default:
		return (FALSE);
	}
	return (TRUE);
}

bool_t
xdr_GET_DIR_DELEGATION4res(XDR *xdrs, GET_DIR_DELEGATION4res *objp)
{

	rpc_inline_t *buf;

	if (!xdr_nfsstat4(xdrs, &objp->gddr_status))
		return (FALSE);
	switch (objp->gddr_status) {
	case NFS4_OK:
		if (!xdr_GET_DIR_DELEGATION4res_non_fatal(xdrs,
		    &objp->GET_DIR_DELEGATION4res_u.gddr_res_non_fatal4))
			return (FALSE);
		break;
	}
	return (TRUE);
}

bool_t
xdr_GETDEVICEINFO4args(XDR *xdrs, GETDEVICEINFO4args *objp)
{

	rpc_inline_t *buf;

	if (!xdr_deviceid4(xdrs, objp->gdia_device_id))
		return (FALSE);
	if (!xdr_layouttype4(xdrs, &objp->gdia_layout_type))
		return (FALSE);
	if (!xdr_count4(xdrs, &objp->gdia_maxcount))
		return (FALSE);
	if (!xdr_bitmap4(xdrs, &objp->gdia_notify_types))
		return (FALSE);
	return (TRUE);
}

bool_t
xdr_GETDEVICEINFO4resok(XDR *xdrs, GETDEVICEINFO4resok *objp)
{

	rpc_inline_t *buf;

	if (!xdr_device_addr4(xdrs, &objp->gdir_device_addr))
		return (FALSE);
	if (!xdr_bitmap4(xdrs, &objp->gdir_notification))
		return (FALSE);
	return (TRUE);
}

bool_t
xdr_GETDEVICEINFO4res(XDR *xdrs, GETDEVICEINFO4res *objp)
{

	rpc_inline_t *buf;

	if (!xdr_nfsstat4(xdrs, &objp->gdir_status))
		return (FALSE);
	switch (objp->gdir_status) {
	case NFS4_OK:
		if (!xdr_GETDEVICEINFO4resok(xdrs,
		    &objp->GETDEVICEINFO4res_u.gdir_resok4))
			return (FALSE);
		break;
	case NFS4ERR_TOOSMALL:
		if (!xdr_count4(xdrs, &objp->GETDEVICEINFO4res_u.gdir_mincount))
			return (FALSE);
		break;
	}
	return (TRUE);
}

bool_t
xdr_GETDEVICELIST4args(XDR *xdrs, GETDEVICELIST4args *objp)
{

	rpc_inline_t *buf;

	if (!xdr_layouttype4(xdrs, &objp->gdla_layout_type))
		return (FALSE);
	if (!xdr_count4(xdrs, &objp->gdla_maxdevices))
		return (FALSE);
	if (!xdr_nfs_cookie4(xdrs, &objp->gdla_cookie))
		return (FALSE);
	if (!xdr_verifier4(xdrs, objp->gdla_cookieverf))
		return (FALSE);
	return (TRUE);
}

bool_t
xdr_GETDEVICELIST4resok(XDR *xdrs, GETDEVICELIST4resok *objp)
{

	rpc_inline_t *buf;

	if (!xdr_nfs_cookie4(xdrs, &objp->gdlr_cookie))
		return (FALSE);
	if (!xdr_verifier4(xdrs, objp->gdlr_cookieverf))
		return (FALSE);
	if (!xdr_array(xdrs,
	    (char **)&objp->gdlr_deviceid_list.gdlr_deviceid_list_val,
	    (uint_t *)&objp->gdlr_deviceid_list.gdlr_deviceid_list_len, ~0,
	    sizeof (deviceid4), (xdrproc_t)xdr_deviceid4))
		return (FALSE);
	if (!xdr_bool(xdrs, &objp->gdlr_eof))
		return (FALSE);
	return (TRUE);
}

bool_t
xdr_GETDEVICELIST4res(XDR *xdrs, GETDEVICELIST4res *objp)
{

	rpc_inline_t *buf;

	if (!xdr_nfsstat4(xdrs, &objp->gdlr_status))
		return (FALSE);
	switch (objp->gdlr_status) {
	case NFS4_OK:
		if (!xdr_GETDEVICELIST4resok(xdrs,
		    &objp->GETDEVICELIST4res_u.gdlr_resok4))
			return (FALSE);
		break;
	}
	return (TRUE);
}

bool_t
xdr_newtime4(XDR *xdrs, newtime4 *objp)
{

	rpc_inline_t *buf;

	if (!xdr_bool(xdrs, &objp->nt_timechanged))
		return (FALSE);
	switch (objp->nt_timechanged) {
	case TRUE:
		if (!xdr_nfstime4(xdrs, &objp->newtime4_u.nt_time))
			return (FALSE);
		break;
	case FALSE:
		break;
	default:
		return (FALSE);
	}
	return (TRUE);
}

bool_t
xdr_newoffset4(XDR *xdrs, newoffset4 *objp)
{

	rpc_inline_t *buf;

	if (!xdr_bool(xdrs, &objp->no_newoffset))
		return (FALSE);
	switch (objp->no_newoffset) {
	case TRUE:
		if (!xdr_offset4(xdrs, &objp->newoffset4_u.no_offset))
			return (FALSE);
		break;
	case FALSE:
		break;
	default:
		return (FALSE);
	}
	return (TRUE);
}

bool_t
xdr_LAYOUTCOMMIT4args(XDR *xdrs, LAYOUTCOMMIT4args *objp)
{

	rpc_inline_t *buf;

	if (!xdr_offset4(xdrs, &objp->loca_offset))
		return (FALSE);
	if (!xdr_length4(xdrs, &objp->loca_length))
		return (FALSE);
	if (!xdr_bool(xdrs, &objp->loca_reclaim))
		return (FALSE);
	if (!xdr_stateid4(xdrs, &objp->loca_stateid))
		return (FALSE);
	if (!xdr_newoffset4(xdrs, &objp->loca_last_write_offset))
		return (FALSE);
	if (!xdr_newtime4(xdrs, &objp->loca_time_modify))
		return (FALSE);
	if (!xdr_layoutupdate4(xdrs, &objp->loca_layoutupdate))
		return (FALSE);
	return (TRUE);
}

bool_t
xdr_newsize4(XDR *xdrs, newsize4 *objp)
{

	rpc_inline_t *buf;

	if (!xdr_bool(xdrs, &objp->ns_sizechanged))
		return (FALSE);
	switch (objp->ns_sizechanged) {
	case TRUE:
		if (!xdr_length4(xdrs, &objp->newsize4_u.ns_size))
			return (FALSE);
		break;
	case FALSE:
		break;
	default:
		return (FALSE);
	}
	return (TRUE);
}

bool_t
xdr_LAYOUTCOMMIT4resok(XDR *xdrs, LAYOUTCOMMIT4resok *objp)
{

	rpc_inline_t *buf;

	if (!xdr_newsize4(xdrs, &objp->locr_newsize))
		return (FALSE);
	return (TRUE);
}

bool_t
xdr_LAYOUTCOMMIT4res(XDR *xdrs, LAYOUTCOMMIT4res *objp)
{

	rpc_inline_t *buf;

	if (!xdr_nfsstat4(xdrs, &objp->locr_status))
		return (FALSE);
	switch (objp->locr_status) {
	case NFS4_OK:
		if (!xdr_LAYOUTCOMMIT4resok(xdrs,
		    &objp->LAYOUTCOMMIT4res_u.locr_resok4))
			return (FALSE);
		break;
	}
	return (TRUE);
}

bool_t
xdr_LAYOUTGET4args(XDR *xdrs, LAYOUTGET4args *objp)
{

	rpc_inline_t *buf;

	if (!xdr_bool(xdrs, &objp->loga_signal_layout_avail))
		return (FALSE);
	if (!xdr_layouttype4(xdrs, &objp->loga_layout_type))
		return (FALSE);
	if (!xdr_layoutiomode4(xdrs, &objp->loga_iomode))
		return (FALSE);
	if (!xdr_offset4(xdrs, &objp->loga_offset))
		return (FALSE);
	if (!xdr_length4(xdrs, &objp->loga_length))
		return (FALSE);
	if (!xdr_length4(xdrs, &objp->loga_minlength))
		return (FALSE);
	if (!xdr_stateid4(xdrs, &objp->loga_stateid))
		return (FALSE);
	if (!xdr_count4(xdrs, &objp->loga_maxcount))
		return (FALSE);
	return (TRUE);
}

bool_t
xdr_LAYOUTGET4resok(XDR *xdrs, LAYOUTGET4resok *objp)
{

	rpc_inline_t *buf;

	if (!xdr_bool(xdrs, &objp->logr_return_on_close))
		return (FALSE);
	if (!xdr_stateid4(xdrs, &objp->logr_stateid))
		return (FALSE);
	if (!xdr_array(xdrs, (char **)&objp->logr_layout.logr_layout_val,
	    (uint_t *)&objp->logr_layout.logr_layout_len, ~0,
	    sizeof (layout4), (xdrproc_t)xdr_layout4))
		return (FALSE);
	return (TRUE);
}

bool_t
xdr_LAYOUTGET4res(XDR *xdrs, LAYOUTGET4res *objp)
{

	rpc_inline_t *buf;

	if (!xdr_nfsstat4(xdrs, &objp->logr_status))
		return (FALSE);
	switch (objp->logr_status) {
	case NFS4_OK:
		if (!xdr_LAYOUTGET4resok(xdrs,
		    &objp->LAYOUTGET4res_u.logr_resok4))
			return (FALSE);
		break;
	case NFS4ERR_LAYOUTTRYLATER:
		if (!xdr_bool(xdrs,
		    &objp->LAYOUTGET4res_u.logr_will_signal_layout_avail))
			return (FALSE);
		break;
	}
	return (TRUE);
}

bool_t
xdr_LAYOUTRETURN4args(XDR *xdrs, LAYOUTRETURN4args *objp)
{

	rpc_inline_t *buf;

	if (!xdr_bool(xdrs, &objp->lora_reclaim))
		return (FALSE);
	if (!xdr_layouttype4(xdrs, &objp->lora_layout_type))
		return (FALSE);
	if (!xdr_layoutiomode4(xdrs, &objp->lora_iomode))
		return (FALSE);
	if (!xdr_layoutreturn4(xdrs, &objp->lora_layoutreturn))
		return (FALSE);
	return (TRUE);
}

bool_t
xdr_layoutreturn_stateid(XDR *xdrs, layoutreturn_stateid *objp)
{

	rpc_inline_t *buf;

	if (!xdr_bool(xdrs, &objp->lrs_present))
		return (FALSE);
	switch (objp->lrs_present) {
	case TRUE:
		if (!xdr_stateid4(xdrs,
		    &objp->layoutreturn_stateid_u.lrs_stateid))
			return (FALSE);
		break;
	case FALSE:
		break;
	default:
		return (FALSE);
	}
	return (TRUE);
}

bool_t
xdr_LAYOUTRETURN4res(XDR *xdrs, LAYOUTRETURN4res *objp)
{

	rpc_inline_t *buf;

	if (!xdr_nfsstat4(xdrs, &objp->lorr_status))
		return (FALSE);
	switch (objp->lorr_status) {
	case NFS4_OK:
		if (!xdr_layoutreturn_stateid(xdrs,
		    &objp->LAYOUTRETURN4res_u.lorr_stateid))
			return (FALSE);
		break;
	}
	return (TRUE);
}

bool_t
xdr_secinfo_style4(XDR *xdrs, secinfo_style4 *objp)
{

	rpc_inline_t *buf;

	if (!xdr_enum(xdrs, (enum_t *)objp))
		return (FALSE);
	return (TRUE);
}

bool_t
xdr_SECINFO_NO_NAME4args(XDR *xdrs, SECINFO_NO_NAME4args *objp)
{

	rpc_inline_t *buf;

	if (!xdr_secinfo_style4(xdrs, objp))
		return (FALSE);
	return (TRUE);
}

bool_t
xdr_SECINFO_NO_NAME4res(XDR *xdrs, SECINFO_NO_NAME4res *objp)
{

	rpc_inline_t *buf;

	if (!xdr_SECINFO4res(xdrs, objp))
		return (FALSE);
	return (TRUE);
}

bool_t
xdr_SEQUENCE4args(XDR *xdrs, SEQUENCE4args *objp)
{

	rpc_inline_t *buf;

	if (!xdr_sessionid4(xdrs, objp->sa_sessionid))
		return (FALSE);
	if (!xdr_sequenceid4(xdrs, &objp->sa_sequenceid))
		return (FALSE);
	if (!xdr_slotid4(xdrs, &objp->sa_slotid))
		return (FALSE);
	if (!xdr_slotid4(xdrs, &objp->sa_highest_slotid))
		return (FALSE);
	if (!xdr_bool(xdrs, &objp->sa_cachethis))
		return (FALSE);
	return (TRUE);
}

bool_t
xdr_SEQUENCE4resok(XDR *xdrs, SEQUENCE4resok *objp)
{

	rpc_inline_t *buf;

	if (!xdr_sessionid4(xdrs, objp->sr_sessionid))
		return (FALSE);
	if (!xdr_sequenceid4(xdrs, &objp->sr_sequenceid))
		return (FALSE);
	if (!xdr_slotid4(xdrs, &objp->sr_slotid))
		return (FALSE);
	if (!xdr_slotid4(xdrs, &objp->sr_highest_slotid))
		return (FALSE);
	if (!xdr_slotid4(xdrs, &objp->sr_target_highest_slotid))
		return (FALSE);
	if (!xdr_uint32_t(xdrs, &objp->sr_status_flags))
		return (FALSE);
	return (TRUE);
}

bool_t
xdr_SEQUENCE4res(XDR *xdrs, SEQUENCE4res *objp)
{

	rpc_inline_t *buf;

	if (!xdr_nfsstat4(xdrs, &objp->sr_status))
		return (FALSE);
	switch (objp->sr_status) {
	case NFS4_OK:
		if (!xdr_SEQUENCE4resok(xdrs, &objp->SEQUENCE4res_u.sr_resok4))
			return (FALSE);
		break;
	}
	return (TRUE);
}

bool_t
xdr_ssa_digest_input4(XDR *xdrs, ssa_digest_input4 *objp)
{

	rpc_inline_t *buf;

	if (!xdr_SEQUENCE4args(xdrs, &objp->sdi_seqargs))
		return (FALSE);
	return (TRUE);
}

bool_t
xdr_SET_SSV4args(XDR *xdrs, SET_SSV4args *objp)
{

	rpc_inline_t *buf;

	if (!xdr_bytes(xdrs, (char **)&objp->ssa_ssv.ssa_ssv_val,
	    (uint_t *)&objp->ssa_ssv.ssa_ssv_len, ~0))
		return (FALSE);
	if (!xdr_bytes(xdrs, (char **)&objp->ssa_digest.ssa_digest_val,
	    (uint_t *)&objp->ssa_digest.ssa_digest_len, ~0))
		return (FALSE);
	return (TRUE);
}

bool_t
xdr_ssr_digest_input4(XDR *xdrs, ssr_digest_input4 *objp)
{

	rpc_inline_t *buf;

	if (!xdr_SEQUENCE4res(xdrs, &objp->sdi_seqres))
		return (FALSE);
	return (TRUE);
}

bool_t
xdr_SET_SSV4resok(XDR *xdrs, SET_SSV4resok *objp)
{

	rpc_inline_t *buf;

	if (!xdr_bytes(xdrs, (char **)&objp->ssr_digest.ssr_digest_val,
	    (uint_t *)&objp->ssr_digest.ssr_digest_len, ~0))
		return (FALSE);
	return (TRUE);
}

bool_t
xdr_SET_SSV4res(XDR *xdrs, SET_SSV4res *objp)
{

	rpc_inline_t *buf;

	if (!xdr_nfsstat4(xdrs, &objp->ssr_status))
		return (FALSE);
	switch (objp->ssr_status) {
	case NFS4_OK:
		if (!xdr_SET_SSV4resok(xdrs, &objp->SET_SSV4res_u.ssr_resok4))
			return (FALSE);
		break;
	}
	return (TRUE);
}

bool_t
xdr_TEST_STATEID4args(XDR *xdrs, TEST_STATEID4args *objp)
{

	rpc_inline_t *buf;

	if (!xdr_array(xdrs, (char **)&objp->ts_stateids.ts_stateids_val,
	    (uint_t *)&objp->ts_stateids.ts_stateids_len, ~0,
	    sizeof (stateid4), (xdrproc_t)xdr_stateid4))
		return (FALSE);
	return (TRUE);
}

bool_t
xdr_TEST_STATEID4resok(XDR *xdrs, TEST_STATEID4resok *objp)
{

	rpc_inline_t *buf;

	if (!xdr_array(xdrs,
	    (char **)&objp->tsr_status_codes.tsr_status_codes_val,
	    (uint_t *)&objp->tsr_status_codes.tsr_status_codes_len, ~0,
	    sizeof (nfsstat4), (xdrproc_t)xdr_nfsstat4))
		return (FALSE);
	return (TRUE);
}

bool_t
xdr_TEST_STATEID4res(XDR *xdrs, TEST_STATEID4res *objp)
{

	rpc_inline_t *buf;

	if (!xdr_nfsstat4(xdrs, &objp->tsr_status))
		return (FALSE);
	switch (objp->tsr_status) {
	case NFS4_OK:
		if (!xdr_TEST_STATEID4resok(xdrs,
		    &objp->TEST_STATEID4res_u.tsr_resok4))
			return (FALSE);
		break;
	}
	return (TRUE);
}

bool_t
xdr_deleg_claim4(XDR *xdrs, deleg_claim4 *objp)
{

	rpc_inline_t *buf;

	if (!xdr_open_claim_type4(xdrs, &objp->dc_claim))
		return (FALSE);
	switch (objp->dc_claim) {
	case CLAIM_FH:
		break;
	case CLAIM_DELEG_PREV_FH:
		break;
	case CLAIM_PREVIOUS:
		if (!xdr_open_delegation_type4(xdrs,
		    &objp->deleg_claim4_u.dc_delegate_type))
			return (FALSE);
		break;
	default:
		return (FALSE);
	}
	return (TRUE);
}

bool_t
xdr_WANT_DELEGATION4args(XDR *xdrs, WANT_DELEGATION4args *objp)
{

	rpc_inline_t *buf;

	if (!xdr_uint32_t(xdrs, &objp->wda_want))
		return (FALSE);
	if (!xdr_deleg_claim4(xdrs, &objp->wda_claim))
		return (FALSE);
	return (TRUE);
}

bool_t
xdr_WANT_DELEGATION4res(XDR *xdrs, WANT_DELEGATION4res *objp)
{

	rpc_inline_t *buf;

	if (!xdr_nfsstat4(xdrs, &objp->wdr_status))
		return (FALSE);
	switch (objp->wdr_status) {
	case NFS4_OK:
		if (!xdr_open_delegation4(xdrs,
		    &objp->WANT_DELEGATION4res_u.wdr_resok4))
			return (FALSE);
		break;
	}
	return (TRUE);
}

bool_t
xdr_DESTROY_CLIENTID4args(XDR *xdrs, DESTROY_CLIENTID4args *objp)
{

	rpc_inline_t *buf;

	if (!xdr_clientid4(xdrs, &objp->dca_clientid))
		return (FALSE);
	return (TRUE);
}

bool_t
xdr_DESTROY_CLIENTID4res(XDR *xdrs, DESTROY_CLIENTID4res *objp)
{

	rpc_inline_t *buf;

	if (!xdr_nfsstat4(xdrs, &objp->dcr_status))
		return (FALSE);
	return (TRUE);
}

bool_t
xdr_RECLAIM_COMPLETE4args(XDR *xdrs, RECLAIM_COMPLETE4args *objp)
{

	rpc_inline_t *buf;

	if (!xdr_bool(xdrs, &objp->rca_one_fs))
		return (FALSE);
	return (TRUE);
}

bool_t
xdr_RECLAIM_COMPLETE4res(XDR *xdrs, RECLAIM_COMPLETE4res *objp)
{

	rpc_inline_t *buf;

	if (!xdr_nfsstat4(xdrs, &objp->rcr_status))
		return (FALSE);
	return (TRUE);
}

/* new operations for NFSv4.1 */


bool_t
xdr_nfs_opnum4(XDR *xdrs, nfs_opnum4 *objp)
{

	rpc_inline_t *buf;

	if (!xdr_enum(xdrs, (enum_t *)objp))
		return (FALSE);
	return (TRUE);
}

bool_t
xdr_nfs_argop4(XDR *xdrs, nfs_argop4 *objp)
{
	nfs4_skip_bytes = 0;

	if (!xdr_nfs_opnum4(xdrs, &objp->argop))
		return (FALSE);
	switch (objp->argop) {
	case OP_ACCESS:
		if (!xdr_ACCESS4args(xdrs, &objp->nfs_argop4_u.opaccess))
			return (FALSE);
		break;
	case OP_CLOSE:
		if (!xdr_CLOSE4args(xdrs, &objp->nfs_argop4_u.opclose))
			return (FALSE);
		break;
	case OP_COMMIT:
		if (!xdr_COMMIT4args(xdrs, &objp->nfs_argop4_u.opcommit))
			return (FALSE);
		break;
	case OP_CREATE:
		if (!xdr_CREATE4args(xdrs, &objp->nfs_argop4_u.opcreate))
			return (FALSE);
		break;
	case OP_DELEGPURGE:
		if (!xdr_DELEGPURGE4args(xdrs,
		    &objp->nfs_argop4_u.opdelegpurge))
			return (FALSE);
		break;
	case OP_DELEGRETURN:
		if (!xdr_DELEGRETURN4args(xdrs,
		    &objp->nfs_argop4_u.opdelegreturn))
			return (FALSE);
		break;
	case OP_GETATTR:
		if (!xdr_GETATTR4args(xdrs, &objp->nfs_argop4_u.opgetattr))
			return (FALSE);
		break;
	case OP_GETFH:
		break;
	case OP_LINK:
		if (!xdr_LINK4args(xdrs, &objp->nfs_argop4_u.oplink))
			return (FALSE);
		break;
	case OP_LOCK:
		if (!xdr_LOCK4args(xdrs, &objp->nfs_argop4_u.oplock))
			return (FALSE);
		break;
	case OP_LOCKT:
		if (!xdr_LOCKT4args(xdrs, &objp->nfs_argop4_u.oplockt))
			return (FALSE);
		break;
	case OP_LOCKU:
		if (!xdr_LOCKU4args(xdrs, &objp->nfs_argop4_u.oplocku))
			return (FALSE);
		break;
	case OP_LOOKUP:
		if (!xdr_LOOKUP4args(xdrs, &objp->nfs_argop4_u.oplookup))
			return (FALSE);
		break;
	case OP_LOOKUPP:
		break;
	case OP_NVERIFY:
		if (!xdr_NVERIFY4args(xdrs,
		    &objp->nfs_argop4_u.opnverify))
			return (FALSE);
		break;
	case OP_OPEN:
		if (!xdr_OPEN4args(xdrs, &objp->nfs_argop4_u.opopen))
			return (FALSE);
		break;
	case OP_OPENATTR:
		if (!xdr_OPENATTR4args(xdrs,
		    &objp->nfs_argop4_u.opopenattr))
			return (FALSE);
		break;
	case OP_OPEN_CONFIRM:
		if (!xdr_OPEN_CONFIRM4args(xdrs,
		    &objp->nfs_argop4_u.opopen_confirm))
			return (FALSE);
		break;
	case OP_OPEN_DOWNGRADE:
		if (!xdr_OPEN_DOWNGRADE4args(xdrs,
		    &objp->nfs_argop4_u.opopen_downgrade))
			return (FALSE);
		break;
	case OP_PUTFH:
		if (!xdr_PUTFH4args(xdrs, &objp->nfs_argop4_u.opputfh))
			return (FALSE);
		break;
	case OP_PUTPUBFH:
		break;
	case OP_PUTROOTFH:
		break;
	case OP_READ:
		if (!xdr_READ4args(xdrs, &objp->nfs_argop4_u.opread))
			return (FALSE);
		break;
	case OP_READDIR:
		if (!xdr_READDIR4args(xdrs,
		    &objp->nfs_argop4_u.opreaddir))
			return (FALSE);
		break;
	case OP_READLINK:
		break;
	case OP_REMOVE:
		if (!xdr_REMOVE4args(xdrs, &objp->nfs_argop4_u.opremove))
			return (FALSE);
		break;
	case OP_RENAME:
		if (!xdr_RENAME4args(xdrs, &objp->nfs_argop4_u.oprename))
			return (FALSE);
		break;
	case OP_RENEW:
		if (!xdr_RENEW4args(xdrs, &objp->nfs_argop4_u.oprenew))
			return (FALSE);
		break;
	case OP_RESTOREFH:
		break;
	case OP_SAVEFH:
		break;
	case OP_SECINFO:
		if (!xdr_SECINFO4args(xdrs,
		    &objp->nfs_argop4_u.opsecinfo))
			return (FALSE);
		break;
	case OP_SETATTR:
		if (!xdr_SETATTR4args(xdrs,
		    &objp->nfs_argop4_u.opsetattr))
			return (FALSE);
		break;
	case OP_SETCLIENTID:
		if (!xdr_SETCLIENTID4args(xdrs,
		    &objp->nfs_argop4_u.opsetclientid))
			return (FALSE);
		break;
	case OP_SETCLIENTID_CONFIRM:
		if (!xdr_SETCLIENTID_CONFIRM4args(xdrs,
		    &objp->nfs_argop4_u.opsetclientid_confirm))
			return (FALSE);
		break;
	case OP_VERIFY:
		if (!xdr_VERIFY4args(xdrs, &objp->nfs_argop4_u.opverify))
			return (FALSE);
		break;
	case OP_WRITE:
		if (!xdr_WRITE4args(xdrs, &objp->nfs_argop4_u.opwrite))
			return (FALSE);
		break;
	case OP_RELEASE_LOCKOWNER:
		if (!xdr_RELEASE_LOCKOWNER4args(xdrs,
		    &objp->nfs_argop4_u.oprelease_lockowner))
			return (FALSE);
		break;
	case OP_BACKCHANNEL_CTL:
		if (!xdr_BACKCHANNEL_CTL4args(xdrs,
		    &objp->nfs_argop4_u.opbackchannel_ctl))
			return (FALSE);
		break;
	case OP_BIND_CONN_TO_SESSION:
		if (!xdr_BIND_CONN_TO_SESSION4args(xdrs,
		    &objp->nfs_argop4_u.opbind_conn_to_session))
			return (FALSE);
		break;
	case OP_EXCHANGE_ID:
		if (!xdr_EXCHANGE_ID4args(xdrs,
		    &objp->nfs_argop4_u.opexchange_id))
			return (FALSE);
		break;
	case OP_CREATE_SESSION:
		if (!xdr_CREATE_SESSION4args(xdrs,
		    &objp->nfs_argop4_u.opcreate_session))
			return (FALSE);
		break;
	case OP_DESTROY_SESSION:
		if (!xdr_DESTROY_SESSION4args(xdrs,
		    &objp->nfs_argop4_u.opdestroy_session))
			return (FALSE);
		break;
	case OP_FREE_STATEID:
		if (!xdr_FREE_STATEID4args(xdrs,
		    &objp->nfs_argop4_u.opfree_stateid))
			return (FALSE);
		break;
	case OP_GET_DIR_DELEGATION:
		if (!xdr_GET_DIR_DELEGATION4args(xdrs,
		    &objp->nfs_argop4_u.opget_dir_delegation))
			return (FALSE);
		break;
	case OP_GETDEVICEINFO:
		if (!xdr_GETDEVICEINFO4args(xdrs,
		    &objp->nfs_argop4_u.opgetdeviceinfo))
			return (FALSE);
		break;
	case OP_GETDEVICELIST:
		if (!xdr_GETDEVICELIST4args(xdrs,
		    &objp->nfs_argop4_u.opgetdevicelist))
			return (FALSE);
		break;
	case OP_LAYOUTCOMMIT:
		if (!xdr_LAYOUTCOMMIT4args(xdrs,
		    &objp->nfs_argop4_u.oplayoutcommit))
			return (FALSE);
		break;
	case OP_LAYOUTGET:
		if (!xdr_LAYOUTGET4args(xdrs,
		    &objp->nfs_argop4_u.oplayoutget))
			return (FALSE);
		break;
	case OP_LAYOUTRETURN:
		if (!xdr_LAYOUTRETURN4args(xdrs,
		    &objp->nfs_argop4_u.oplayoutreturn))
			return (FALSE);
		break;
	case OP_SECINFO_NO_NAME:
		if (!xdr_SECINFO_NO_NAME4args(xdrs,
		    &objp->nfs_argop4_u.opsecinfo_no_name))
			return (FALSE);
		break;
	case OP_SEQUENCE:
		if (!xdr_SEQUENCE4args(xdrs,
		    &objp->nfs_argop4_u.opsequence))
			return (FALSE);
		break;
	case OP_SET_SSV:
		if (!xdr_SET_SSV4args(xdrs,
		    &objp->nfs_argop4_u.opset_ssv))
			return (FALSE);
		break;
	case OP_TEST_STATEID:
		if (!xdr_TEST_STATEID4args(xdrs,
		    &objp->nfs_argop4_u.optest_stateid))
			return (FALSE);
		break;
	case OP_WANT_DELEGATION:
		if (!xdr_WANT_DELEGATION4args(xdrs,
		    &objp->nfs_argop4_u.opwant_delegation))
			return (FALSE);
		break;
	case OP_DESTROY_CLIENTID:
		if (!xdr_DESTROY_CLIENTID4args(xdrs,
		    &objp->nfs_argop4_u.opdestroy_clientid))
			return (FALSE);
		break;
	case OP_RECLAIM_COMPLETE:
		if (!xdr_RECLAIM_COMPLETE4args(xdrs,
		    &objp->nfs_argop4_u.opreclaim_complete))
			return (FALSE);
		break;
	case OP_ILLEGAL:
		break;
	default:
		return (FALSE);
	}
	return (TRUE);
}

bool_t
xdr_nfs_resop4(XDR *xdrs, nfs_resop4 *objp)
{
	nfs4_skip_bytes = 0;

	if (!xdr_nfs_opnum4(xdrs, &objp->resop))
		return (FALSE);
	switch (objp->resop) {
	case OP_ACCESS:
		if (!xdr_ACCESS4res(xdrs, &objp->nfs_resop4_u.opaccess))
			return (FALSE);
		break;
	case OP_CLOSE:
		if (!xdr_CLOSE4res(xdrs, &objp->nfs_resop4_u.opclose))
			return (FALSE);
		break;
	case OP_COMMIT:
		if (!xdr_COMMIT4res(xdrs, &objp->nfs_resop4_u.opcommit))
			return (FALSE);
		break;
	case OP_CREATE:
		if (!xdr_CREATE4res(xdrs, &objp->nfs_resop4_u.opcreate))
			return (FALSE);
		break;
	case OP_DELEGPURGE:
		if (!xdr_DELEGPURGE4res(xdrs,
		    &objp->nfs_resop4_u.opdelegpurge))
			return (FALSE);
		break;
	case OP_DELEGRETURN:
		if (!xdr_DELEGRETURN4res(xdrs,
		    &objp->nfs_resop4_u.opdelegreturn))
			return (FALSE);
		break;
	case OP_GETATTR:
		if (!xdr_GETATTR4res(xdrs, &objp->nfs_resop4_u.opgetattr))
			return (FALSE);
		break;
	case OP_GETFH:
		if (!xdr_GETFH4res(xdrs, &objp->nfs_resop4_u.opgetfh))
			return (FALSE);
		break;
	case OP_LINK:
		if (!xdr_LINK4res(xdrs, &objp->nfs_resop4_u.oplink))
			return (FALSE);
		break;
	case OP_LOCK:
		if (!xdr_LOCK4res(xdrs, &objp->nfs_resop4_u.oplock))
			return (FALSE);
		break;
	case OP_LOCKT:
		if (!xdr_LOCKT4res(xdrs, &objp->nfs_resop4_u.oplockt))
			return (FALSE);
		break;
	case OP_LOCKU:
		if (!xdr_LOCKU4res(xdrs, &objp->nfs_resop4_u.oplocku))
			return (FALSE);
		break;
	case OP_LOOKUP:
		if (!xdr_LOOKUP4res(xdrs, &objp->nfs_resop4_u.oplookup))
			return (FALSE);
		break;
	case OP_LOOKUPP:
		if (!xdr_LOOKUPP4res(xdrs,
		    &objp->nfs_resop4_u.oplookupp))
			return (FALSE);
		break;
	case OP_NVERIFY:
		if (!xdr_NVERIFY4res(xdrs,
		    &objp->nfs_resop4_u.opnverify))
			return (FALSE);
		break;
	case OP_OPEN:
		if (!xdr_OPEN4res(xdrs, &objp->nfs_resop4_u.opopen))
			return (FALSE);
		break;
	case OP_OPENATTR:
		if (!xdr_OPENATTR4res(xdrs,
		    &objp->nfs_resop4_u.opopenattr))
			return (FALSE);
		break;
	case OP_OPEN_CONFIRM:
		if (!xdr_OPEN_CONFIRM4res(xdrs,
		    &objp->nfs_resop4_u.opopen_confirm))
			return (FALSE);
		break;
	case OP_OPEN_DOWNGRADE:
		if (!xdr_OPEN_DOWNGRADE4res(xdrs,
		    &objp->nfs_resop4_u.opopen_downgrade))
			return (FALSE);
		break;
	case OP_PUTFH:
		if (!xdr_PUTFH4res(xdrs, &objp->nfs_resop4_u.opputfh))
			return (FALSE);
		break;
	case OP_PUTPUBFH:
		if (!xdr_PUTPUBFH4res(xdrs,
		    &objp->nfs_resop4_u.opputpubfh))
			return (FALSE);
		break;
	case OP_PUTROOTFH:
		if (!xdr_PUTROOTFH4res(xdrs,
		    &objp->nfs_resop4_u.opputrootfh))
			return (FALSE);
		break;
	case OP_READ:
		if (!xdr_READ4res(xdrs, &objp->nfs_resop4_u.opread))
			return (FALSE);
		break;
	case OP_READDIR:
		if (!xdr_READDIR4res(xdrs,
		    &objp->nfs_resop4_u.opreaddir))
			return (FALSE);
		break;
	case OP_READLINK:
		if (!xdr_READLINK4res(xdrs,
		    &objp->nfs_resop4_u.opreadlink))
			return (FALSE);
		break;
	case OP_REMOVE:
		if (!xdr_REMOVE4res(xdrs, &objp->nfs_resop4_u.opremove))
			return (FALSE);
		break;
	case OP_RENAME:
		if (!xdr_RENAME4res(xdrs, &objp->nfs_resop4_u.oprename))
			return (FALSE);
		break;
	case OP_RENEW:
		if (!xdr_RENEW4res(xdrs, &objp->nfs_resop4_u.oprenew))
			return (FALSE);
		break;
	case OP_RESTOREFH:
		if (!xdr_RESTOREFH4res(xdrs,
		    &objp->nfs_resop4_u.oprestorefh))
			return (FALSE);
		break;
	case OP_SAVEFH:
		if (!xdr_SAVEFH4res(xdrs, &objp->nfs_resop4_u.opsavefh))
			return (FALSE);
		break;
	case OP_SECINFO:
		if (!xdr_SECINFO4res(xdrs,
		    &objp->nfs_resop4_u.opsecinfo))
			return (FALSE);
		break;
	case OP_SETATTR:
		if (!xdr_SETATTR4res(xdrs,
		    &objp->nfs_resop4_u.opsetattr))
			return (FALSE);
		break;
	case OP_SETCLIENTID:
		if (!xdr_SETCLIENTID4res(xdrs,
		    &objp->nfs_resop4_u.opsetclientid))
			return (FALSE);
		break;
	case OP_SETCLIENTID_CONFIRM:
		if (!xdr_SETCLIENTID_CONFIRM4res(xdrs,
		    &objp->nfs_resop4_u.opsetclientid_confirm))
			return (FALSE);
		break;
	case OP_VERIFY:
		if (!xdr_VERIFY4res(xdrs, &objp->nfs_resop4_u.opverify))
			return (FALSE);
		break;
	case OP_WRITE:
		if (!xdr_WRITE4res(xdrs, &objp->nfs_resop4_u.opwrite))
			return (FALSE);
		break;
	case OP_RELEASE_LOCKOWNER:
		if (!xdr_RELEASE_LOCKOWNER4res(xdrs,
		    &objp->nfs_resop4_u.oprelease_lockowner))
			return (FALSE);
		break;
	case OP_BACKCHANNEL_CTL:
		if (!xdr_BACKCHANNEL_CTL4res(xdrs,
		    &objp->nfs_resop4_u.opbackchannel_ctl))
			return (FALSE);
		break;
	case OP_BIND_CONN_TO_SESSION:
		if (!xdr_BIND_CONN_TO_SESSION4res(xdrs,
		    &objp->nfs_resop4_u.opbind_conn_to_session))
			return (FALSE);
		break;
	case OP_EXCHANGE_ID:
		if (!xdr_EXCHANGE_ID4res(xdrs,
		    &objp->nfs_resop4_u.opexchange_id))
			return (FALSE);
		break;
	case OP_CREATE_SESSION:
		if (!xdr_CREATE_SESSION4res(xdrs,
		    &objp->nfs_resop4_u.opcreate_session))
			return (FALSE);
		break;
	case OP_DESTROY_SESSION:
		if (!xdr_DESTROY_SESSION4res(xdrs,
		    &objp->nfs_resop4_u.opdestroy_session))
			return (FALSE);
		break;
	case OP_FREE_STATEID:
		if (!xdr_FREE_STATEID4res(xdrs,
		    &objp->nfs_resop4_u.opfree_stateid))
			return (FALSE);
		break;
	case OP_GET_DIR_DELEGATION:
		if (!xdr_GET_DIR_DELEGATION4res(xdrs,
		    &objp->nfs_resop4_u.opget_dir_delegation))
			return (FALSE);
		break;
	case OP_GETDEVICEINFO:
		if (!xdr_GETDEVICEINFO4res(xdrs,
		    &objp->nfs_resop4_u.opgetdeviceinfo))
			return (FALSE);
		break;
	case OP_GETDEVICELIST:
		if (!xdr_GETDEVICELIST4res(xdrs,
		    &objp->nfs_resop4_u.opgetdevicelist))
			return (FALSE);
		break;
	case OP_LAYOUTCOMMIT:
		if (!xdr_LAYOUTCOMMIT4res(xdrs,
		    &objp->nfs_resop4_u.oplayoutcommit))
			return (FALSE);
		break;
	case OP_LAYOUTGET:
		if (!xdr_LAYOUTGET4res(xdrs,
		    &objp->nfs_resop4_u.oplayoutget))
			return (FALSE);
		break;
	case OP_LAYOUTRETURN:
		if (!xdr_LAYOUTRETURN4res(xdrs,
		    &objp->nfs_resop4_u.oplayoutreturn))
			return (FALSE);
		break;
	case OP_SECINFO_NO_NAME:
		if (!xdr_SECINFO_NO_NAME4res(xdrs,
		    &objp->nfs_resop4_u.opsecinfo_no_name))
			return (FALSE);
		break;
	case OP_SEQUENCE:
		if (!xdr_SEQUENCE4res(xdrs,
		    &objp->nfs_resop4_u.opsequence))
			return (FALSE);
		break;
	case OP_SET_SSV:
		if (!xdr_SET_SSV4res(xdrs,
		    &objp->nfs_resop4_u.opset_ssv))
			return (FALSE);
		break;
	case OP_TEST_STATEID:
		if (!xdr_TEST_STATEID4res(xdrs,
		    &objp->nfs_resop4_u.optest_stateid))
			return (FALSE);
		break;
	case OP_WANT_DELEGATION:
		if (!xdr_WANT_DELEGATION4res(xdrs,
		    &objp->nfs_resop4_u.opwant_delegation))
			return (FALSE);
		break;
	case OP_DESTROY_CLIENTID:
		if (!xdr_DESTROY_CLIENTID4res(xdrs,
		    &objp->nfs_resop4_u.opdestroy_clientid))
			return (FALSE);
		break;
	case OP_RECLAIM_COMPLETE:
		if (!xdr_RECLAIM_COMPLETE4res(xdrs,
		    &objp->nfs_resop4_u.opreclaim_complete))
			return (FALSE);
		break;
	case OP_ILLEGAL:
		if (!xdr_ILLEGAL4res(xdrs,
		    &objp->nfs_resop4_u.opillegal))
			return (FALSE);
		break;
	default:
		return (FALSE);
	}
	return (TRUE);
}

bool_t
xdr_COMPOUND4args(XDR *xdrs, COMPOUND4args *objp)
{

	rpc_inline_t *buf;

	if (!xdr_utf8str_cs(xdrs, &objp->tag))
		return (FALSE);
	if (!xdr_uint32_t(xdrs, &objp->minorversion))
		return (FALSE);
	if (!xdr_array(xdrs, (char **)&objp->argarray.argarray_val,
	    (uint_t *)&objp->argarray.argarray_len, ~0,
	    sizeof (nfs_argop4), (xdrproc_t)xdr_nfs_argop4))
		return (FALSE);
	return (TRUE);
}

bool_t
xdr_COMPOUND4res(XDR *xdrs, COMPOUND4res *objp)
{

	rpc_inline_t *buf;

	if (!xdr_nfsstat4(xdrs, &objp->status))
		return (FALSE);
	if (!xdr_utf8str_cs(xdrs, &objp->tag))
		return (FALSE);
	if (!xdr_array(xdrs, (char **)&objp->resarray.resarray_val,
	    (uint_t *)&objp->resarray.resarray_len, ~0,
	    sizeof (nfs_resop4), (xdrproc_t)xdr_nfs_resop4))
		return (FALSE);
	return (TRUE);
}

bool_t
xdr_CB_GETATTR4args(XDR *xdrs, CB_GETATTR4args *objp)
{

	rpc_inline_t *buf;

	if (!xdr_nfs_fh4(xdrs, &objp->fh))
		return (FALSE);
	if (!xdr_bitmap4(xdrs, &objp->attr_request))
		return (FALSE);
	return (TRUE);
}

bool_t
xdr_CB_GETATTR4resok(XDR *xdrs, CB_GETATTR4resok *objp)
{

	rpc_inline_t *buf;

	if (!xdr_fattr4(xdrs, &objp->obj_attributes))
		return (FALSE);
	return (TRUE);
}

bool_t
xdr_CB_GETATTR4res(XDR *xdrs, CB_GETATTR4res *objp)
{

	rpc_inline_t *buf;

	if (!xdr_nfsstat4(xdrs, &objp->status))
		return (FALSE);
	switch (objp->status) {
	case NFS4_OK:
		if (!xdr_CB_GETATTR4resok(xdrs, &objp->CB_GETATTR4res_u.resok4))
			return (FALSE);
		break;
	}
	return (TRUE);
}

bool_t
xdr_CB_RECALL4args(XDR *xdrs, CB_RECALL4args *objp)
{

	rpc_inline_t *buf;

	if (!xdr_stateid4(xdrs, &objp->stateid))
		return (FALSE);
	if (!xdr_bool(xdrs, &objp->truncate))
		return (FALSE);
	if (!xdr_nfs_fh4(xdrs, &objp->fh))
		return (FALSE);
	return (TRUE);
}

bool_t
xdr_CB_RECALL4res(XDR *xdrs, CB_RECALL4res *objp)
{

	rpc_inline_t *buf;

	if (!xdr_nfsstat4(xdrs, &objp->status))
		return (FALSE);
	return (TRUE);
}

bool_t
xdr_CB_ILLEGAL4res(XDR *xdrs, CB_ILLEGAL4res *objp)
{

	rpc_inline_t *buf;

	if (!xdr_nfsstat4(xdrs, &objp->status))
		return (FALSE);
	return (TRUE);
}

bool_t
xdr_layoutrecall_type4(XDR *xdrs, layoutrecall_type4 *objp)
{

	rpc_inline_t *buf;

	if (!xdr_enum(xdrs, (enum_t *)objp))
		return (FALSE);
	return (TRUE);
}

bool_t
xdr_layoutrecall_file4(XDR *xdrs, layoutrecall_file4 *objp)
{

	rpc_inline_t *buf;

	if (!xdr_nfs_fh4(xdrs, &objp->lor_fh))
		return (FALSE);
	if (!xdr_offset4(xdrs, &objp->lor_offset))
		return (FALSE);
	if (!xdr_length4(xdrs, &objp->lor_length))
		return (FALSE);
	if (!xdr_stateid4(xdrs, &objp->lor_stateid))
		return (FALSE);
	return (TRUE);
}

bool_t
xdr_layoutrecall4(XDR *xdrs, layoutrecall4 *objp)
{

	rpc_inline_t *buf;

	if (!xdr_layoutrecall_type4(xdrs, &objp->lor_recalltype))
		return (FALSE);
	switch (objp->lor_recalltype) {
	case LAYOUTRECALL4_FILE:
		if (!xdr_layoutrecall_file4(xdrs,
		    &objp->layoutrecall4_u.lor_layout))
			return (FALSE);
		break;
	case LAYOUTRECALL4_FSID:
		if (!xdr_fsid4(xdrs, &objp->layoutrecall4_u.lor_fsid))
			return (FALSE);
		break;
	case LAYOUTRECALL4_ALL:
		break;
	default:
		return (FALSE);
	}
	return (TRUE);
}

bool_t
xdr_CB_LAYOUTRECALL4args(XDR *xdrs, CB_LAYOUTRECALL4args *objp)
{

	rpc_inline_t *buf;

	if (!xdr_layouttype4(xdrs, &objp->clora_type))
		return (FALSE);
	if (!xdr_layoutiomode4(xdrs, &objp->clora_iomode))
		return (FALSE);
	if (!xdr_bool(xdrs, &objp->clora_changed))
		return (FALSE);
	if (!xdr_layoutrecall4(xdrs, &objp->clora_recall))
		return (FALSE);
	return (TRUE);
}

bool_t
xdr_CB_LAYOUTRECALL4res(XDR *xdrs, CB_LAYOUTRECALL4res *objp)
{

	rpc_inline_t *buf;

	if (!xdr_nfsstat4(xdrs, &objp->clorr_status))
		return (FALSE);
	return (TRUE);
}

bool_t
xdr_notify_type4(XDR *xdrs, notify_type4 *objp)
{

	rpc_inline_t *buf;

	if (!xdr_enum(xdrs, (enum_t *)objp))
		return (FALSE);
	return (TRUE);
}

bool_t
xdr_notify_entry4(XDR *xdrs, notify_entry4 *objp)
{

	rpc_inline_t *buf;

	if (!xdr_component4(xdrs, &objp->ne_file))
		return (FALSE);
	if (!xdr_fattr4(xdrs, &objp->ne_attrs))
		return (FALSE);
	return (TRUE);
}

bool_t
xdr_prev_entry4(XDR *xdrs, prev_entry4 *objp)
{

	rpc_inline_t *buf;

	if (!xdr_notify_entry4(xdrs, &objp->pe_prev_entry))
		return (FALSE);
	if (!xdr_nfs_cookie4(xdrs, &objp->pe_prev_entry_cookie))
		return (FALSE);
	return (TRUE);
}

bool_t
xdr_notify_remove4(XDR *xdrs, notify_remove4 *objp)
{

	rpc_inline_t *buf;

	if (!xdr_notify_entry4(xdrs, &objp->nrm_old_entry))
		return (FALSE);
	if (!xdr_nfs_cookie4(xdrs, &objp->nrm_old_entry_cookie))
		return (FALSE);
	return (TRUE);
}

bool_t
xdr_notify_add4(XDR *xdrs, notify_add4 *objp)
{

	rpc_inline_t *buf;

	if (!xdr_array(xdrs, (char **)&objp->nad_old_entry.nad_old_entry_val,
	    (uint_t *)&objp->nad_old_entry.nad_old_entry_len, 1,
	    sizeof (notify_remove4), (xdrproc_t)xdr_notify_remove4))
		return (FALSE);
	if (!xdr_notify_entry4(xdrs, &objp->nad_new_entry))
		return (FALSE);
	if (!xdr_array(xdrs,
	    (char **)&objp->nad_new_entry_cookie.nad_new_entry_cookie_val,
	    (uint_t *)&objp->nad_new_entry_cookie.nad_new_entry_cookie_len, 1,
	    sizeof (nfs_cookie4), (xdrproc_t)xdr_nfs_cookie4))
		return (FALSE);
	if (!xdr_array(xdrs, (char **)&objp->nad_prev_entry.nad_prev_entry_val,
	    (uint_t *)&objp->nad_prev_entry.nad_prev_entry_len, 1,
	    sizeof (prev_entry4), (xdrproc_t)xdr_prev_entry4))
		return (FALSE);
	if (!xdr_bool(xdrs, &objp->nad_last_entry))
		return (FALSE);
	return (TRUE);
}

bool_t
xdr_notify_attr4(XDR *xdrs, notify_attr4 *objp)
{

	rpc_inline_t *buf;

	if (!xdr_notify_entry4(xdrs, &objp->na_changed_entry))
		return (FALSE);
	return (TRUE);
}

bool_t
xdr_notify_rename4(XDR *xdrs, notify_rename4 *objp)
{

	rpc_inline_t *buf;

	if (!xdr_notify_remove4(xdrs, &objp->nrn_old_entry))
		return (FALSE);
	if (!xdr_notify_add4(xdrs, &objp->nrn_new_entry))
		return (FALSE);
	return (TRUE);
}

bool_t
xdr_notify_verifier4(XDR *xdrs, notify_verifier4 *objp)
{

	rpc_inline_t *buf;

	if (!xdr_verifier4(xdrs, objp->nv_old_cookieverf))
		return (FALSE);
	if (!xdr_verifier4(xdrs, objp->nv_new_cookieverf))
		return (FALSE);
	return (TRUE);
}

bool_t
xdr_notifylist4(XDR *xdrs, notifylist4 *objp)
{

	rpc_inline_t *buf;

	if (!xdr_bytes(xdrs, (char **)&objp->notifylist4_val,
	    (uint_t *)&objp->notifylist4_len, ~0))
		return (FALSE);
	return (TRUE);
}

bool_t
xdr_notify4(XDR *xdrs, notify4 *objp)
{

	rpc_inline_t *buf;

	if (!xdr_bitmap4(xdrs, &objp->notify_mask))
		return (FALSE);
	if (!xdr_notifylist4(xdrs, &objp->notify_vals))
		return (FALSE);
	return (TRUE);
}

bool_t
xdr_CB_NOTIFY4args(XDR *xdrs, CB_NOTIFY4args *objp)
{

	rpc_inline_t *buf;

	if (!xdr_stateid4(xdrs, &objp->cna_stateid))
		return (FALSE);
	if (!xdr_nfs_fh4(xdrs, &objp->cna_fh))
		return (FALSE);
	if (!xdr_array(xdrs, (char **)&objp->cna_changes.cna_changes_val,
	    (uint_t *)&objp->cna_changes.cna_changes_len, ~0,
	    sizeof (notify4), (xdrproc_t)xdr_notify4))
		return (FALSE);
	return (TRUE);
}

bool_t
xdr_CB_NOTIFY4res(XDR *xdrs, CB_NOTIFY4res *objp)
{

	rpc_inline_t *buf;

	if (!xdr_nfsstat4(xdrs, &objp->cnr_status))
		return (FALSE);
	return (TRUE);
}

bool_t
xdr_CB_PUSH_DELEG4args(XDR *xdrs, CB_PUSH_DELEG4args *objp)
{

	rpc_inline_t *buf;

	if (!xdr_nfs_fh4(xdrs, &objp->cpda_fh))
		return (FALSE);
	if (!xdr_open_delegation4(xdrs, &objp->cpda_delegation))
		return (FALSE);
	return (TRUE);
}

bool_t
xdr_CB_PUSH_DELEG4res(XDR *xdrs, CB_PUSH_DELEG4res *objp)
{

	rpc_inline_t *buf;

	if (!xdr_nfsstat4(xdrs, &objp->cpdr_status))
		return (FALSE);
	return (TRUE);
}

bool_t
xdr_CB_RECALL_ANY4args(XDR *xdrs, CB_RECALL_ANY4args *objp)
{

	rpc_inline_t *buf;

	if (!xdr_uint32_t(xdrs, &objp->craa_objects_to_keep))
		return (FALSE);
	if (!xdr_bitmap4(xdrs, &objp->craa_type_mask))
		return (FALSE);
	return (TRUE);
}

bool_t
xdr_CB_RECALL_ANY4res(XDR *xdrs, CB_RECALL_ANY4res *objp)
{

	rpc_inline_t *buf;

	if (!xdr_nfsstat4(xdrs, &objp->crar_status))
		return (FALSE);
	return (TRUE);
}

bool_t
xdr_CB_RECALLABLE_OBJ_AVAIL4args(XDR *xdrs, CB_RECALLABLE_OBJ_AVAIL4args *objp)
{

	rpc_inline_t *buf;

	if (!xdr_CB_RECALL_ANY4args(xdrs, objp))
		return (FALSE);
	return (TRUE);
}

bool_t
xdr_CB_RECALLABLE_OBJ_AVAIL4res(XDR *xdrs, CB_RECALLABLE_OBJ_AVAIL4res *objp)
{

	rpc_inline_t *buf;

	if (!xdr_nfsstat4(xdrs, &objp->croa_status))
		return (FALSE);
	return (TRUE);
}

bool_t
xdr_CB_RECALL_SLOT4args(XDR *xdrs, CB_RECALL_SLOT4args *objp)
{

	rpc_inline_t *buf;

	if (!xdr_slotid4(xdrs, &objp->rsa_target_highest_slotid))
		return (FALSE);
	return (TRUE);
}

bool_t
xdr_CB_RECALL_SLOT4res(XDR *xdrs, CB_RECALL_SLOT4res *objp)
{

	rpc_inline_t *buf;

	if (!xdr_nfsstat4(xdrs, &objp->rsr_status))
		return (FALSE);
	return (TRUE);
}

bool_t
xdr_referring_call4(XDR *xdrs, referring_call4 *objp)
{

	rpc_inline_t *buf;

	if (!xdr_sequenceid4(xdrs, &objp->rc_sequenceid))
		return (FALSE);
	if (!xdr_slotid4(xdrs, &objp->rc_slotid))
		return (FALSE);
	return (TRUE);
}

bool_t
xdr_referring_call_list4(XDR *xdrs, referring_call_list4 *objp)
{

	rpc_inline_t *buf;

	if (!xdr_sessionid4(xdrs, objp->rcl_sessionid))
		return (FALSE);
	if (!xdr_array(xdrs,
	    (char **)&objp->rcl_referring_calls.rcl_referring_calls_val,
	    (uint_t *)&objp->rcl_referring_calls.rcl_referring_calls_len, ~0,
	    sizeof (referring_call4), (xdrproc_t)xdr_referring_call4))
		return (FALSE);
	return (TRUE);
}

bool_t
xdr_CB_SEQUENCE4args(XDR *xdrs, CB_SEQUENCE4args *objp)
{

	rpc_inline_t *buf;

	if (!xdr_sessionid4(xdrs, objp->csa_sessionid))
		return (FALSE);
	if (!xdr_sequenceid4(xdrs, &objp->csa_sequenceid))
		return (FALSE);
	if (!xdr_slotid4(xdrs, &objp->csa_slotid))
		return (FALSE);
	if (!xdr_slotid4(xdrs, &objp->csa_highest_slotid))
		return (FALSE);
	if (!xdr_bool(xdrs, &objp->csa_cachethis))
		return (FALSE);
	if (!xdr_array(xdrs,
	    (char **)&objp->csa_referring_call_lists.
	    csa_referring_call_lists_val,
	    (uint_t *)&objp->csa_referring_call_lists.
	    csa_referring_call_lists_len,
	    ~0,
	    sizeof (referring_call_list4), (xdrproc_t)xdr_referring_call_list4))
		return (FALSE);
	return (TRUE);
}

bool_t
xdr_CB_SEQUENCE4resok(XDR *xdrs, CB_SEQUENCE4resok *objp)
{

	rpc_inline_t *buf;

	if (!xdr_sessionid4(xdrs, objp->csr_sessionid))
		return (FALSE);
	if (!xdr_sequenceid4(xdrs, &objp->csr_sequenceid))
		return (FALSE);
	if (!xdr_slotid4(xdrs, &objp->csr_slotid))
		return (FALSE);
	if (!xdr_slotid4(xdrs, &objp->csr_highest_slotid))
		return (FALSE);
	if (!xdr_slotid4(xdrs, &objp->csr_target_highest_slotid))
		return (FALSE);
	return (TRUE);
}

bool_t
xdr_CB_SEQUENCE4res(XDR *xdrs, CB_SEQUENCE4res *objp)
{

	rpc_inline_t *buf;

	if (!xdr_nfsstat4(xdrs, &objp->csr_status))
		return (FALSE);
	switch (objp->csr_status) {
	case NFS4_OK:
		if (!xdr_CB_SEQUENCE4resok(xdrs,
		    &objp->CB_SEQUENCE4res_u.csr_resok4))
			return (FALSE);
		break;
	}
	return (TRUE);
}

bool_t
xdr_CB_WANTS_CANCELLED4args(XDR *xdrs, CB_WANTS_CANCELLED4args *objp)
{

	rpc_inline_t *buf;

	if (!xdr_bool(xdrs, &objp->cwca_contended_wants_cancelled))
		return (FALSE);
	if (!xdr_bool(xdrs, &objp->cwca_resourced_wants_cancelled))
		return (FALSE);
	return (TRUE);
}

bool_t
xdr_CB_WANTS_CANCELLED4res(XDR *xdrs, CB_WANTS_CANCELLED4res *objp)
{

	rpc_inline_t *buf;

	if (!xdr_nfsstat4(xdrs, &objp->cwcr_status))
		return (FALSE);
	return (TRUE);
}

bool_t
xdr_CB_NOTIFY_LOCK4args(XDR *xdrs, CB_NOTIFY_LOCK4args *objp)
{

	rpc_inline_t *buf;

	if (!xdr_nfs_fh4(xdrs, &objp->cnla_fh))
		return (FALSE);
	if (!xdr_lock_owner4(xdrs, &objp->cnla_lock_owner))
		return (FALSE);
	return (TRUE);
}

bool_t
xdr_CB_NOTIFY_LOCK4res(XDR *xdrs, CB_NOTIFY_LOCK4res *objp)
{

	rpc_inline_t *buf;

	if (!xdr_nfsstat4(xdrs, &objp->cnlr_status))
		return (FALSE);
	return (TRUE);
}

bool_t
xdr_notify_deviceid_type4(XDR *xdrs, notify_deviceid_type4 *objp)
{

	rpc_inline_t *buf;

	if (!xdr_enum(xdrs, (enum_t *)objp))
		return (FALSE);
	return (TRUE);
}

bool_t
xdr_notify_deviceid_delete4(XDR *xdrs, notify_deviceid_delete4 *objp)
{

	rpc_inline_t *buf;

	if (!xdr_layouttype4(xdrs, &objp->ndd_layouttype))
		return (FALSE);
	if (!xdr_deviceid4(xdrs, objp->ndd_deviceid))
		return (FALSE);
	return (TRUE);
}

bool_t
xdr_notify_deviceid_change4(XDR *xdrs, notify_deviceid_change4 *objp)
{

	rpc_inline_t *buf;

	if (!xdr_layouttype4(xdrs, &objp->ndc_layouttype))
		return (FALSE);
	if (!xdr_deviceid4(xdrs, objp->ndc_deviceid))
		return (FALSE);
	if (!xdr_bool(xdrs, &objp->ndc_immediate))
		return (FALSE);
	return (TRUE);
}

bool_t
xdr_CB_NOTIFY_DEVICEID4args(XDR *xdrs, CB_NOTIFY_DEVICEID4args *objp)
{

	rpc_inline_t *buf;

	if (!xdr_array(xdrs, (char **)&objp->cnda_changes.cnda_changes_val,
	    (uint_t *)&objp->cnda_changes.cnda_changes_len, ~0,
	    sizeof (notify4), (xdrproc_t)xdr_notify4))
		return (FALSE);
	return (TRUE);
}

bool_t
xdr_CB_NOTIFY_DEVICEID4res(XDR *xdrs, CB_NOTIFY_DEVICEID4res *objp)
{

	rpc_inline_t *buf;

	if (!xdr_nfsstat4(xdrs, &objp->cndr_status))
		return (FALSE);
	return (TRUE);
}

/* Callback operations new to NFSv4.1 */

bool_t
xdr_nfs_cb_opnum4(XDR *xdrs, nfs_cb_opnum4 *objp)
{

	rpc_inline_t *buf;

	if (!xdr_enum(xdrs, (enum_t *)objp))
		return (FALSE);
	return (TRUE);
}

bool_t
xdr_nfs_cb_argop4(XDR *xdrs, nfs_cb_argop4 *objp)
{

	rpc_inline_t *buf;

	if (!xdr_u_int(xdrs, &objp->argop))
		return (FALSE);
	switch (objp->argop) {
	case OP_CB_GETATTR:
		if (!xdr_CB_GETATTR4args(xdrs,
		    &objp->nfs_cb_argop4_u.opcbgetattr))
			return (FALSE);
		break;
	case OP_CB_RECALL:
		if (!xdr_CB_RECALL4args(xdrs,
		    &objp->nfs_cb_argop4_u.opcbrecall))
			return (FALSE);
		break;
	case OP_CB_LAYOUTRECALL:
		if (!xdr_CB_LAYOUTRECALL4args(xdrs,
		    &objp->nfs_cb_argop4_u.opcblayoutrecall))
			return (FALSE);
		break;
	case OP_CB_NOTIFY:
		if (!xdr_CB_NOTIFY4args(xdrs,
		    &objp->nfs_cb_argop4_u.opcbnotify))
			return (FALSE);
		break;
	case OP_CB_PUSH_DELEG:
		if (!xdr_CB_PUSH_DELEG4args(xdrs,
		    &objp->nfs_cb_argop4_u.opcbpush_deleg))
			return (FALSE);
		break;
	case OP_CB_RECALL_ANY:
		if (!xdr_CB_RECALL_ANY4args(xdrs,
		    &objp->nfs_cb_argop4_u.opcbrecall_any))
			return (FALSE);
		break;
	case OP_CB_RECALLABLE_OBJ_AVAIL:
		if (!xdr_CB_RECALLABLE_OBJ_AVAIL4args(xdrs,
		    &objp->nfs_cb_argop4_u.opcbrecallable_obj_avail))
			return (FALSE);
		break;
	case OP_CB_RECALL_SLOT:
		if (!xdr_CB_RECALL_SLOT4args(xdrs,
		    &objp->nfs_cb_argop4_u.opcbrecall_slot))
			return (FALSE);
		break;
	case OP_CB_SEQUENCE:
		if (!xdr_CB_SEQUENCE4args(xdrs,
		    &objp->nfs_cb_argop4_u.opcbsequence))
			return (FALSE);
		break;
	case OP_CB_WANTS_CANCELLED:
		if (!xdr_CB_WANTS_CANCELLED4args(xdrs,
		    &objp->nfs_cb_argop4_u.opcbwants_cancelled))
			return (FALSE);
		break;
	case OP_CB_NOTIFY_LOCK:
		if (!xdr_CB_NOTIFY_LOCK4args(xdrs,
		    &objp->nfs_cb_argop4_u.opcbnotify_lock))
			return (FALSE);
		break;
	case OP_CB_NOTIFY_DEVICEID:
		if (!xdr_CB_NOTIFY_DEVICEID4args(xdrs,
		    &objp->nfs_cb_argop4_u.opcbnotify_deviceid))
			return (FALSE);
		break;
	case OP_CB_ILLEGAL:
		break;
	default:
		return (FALSE);
	}
	return (TRUE);
}

bool_t
xdr_nfs_cb_resop4(XDR *xdrs, nfs_cb_resop4 *objp)
{

	rpc_inline_t *buf;

	if (!xdr_u_int(xdrs, &objp->resop))
		return (FALSE);
	switch (objp->resop) {
	case OP_CB_GETATTR:
		if (!xdr_CB_GETATTR4res(xdrs,
		    &objp->nfs_cb_resop4_u.opcbgetattr))
			return (FALSE);
		break;
	case OP_CB_RECALL:
		if (!xdr_CB_RECALL4res(xdrs,
		    &objp->nfs_cb_resop4_u.opcbrecall))
			return (FALSE);
		break;
	case OP_CB_LAYOUTRECALL:
		if (!xdr_CB_LAYOUTRECALL4res(xdrs,
		    &objp->nfs_cb_resop4_u.opcblayoutrecall))
			return (FALSE);
		break;
	case OP_CB_NOTIFY:
		if (!xdr_CB_NOTIFY4res(xdrs,
		    &objp->nfs_cb_resop4_u.opcbnotify))
			return (FALSE);
		break;
	case OP_CB_PUSH_DELEG:
		if (!xdr_CB_PUSH_DELEG4res(xdrs,
		    &objp->nfs_cb_resop4_u.opcbpush_deleg))
			return (FALSE);
		break;
	case OP_CB_RECALL_ANY:
		if (!xdr_CB_RECALL_ANY4res(xdrs,
		    &objp->nfs_cb_resop4_u.opcbrecall_any))
			return (FALSE);
		break;
	case OP_CB_RECALLABLE_OBJ_AVAIL:
		if (!xdr_CB_RECALLABLE_OBJ_AVAIL4res(xdrs,
		    &objp->nfs_cb_resop4_u.opcbrecallable_obj_avail))
			return (FALSE);
		break;
	case OP_CB_RECALL_SLOT:
		if (!xdr_CB_RECALL_SLOT4res(xdrs,
		    &objp->nfs_cb_resop4_u.opcbrecall_slot))
			return (FALSE);
		break;
	case OP_CB_SEQUENCE:
		if (!xdr_CB_SEQUENCE4res(xdrs,
		    &objp->nfs_cb_resop4_u.opcbsequence))
			return (FALSE);
		break;
	case OP_CB_WANTS_CANCELLED:
		if (!xdr_CB_WANTS_CANCELLED4res(xdrs,
		    &objp->nfs_cb_resop4_u.opcbwants_cancelled))
			return (FALSE);
		break;
	case OP_CB_NOTIFY_LOCK:
		if (!xdr_CB_NOTIFY_LOCK4res(xdrs,
		    &objp->nfs_cb_resop4_u.opcbnotify_lock))
			return (FALSE);
		break;
	case OP_CB_NOTIFY_DEVICEID:
		if (!xdr_CB_NOTIFY_DEVICEID4res(xdrs,
		    &objp->nfs_cb_resop4_u.opcbnotify_deviceid))
			return (FALSE);
		break;
	case OP_CB_ILLEGAL:
		if (!xdr_CB_ILLEGAL4res(xdrs,
		    &objp->nfs_cb_resop4_u.opcbillegal))
			return (FALSE);
		break;
	default:
		return (FALSE);
	}
	return (TRUE);
}

bool_t
xdr_CB_COMPOUND4args(XDR *xdrs, CB_COMPOUND4args *objp)
{

	rpc_inline_t *buf;

	if (!xdr_utf8str_cs(xdrs, &objp->tag))
		return (FALSE);
	if (!xdr_uint32_t(xdrs, &objp->minorversion))
		return (FALSE);
	if (!xdr_uint32_t(xdrs, &objp->callback_ident))
		return (FALSE);
	if (!xdr_array(xdrs, (char **)&objp->argarray.argarray_val,
	    (uint_t *)&objp->argarray.argarray_len, ~0,
	    sizeof (nfs_cb_argop4), (xdrproc_t)xdr_nfs_cb_argop4))
		return (FALSE);
	return (TRUE);
}

bool_t
xdr_CB_COMPOUND4res(XDR *xdrs, CB_COMPOUND4res *objp)
{

	rpc_inline_t *buf;

	if (!xdr_nfsstat4(xdrs, &objp->status))
		return (FALSE);
	if (!xdr_utf8str_cs(xdrs, &objp->tag))
		return (FALSE);
	if (!xdr_array(xdrs, (char **)&objp->resarray.resarray_val,
	    (uint_t *)&objp->resarray.resarray_len, ~0,
	    sizeof (nfs_cb_resop4), (xdrproc_t)xdr_nfs_cb_resop4))
		return (FALSE);
	return (TRUE);
}

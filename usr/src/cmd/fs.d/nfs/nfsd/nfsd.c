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
 * Copyright 2006 Sun Microsystems, Inc.  All rights reserved.
 * Use is subject to license terms.
 */

/*	Copyright (c) 1984, 1986, 1987, 1988, 1989 AT&T		*/
/*	  All Rights Reserved  	*/

/*
 * University Copyright- Copyright (c) 1982, 1986, 1988
 * The Regents of the University of California
 * All Rights Reserved
 *
 * University Acknowledgment- Portions of this document are derived from
 * software developed by the University of California, Berkeley, and its
 * contributors.
 */

/* LINTLIBRARY */
/* PROTOLIB1 */

#pragma ident	"%Z%%M%	%I%	%E% SMI"

/* NFS server */

#include <sys/param.h>
#include <sys/types.h>
#include <syslog.h>
#include <tiuser.h>
#include <rpc/rpc.h>
#include <errno.h>
#include <thread.h>
#include <sys/resource.h>
#include <sys/time.h>
#include <sys/file.h>
#include <nfs/nfs.h>
#include <nfs/nfs_acl.h>
#include <nfs/nfssys.h>
#include <stdio.h>
#include <stdio_ext.h>
#include <stdlib.h>
#include <signal.h>
#include <netconfig.h>
#include <netdir.h>
#include <string.h>
#include <unistd.h>
#include <stropts.h>
#include <sys/tihdr.h>
#include <poll.h>
#include <priv_utils.h>
#include <sys/tiuser.h>
#include <netinet/tcp.h>
#include <deflt.h>
#include <rpcsvc/daemon_utils.h>
#include <rpcsvc/nfs4_prot.h>
#include "nfs_tbind.h"
#include "thrpool.h"

/* quiesce requests will be ignored if nfs_server_vers_max < QUIESCE_VERSMIN */
#define	QUIESCE_VERSMIN	4

static	int	nfssvc(int, struct netbuf, struct netconfig *);
static int nfssvcpool(int maxservers);
static	void	usage(void);

extern	int	_nfssys(int, void *);

/* signal handlers */
static void sigflush(int);
static void quiesce(int);

static	char	*MyName;
static	NETSELDECL(defaultproviders)[] = { "/dev/tcp6", "/dev/tcp", "/dev/udp",
					    "/dev/udp6", NULL };
/* static	NETSELDECL(defaultprotos)[] =	{ NC_UDP, NC_TCP, NULL }; */
/*
 * The following are all globals used by routines in nfs_tbind.c.
 */
size_t	end_listen_fds;		/* used by conn_close_oldest() */
size_t	num_fds = 0;		/* used by multiple routines */
int	listen_backlog = 32;	/* used by bind_to_{provider,proto}() */
int	num_servers;		/* used by cots_listen_event() */
int	(*Mysvc)(int, struct netbuf, struct netconfig *) = nfssvc;
				/* used by cots_listen_event() */
int	max_conns_allowed = -1;	/* used by cots_listen_event() */

/*
 * Keep track of min/max versions of NFS protocol to be started.
 * Start with the defaults (min == 2, max == 3).  We have the
 * capability of starting vers=4 but only if the user requests it.
 */
int	nfs_server_vers_min = NFS_VERSMIN_DEFAULT;
int	nfs_server_vers_max = NFS_VERSMAX_DEFAULT;

/*
 * Set the default for server delegation enablement and set per
 * /etc/default/nfs configuration (if present).
 */
int	nfs_server_delegation = NFS_SERVER_DELEGATION_DEFAULT;

int
main(int ac, char *av[])
{
	char *dir = "/";
	int allflag = 0;
	int df_allflag = 0;
	int opt_cnt = 0;
	int maxservers = 1;	/* zero allows inifinte number of threads */
	int maxservers_set = 0;
	int logmaxservers = 0;
	int pid;
	int i;
	char *provider = (char *)NULL;
	char *df_provider = (char *)NULL;
	struct protob *protobp0, *protobp;
	NETSELDECL(proto) = NULL;
	NETSELDECL(df_proto) = NULL;
	NETSELPDECL(providerp);
	char *defval;
	boolean_t can_do_mlp;

	MyName = *av;

	/*
	 * Initializations that require more privileges than we need to run.
	 */
	(void) _create_daemon_lock(NFSD, DAEMON_UID, DAEMON_GID);
	svcsetprio();

	can_do_mlp = priv_ineffect(PRIV_NET_BINDMLP);
	if (__init_daemon_priv(PU_RESETGROUPS|PU_CLEARLIMITSET,
	    DAEMON_UID, DAEMON_GID, PRIV_SYS_NFS,
	    can_do_mlp ? PRIV_NET_BINDMLP : NULL, NULL) == -1) {
		(void) fprintf(stderr, "%s should be run with"
			" sufficient privileges\n", av[0]);
		exit(1);
	}

	(void) enable_extended_FILE_stdio(-1, -1);

	/*
	 * Read in the values from config file first before we check
	 * commandline options so the options override the file.
	 */
	if ((defopen(NFSADMIN)) == 0) {
		if ((defval = defread("NFSD_MAX_CONNECTIONS=")) != NULL) {
			errno = 0;
			max_conns_allowed = strtol(defval, (char **)NULL, 10);
			if (errno != 0) {
				max_conns_allowed = -1;
			}
		}
		if ((defval = defread("NFSD_LISTEN_BACKLOG=")) != NULL) {
			errno = 0;
			listen_backlog = strtol(defval, (char **)NULL, 10);
			if (errno != 0) {
				listen_backlog = 32;
			}
		}
		if ((defval = defread("NFSD_PROTOCOL=")) != NULL) {
			df_proto = strdup(defval);
			opt_cnt++;
			if (strncasecmp("ALL", defval, 3) == 0) {
				free(df_proto);
				df_proto = NULL;
				df_allflag = 1;
			}
		}
		if ((defval = defread("NFSD_DEVICE=")) != NULL) {
			df_provider = strdup(defval);
			opt_cnt++;
		}
		if ((defval = defread("NFSD_SERVERS=")) != NULL) {
			errno = 0;
			maxservers = strtol(defval, (char **)NULL, 10);
			if (errno != 0) {
				maxservers = 1;
			} else {
				maxservers_set = 1;
			}
		}
		if ((defval = defread("NFS_SERVER_VERSMIN=")) != NULL) {
			errno = 0;
			nfs_server_vers_min =
				strtol(defval, (char **)NULL, 10);
			if (errno != 0) {
				nfs_server_vers_min = NFS_VERSMIN_DEFAULT;
			}
		}
		if ((defval = defread("NFS_SERVER_VERSMAX=")) != NULL) {
			errno = 0;
			nfs_server_vers_max =
				strtol(defval, (char **)NULL, 10);
			if (errno != 0) {
				nfs_server_vers_max = NFS_VERSMAX_DEFAULT;
			}
		}
		if ((defval = defread("NFS_SERVER_DELEGATION=")) != NULL) {
			if (strcmp(defval, "off") == 0) {
				nfs_server_delegation = FALSE;
			}
		}

		/* close defaults file */
		defopen(NULL);
	}

	/*
	 * Conflict options error messages.
	 */
	if (opt_cnt > 1) {
		(void) fprintf(stderr, "\nConflicting options, only one of "
		    "the following options can be specified\n"
		    "in " NFSADMIN ":\n"
		    "\tNFSD_PROTOCOL=ALL\n"
		    "\tNFSD_PROTOCOL=protocol\n"
		    "\tNFSD_DEVICE=device\n\n");
		usage();
	}
	opt_cnt = 0;

	while ((i = getopt(ac, av, "ac:p:t:l:")) != EOF) {
		switch (i) {
		case 'a':
			free(df_proto);
			df_proto = NULL;
			free(df_provider);
			df_provider = NULL;

			allflag = 1;
			opt_cnt++;
			break;

		case 'c':
			max_conns_allowed = atoi(optarg);
			break;

		case 'p':
			proto = optarg;
			df_allflag = 0;
			opt_cnt++;
			break;

		case 't':
			provider = optarg;
			df_allflag = 0;
			opt_cnt++;
			break;

		case 'l':
			listen_backlog = atoi(optarg);
			break;

		case '?':
			usage();
			/* NOTREACHED */
		}
	}

	allflag = df_allflag;
	if (proto == NULL)
		proto = df_proto;
	if (provider == NULL)
		provider = df_provider;

	/*
	 * Conflict options error messages.
	 */
	if (opt_cnt > 1) {
		(void) fprintf(stderr, "\nConflicting options, only one of "
		    "the following options can be specified\n"
		    "on the command line:\n"
		    "\t-a\n"
		    "\t-p protocol\n"
		    "\t-t transport\n\n");
		usage();
	}

	if (proto != NULL &&
	    strncasecmp(proto, NC_UDP, strlen(NC_UDP)) == 0) {
		if (nfs_server_vers_max == NFS_V4) {
			if (nfs_server_vers_min == NFS_V4) {
				syslog(LOG_ERR,
					"NFS version 4 is not supported "
					"with the UDP protocol.  Exiting\n");
				fprintf(stderr,
					"NFS version 4 is not supported "
					"with the UDP protocol.  Exiting\n");
				exit(3);
			} else {
				fprintf(stderr,
					"NFS version 4 is not supported "
					"with the UDP protocol.\n");
			}
		}
	}

	/*
	 * If there is exactly one more argument, it is the number of
	 * servers.
	 */
	if (optind == ac - 1) {
		maxservers = atoi(av[optind]);
		maxservers_set = 1;
	}
	/*
	 * If there are two or more arguments, then this is a usage error.
	 */
	else if (optind < ac - 1)
		usage();
	/*
	 * Check the ranges for min/max version specified
	 */
	else if ((nfs_server_vers_min > nfs_server_vers_max) ||
		(nfs_server_vers_min < NFS_VERSMIN) ||
		(nfs_server_vers_max > NFS_VERSMAX))
		usage();
	/*
	 * There are no additional arguments, and we haven't set maxservers
	 * explicitly via the config file, we use a default number of
	 * servers.  We will log this.
	 */
	else if (maxservers_set == 0)
		logmaxservers = 1;

	/*
	 * Basic Sanity checks on options
	 *
	 * max_conns_allowed must be positive, except for the special
	 * value of -1 which is used internally to mean unlimited, -1 isn't
	 * documented but we allow it anyway.
	 *
	 * maxservers must be positive
	 * listen_backlog must be positive or zero
	 */
	if (((max_conns_allowed != -1) && (max_conns_allowed <= 0)) ||
	    (listen_backlog < 0) || (maxservers <= 0)) {
		usage();
	}

	/*
	 * Set current dir to server root
	 */
	if (chdir(dir) < 0) {
		(void) fprintf(stderr, "%s:  ", MyName);
		perror(dir);
		exit(1);
	}

#ifndef DEBUG
	/*
	 * Background
	 */
	pid = fork();
	if (pid < 0) {
		perror("nfsd: fork");
		exit(1);
	}
	if (pid != 0)
		exit(0);

	/*
	 * Close existing file descriptors, open "/dev/null" as
	 * standard input, output, and error, and detach from
	 * controlling terminal.
	 */
	closefrom(0);
	(void) open("/dev/null", O_RDONLY);
	(void) open("/dev/null", O_WRONLY);
	(void) dup(1);
	(void) setsid();
#endif
	openlog(MyName, LOG_PID | LOG_NDELAY, LOG_DAEMON);

	/*
	 * establish our lock on the lock file and write our pid to it.
	 * exit if some other process holds the lock, or if there's any
	 * error in writing/locking the file.
	 */
	pid = _enter_daemon_lock(NFSD);
	switch (pid) {
	case 0:
		break;
	case -1:
		syslog(LOG_ERR, "error locking for %s: %s", NFSD,
		    strerror(errno));
		exit(2);
	default:
		/* daemon was already running */
		exit(0);
	}

	sigset(SIGTERM, sigflush);
	sigset(SIGUSR1, quiesce);

	if (logmaxservers) {
		(void) syslog(LOG_INFO,
			"Number of servers not specified. Using default of %d.",
			maxservers);
	}

	/*
	 * Make sure to unregister any previous versions in case the
	 * user is reconfiguring the server in interesting ways.
	 */
	svc_unreg(NFS_PROGRAM, NFS_VERSION);
	svc_unreg(NFS_PROGRAM, NFS_V3);
	svc_unreg(NFS_PROGRAM, NFS_V4);
	svc_unreg(NFS_ACL_PROGRAM, NFS_ACL_V2);
	svc_unreg(NFS_ACL_PROGRAM, NFS_ACL_V3);

	/*
	 * Set up kernel RPC thread pool for the NFS server.
	 */
	if (nfssvcpool(maxservers)) {
		(void) syslog(LOG_ERR,
			"Can't set up kernel NFS service: %m. Exiting");
		exit(1);
	}


	/*
	 * Set up blocked thread to do LWP creation on behalf of the kernel.
	 */
	if (svcwait(NFS_SVCPOOL_ID)) {
		(void) syslog(LOG_ERR,
		    "Can't set up NFS pool creator: %m, Exiting");
		exit(1);
	}

	/*
	 * RDMA start and stop thread.
	 * Per pool RDMA listener creation and
	 * destructor thread.
	 *
	 * start rdma services and block in the kernel.
	 */
	if (svcrdma(NFS_SVCPOOL_ID, nfs_server_vers_min, nfs_server_vers_max,
		nfs_server_delegation)) {
		(void) syslog(LOG_ERR,
		    "Can't set up RDMA creator thread : %m.");
	}

	/*
	 * Build a protocol block list for registration.
	 */
	protobp0 = protobp = (struct protob *)malloc(sizeof (struct protob));
	protobp->serv = "NFS";
	protobp->versmin = nfs_server_vers_min;
	protobp->versmax = nfs_server_vers_max;
	protobp->program = NFS_PROGRAM;

	protobp->next = (struct protob *)malloc(sizeof (struct protob));
	protobp = protobp->next;
	protobp->serv = "NFS_ACL";		/* not used */
	protobp->versmin = nfs_server_vers_min;
	/* XXX - this needs work to get the version just right */
	protobp->versmax = (nfs_server_vers_max > NFS_ACL_V3) ?
		NFS_ACL_V3 : nfs_server_vers_max;
	protobp->program = NFS_ACL_PROGRAM;
	protobp->next = (struct protob *)NULL;

	if (allflag) {
		if (do_all(protobp0, nfssvc) == -1)
			exit(1);
	} else if (proto) {
		/* there's more than one match for the same protocol */
		struct netconfig *nconf;
		NCONF_HANDLE *nc;
		bool_t	protoFound = FALSE;
		if ((nc = setnetconfig()) == (NCONF_HANDLE *) NULL) {
			syslog(LOG_ERR, "setnetconfig failed: %m");
			goto done;
		}
		while (nconf = getnetconfig(nc)) {
			if (strcmp(nconf->nc_proto, proto) == 0) {
				protoFound = TRUE;
				do_one(nconf->nc_device, NULL,
					protobp0, nfssvc);
			}
		}
		(void) endnetconfig(nc);
		if (protoFound == FALSE)
			syslog(LOG_ERR, "couldn't find netconfig entry \
for protocol %s", proto);

	} else if (provider)
		do_one(provider, proto, protobp0, nfssvc);
	else {
		for (providerp = defaultproviders;
			*providerp != NULL; providerp++) {
			provider = *providerp;
			do_one(provider, NULL, protobp0, nfssvc);
		}
	}
done:

	free(protobp);
	free(protobp0);

	if (num_fds == 0) {
		(void) syslog(LOG_ERR,
		"Could not start NFS service for any protocol. Exiting.");
		exit(1);
	}

	end_listen_fds = num_fds;

	/*
	 * Get rid of unneeded privileges.
	 */
	__fini_daemon_priv(PRIV_PROC_FORK, PRIV_PROC_EXEC, PRIV_PROC_SESSION,
	    PRIV_FILE_LINK_ANY, PRIV_PROC_INFO, (char *)NULL);

	/*
	 * Poll for non-data control events on the transport descriptors.
	 */
	poll_for_action();

	/*
	 * If we get here, something failed in poll_for_action().
	 */
	return (1);
}

static int
nfssvcpool(int maxservers)
{
	struct svcpool_args npa;

	npa.id = NFS_SVCPOOL_ID;
	npa.maxthreads = maxservers;
	npa.redline = 0;
	npa.qsize = 0;
	npa.timeout = 0;
	npa.stksize = 0;
	npa.max_same_xprt = 0;
	return (_nfssys(SVCPOOL_CREATE, &npa));
}

/*
 * Establish NFS service thread.
 */
static int
nfssvc(int fd, struct netbuf addrmask, struct netconfig *nconf)
{
	struct nfs_svc_args nsa;

	nsa.fd = fd;
	nsa.netid = nconf->nc_netid;
	nsa.addrmask = addrmask;
	if (strncasecmp(nconf->nc_proto, NC_UDP, strlen(NC_UDP)) == 0) {
		nsa.versmax = (nfs_server_vers_max > NFS_V3) ?
			NFS_V3 : nfs_server_vers_max;
		nsa.versmin = nfs_server_vers_min;
		/*
		 * If no version left, silently do nothing, previous
		 * checks will have assured at least TCP is available.
		 */
		if (nsa.versmin > nsa.versmax)
			return (0);
	} else {
		nsa.versmax = nfs_server_vers_max;
		nsa.versmin = nfs_server_vers_min;
	}
	nsa.delegation = nfs_server_delegation;
	return (_nfssys(NFS_SVC, &nsa));
}

static void
usage(void)
{
	(void) fprintf(stderr,
"usage: %s [ -a ] [ -c max_conns ] [ -p protocol ] [ -t transport ] ", MyName);
	(void) fprintf(stderr, "\n[ -l listen_backlog ] [ nservers ]\n");
	(void) fprintf(stderr,
"\twhere -a causes <nservers> to be started on each appropriate transport,\n");
	(void) fprintf(stderr,
"\tmax_conns is the maximum number of concurrent connections allowed,\n");
	(void) fprintf(stderr, "\t\tand max_conns must be a decimal number");
	(void) fprintf(stderr, "> zero,\n");
	(void) fprintf(stderr, "\tprotocol is a protocol identifier,\n");
	(void) fprintf(stderr,
		"\ttransport is a transport provider name (i.e. device),\n");
	(void) fprintf(stderr,
		"\tlisten_backlog is the TCP listen backlog,\n");
	(void) fprintf(stderr,
		"\tand <nservers> must be a decimal number > zero.\n");
	exit(1);
}

/*
 * Issue nfssys system call to flush all logging buffers asynchronously.
 *
 * NOTICE: It is extremely important to flush NFS logging buffers when
 *	   nfsd exits. When the system is halted or rebooted nfslogd
 *	   may not have an opportunity to flush the buffers.
 */
static void
nfsl_flush()
{
	struct nfsl_flush_args nfa;

	memset((void *)&nfa, 0, sizeof (nfa));
	nfa.version = NFSL_FLUSH_ARGS_VERS;
	nfa.directive = NFSL_ALL;	/* flush all asynchronously */

	if (_nfssys(LOG_FLUSH, &nfa) < 0)
		syslog(LOG_ERR, "_nfssys(LOG_FLUSH) failed: %s\n",
			strerror(errno));
}

/*
 * SIGTERM handler.
 * Flush logging buffers and exit.
 */
static void
sigflush(int sig)
{
	nfsl_flush();
	exit(0);
}

/*
 * SIGUSR1 handler.
 * Request server quiesce, then exit. For subsequent warm start.
 * Equivalent to SIGTERM handler if nfs_server_vers_max < QUIESCE_VERSMIN.
 */
static void
quiesce(int sig)
{
	int error;
	int id = NFS_SVCPOOL_ID;

	if (nfs_server_vers_max >= QUIESCE_VERSMIN) {
		/* Request server quiesce at next shutdown */
		error = _nfssys(NFS_SVC_REQUEST_QUIESCE, &id);
		if (error) {
			syslog(LOG_ERR,
			    "_nfssys(NFS_SVC_REQUEST_QUIESCE) failed: %s\n",
			    strerror(errno));
			return;
		}
	}

	/* Flush logging buffers */
	nfsl_flush();

	exit(0);
}

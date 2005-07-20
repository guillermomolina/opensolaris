#!/sbin/sh
#
# CDDL HEADER START
#
# The contents of this file are subject to the terms of the
# Common Development and Distribution License, Version 1.0 only
# (the "License").  You may not use this file except in compliance
# with the License.
#
# You can obtain a copy of the license at usr/src/OPENSOLARIS.LICENSE
# or http://www.opensolaris.org/os/licensing.
# See the License for the specific language governing permissions
# and limitations under the License.
#
# When distributing Covered Code, include this CDDL HEADER in each
# file and include the License file at usr/src/OPENSOLARIS.LICENSE.
# If applicable, add the following below this CDDL HEADER, with the
# fields enclosed by brackets "[]" replaced with your own identifying
# information: Portions Copyright [yyyy] [name of copyright owner]
#
# CDDL HEADER END
#
#	Copyright (c) 1984, 1986, 1987, 1988, 1989 AT&T
#	  All Rights Reserved


#
# Copyright 2005 Sun Microsystems, Inc.  All rights reserved.
# Use is subject to license terms.
#
# ident	"%Z%%M%	%I%	%E% SMI"

STARTLST="16boot.server"

INIT_STARTLST="76snmpdx 77dmi"

INSDIR=${ROOT}/etc/rc3.d

if [ ! -d ${INSDIR} ]
then
	mkdir ${INSDIR}
	eval ${CH}chmod 755 ${INSDIR}
	eval ${CH}chgrp sys ${INSDIR}
	eval ${CH}chown root ${INSDIR}
fi
for f in ${STARTLST}
do
	name=`echo $f | sed -e 's/^..//'`
	rm -f ${INSDIR}/S$f
	ln ${ROOT}/etc/init.d/${name} ${INSDIR}/S$f
done
for f in ${INIT_STARTLST}
do
	name=`echo $f | sed -e 's/^..//'`
	rm -f ${INSDIR}/S$f
	ln ${ROOT}/etc/init.d/init.${name} ${INSDIR}/S$f
done

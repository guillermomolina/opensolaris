
/* : : generated by proto : : */
/***********************************************************************
*                                                                      *
*               This software is part of the ast package               *
*          Copyright (c) 1985-2008 AT&T Intellectual Property          *
*                      and is licensed under the                       *
*                  Common Public License, Version 1.0                  *
*                    by AT&T Intellectual Property                     *
*                                                                      *
*                A copy of the License is available at                 *
*            http://www.opensource.org/licenses/cpl1.0.txt             *
*         (with md5 checksum 059e8cd6165cb4c31e351f2b69388fd9)         *
*                                                                      *
*              Information and Software Systems Research               *
*                            AT&T Research                             *
*                           Florham Park NJ                            *
*                                                                      *
*                 Glenn Fowler <gsf@research.att.com>                  *
*                  David Korn <dgk@research.att.com>                   *
*                   Phong Vo <kpv@research.att.com>                    *
*                                                                      *
***********************************************************************/
                  
/*
 * Glenn Fowler
 * AT&T Research
 *
 * 3d fs interface definitions
 */

#ifndef _FS3D_H
#if !defined(__PROTO__)
#include <prototyped.h>
#endif
#if !defined(__LINKAGE__)
#define __LINKAGE__		/* 2004-08-11 transition */
#endif

#define _FS3D_H

#include <ast_fs.h>

#if _int_st_spare1
#define iview(p)	((p)->st_spare1)
#define IVIEW(p,v)	((p)->st_spare1=(v))
#else
#if _ary_st_spare4
#define iview(p)	((p)->st_spare4[0])
#define IVIEW(p,v)	((p)->st_spare4[0]=(v))
#else
#if _ary_st_pad4
#define iview(p)	((p)->st_pad4[0])
#define IVIEW(p,v)	((p)->st_pad4[0]=(v))
#else
#if _mem_st_rdev_stat
#define iview(p)	((S_ISBLK((p)->st_mode)||S_ISCHR((p)->st_mode))?0:(p)->st_rdev)
#define IVIEW(p,v)	do{if(!S_ISBLK((p)->st_mode)&&!S_ISCHR((p)->st_mode))(p)->st_rdev=(v);}while(0)
#else
#define iview(p)	0
#define IVIEW(p,v)
#endif
#endif
#endif
#endif

/*
 * special options
 */

#define FS3D_init	"/#option/init"
#define FS3D_on		"/#option/3d"
#define FS3D_off	"/#option/2d"

/*
 * fs3d(3) ops
 */

#define FS3D_OP(o,a)	(((a)<<3)|(o))

#define FS3D_INIT	FS3D_OP_INIT	/* re-initialize tables		*/
#define FS3D_OFF	FS3D_OP_OFF
#define FS3D_ON		FS3D_OP_ON
#define FS3D_TEST	FS3D_OP_TEST
#define FS3D_LIMIT(n)	FS3D_OP(FS3D_OP_LIMIT,n)

#define FS3D_op(x)	((x)&07)
#define FS3D_arg(x)	(((x)>>3)&07777)

#define FS3D_OP_OFF	0
#define FS3D_OP_ON	1
#define FS3D_OP_TEST	2
#define FS3D_OP_LIMIT	3
#define FS3D_OP_INIT	7

/*
 * mount(2) ops
 */

#define FS3D_ALL	(FS3D_VIEW|FS3D_VERSION)
#define FS3D_VIEW	002
#define FS3D_VERSION	004
#define FS3D_GET	010
#define FS3D_SIZE(n)	((n)<<4)
#define FS3D_SIZEOF(n)	((n)>>4)

extern __MANGLE__ int		mount __PROTO__((const char*, char*, int, __V_*));

#if _BLD_ast && defined(__EXPORT__)
#undef __MANGLE__
#define __MANGLE__ __LINKAGE__		__EXPORT__
#endif

extern __MANGLE__ int		fs3d __PROTO__((int));
extern __MANGLE__ char*		pathnext __PROTO__((char*, char*, long*));

#undef __MANGLE__
#define __MANGLE__ __LINKAGE__

#endif

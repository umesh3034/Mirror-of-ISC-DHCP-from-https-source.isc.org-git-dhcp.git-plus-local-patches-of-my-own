/* sunos4.h

   System dependencies for SunOS 4 (tested on 4.1.4)... */

/*
 * Copyright (c) 2004-2017 by Internet Systems Consortium, Inc. ("ISC")
 * Copyright (c) 1996-2003 by Internet Software Consortium
 *
 * This Source Code Form is subject to the terms of the Mozilla Public
 * License, v. 2.0. If a copy of the MPL was not distributed with this
 * file, You can obtain one at http://mozilla.org/MPL/2.0/.
 *
 * THE SOFTWARE IS PROVIDED "AS IS" AND ISC DISCLAIMS ALL WARRANTIES
 * WITH REGARD TO THIS SOFTWARE INCLUDING ALL IMPLIED WARRANTIES OF
 * MERCHANTABILITY AND FITNESS.  IN NO EVENT SHALL ISC BE LIABLE FOR
 * ANY SPECIAL, DIRECT, INDIRECT, OR CONSEQUENTIAL DAMAGES OR ANY DAMAGES
 * WHATSOEVER RESULTING FROM LOSS OF USE, DATA OR PROFITS, WHETHER IN AN
 * ACTION OF CONTRACT, NEGLIGENCE OR OTHER TORTIOUS ACTION, ARISING OUT
 * OF OR IN CONNECTION WITH THE USE OR PERFORMANCE OF THIS SOFTWARE.
 *
 *   Internet Systems Consortium, Inc.
 *   950 Charter Street
 *   Redwood City, CA 94063
 *   <info@isc.org>
 *   https://www.isc.org/
 *
 */

/* Basic Integer Types not defined in SunOS headers... */

#define int8_t		char
#define int16_t		short
#define int32_t		int

#define u_int8_t	unsigned char
#define u_int16_t	unsigned short 
#define u_int32_t	unsigned int

#define	ssize_t		int

#define SOCKLEN_T	int

#define fpos_t		long
#define fgetpos(f, p)	(((*(p)) = ftell (f)) == -1 ? -1 : 0)
#define fsetpos(f, p)	(fseek (f, p, SEEK_SET))

/* No endian.h either. */
/*
 * Definitions for byte order, according to byte significance from low
 * address to high.
 */
#define LITTLE_ENDIAN   1234    /* LSB first: i386, vax */
#define BIG_ENDIAN      4321    /* MSB first: 68000, ibm, net */
#define PDP_ENDIAN      3412    /* LSB first in word, MSW first in long */

#define BYTE_ORDER      BIG_ENDIAN

/* The jmp_buf type is an array on SunOS, so we can't dereference it
   and must declare it differently. */
#define jbp_decl(x)	jmp_buf x
#define jref(x)		(x)
#define jdref(x)	(x)
#define jrefproto	jmp_buf

#include <syslog.h>
#include <sys/types.h>

#include <string.h>
#include <errno.h>
#include <unistd.h>
#include <sys/wait.h>
#include <signal.h>
#include <setjmp.h>
#include <limits.h>
#include <poll.h>

extern int h_errno;

#include <net/if.h>
#include <net/if_arp.h>

/*
 * Definitions for IP type of service (ip_tos)
 */
#define IPTOS_LOWDELAY          0x10
#define IPTOS_THROUGHPUT        0x08
#define IPTOS_RELIABILITY       0x04
/*      IPTOS_LOWCOST           0x02 XXX */

/* SunOS systems don't have /var/run, but some sites have added it.
   If you want to put dhcpd.pid in /var/run, define _PATH_DHCPD_PID
   in site.h. */
#ifndef _PATH_DHCPD_PID
#define _PATH_DHCPD_PID	"/etc/dhcpd.pid"
#endif
#ifndef _PATH_DHCPD6_PID
#define _PATH_DHCPD6_PID "/etc/dhcpd6.pid"
#endif
#ifndef _PATH_DHCLIENT_PID
#define _PATH_DHCLIENT_PID "/etc/dhclient.pid"
#endif
#ifndef _PATH_DHCLIENT6_PID
#define _PATH_DHCLIENT6_PID "/etc/dhclient6.pid"
#endif
#ifndef _PATH_DHCRELAY_PID
#define _PATH_DHCRELAY_PID "/etc/dhcrelay.pid"
#endif

#ifdef __GNUC__
/* Varargs stuff: use stdarg.h instead ... */
#include <stdarg.h>
#define VA_DOTDOTDOT ...
#define VA_start(list, last) va_start (list, last)
#define va_dcl
#else /* !__GNUC__*/
/* Varargs stuff... */
#include <varargs.h>
#define VA_DOTDOTDOT va_alist
#define VA_start(list, last) va_start (list)
#endif /* !__GNUC__*/

/* SunOS doesn't support limited sprintfs. */
#define NO_SNPRINTF

/* SunOS doesn't supply strerror... */
#define NO_STRERROR
char *strerror (int);

#define NEED_INET_ATON

/* By default, use NIT API for receiving and sending packets... */
#if defined (USE_DEFAULT_NETWORK)
#  define USE_NIT
#endif

#define EOL	'\n'
#define VOIDPTR	void *

#include <time.h>
#include <sys/time.h>

#define TIME time_t
#define GET_TIME(x)	time ((x))

#ifdef NEED_PRAND_CONF
const char *cmds[] = {
	"/bin/ps -axlw 2>&1",
	"/usr/ucb/netstat -an 2>&1",
	"/bin/df  2>&1",
	"/usr/bin/dig com. soa +ti=1 +retry=0 2>&1",
	"/usr/ucb/uptime  2>&1",
	"/usr/ucb/netstat -an 2>&1",
	"/bin/iostat  2>&1",
	NULL
};

const char *dirs[] = {
	"/tmp",
	"/var/tmp",
	".",
	"/",
	"/var/spool",
	"/var/adm",
	"/dev",
	"/var/mail",
	"/home",
	NULL
};

const char *files[] = {
	"/var/adm/messages",
	"/var/adm/wtmp",
	"/var/adm/lastlog",
	NULL
};
#endif /* NEED_PRAND_CONF */

/* -----------------------------------------------------------------------------
 *
 * (c) The University of Glasgow 2002
 *
 * Definitions for package `unix' which are visible in Haskell land.
 *
 * ---------------------------------------------------------------------------*/

#ifndef HSUNIX_H
#define HSUNIX_H

#include "HsUnixConfig.h"
#include "HsFFI.h"

/* ultra-evil... */
#undef PACKAGE_BUGREPORT
#undef PACKAGE_NAME
#undef PACKAGE_STRING
#undef PACKAGE_TARNAME
#undef PACKAGE_VERSION

#include <stdlib.h>
#include <stdio.h>

#ifdef HAVE_STRING_H
#include <string.h>
#endif
#ifdef HAVE_SYS_TIMES_H
#include <sys/times.h>
#endif
#ifdef HAVE_SYS_TIME_H
#include <sys/time.h>
#endif
#ifdef HAVE_SYS_RESOURCE_H
#include <sys/resource.h>
#endif
#ifdef HAVE_SYS_WAIT_H
#include <sys/wait.h>
#endif
#ifdef HAVE_SYS_STAT_H
#include <sys/stat.h>
#endif
#ifdef HAVE_TIME_H
#include <time.h>
#endif
#ifdef HAVE_UNISTD_H
#include <unistd.h>
#endif
#ifdef HAVE_UTIME_H
#include <utime.h>
#endif
#ifdef HAVE_FCNTL_H
#include <fcntl.h>
#endif
#ifdef HAVE_LIMITS_H
#include <limits.h>
#endif
#ifdef HAVE_TERMIOS_H
#include <termios.h>
#endif
#ifdef HAVE_SYS_UTSNAME_H
#include <sys/utsname.h>
#endif
#ifdef HAVE_PWD_H
#include <pwd.h>
#endif
#ifdef HAVE_GRP_H
#include <grp.h>
#endif
#ifdef HAVE_DIRENT_H
#include <dirent.h>
#endif

#if defined(HAVE_BSD_LIBUTIL_H)
#include <bsd/libutil.h>
#elif defined(HAVE_LIBUTIL_H)
#include <libutil.h>
#endif
#ifdef HAVE_PTY_H
#include <pty.h>
#endif
#ifdef HAVE_UTMP_H
#include <utmp.h>
#endif
#ifdef HAVE_DLFCN_H
#include <dlfcn.h>
#endif
#ifdef HAVE_SIGNAL_H
#include <signal.h>
#endif

/* defined in rts/posix/Signals.c */
extern HsInt nocldstop;

/* defined in libc */
extern char **environ;

#ifdef HAVE_RTLDNEXT
void *__hsunix_rtldNext (void);
#endif

#ifdef HAVE_RTLDDEFAULT
void *__hsunix_rtldDefault (void);
#endif

/* O_SYNC doesn't exist on Mac OS X and (at least some versions of) FreeBSD,
fall back to O_FSYNC, which should be the same */
#ifndef O_SYNC
# define O_SYNC O_FSYNC
#endif

// not part of POSIX, hence may not be always defined
#ifndef WCOREDUMP
# define WCOREDUMP(s) 0
#endif

// push a SVR4 STREAMS module; do nothing if STREAMS not available
int __hsunix_push_module(int fd, const char *module);

#endif

#ifdef mingw32_BUILD_OS 

#ifndef HAVE_SYS_RESOURCE_H

# define RLIMIT_CORE 4
# define RLIMIT_CPU 0
# define RLIMIT_DATA 2
# define RLIMIT_FSIZE 1
# define RLIMIT_NOFILE 5
# define RLIMIT_STACK 3
# define RLIM_INFINITY	(~0UL)

typedef unsigned long rlim_t;

struct rlimit {
	rlim_t	rlim_cur;
	rlim_t	rlim_max;
};

/* Used for get/setpriority */
#define PRIO_PROCESS	0
#define PRIO_PGRP	1
#define PRIO_USER	2

#endif

#ifndef HAVE_SYS_UTSNAME_H

#define _UTSNAME_LENGTH 65

struct utsname
{
  char sysname[_UTSNAME_LENGTH + 1];
  char nodename[_UTSNAME_LENGTH];
  char release[_UTSNAME_LENGTH];
  char version[_UTSNAME_LENGTH];
  char machine[_UTSNAME_LENGTH];
#if __GNU_VISIBLE
  char domainname[_UTSNAME_LENGTH];
#else
  char __domainname[_UTSNAME_LENGTH];
#endif
};

#endif

// from unistd.h
#define _SC_ARG_MAX                       0
#define _SC_CHILD_MAX                     1
#define _SC_CLK_TCK                       2
#define _SC_NGROUPS_MAX                   3
#define _SC_OPEN_MAX                      4
#define _SC_JOB_CONTROL                   5
#define _SC_SAVED_IDS                     6
#define _SC_VERSION                       7

#define _PC_LINK_MAX                      0
#define _PC_MAX_CANON                     1
#define _PC_MAX_INPUT                     2
#define _PC_NAME_MAX                      3
#define _PC_PATH_MAX                      4
#define _PC_PIPE_BUF                      5
#define _PC_CHOWN_RESTRICTED              6
#define _PC_NO_TRUNC                      7
#define _PC_VDISABLE                      8

// from sys/types.h
typedef int gid_t;
typedef int uid_t;

#ifndef HAVE_GRP_H

struct group {
	char	*gr_name;		/* group name */
	char	*gr_passwd;		/* group password */
	gid_t	gr_gid;			/* group id */
	char	**gr_mem;		/* group members */
};

#endif

#ifndef HAVE_PWD_H

struct passwd {
	char	*pw_name;		/* user name */
	char	*pw_passwd;		/* encrypted password */
	uid_t	pw_uid;			/* user uid */
	gid_t	pw_gid;			/* user gid */
	char	*pw_comment;		/* comment */
	char	*pw_gecos;		/* Honeywell login info */
	char	*pw_dir;		/* home directory */
	char	*pw_shell;		/* default shell */
};

#endif

// from sys/signal.h

union sigval {
	int sival_int;
	void *sival_ptr;
};
typedef struct {
	int si_signo;
	int si_code;
	union sigval si_value;
	int si_errno;
	pid_t si_pid;
	uid_t si_uid;
	void *si_addr;
	int si_status;
	int si_band;
} siginfo_t;

#ifndef HAVE_DLFCN_H

#define RTLD_DEFAULT    NULL

/* valid values for mode argument to dlopen */
#define RTLD_LOCAL	0	/* Symbols in this dlopen'ed obj are not     */
				/* visible to other dlopen'ed objs.          */
#define RTLD_LAZY	1	/* Lazy function call binding.               */
#define RTLD_NOW	2	/* Immediate function call binding.          */
#define RTLD_GLOBAL	4	/* Symbols in this dlopen'ed obj are visible */
				/* to other dlopen'ed objs.                  */

struct flock {
	short	l_type;		/* F_RDLCK, F_WRLCK, or F_UNLCK */
	short	l_whence;	/* flag to choose starting offset */
	long	l_start;	/* relative offset, in bytes */
	long	l_len;		/* length, in bytes; 0 means lock to EOF */
	short	l_pid;		/* returned with F_GETLK */
	short	l_xxx;		/* reserved for future use */
};

#define	_FSYNC		0x2000	/* do all writes synchronously */
#define	_FNONBLOCK	0x4000	/* non blocking I/O (POSIX style) */
#define	_FNOCTTY	0x8000	/* don't assign a ctty on this open */
 
#define	O_NONBLOCK	_FNONBLOCK
#define	O_NOCTTY	_FNOCTTY

#define	FD_CLOEXEC	1	/* posix */

#define	F_GETFD		1	/* Get fildes flags (close on exec) */
#define	F_SETFD		2	/* Set fildes flags (close on exec) */
#define	F_GETFL		3	/* Get file flags */
#define	F_SETFL		4	/* Set file flags */
#define	F_GETLK  	7	/* Get record-locking information */
#define	F_SETLK  	8	/* Set or Clear a record-lock (Non-Blocking) */
#define	F_SETLKW 	9	/* Set or Clear a record-lock (Blocking) */

#define	F_RDLCK		1	/* read lock */
#define	F_WRLCK		2	/* write lock */
#define	F_UNLCK		3	/* remove lock(s) */

#endif

// #ifndef HAVE_SYS_STAT_H

#define		_IFLNK	0120000	/* symbolic link */
#define		_IFSOCK	0140000	/* socket */

#define	S_ISUID		0004000	/* set user id on execution */
#define	S_ISGID		0002000	/* set group id on execution */
#define	S_IFLNK		_IFLNK
#define	S_IFSOCK	_IFSOCK

// #endif

#ifndef HAVE_SYS_TIMES_H

struct tms {
	clock_t	tms_utime;		/* user time */
	clock_t	tms_stime;		/* system time */
	clock_t	tms_cutime;		/* user time, children */
	clock_t	tms_cstime;		/* system time, children */
};

#endif

#ifndef HAVE_SYS_WAIT_H

#define WNOHANG 1
#define WUNTRACED 2
#define WCONTINUED 8

#endif

#ifndef HAVE_TERMIOS_H

#define _POSIX_VDISABLE '\0'

#define TCOOFF		0
#define TCOON		1
#define TCIOFF		2
#define TCION		3

#define TCIFLUSH	0
#define TCOFLUSH	1
#define TCIOFLUSH	2
#define TCFLSH          3

#define TCSAFLUSH	1
#define TCSANOW		2
#define TCSADRAIN	3
#define TCSADFLUSH	4

/* iflag bits */
#define IGNBRK	0x00001
#define BRKINT	0x00002
#define IGNPAR	0x00004
#define IMAXBEL	0x00008
#define INPCK	0x00010
#define ISTRIP	0x00020
#define INLCR	0x00040
#define IGNCR	0x00080
#define ICRNL	0x00100
#define IXON	0x00400
#define IXOFF	0x01000
#define IUCLC	0x04000
#define IXANY	0x08000
#define PARMRK	0x10000
#define IUTF8	0x20000

/* oflag bits */

#define OPOST	0x00001
#define OLCUC	0x00002
#define OCRNL	0x00004
#define ONLCR	0x00008
#define ONOCR	0x00010
#define ONLRET	0x00020
#define OFILL	0x00040
#define CRDLY	0x00180
#define CR0	0x00000
#define CR1	0x00080
#define CR2	0x00100
#define CR3	0x00180
#define NLDLY	0x00200
#define NL0	0x00000
#define NL1	0x00200
#define BSDLY	0x00400
#define BS0	0x00000
#define BS1	0x00400
#define TABDLY	0x01800
#define TAB0	0x00000
#define TAB1	0x00800
#define TAB2	0x01000
#define TAB3	0x01800
#define XTABS	0x01800
#define VTDLY	0x02000
#define VT0	0x00000
#define VT1	0x02000
#define FFDLY	0x04000
#define FF0	0x00000
#define FF1	0x04000
#define OFDEL	0x08000

/* cflag bits */

/* Baud rate values.  These must fit in speed_t, which is unsigned
   char.  See also the extended baud rates below.  These baud rates
   set an additional bit. */
#define CBAUD	 0x0100f
#define B0	 0x00000
#define B50	 0x00001
#define B75	 0x00002
#define B110	 0x00003
#define B134	 0x00004
#define B150	 0x00005
#define B200	 0x00006
#define B300	 0x00007
#define B600	 0x00008
#define B1200	 0x00009
#define B1800	 0x0000a
#define B2400	 0x0000b
#define B4800	 0x0000c
#define B9600	 0x0000d
#define B19200	 0x0000e
#define B38400	 0x0000f

#define CSIZE	 0x00030
#define CS5	 0x00000
#define CS6	 0x00010
#define CS7	 0x00020
#define CS8	 0x00030
#define CSTOPB	 0x00040
#define CREAD	 0x00080
#define PARENB	 0x00100
#define PARODD	 0x00200
#define HUPCL	 0x00400
#define CLOCAL	 0x00800

/* lflag bits */
#define ISIG	0x0001
#define ICANON	0x0002
#define ECHO	0x0004
#define ECHOE	0x0008
#define ECHOK	0x0010
#define ECHONL	0x0020
#define NOFLSH	0x0040
#define TOSTOP	0x0080
#define IEXTEN	0x0100
#define FLUSHO	0x0200
#define ECHOKE	0x0400
#define ECHOCTL	0x0800

#define VDISCARD	1
#define VEOL		2
#define VEOL2		3
#define VEOF		4
#define VERASE		5
#define VINTR		6
#define VKILL		7
#define VLNEXT		8
#define VMIN		9
#define VQUIT		10
#define VREPRINT	11
#define VSTART		12
#define VSTOP		13
#define VSUSP		14
#define VSWTC		15
#define VTIME		16
#define VWERASE	17

#define NCCS		18

typedef unsigned char cc_t;
typedef unsigned int  tcflag_t;
typedef unsigned int  speed_t;

struct termios
{
  tcflag_t	c_iflag;
  tcflag_t	c_oflag;
  tcflag_t	c_cflag;
  tcflag_t	c_lflag;
  char		c_line;
  cc_t		c_cc[NCCS];
  speed_t	c_ispeed;
  speed_t	c_ospeed;
};

#endif

#endif


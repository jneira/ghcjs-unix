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

#endif

# ===========================================================================
#          http://www.gnu.org/software/autoconf-archive/ax_ext.html
# ===========================================================================
#
# SYNOPSIS
#
#   AX_POWERPC_SIMD
#
# DESCRIPTION
#
#   Find supported SIMD extensions by for PowerPC on AIX and Linux. When an SIMD
#   extension is found, the -m"simdextensionname" is added to SIMD_FLAGS
#
#   This macro calls:
#
#     AC_SUBST(SIMD_FLAGS)
#
#   And defines:
#
#     HAVE_ALTIVEC / HAVE_VSX
#
# LICENSE
#
#   Copyright (c) 2011 Christopher Horler <cshorler@googlemail.com>
#
#   Copying and distribution of this file, with or without modification, are
#   permitted in any medium without royalty provided the copyright notice
#   and this notice are preserved. This file is offered as-is, without any
#   warranty.

AC_DEFUN([AX_POWERPC_SIMD], [
case $build_cpu:$build_os in
    powerpc*:aix5.3*|powerpc*:aix[67]*)
        AX_POWERPC_SIMD_AIX
    ;;
    powerpc*:linux*)
        AX_POWERPC_SIMD_LINUX
    ;;
esac
])

AC_DEFUN([AX_POWERPC_SIMD_LINUX], [
  AX_POWERPC_CPUID([altivec])
  AX_POWERPC_CPUID([vsx])
])

# wrapper
AC_DEFUN([AX_POWERPC_CPUID], [AX_POWERPC_CPUID_INT($1, m4_toupper([$1]))])

# internal function
AC_DEFUN([AX_POWERPC_CPUID_INT],
[AC_REQUIRE([AC_PROG_CC])
AC_LANG_PUSH([C])
AC_CACHE_CHECK([for powerpc $1 feature], [ax_cv_powerpc_$1],
 [AC_RUN_IFELSE([AC_LANG_PROGRAM([
#include <sys/types.h>
#include <sys/stat.h>
#include <fcntl.h>
#include <unistd.h>
#include <stdio.h>

#include <linux/auxvec.h>
#include <asm/cputable.h>

static int available = -1; 	
 	],
 	[[
	int is_avail = 0;
	
	char fname[64];
	unsigned long buf[64];
	ssize_t count;
	pid_t pid;
	int fd, i;
	
	if (available != -1)
		return available;

	pid = getpid();
	snprintf(fname, sizeof(fname)-1, "/proc/%d/auxv", pid);

	fd = open(fname, O_RDONLY);
	if (fd < 0)
		goto out;
 more:
	count = read(fd, buf, sizeof(buf));
	if (count < 0)
		goto out_close;
	
	for (i=0; i < (count / sizeof(unsigned long)); i += 2) {
		if (buf[i] == AT_HWCAP) {
			is_avail = !!(buf[i+1] & PPC_FEATURE_HAS_$2);
			goto out_close;
		} else if (buf[i] == AT_NULL) {
			goto out_close;
		}
	}

	if (count == sizeof(buf))
		goto more;
 out_close:
	close(fd);
 out:
	available = is_avail;
	return available; 	
 	]])],
     [ax_cv_powerpc_$1=no],
     [ax_cv_powerpc_$1=yes],
     [ax_cv_powerpc_$1=no])])
AC_LANG_POP([C])
])

AC_DEFUN([AX_POWERPC_SIMD_AIX], [
  AC_LANG_PUSH([C])
  AC_CHECK_DECL([__power_vmx], [], [], [/usr/include/sys/systemcfg.h])
  if test "x$ac_cv_have_decl___power_vmx" = xyes; then
    AC_CACHE_CHECK([for powerpc altivec/vsx features], [ax_cv_powerpc_altivec],
     [AC_RUN_IFELSE([AC_LANG_PROGRAM([
#include <sys/systemcfg.h>
     ], [
     int available = 0;
     unsigned long has_altivec = __power_vmx();
     available = !! has_altivec;

     return available;
      ])],
     [ax_cv_powerpc_altivec=no],
     [ax_cv_powerpc_altivec=yes],
     [ax_cv_powerpc_altivec=no])])
  else
     [ax_cv_powerpc_altivec=no]
  fi
  AC_LANG_POP([C])
])




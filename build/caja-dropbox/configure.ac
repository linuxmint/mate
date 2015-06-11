# Initialization

AC_INIT([caja-dropbox], [1.10.0], [http://www.mate-desktop.org/])

AM_INIT_AUTOMAKE([1.9 tar-ustar dist-xz foreign no-dist-gzip])

AC_CONFIG_MACRO_DIR([m4])
AC_PREFIX_DEFAULT(/usr)

AC_CONFIG_HEADERS(config.h)

# not ready for i18n yet
#AC_PROG_INTLTOOL([0.29])

# Dependency checks
CAJA_REQUIRED=1.1.0
GLIB_REQUIRED=2.14.0

# Used programs
AC_PROG_CC
AM_PROG_LIBTOOL

# Check for pkg-config
AC_CHECK_PROG(HAVE_PKGCONFIG, pkg-config, yes, no)
AC_PATH_PROG(PKG_CONFIG, pkg-config, no)
if test "x$HAVE_PKGCONFIG" = "xno"; then
	AC_MSG_ERROR(you need to have pkgconfig installed !)
fi

PKG_CHECK_MODULES(CAJA, libcaja-extension >= $CAJA_REQUIRED)
PKG_CHECK_MODULES(GLIB, glib-2.0 >= $GLIB_REQUIRED)

AC_PATH_PROG([PYTHON], [python])

AC_PATH_PROG([RST2MAN], [rst2man], [python rst2man.py])
AC_SUBST(RST2MAN)

# define module checking macro
AC_DEFUN([PYTHON_CHECK_MODULE], [
AC_MSG_CHECKING([for $1])

cat <<EOF | python
try:
 import $2
except:
 exit(1)
else:
 exit(0)
EOF

if test $? -ne 0; then
   AC_MSG_RESULT([no])
   AC_MSG_ERROR([couldn't find $1])
else
   AC_MSG_RESULT([yes])
fi
])

PYTHON_CHECK_MODULE(pygtk, gtk)
PYTHON_CHECK_MODULE(gobject, gobject)
PYTHON_CHECK_MODULE(docutils, docutils)

# Make dependency CFLAGS and LIBS available
AC_SUBST(CAJA_CFLAGS)
AC_SUBST(CAJA_LIBS)
AC_SUBST(GLIB_CFLAGS)
AC_SUBST(GLIB_LIBS)

# lol stolen from the automake manual
AC_ARG_ENABLE([debug],
[  --enable-debug    Turn on debugging],
[case "${enableval}" in
yes) debug=true ;;
no)  debug=false ;;
*) AC_MSG_ERROR([bad value ${enableval} for --enable-debug]) ;;
esac],[debug=false])
AM_CONDITIONAL([DEBUG], [test x$debug = xtrue])

AC_ARG_WITH(caja-extension-dir,
              [AS_HELP_STRING([--with-caja-extension-dir],
                    [specify the caja extension directory])])

# Get caja extensions directory
AC_MSG_CHECKING([for caja extension directory])
if test -n "$with_caja_extension_dir"; then
    CAJA_EXTENSION_DIR=$with_caja_extension_dir
else
    CAJA_EXTENSION_DIR=`$PKG_CONFIG --variable=extensiondir libcaja-extension`
fi
if test -z "$CAJA_EXTENSION_DIR"; then
    CAJA_EXTENSION_DIR='${exec_prefix}/lib/caja/extension-1.0'
fi

AC_MSG_RESULT([${CAJA_EXTENSION_DIR}])
AC_SUBST(CAJA_EXTENSION_DIR)

CAJA_VERSION=`$PKG_CONFIG --modversion libcaja-extension`
if test -n "$CAJA_VERSION"; then
    CAJA_VERSION_MAJOR=`echo -n $CAJA_VERSION | cut -d . -f 1`
    CAJA_VERSION_MINOR=`echo -n $CAJA_VERSION | cut -d . -f 2`
    CAJA_VERSION_MICRO=`echo -n $CAJA_VERSION | cut -d . -f 3`
fi

AC_DEFINE_UNQUOTED(CAJA_VERSION_MAJOR, [$CAJA_VERSION_MAJOR], [ caja version major])
AC_DEFINE_UNQUOTED(CAJA_VERSION_MINOR, [$CAJA_VERSION_MINOR], [ caja version minor])
AC_DEFINE_UNQUOTED(CAJA_VERSION_MICRO, [$CAJA_VERSION_MICRO], [ caja version micro])

EMBLEM_DIR='${datadir}/caja-dropbox/emblems'
AC_SUBST(EMBLEM_DIR)

AC_CONFIG_FILES([
	Makefile
	src/Makefile
	data/Makefile
	data/libcaja-dropbox.caja-extension
	data/icons/Makefile
	data/icons/hicolor/Makefile
	data/icons/hicolor/16x16/Makefile
	data/icons/hicolor/16x16/apps/Makefile
	data/icons/hicolor/22x22/Makefile
	data/icons/hicolor/22x22/apps/Makefile
	data/icons/hicolor/24x24/Makefile
	data/icons/hicolor/24x24/apps/Makefile
	data/icons/hicolor/32x32/Makefile
	data/icons/hicolor/32x32/apps/Makefile
	data/icons/hicolor/48x48/Makefile
	data/icons/hicolor/48x48/apps/Makefile
	data/icons/hicolor/64x64/Makefile
	data/icons/hicolor/64x64/apps/Makefile
	data/icons/hicolor/256x256/Makefile
	data/icons/hicolor/256x256/apps/Makefile
	data/emblems/Makefile])

AC_OUTPUT

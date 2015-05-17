AC_PREREQ(2.60)

AC_INIT([mate-media],
        [1.8.0],
        [http://www.mate-desktop.org/])

AC_CONFIG_AUX_DIR([build-aux])

AM_INIT_AUTOMAKE([1.9 no-dist-gzip dist-xz -Wall -Wno-portability tar-pax foreign check-news])

AM_MAINTAINER_MODE

if type -p stow > /dev/null && test -d /usr/local/stow ; then
   AC_MSG_NOTICE([*** Found /usr/local/stow: default install prefix set to /usr/local/stow/${PACKAGE}-${VERSION} ***])
   ac_default_prefix="/usr/local/stow/${PACKAGE}-${VERSION}"
fi

AC_CONFIG_HEADERS([config.h])
AC_CONFIG_MACRO_DIR([m4])

IT_PROG_INTLTOOL([0.35.0])

AC_PROG_CC
AC_ISC_POSIX

# Checks for programs.
AC_PROG_INSTALL
AC_PROG_LN_S
AC_PROG_MAKE_SET

# Checks for header files.
AC_HEADER_STDC
AC_CHECK_HEADERS([fcntl.h limits.h malloc.h strings.h sys/ioctl.h unistd.h])
AC_CHECK_HEADERS([sys/sockio.h sys/param.h])

# Checks for typedefs, structures, and compiler characteristics.
AC_C_CONST
AC_C_INLINE
AC_TYPE_OFF_T
AC_TYPE_SIZE_T

# Checks for library functions.
AC_PROG_GCC_TRADITIONAL
AC_FUNC_MMAP

GLIB_REQUIRED_VERSION=2.18.2
GIO_REQUIRED_VERSION=2.25.0
PA_REQUIRED_VERSION=0.9.16
CANBERRA_REQUIRED_VERSION=0.13
MATE_DESKTOP_REQUIRED_VERSION=1.7.3
MATE_PANEL_REQUIRED_VERSION=1.7.0

dnl=======================================================================
dnl Support multiple GTK versions
dnl=======================================================================

AC_MSG_CHECKING([which gtk+ version to compile against])
AC_ARG_WITH([gtk],
  [AS_HELP_STRING([--with-gtk=2.0|3.0],[which gtk+ version to compile against (default: 2.0)])],
  [case "$with_gtk" in
     2.0|3.0) ;;
     *) AC_MSG_ERROR([invalid gtk version specified]) ;;
   esac],
  [with_gtk=2.0])
AC_MSG_RESULT([$with_gtk])

case "$with_gtk" in
  2.0) GTK_API_VERSION=2.0
       GTK_REQUIRED_VERSION=2.24.0
       CANBERRA_API_VERSION=
       UNIQUE_API_VERSION=1.0
       ;;
  3.0) GTK_API_VERSION=3.0
       GTK_REQUIRED_VERSION=3.0.0
       CANBERRA_API_VERSION=3
       UNIQUE_API_VERSION=3.0
       ;;
esac

dnl=======================================================================
dnl Check for libcanberra
dnl=======================================================================

PKG_CHECK_MODULES(SOUND_THEME,
        gobject-2.0 >= $GLIB_REQUIRED_VERSION
        gtk+-$GTK_API_VERSION >= $GTK_REQUIRED_VERSION
        gio-2.0 >= $GIO_REQUIRED_VERSION
        libcanberra-gtk$CANBERRA_API_VERSION >= $CANBERRA_REQUIRED_VERSION
        libxml-2.0,
        have_soundtheme=yes,
        have_soundtheme=no)

if test "x$have_soundtheme" = "xyes" ; then
  AC_DEFINE(HAVE_SOUND_THEME, [], [Define if we can build sound theme])
fi
AM_CONDITIONAL(HAVE_SOUND_THEME, test x$have_soundtheme = xyes)
AC_SUBST(HAVE_SOUND_THEME)
AC_SUBST(SOUNDTHEME_CFLAGS)
AC_SUBST(SOUNDTHEME_LIBS)

dnl=======================================================================
dnl Check for the new volume control modules
dnl=======================================================================

AC_ARG_ENABLE([pulseaudio],
              AS_HELP_STRING([--enable-pulseaudio],
                             [Enable PulseAudio support @<:@default=auto@:>@]),
              enable_pulseaudio=$enableval, enable_pulseaudio=auto)

if test "x$enable_pulseaudio" != "xno"; then

  PKG_CHECK_MODULES(PULSEAUDIO,
          libpulse >= $PA_REQUIRED_VERSION libpulse-mainloop-glib >= $PA_REQUIRED_VERSION,
          have_pulseaudio=yes,
          have_pulseaudio=no)

  if test "x$enable_pulseaudio" = "xyes" -a "x$have_pulseaudio" = "xno"; then
    AC_MSG_ERROR([PulseAudio support explicitly requested but dependencies not found])
  fi

  if test "x$have_pulseaudio" = "xyes" ; then
    PKG_CHECK_MODULES(VOLUME_CONTROL,
            gobject-2.0 >= $GLIB_REQUIRED_VERSION
            gtk+-$GTK_API_VERSION >= $GTK_REQUIRED_VERSION
            gio-2.0 >= $GIO_REQUIRED_VERSION
            libcanberra-gtk$CANBERRA_API_VERSION >= $CANBERRA_REQUIRED_VERSION
            unique-$UNIQUE_API_VERSION
            libxml-2.0
            mate-desktop-2.0 >= $MATE_DESKTOP_REQUIRED_VERSION
    )

    AC_SUBST(VOLUME_CONTROL_CFLAGS)
    AC_SUBST(VOLUME_CONTROL_LIBS)
    
    if $PKG_CONFIG --atleast-version 2.26 glib-2.0; then
        VOLUME_CONTROL_CFLAGS="$VOLUME_CONTROL_CFLAGS -DG_CONST_RETURN=const"
    fi
    
    AC_DEFINE(HAVE_PULSEAUDIO, [], [Define if we have pulseaudio])
  fi
else
  have_pulseaudio=no
fi
AM_CONDITIONAL(HAVE_PULSEAUDIO, test x$have_pulseaudio = xyes)
AC_SUBST(HAVE_PULSEAUDIO)
AC_SUBST(PULSEAUDIO_CFLAGS)
AC_SUBST(PULSEAUDIO_LIBS)

dnl=======================================================================
dnl Check for GStreamer deps
dnl=======================================================================

GST_REQ=0.10.23
GST_PLUGINS_BASE_REQ=0.10.23
GST_MAJORMINOR=0.10

dnl make available to Makefile.am
AC_SUBST(GST_MAJORMINOR)
AC_DEFINE_UNQUOTED(GST_MAJORMINOR_QUOTED, "$GST_MAJORMINOR",
  [major/minor of GStreamer as a string constant])

have_gst=no

PKG_CHECK_MODULES(GSR, [
  gstreamer-$GST_MAJORMINOR >= $GST_REQ
  gstreamer-plugins-base-$GST_MAJORMINOR >= $GST_REQ
  gtk+-$GTK_API_VERSION >= $GTK_REQUIRED_VERSION
  gio-2.0 >= $GIO_REQUIRED_VERSION],
  have_gst=yes,
  [
    AC_MSG_RESULT(no)
    AC_MSG_WARN($GSR_PKG_ERRORS)
    PROGRAMS_GRECORD_ERROR="$GSR_PKG_ERRORS"
  ])

AC_SUBST(GSR_CFLAGS)
AC_SUBST(GSR_LIBS)
AM_CONDITIONAL(HAVE_GSTREAMER, [test x$have_gst = xyes])

GLIB_GSETTINGS

AC_PATH_PROG(GLIB_GENMARSHAL, glib-genmarshal)

dnl=======================================================================
dnl i18n
dnl=======================================================================

GETTEXT_PACKAGE=mate-media
AC_SUBST(GETTEXT_PACKAGE)
AC_DEFINE_UNQUOTED(GETTEXT_PACKAGE, "$GETTEXT_PACKAGE", [Define to the Gettext package name])
AM_GLIB_GNU_GETTEXT

YELP_HELP_INIT

AM_PROG_LIBTOOL
AM_PROG_CC_C_O

dnl=======================================================================
dnl gst-mixer
dnl=======================================================================

have_gstmixer=no

AC_ARG_ENABLE([gstmix],
  AS_HELP_STRING([--enable-gstmix], [enable gstreamer mixer]),
  ,enable_gstmix=auto)

if test "x$enable_gstmix" = "xauto" && test "x$have_pulseaudio" = "xno"; then
  enable_gstmix=yes
fi

if test "x$have_gst" = "xyes" && test "x$enable_gstmix" = "xyes";
then
  PKG_CHECK_MODULES(GSTMIXER, [
    gtk+-$GTK_API_VERSION
    gio-2.0 >= $GIO_REQUIRED_VERSION
    gstreamer-$GST_MAJORMINOR
    gstreamer-plugins-base-$GST_MAJORMINOR
  ],
  [
    OLD_CPPFLAGS=$CPPFLAGS
    CPPFLAGS="$CPPFLAGS $GSTMIXER_CFLAGS"

    AC_CHECK_HEADER(gst/audio/mixerutils.h,
      [AC_CHECK_HEADER(gst/interfaces/mixer.h,
        [AC_CHECK_HEADER(gst/interfaces/propertyprobe.h, have_gstmixer=yes)])])

    CPPFLAGS=$OLD_CPPFLAGS
    GSTMIXER_LIBS="$GSTMIXER_LIBS -lgstinterfaces-$GST_MAJORMINOR -lgstaudio-$GST_MAJORMINOR"
  ])
fi

AC_SUBST(GSTMIXER_CFLAGS)
AC_SUBST(GSTMIXER_LIBS)
AM_CONDITIONAL(HAVE_GSTMIXER, [test x$have_gstmixer = xyes])

dnl=======================================================================
dnl gst-mixer-applet
dnl=======================================================================
have_gstmixer_applet=no
if test "x$have_gstmixer" = "xyes"; then
    AC_ARG_ENABLE([gst-mixer-applet],
        AC_HELP_STRING([--enable-gst-mixer-applet], [Enable the gstreamer-based mixer applet.]),
        enable_mixerapplet=$enableval,
        enable_mixerapplet=no)
    if test "x$enable_mixerapplet" != "xno"; then
        have_gstmixer_applet=yes
        MIXERAPPLET_DEPS="gstreamer-$GST_MAJORMINOR >= $GST_REQ
                           gstreamer-interfaces-$GST_MAJORMINOR >= $GST_REQ
                           gstreamer-audio-$GST_MAJORMINOR >= $GST_REQ
                           mate-desktop-2.0 >= $MATE_DESKTOP_REQUIRED_VERSION
                           libmatepanelapplet-4.0 >= $MATE_PANEL_REQUIRED_VERSION"
        PKG_CHECK_MODULES(MIXERAPPLET, $MIXERAPPLET_DEPS, have_gst_mixer_applet_deps=yes, have_gst_mixer_applet_deps=no)
        if test "x$have_gst_mixer_applet_deps" = "xno"; then
            have_gstmixer_applet=no
            enable_mixerapplet=no
            AC_MSG_ERROR([Mixer applet explicitly requested but a compatible gstreamer version was not found])
        fi
    fi
    AC_SUBST(MIXERAPPLET_CFLAGS)
    AC_SUBST(MIXERAPPLET_LIBS)
fi
AM_CONDITIONAL(HAVE_GSTMIXER_APPLET, test "x$have_gstmixer_applet" = "xyes")

dnl ---------------------------------------------------------------------------
dnl - Finish
dnl ---------------------------------------------------------------------------

m4_ifdef([AM_SILENT_RULES],[AM_SILENT_RULES([yes])])

MATE_MAINTAINER_MODE_DEFINES
MATE_COMPILE_WARNINGS([maximum])
MATE_CXX_WARNINGS

AC_ARG_ENABLE(deprecated,
        [AS_HELP_STRING([--enable-deprecated],
                [warn about deprecated usages [default=no]])],,
         [enable_deprecated=no])

if test "x$enable_deprecated" = "xyes"; then
   DISABLE_DEPRECATED=""
     AC_SUBST(DISABLE_DEPRECATED)
fi

# Turn on the additional warnings last, so warnings don't affect other tests.
AC_ARG_ENABLE(more-warnings,
        [AC_HELP_STRING([--enable-more-warnings],
        [Maximum compiler warnings])],
        set_more_warnings="$enableval",[
                if test -d $srcdir/.git; then
                        set_more_warnings=yes
                else
                        set_more_warnings=no
                fi
        ])
AC_MSG_CHECKING(for more warnings)
if test "$GCC" = "yes" -a "$set_more_warnings" != "no"; then
        AC_MSG_RESULT(yes)
        CFLAGS="\
        -Wall \
        -Wchar-subscripts -Wmissing-declarations -Wmissing-prototypes \
        -Wnested-externs -Wpointer-arith \
        -Wcast-align -Wsign-compare \
        $CFLAGS"

        for option in -Wno-unused-parameter -Wno-strict-aliasing -Wno-sign-compare; do
                SAVE_CFLAGS="$CFLAGS"
                CFLAGS="$CFLAGS $option"
                AC_MSG_CHECKING([whether gcc understands $option])
                AC_TRY_COMPILE([], [],
                        has_option=yes,
                        has_option=no,)
                if test $has_option = no; then
                        CFLAGS="$SAVE_CFLAGS"
                fi
                AC_MSG_RESULT($has_option)
                unset has_option
                unset SAVE_CFLAGS
        done
        unset option
else
        AC_MSG_RESULT(no)
fi


AC_SUBST(CFLAGS)
AC_SUBST(CPPFLAGS)
AC_SUBST(LIBS)
AC_SUBST(LDFLAGS)

AC_CONFIG_FILES([
Makefile
man/Makefile
po/Makefile.in
sound-theme/Makefile
sound-theme/sounds/Makefile
mate-volume-control/Makefile
mate-volume-control/data/Makefile
mate-volume-control/data/mate-volume-control.desktop.in
mate-volume-control/data/icons/Makefile
mate-volume-control/data/icons/16x16/Makefile
mate-volume-control/data/icons/16x16/status/Makefile
mate-volume-control/data/icons/22x22/Makefile
mate-volume-control/data/icons/22x22/status/Makefile
mate-volume-control/data/icons/24x24/Makefile
mate-volume-control/data/icons/24x24/status/Makefile
mate-volume-control/data/icons/32x32/Makefile
mate-volume-control/data/icons/32x32/status/Makefile
mate-volume-control/data/icons/scalable/Makefile
mate-volume-control/data/icons/scalable/devices/Makefile
mate-volume-control/data/icons/scalable/status/Makefile
mate-volume-control/src/Makefile
gst-mixer/Makefile
gst-mixer/icons/Makefile
gst-mixer/icons/16x16/Makefile
gst-mixer/icons/16x16/devices/Makefile
gst-mixer/icons/16x16/status/Makefile
gst-mixer/src/Makefile
gst-mixer/pixmaps/Makefile
gst-mixer/doc/Makefile
gst-mixer/mate-volume-control.desktop.in
gst-mixer-applet/Makefile
gst-mixer-applet/docs/Makefile
])

AC_OUTPUT

echo "

                    ${PACKAGE} ${VERSION}
                    ============


        Prefix:                      ${prefix}
        Source code location:        ${srcdir}
        Compiler:                    ${CC}
        CFLAGS:                      ${CFLAGS}

        GTK+ API version:            ${GTK_API_VERSION}

        PulseAudio Volume Control:   $have_pulseaudio

        GStreamer mixer:             $have_gstmixer
        GStreamer mixer applet:      $have_gstmixer_applet

"

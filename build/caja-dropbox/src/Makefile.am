AM_CPPFLAGS =						\
	-I$(top_srcdir)					\
	-I$(top_builddir)

caja_extensiondir=$(CAJA_EXTENSION_DIR)

caja_extension_LTLIBRARIES=libcaja-dropbox.la

libcaja_dropbox_la_CFLAGS = 	                \
	-DDATADIR=\"$(datadir)\"					    \
	-DEMBLEMDIR=\"$(EMBLEM_DIR)\"					\
	-Wall                                           \
	$(WARN_CFLAGS)                                  \
	$(DISABLE_DEPRECATED_CFLAGS)					\
	$(CAJA_CFLAGS)                              \
	$(GLIB_CFLAGS)

if DEBUG
libcaja_dropbox_la_CFLAGS += -DND_DEBUG
else
libcaja_dropbox_la_CFLAGS += -DG_DISABLE_ASSERT -DG_DISABLE_CHECKS
endif

libcaja_dropbox_la_SOURCES = \
	caja-dropbox.c       \
	caja-dropbox.h       \
	caja-dropbox-hooks.h \
	caja-dropbox-hooks.c \
	dropbox-command-client.h \
	dropbox-command-client.c \
	dropbox-client.c dropbox-client.h \
	g-util.h \
	async-io-coroutine.h \
	dropbox-client-util.c \
	dropbox-client-util.h \
	dropbox.c

libcaja_dropbox_la_LDFLAGS = -module -avoid-version
libcaja_dropbox_la_LIBADD  = $(CAJA_LIBS) $(GLIB_LIBS)

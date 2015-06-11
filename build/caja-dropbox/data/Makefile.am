applicationdir = $(datadir)/applications
application_DATA = caja-dropbox.desktop

extensiondir = $(datadir)/caja/extensions
extension_in_files = libcaja-dropbox.caja-extension.in
extension_DATA = $(extension_in_files:.caja-extension.in=.caja-extension)

EXTRA_DIST = $(application_DATA)

CLEANFILES = $(extension_data)

SUBDIRS = icons emblems

/*
 * Copyright 2008 Evenflow, Inc.
 *
 * caja-dropbox.h
 * Header file for caja-dropbox.c
 *
 * This file is part of caja-dropbox.
 *
 * caja-dropbox is free software: you can redistribute it and/or modify
 * it under the terms of the GNU General Public License as published by
 * the Free Software Foundation, either version 3 of the License, or
 * (at your option) any later version.
 *
 * caja-dropbox is distributed in the hope that it will be useful,
 * but WITHOUT ANY WARRANTY; without even the implied warranty of
 * MERCHANTABILITY or FITNESS FOR A PARTICULAR PURPOSE.  See the
 * GNU General Public License for more details.
 *
 * You should have received a copy of the GNU General Public License
 * along with caja-dropbox.  If not, see <http://www.gnu.org/licenses/>.
 *
 */

#ifndef CAJA_DROPBOX_H
#define CAJA_DROPBOX_H

#include <glib.h>
#include <glib-object.h>

#include <libcaja-extension/caja-info-provider.h>

#include "dropbox-command-client.h"
#include "caja-dropbox-hooks.h"
#include "dropbox-client.h"

G_BEGIN_DECLS

/* Declarations for the dropbox extension object.  This object will be
 * instantiated by caja.  It implements the GInterfaces
 * exported by libcaja. */

#define CAJA_TYPE_DROPBOX	  (caja_dropbox_get_type ())
#define CAJA_DROPBOX(o)	  (G_TYPE_CHECK_INSTANCE_CAST ((o), CAJA_TYPE_DROPBOX, CajaDropbox))
#define CAJA_IS_DROPBOX(o)	  (G_TYPE_CHECK_INSTANCE_TYPE ((o), CAJA_TYPE_DROPBOX))
typedef struct _CajaDropbox      CajaDropbox;
typedef struct _CajaDropboxClass CajaDropboxClass;

struct _CajaDropbox {
  GObject parent_slot;
  GHashTable *filename2obj;
  GHashTable *obj2filename;
  GMutex *emblem_paths_mutex;
  GHashTable *emblem_paths;
  DropboxClient dc;
};

struct _CajaDropboxClass {
	GObjectClass parent_slot;
};

GType caja_dropbox_get_type(void);
void  caja_dropbox_register_type(GTypeModule *module);

extern gboolean dropbox_use_caja_submenu_workaround;
extern gboolean dropbox_use_operation_in_progress_workaround;

G_END_DECLS

#endif

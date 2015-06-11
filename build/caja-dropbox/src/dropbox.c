/*
 * Copyright 2008 Evenflow, Inc.
 *
 * dropbox.c
 * Caja module registering functions for the Dropbox extension.
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

#ifdef HAVE_CONFIG_H
#include <config.h>
#endif

#include <glib-object.h>

#include <gdk/gdk.h>
#include <gtk/gtk.h>

#include "caja-dropbox.h"

static GType type_list[1];

void
caja_module_initialize (GTypeModule *module) {
  g_print ("Initializing %s\n", PACKAGE_STRING);

  caja_dropbox_register_type (module);
  type_list[0] = CAJA_TYPE_DROPBOX;

  dropbox_use_caja_submenu_workaround = FALSE;
  dropbox_use_operation_in_progress_workaround = TRUE;
}

void
caja_module_shutdown (void) {
  g_print ("Shutting down dropbox extension\n");
}

void
caja_module_list_types (const GType **types,
                            int *num_types) {
  *types = type_list;
  *num_types = G_N_ELEMENTS (type_list);
}

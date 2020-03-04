#pragma once

#if !defined(__HARVEST_HEADER_INTERNAL__) && !defined(__HARVEST_COMPILATION__)
#	error "Only <harvest-glib/harvest.h> can be included directly."
#endif

#include <glib-object.h>

G_BEGIN_DECLS

GType harvest_estimate_state_get_type(void) G_GNUC_CONST;
#define HARVEST_TYPE_ESTIMATE_STATE (harvest_estimate_state_get_type())

G_END_DECLS

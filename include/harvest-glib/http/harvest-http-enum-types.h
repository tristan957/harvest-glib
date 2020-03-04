#pragma once

#if !defined(__HARVEST_HEADER_INTERNAL__) && !defined(__HARVEST_COMPILATION__)
#	error "Only <harvest-glib/harvest.h> can be included directly."
#endif

#include <glib-object.h>

G_BEGIN_DECLS

GType http_method_get_type(void) G_GNUC_CONST;
#define HTTP_TYPE_METHOD (http_method_get_type())

GType http_status_code_get_type(void) G_GNUC_CONST;
#define HTTP_TYPE_STATUS_CODE (http_status_code_get_type())

G_END_DECLS

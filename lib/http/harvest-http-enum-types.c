#include <gio/gio.h>

#include "harvest-glib/http/harvest-http.h"

#define C_ENUM(v)  ((gint) v)
#define C_FLAGS(v) ((guint) v)

GType
http_method_get_type(void)
{
	static volatile gsize g_define_type_id__volatile = 0;
	// clang-format off
	static const GEnumValue values[] = {
		{ C_ENUM(HTTP_METHOD_GET), "HTTP_METHOD_GET", "GET" },
		{ C_ENUM(HTTP_METHOD_POST), "HTTP_METHOD_POST", "POST" },
		{ C_ENUM(HTTP_METHOD_PATCH), "HTTP_METHOD_PATCH", "PATCH" },
		{ C_ENUM(HTTP_METHOD_DELETE), "HTTP_METHOD_DELETE", "DELETE" },
		{ 0, NULL, NULL }
	};
	// clang-format on

	if (g_once_init_enter(&g_define_type_id__volatile)) {
		GType g_define_type_id
			= g_enum_register_static(g_intern_static_string("HttpMethod"), values);
		g_once_init_leave(&g_define_type_id__volatile, g_define_type_id);
	}

	return g_define_type_id__volatile;
}

GType
http_status_code_get_type(void)
{
	static volatile gsize g_define_type_id__volatile = 0;
	// clang-format off
	static const GEnumValue values[] = {
		{ C_ENUM(HTTP_STATUS_OK), "HTTP_STATUS_OK", "OK" },
		{ C_ENUM(HTTP_STATUS_CREATED), "HTTP_STATUS_CREATED", "Created" },
		{ C_ENUM(HTTP_STATUS_FORBIDDEN), "HTTP_STATUS_FORBIDDEN", "Forbidden" },
		{ C_ENUM(HTTP_STATUS_NOT_FOUND), "HTTP_STATUS_NOT_FOUND", "NotFound" },
		{ C_ENUM(HTTP_STATUS_UNPROCESSABLE), "HTTP_STATUS_UNPROCESSABLE", "Unprocessable" },
		{ C_ENUM(HTTP_STATUS_TOO_MANY_REQUESTS), "HTTP_STATUS_TOO_MANY_REQUESTS", "TooManyRequests" },
		{ C_ENUM(HTTP_STATUS_INTERNAL_SERVER_ERROR), "HTTP_STATUS_INTERNAL_SERVER_ERROR", "InternalServerError" },
		{ 0, NULL, NULL }
	};
	// clang-format on

	if (g_once_init_enter(&g_define_type_id__volatile)) {
		GType g_define_type_id
			= g_enum_register_static(g_intern_static_string("HttpStatusCode"), values);
		g_once_init_leave(&g_define_type_id__volatile, g_define_type_id);
	}

	return g_define_type_id__volatile;
}

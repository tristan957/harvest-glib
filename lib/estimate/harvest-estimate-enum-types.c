#include <gio/gio.h>

#include "harvest-glib/estimate/harvest-estimate-enum-types.h"
#include "harvest-glib/estimate/harvest-estimate.h"

#define C_ENUM(v)  ((gint) v)
#define C_FLAGS(v) ((guint) v)

GType
harvest_estimate_state_get_type(void)
{
	static volatile gsize g_define_type_id__volatile = 0;
	// clang-format off
	static const GEnumValue values[] = {
		{ C_ENUM(HARVEST_ESTIMATE_STATE_DRAFT), "HARVEST_ESTIMATE_STATE_DRAFT", "draft" },
		{ C_ENUM(HARVEST_ESTIMATE_STATE_SENT), "HARVEST_ESTIMATE_STATE_SENT", "sent" },
		{ C_ENUM(HARVEST_ESTIMATE_STATE_ACCEPTED), "HARVEST_ESTIMATE_STATE_ACCEPTED", "accepted" },
		{ C_ENUM(HARVEST_ESTIMATE_STATE_DECLINED), "HARVEST_ESTIMATE_STATE_DECLINED", "declined" },
		{ 0, NULL, NULL }
	};
	// clang-format on

	if (g_once_init_enter(&g_define_type_id__volatile)) {
		GType g_define_type_id
			= g_enum_register_static(g_intern_static_string("HarvestEstimateState"), values);
		g_once_init_leave(&g_define_type_id__volatile, g_define_type_id);
	}

	return g_define_type_id__volatile;
}

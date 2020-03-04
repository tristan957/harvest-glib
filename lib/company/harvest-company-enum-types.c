#include <gio/gio.h>

#include "harvest-glib/company/harvest-company-enum-types.h"
#include "harvest-glib/company/harvest-company.h"

#define C_ENUM(v)  ((gint) v)
#define C_FLAGS(v) ((guint) v)

GType
harvest_week_start_day_get_type(void)
{
	static volatile gsize g_define_type_id__volatile = 0;

	if (g_once_init_enter(&g_define_type_id__volatile)) {
		// clang-format off
		static const GEnumValue values[] = {
			{ C_ENUM(HARVEST_WEEK_START_DAY_SATURDAY), "HARVEST_WEEK_START_DAY_SATURDAY", "Saturday" },
			{ C_ENUM(HARVEST_WEEK_START_DAY_SUNDAY), "HARVEST_WEEK_START_DAY_SUNDAY", "Sunday" },
			{ C_ENUM(HARVEST_WEEK_START_DAY_MONDAY), "HARVEST_WEEK_START_DAY_MONDAY", "Monday" },
			{ 0, NULL, NULL }
		};
		// clang-format on

		GType g_define_type_id
			= g_enum_register_static(g_intern_static_string("HarvestWeekStartDay"), values);
		g_once_init_leave(&g_define_type_id__volatile, g_define_type_id);
	}

	return g_define_type_id__volatile;
}

GType
harvest_time_format_get_type(void)
{
	static volatile gsize g_define_type_id__volatile = 0;

	if (g_once_init_enter(&g_define_type_id__volatile)) {
		// clang-format off
		static const GEnumValue values[] = {
			{ C_ENUM(HARVEST_TIME_FORMAT_DECIMAL), "HARVEST_TIME_FORMAT_DECIMAL", "decimal" },
			{ C_ENUM(HARVEST_TIME_FORMAT_HOURS_MINUTES), "HARVEST_TIME_FORMAT_HOURS_MINUTES", "hours_minutes" },
			{ 0, NULL, NULL }
		};
		// clang-format on

		GType g_define_type_id
			= g_enum_register_static(g_intern_static_string("HarvestTimeFormat"), values);
		g_once_init_leave(&g_define_type_id__volatile, g_define_type_id);
	}

	return g_define_type_id__volatile;
}

GType
harvest_plan_type_get_type(void)
{
	static volatile gsize g_define_type_id__volatile = 0;

	if (g_once_init_enter(&g_define_type_id__volatile)) {
		// clang-format off
		static const GEnumValue values[] = {
			{ C_ENUM(HARVEST_PLAN_TYPE_TRIAL), "HARVEST_PLAN_TYPE_TRIAL", "trial" },
			{ C_ENUM(HARVEST_PLAN_TYPE_FREE), "HARVEST_PLAN_TYPE_FREE", "free" },
			{ C_ENUM(HARVEST_PLAN_TYPE_SIMPLE_V4), "HARVEST_PLAN_TYPE_SIMPLE_V4", "simple-v4" },
			{ C_ENUM(HARVEST_PLAN_TYPE_BUSINESS), "HARVEST_PLAN_TYPE_BUSINESS", "business" },
			{ 0, NULL, NULL}
		};
		// clang-format on

		GType g_define_type_id
			= g_enum_register_static(g_intern_static_string("HarvestPlanType"), values);
		g_once_init_leave(&g_define_type_id__volatile, g_define_type_id);
	}

	return g_define_type_id__volatile;
}

GType
harvest_clock_get_type(void)
{
	static volatile gsize g_define_type_id__volatile = 0;

	if (g_once_init_enter(&g_define_type_id__volatile)) {
		// clang-format off
		static const GEnumValue values[] = {
			{ C_ENUM(HARVEST_CLOCK_12H), "HARVEST_CLOCK_12H", "12h" },
			{ C_ENUM(HARVEST_CLOCK_24H), "HARVEST_CLOCK_24H", "24h" },
			{ 0, NULL, NULL }
		};
		// clang-format on

		GType g_define_type_id
			= g_enum_register_static(g_intern_static_string("HarvestClock"), values);
		g_once_init_leave(&g_define_type_id__volatile, g_define_type_id);
	}

	return g_define_type_id__volatile;
}

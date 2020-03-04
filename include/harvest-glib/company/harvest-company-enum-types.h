#pragma once

#if !defined(__HARVEST_HEADER_INTERNAL__) && !defined(__HARVEST_COMPILATION__)
#	error "Only <harvest-glib/harvest.h> can be included directly."
#endif

#include <glib-object.h>

G_BEGIN_DECLS

GType harvest_week_start_day_get_type(void) G_GNUC_CONST;
#define HARVEST_TYPE_WEEK_START_DAY (harvest_week_start_day_get_type())

GType harvest_time_format_get_type(void) G_GNUC_CONST;
#define HARVEST_TYPE_TIME_FORMAT (harvest_time_format_get_type())

GType harvest_plan_type_get_type(void) G_GNUC_CONST;
#define HARVEST_TYPE_PLAN_TYPE (harvest_plan_type_get_type())

GType harvest_clock_get_type(void) G_GNUC_CONST;
#define HARVEST_TYPE_CLOCK (harvest_clock_get_type())

G_END_DECLS

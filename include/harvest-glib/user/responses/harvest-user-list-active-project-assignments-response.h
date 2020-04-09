#pragma once

#if !defined(__HARVEST_HEADER_INTERNAL__) && !defined(__HARVEST_COMPILATION__)
#	error "Only <harvest-glib/harvest.h> can be included directly."
#endif

#include <glib-object.h>

#include "harvest-glib/http/response/harvest-paged-response.h"

G_BEGIN_DECLS

#define HARVEST_TYPE_USER_LIST_ACTIVE_PROJECT_ASSIGNMENTS_RESPONSE                                 \
	(harvest_user_list_active_project_assignments_response_get_type())
G_DECLARE_FINAL_TYPE(HarvestUserListActiveProjectAssignmentsResponse,
	harvest_user_list_active_project_assignments_response, HARVEST,
	USER_LIST_ACTIVE_PROJECT_ASSIGNMENTS_RESPONSE, HarvestPagedResponse)

GPtrArray *harvest_user_list_active_project_assignments_response_get_project_assignments(
	HarvestUserListActiveProjectAssignmentsResponse *self);

G_END_DECLS

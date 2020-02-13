#pragma once

#if !defined(__HARVEST_HEADER_INTERNAL__) && !defined(__HARVEST_COMPILATION__)
#	error "Only <harvest-glib/harvest.h> can be included directly."
#endif

#include <glib-object.h>

#include "harvest-glib/http/request/harvest-paged-request.h"

G_BEGIN_DECLS

#define HARVEST_TYPE_USER_LIST_ACTIVE_PROJECT_ASSIGNMENTS_REQUEST                                  \
	(harvest_user_list_active_project_assignments_request_get_type())
G_DECLARE_FINAL_TYPE(HarvestUserListActiveProjectAssignmentsRequest,
	harvest_user_list_active_project_assignments_request, HARVEST,
	USER_LIST_ACTIVE_PROJECT_ASSIGNMENTS_REQUEST, HarvestPagedRequest)

HarvestUserListActiveProjectAssignmentsRequest *
harvest_user_list_active_project_assignments_request_new(
	const int user_id, char *first_prop_name, ...) G_GNUC_WARN_UNUSED_RESULT;

G_END_DECLS

#include "config.h"

#include <glib-object.h>
#include <glib/gi18n.h>

#include "harvest-glib/http/request/harvest-paged-request.h"
#include "harvest-glib/user/requests/harvest-user-list-active-project-assignments-request.h"

struct _HarvestUserListActiveProjectAssignmentsRequest
{
	HarvestPagedRequest parent_instance;

	int user_id;
	GDateTime *updated_since;
};

G_DEFINE_TYPE(HarvestUserListActiveProjectAssignmentsRequest,
	harvest_user_list_active_project_assignments_request, HARVEST_TYPE_PAGED_REQUEST)

enum HarvestUserListActiveProjectAssignmentsRequest
{
	PROP_0,
	PROP_USER_ID,
	PROP_UPDATED_SINCE,
	N_PROPS,
};

static GParamSpec *obj_properties[N_PROPS];

static char *
harvest_user_list_active_project_assignments_request_serialize_query_params(
	HarvestUserListActiveProjectAssignmentsRequest *self)
{
	g_autofree char *paging_params
		= HARVEST_REQUEST_CLASS(harvest_user_list_active_project_assignments_request_parent_class)
			  ->serialize_query_params(HARVEST_REQUEST(self));

	g_autoptr(GString) query_params = g_string_new(NULL);
	if (self->updated_since != NULL)
		g_string_append_printf(
			query_params, "&%s", g_date_time_format_iso8601(self->updated_since));
	if (paging_params != NULL)
		g_string_append(query_params, paging_params);

	return g_strdup(query_params->str);
}

static void
harvest_user_list_active_project_assignments_request_finalize(GObject *obj)
{
	HarvestUserListActiveProjectAssignmentsRequest *self
		= HARVEST_USER_LIST_ACTIVE_PROJECT_ASSIGNMENTS_REQUEST(obj);

	g_date_time_unref(self->updated_since);

	G_OBJECT_CLASS(harvest_user_list_active_project_assignments_request_parent_class)
		->finalize(obj);
}

static void
harvest_user_list_active_project_assignments_request_get_property(
	GObject *obj, guint prop_id, GValue *val, GParamSpec *pspec)
{
	HarvestUserListActiveProjectAssignmentsRequest *self
		= HARVEST_USER_LIST_ACTIVE_PROJECT_ASSIGNMENTS_REQUEST(obj);

	switch (prop_id) {
	case PROP_USER_ID:
		g_value_set_int(val, self->user_id);
		break;
	case PROP_UPDATED_SINCE:
		g_value_set_boxed(val, self->updated_since);
		break;
	default:
		G_OBJECT_WARN_INVALID_PROPERTY_ID(obj, prop_id, pspec);
	}
}

static void
harvest_user_list_active_project_assignments_request_set_property(
	GObject *obj, guint prop_id, const GValue *val, GParamSpec *pspec)
{
	HarvestUserListActiveProjectAssignmentsRequest *self
		= HARVEST_USER_LIST_ACTIVE_PROJECT_ASSIGNMENTS_REQUEST(obj);

	switch (prop_id) {
	case PROP_USER_ID:
		self->user_id = g_value_get_int(val);
		break;
	case PROP_UPDATED_SINCE:
		g_date_time_unref(self->updated_since);
		self->updated_since = g_value_dup_boxed(val);
		break;
	default:
		G_OBJECT_WARN_INVALID_PROPERTY_ID(obj, prop_id, pspec);
	}
}

static void
harvest_user_list_active_project_assignments_request_class_init(
	HarvestUserListActiveProjectAssignmentsRequestClass *klass)
{
	GObjectClass *obj_class		   = G_OBJECT_CLASS(klass);
	HarvestRequestClass *req_class = HARVEST_REQUEST_CLASS(klass);

	obj_class->finalize		= harvest_user_list_active_project_assignments_request_finalize;
	obj_class->get_property = harvest_user_list_active_project_assignments_request_get_property;
	obj_class->set_property = harvest_user_list_active_project_assignments_request_set_property;
	req_class->serialize_query_params
		= harvest_user_list_active_project_assignments_request_serialize_query_params;

	obj_properties[PROP_USER_ID]	   = g_param_spec_int("user-id", _("User ID"),
		  _("ID of the user to retrieve project assignments of."), 0, INT_MAX, 0,
		  G_PARAM_READWRITE | G_PARAM_CONSTRUCT | G_PARAM_STATIC_STRINGS);
	obj_properties[PROP_UPDATED_SINCE] = g_param_spec_boxed("updated-since", _("Updated Since"),
		_("Only return project assignments that have been updated since the given date and time."),
		G_TYPE_DATE_TIME, G_PARAM_READWRITE | G_PARAM_CONSTRUCT | G_PARAM_STATIC_STRINGS);

	g_object_class_install_properties(obj_class, N_PROPS, obj_properties);
}

static void
harvest_user_list_active_project_assignments_request_init(
	G_GNUC_UNUSED HarvestUserListActiveProjectAssignmentsRequest *self)
{}

HarvestUserListActiveProjectAssignmentsRequest *
harvest_user_list_active_project_assignments_request_new(
	const int user_id, char *first_prop_name, ...)
{
	HarvestUserListActiveProjectAssignmentsRequest *req = NULL;

	if (first_prop_name == NULL) {
		req = HARVEST_USER_LIST_ACTIVE_PROJECT_ASSIGNMENTS_REQUEST(g_object_new_with_properties(
			HARVEST_TYPE_USER_LIST_ACTIVE_PROJECT_ASSIGNMENTS_REQUEST, 0, NULL, NULL));
	} else {
		va_list var_args;
		va_start(var_args, first_prop_name);
		req = HARVEST_USER_LIST_ACTIVE_PROJECT_ASSIGNMENTS_REQUEST(g_object_new_valist(
			HARVEST_TYPE_USER_LIST_ACTIVE_PROJECT_ASSIGNMENTS_REQUEST, first_prop_name, var_args));
		va_end(var_args);
	}

	g_autoptr(HarvestResponseMetadata) response_metadata
		= harvest_response_metadata_new(G_TYPE_NONE, HTTP_STATUS_OK);

	g_autofree char *endpoint = g_strdup_printf("/users/%d/project_assignments", user_id);

	g_object_set(req, "user-id", user_id, "http-method", HTTP_METHOD_GET, "endpoint", endpoint,
		"response-metadata", response_metadata, NULL);

	return req;
}

#include "config.h"

#include <glib-object.h>
#include <glib/gi18n.h>
#include <json-glib/json-glib.h>

#include "harvest-glib/http/response/harvest-paged-response.h"
#include "harvest-glib/user/harvest-user-project-assignment.h"
#include "harvest-glib/user/responses/harvest-user-list-active-project-assignments-response.h"

struct _HarvestUserListActiveProjectAssignmentsResponse
{
	HarvestPagedResponse parent_instance;

	GPtrArray *project_assignments; // HarvestUserProjectAssignment*
};

static void harvest_user_list_active_project_assignments_response_json_serializable_init(
	JsonSerializableIface *iface);

G_DEFINE_TYPE_WITH_CODE(HarvestUserListActiveProjectAssignmentsResponse,
	harvest_user_list_active_project_assignments_response, HARVEST_TYPE_PAGED_RESPONSE,
	G_IMPLEMENT_INTERFACE(JSON_TYPE_SERIALIZABLE,
		harvest_user_list_active_project_assignments_response_json_serializable_init))

enum HarvestUserProjectAssingmentsResponseProps
{
	PROP_0,
	PROP_PROJECT_ASSIGNMENTS,
	N_PROPS,
};

static GParamSpec *obj_properties[N_PROPS];

static void
add_to_project_assignments(
	G_GNUC_UNUSED JsonArray *array, G_GNUC_UNUSED guint index, JsonNode *node, gpointer user_data)
{
	GPtrArray *project_assignments = (GPtrArray *) (user_data);
	g_ptr_array_add(
		project_assignments, json_gobject_deserialize(HARVEST_TYPE_USER_PROJECT_ASSIGNMENT, node));
}

static gboolean
harvest_user_list_active_project_assignments_response_json_deserialize(JsonSerializable *self,
	const gchar *prop_name, GValue *val, GParamSpec *pspec, JsonNode *prop_node)
{
	if (pspec == obj_properties[PROP_PROJECT_ASSIGNMENTS]) {
		JsonArray *arr				   = json_node_get_array(prop_node);
		const guint length			   = json_array_get_length(arr);
		GPtrArray *project_assignments = g_ptr_array_new_full(length, g_object_unref);
		json_array_foreach_element(arr, add_to_project_assignments, project_assignments);
		g_value_set_boxed(val, project_assignments);

		return TRUE;
	}

	return json_serializable_default_deserialize_property(self, prop_name, val, pspec, prop_node);
}

static void
harvest_user_list_active_project_assignments_response_json_serializable_init(
	JsonSerializableIface *iface)
{
	iface->deserialize_property
		= harvest_user_list_active_project_assignments_response_json_deserialize;
}

static void
harvest_user_list_active_project_assignments_response_finalize(GObject *obj)
{
	HarvestUserListActiveProjectAssignmentsResponse *self
		= HARVEST_USER_LIST_ACTIVE_PROJECT_ASSIGNMENTS_RESPONSE(obj);

	if (self->project_assignments)
		g_ptr_array_unref(self->project_assignments);

	G_OBJECT_CLASS(harvest_user_list_active_project_assignments_response_parent_class)
		->finalize(obj);
}

static void
harvest_user_list_active_project_assignments_response_get_property(
	GObject *obj, guint prop_id, GValue *val, GParamSpec *pspec)
{
	HarvestUserListActiveProjectAssignmentsResponse *self
		= HARVEST_USER_LIST_ACTIVE_PROJECT_ASSIGNMENTS_RESPONSE(obj);

	switch (prop_id) {
	case PROP_PROJECT_ASSIGNMENTS:
		g_value_set_boxed(val, self->project_assignments);
		break;
	default:
		G_OBJECT_WARN_INVALID_PROPERTY_ID(obj, prop_id, pspec);
	}
}

static void
harvest_user_list_active_project_assignments_response_set_property(
	GObject *obj, guint prop_id, const GValue *val, GParamSpec *pspec)
{
	HarvestUserListActiveProjectAssignmentsResponse *self
		= HARVEST_USER_LIST_ACTIVE_PROJECT_ASSIGNMENTS_RESPONSE(obj);

	switch (prop_id) {
	case PROP_PROJECT_ASSIGNMENTS:
		if (self->project_assignments)
			g_ptr_array_unref(self->project_assignments);
		self->project_assignments = g_value_dup_boxed(val);
		break;
	default:
		G_OBJECT_WARN_INVALID_PROPERTY_ID(obj, prop_id, pspec);
	}
}

static void
harvest_user_list_active_project_assignments_response_class_init(
	HarvestUserListActiveProjectAssignmentsResponseClass *klass)
{
	GObjectClass *obj_class = G_OBJECT_CLASS(klass);

	obj_class->finalize		= harvest_user_list_active_project_assignments_response_finalize;
	obj_class->get_property = harvest_user_list_active_project_assignments_response_get_property;
	obj_class->set_property = harvest_user_list_active_project_assignments_response_set_property;

	obj_properties[PROP_PROJECT_ASSIGNMENTS] = g_param_spec_boxed("project-assignments",
		_("Project Assignments"), _("Project assignments for the requested user."),
		G_TYPE_PTR_ARRAY, G_PARAM_CONSTRUCT | G_PARAM_READWRITE);

	g_object_class_install_properties(obj_class, N_PROPS, obj_properties);
}

static void
harvest_user_list_active_project_assignments_response_init(
	G_GNUC_UNUSED HarvestUserListActiveProjectAssignmentsResponse *self)
{}

GPtrArray *
harvest_user_list_active_project_assignments_response_get_project_assignments(
	HarvestUserListActiveProjectAssignmentsResponse *self)
{
	g_return_val_if_fail(HARVEST_IS_USER_LIST_ACTIVE_PROJECT_ASSIGNMENTS_RESPONSE(self), NULL);

	return self->project_assignments;
}

#include "config.h"

#include <float.h>
#include <limits.h>

#include <glib-object.h>
#include <glib/gi18n-lib.h>
#include <json-glib/json-glib.h>

#include "harvest-glib/client/harvest-client.h"
#include "harvest-glib/project/harvest-project-task-assignment.h"
#include "harvest-glib/project/harvest-project.h"
#include "harvest-glib/user/harvest-user-project-assignment.h"
#include "harvest-glib/user/harvest-user.h"

struct _HarvestUserProjectAssignment
{
	GObject parent_instance;

	int id;
	gboolean is_active : 1;
	gboolean is_project_manager : 1;
	gboolean use_default_rates : 1;
	double *hourly_rate;
	double *budget;
	GDateTime *created_at;
	GDateTime *updated_at;
	HarvestProject *project;
	HarvestClient *client;
	GPtrArray *task_assignments; // HarvestProjectTaskAssignment
};

static void harvest_user_project_assignment_json_serializable_init(JsonSerializableIface *iface);

G_DEFINE_TYPE_WITH_CODE(HarvestUserProjectAssignment, harvest_user_project_assignment,
	G_TYPE_OBJECT,
	G_IMPLEMENT_INTERFACE(
		JSON_TYPE_SERIALIZABLE, harvest_user_project_assignment_json_serializable_init))

enum HarvestUserProjectAssignmentProps
{
	PROP_0,
	PROP_ID,
	PROP_IS_ACTIVE,
	PROP_IS_PROJECT_MANAGER,
	PROP_USE_DEFAULT_RATES,
	PROP_HOURLY_RATE,
	PROP_BUDGET,
	PROP_CREATED_AT,
	PROP_UPDATED_AT,
	PROP_PROJECT,
	PROP_CLIENT,
	PROP_TASK_ASSIGNMENTS,
	N_PROPS,
};

static GParamSpec *obj_properties[N_PROPS];

static void
add_to_task_assignments(
	G_GNUC_UNUSED JsonArray *array, G_GNUC_UNUSED guint index, JsonNode *node, gpointer user_data)
{
	g_ptr_array_add(
		user_data, json_gobject_deserialize(HARVEST_TYPE_PROJECT_TASK_ASSIGNMENT, node));
}

static gboolean
harvest_user_project_assignment_deserialize_property(JsonSerializable *serializable,
	const gchar *prop_name, GValue *val, GParamSpec *pspec, JsonNode *prop_node)
{
	if (pspec == obj_properties[PROP_CREATED_AT] || pspec == obj_properties[PROP_UPDATED_AT]) {
		const GDateTime *dt = g_date_time_new_from_iso8601(json_node_get_string(prop_node), NULL);
		g_value_set_boxed(val, dt);

		return TRUE;
	} else if (pspec == obj_properties[PROP_PROJECT]) {
		GObject *obj = json_gobject_deserialize(HARVEST_TYPE_PROJECT, prop_node);
		g_value_set_object(val, obj);

		return TRUE;
	} else if (pspec == obj_properties[PROP_CLIENT]) {
		GObject *obj = json_gobject_deserialize(HARVEST_TYPE_CLIENT, prop_node);
		g_value_set_object(val, obj);

		return TRUE;
	} else if (pspec == obj_properties[PROP_TASK_ASSIGNMENTS]) {
		JsonArray *arr				= json_node_get_array(prop_node);
		const guint length			= json_array_get_length(arr);
		GPtrArray *task_assignments = g_ptr_array_new_full(length, g_object_unref);
		json_array_foreach_element(arr, add_to_task_assignments, task_assignments);
		g_value_set_boxed(val, task_assignments);

		return TRUE;
	} else if (pspec == obj_properties[PROP_BUDGET] || pspec == obj_properties[PROP_HOURLY_RATE]) {
		if (json_node_is_null(prop_node)) {
			g_value_set_pointer(val, NULL);
		} else {
			const double dbl_value = json_node_get_double(prop_node);
			double *mem			   = g_malloc0(sizeof(double));
			memcpy(mem, &dbl_value, sizeof(double));
			g_value_set_pointer(val, mem);
		}

		return TRUE;
	}

	return json_serializable_default_deserialize_property(
		serializable, prop_name, val, pspec, prop_node);
}

static void
harvest_user_project_assignment_json_serializable_init(JsonSerializableIface *iface)
{
	iface->deserialize_property = harvest_user_project_assignment_deserialize_property;
}

static void
harvest_user_project_assignment_finalize(GObject *obj)
{
	HarvestUserProjectAssignment *self = HARVEST_USER_PROJECT_ASSIGNMENT(obj);

	if (self->created_at)
		g_date_time_unref(self->created_at);
	if (self->updated_at)
		g_date_time_unref(self->updated_at);
	if (self->project)
		g_object_unref(self->project);
	if (self->client)
		g_object_unref(self->client);
	if (self->task_assignments)
		g_ptr_array_unref(self->task_assignments);
	g_free(self->budget);

	G_OBJECT_CLASS(harvest_user_project_assignment_parent_class)->finalize(obj);
}

static void
harvest_user_project_assignment_get_property(
	GObject *obj, guint prop_id, GValue *val, GParamSpec *pspec)
{
	HarvestUserProjectAssignment *self = HARVEST_USER_PROJECT_ASSIGNMENT(obj);

	switch (prop_id) {
	case PROP_ID:
		g_value_set_int(val, self->id);
		break;
	case PROP_IS_ACTIVE:
		g_value_set_boolean(val, self->is_active);
		break;
	case PROP_IS_PROJECT_MANAGER:
		g_value_set_boolean(val, self->is_project_manager);
		break;
	case PROP_USE_DEFAULT_RATES:
		g_value_set_boolean(val, self->use_default_rates);
		break;
	case PROP_HOURLY_RATE:
		g_value_set_pointer(val, self->hourly_rate);
		break;
	case PROP_BUDGET:
		g_value_set_pointer(val, self->budget);
		break;
	case PROP_CREATED_AT:
		g_value_set_boxed(val, self->created_at);
		break;
	case PROP_UPDATED_AT:
		g_value_set_boxed(val, self->updated_at);
		break;
	case PROP_PROJECT:
		g_value_set_object(val, self->project);
		break;
	case PROP_CLIENT:
		g_value_set_object(val, self->client);
		break;
	case PROP_TASK_ASSIGNMENTS:
		g_value_set_boxed(val, self->task_assignments);
		break;
	default:
		G_OBJECT_WARN_INVALID_PROPERTY_ID(obj, prop_id, pspec);
	}
}

static void
harvest_user_project_assignment_set_property(
	GObject *obj, guint prop_id, const GValue *val, GParamSpec *pspec)
{
	HarvestUserProjectAssignment *self = HARVEST_USER_PROJECT_ASSIGNMENT(obj);

	switch (prop_id) {
	case PROP_ID:
		self->id = g_value_get_int(val);
		break;
	case PROP_IS_ACTIVE:
		self->is_active = g_value_get_boolean(val);
		break;
	case PROP_IS_PROJECT_MANAGER:
		self->is_project_manager = g_value_get_boolean(val);
		break;
	case PROP_USE_DEFAULT_RATES:
		self->use_default_rates = g_value_get_boolean(val);
		break;
	case PROP_HOURLY_RATE:
		g_free(self->hourly_rate);
		self->hourly_rate = g_value_get_pointer(val);
		break;
	case PROP_BUDGET:
		g_free(self->budget);
		self->budget = g_value_get_pointer(val);
		break;
	case PROP_CREATED_AT:
		if (self->created_at)
			g_date_time_unref(self->created_at);
		self->created_at = g_value_dup_boxed(val);
		break;
	case PROP_UPDATED_AT:
		if (self->updated_at)
			g_date_time_unref(self->updated_at);
		self->updated_at = g_value_dup_boxed(val);
		break;
	case PROP_PROJECT:
		if (self->project)
			g_object_unref(self->project);
		self->project = g_value_dup_object(val);
		break;
	case PROP_CLIENT:
		if (self->client)
			g_object_unref(self->client);
		self->client = g_value_dup_object(val);
		break;
	case PROP_TASK_ASSIGNMENTS:
		if (self->task_assignments)
			g_ptr_array_unref(self->task_assignments);
		break;
	default:
		G_OBJECT_WARN_INVALID_PROPERTY_ID(obj, prop_id, pspec);
	}
}

static void
harvest_user_project_assignment_class_init(HarvestUserProjectAssignmentClass *klass)
{
	GObjectClass *obj_class = G_OBJECT_CLASS(klass);

	obj_class->finalize		= harvest_user_project_assignment_finalize;
	obj_class->get_property = harvest_user_project_assignment_get_property;
	obj_class->set_property = harvest_user_project_assignment_set_property;

	obj_properties[PROP_ID]
		= g_param_spec_int("id", _("ID"), _("Unique ID for the project assignment."), 0, INT_MAX, 0,
			G_PARAM_READWRITE | G_PARAM_CONSTRUCT);
	obj_properties[PROP_IS_ACTIVE] = g_param_spec_boolean("is_active", _("Is Active"),
		_("Whether the project assignment is active or archived."), FALSE,
		G_PARAM_READWRITE | G_PARAM_CONSTRUCT);
	obj_properties[PROP_IS_PROJECT_MANAGER]
		= g_param_spec_boolean("is-project-manager", _("Is Project Manager"),
			_("Determines if the user has project manager permissions for the project."), FALSE,
			G_PARAM_READWRITE | G_PARAM_CONSTRUCT);
	obj_properties[PROP_USE_DEFAULT_RATES]
		= g_param_spec_boolean("use_default_rates", _("Use Default Rates"),
			_("Determines which billable rate(s) will be used on the project for this user when "
			  "bill_by is People. When true, the project will use the user’s default billable "
			  "rates. "
			  "When false, the project will use the custom rate defined on this user assignment."),
			FALSE, G_PARAM_READWRITE | G_PARAM_CONSTRUCT);
	obj_properties[PROP_HOURLY_RATE]	  = g_param_spec_pointer("hourly-rate", _("Hourly Rate"),
		 _("Custom rate used when the project’s bill_by is People and use_default_rates is "
		   "false."),
		 G_PARAM_READWRITE | G_PARAM_CONSTRUCT);
	obj_properties[PROP_BUDGET]			  = g_param_spec_pointer("budget", _("Budget"),
		  _("Budget used when the project’s budget_by is person."),
		  G_PARAM_READWRITE | G_PARAM_CONSTRUCT);
	obj_properties[PROP_CREATED_AT]		  = g_param_spec_boxed("created-at", _("Created At"),
		  _("Date and time the project assignment was created."), G_TYPE_DATE_TIME,
		  G_PARAM_READWRITE | G_PARAM_CONSTRUCT);
	obj_properties[PROP_UPDATED_AT]		  = g_param_spec_boxed("updated-at", _("Updated At"),
		  _("Date and time the project assignment was last updated."), G_TYPE_DATE_TIME,
		  G_PARAM_READWRITE | G_PARAM_CONSTRUCT);
	obj_properties[PROP_PROJECT]		  = g_param_spec_object("project", _("Project"),
		 _("An object containing the assigned project id, name, and code."), HARVEST_TYPE_PROJECT,
		 G_PARAM_READWRITE | G_PARAM_CONSTRUCT);
	obj_properties[PROP_CLIENT]			  = g_param_spec_object("client", _("Client"),
		  _("An object containing the project’s client id and name."), HARVEST_TYPE_CLIENT,
		  G_PARAM_READWRITE | G_PARAM_CONSTRUCT);
	obj_properties[PROP_TASK_ASSIGNMENTS] = g_param_spec_boxed("task-assignments",
		_("Task Assignments"), _("Array of task assignment objects associated with the project."),
		G_TYPE_PTR_ARRAY, G_PARAM_READWRITE | G_PARAM_CONSTRUCT);

	g_object_class_install_properties(obj_class, N_PROPS, obj_properties);
}

static void
harvest_user_project_assignment_init(G_GNUC_UNUSED HarvestUserProjectAssignment *self)
{}

int
harvest_user_project_assignment_get_id(HarvestUserProjectAssignment *self)
{
	g_return_val_if_fail(HARVEST_IS_USER_PROJECT_ASSIGNMENT(self), -1);

	return self->id;
}

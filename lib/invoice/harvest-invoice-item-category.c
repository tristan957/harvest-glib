#include "config.h"

#include <limits.h>

#include <glib-object.h>
#include <glib/gi18n-lib.h>
#include <json-glib/json-glib.h>

#include "harvest-glib/invoice/harvest-invoice-item-category.h"

struct _HarvestInvoiceItemCategory
{
	GObject parent_instance;

	int id;
	char *name;
	gboolean use_as_service : 1;
	gboolean use_as_expense : 1;
	GDateTime *created_at;
	GDateTime *updated_at;
};

static void harvest_invoice_item_category_json_serializable_init(JsonSerializableIface *iface);

G_DEFINE_TYPE_WITH_CODE(HarvestInvoiceItemCategory, harvest_invoice_item_category, G_TYPE_OBJECT,
	G_IMPLEMENT_INTERFACE(
		JSON_TYPE_SERIALIZABLE, harvest_invoice_item_category_json_serializable_init))

enum HarvestInvoiceItemCategoryProps
{
	PROP_0,
	PROP_ID,
	PROP_NAME,
	PROP_USE_AS_SERVICE,
	PROP_USE_AS_EXPENSE,
	PROP_CREATED_AT,
	PROP_UPDATED_AT,
	N_PROPS,
};

static GParamSpec *obj_properties[N_PROPS];

static gboolean
harvest_invoice_item_category_deserialize_property(JsonSerializable *serializable,
	const gchar *prop_name, GValue *val, GParamSpec *pspec, JsonNode *prop_node)
{
	if (g_strcmp0(prop_name, "created_at") == 0 || g_strcmp0(prop_name, "updated_at") == 0) {
		const GDateTime *dt = g_date_time_new_from_iso8601(json_node_get_string(prop_node), NULL);
		g_value_set_boxed(val, dt);

		return TRUE;
	}

	return json_serializable_default_deserialize_property(
		serializable, prop_name, val, pspec, prop_node);
}

static void
harvest_invoice_item_category_json_serializable_init(JsonSerializableIface *iface)
{
	iface->deserialize_property = harvest_invoice_item_category_deserialize_property;
}

static void
harvest_invoice_item_category_finalize(GObject *obj)
{
	HarvestInvoiceItemCategory *self = HARVEST_INVOICE_ITEM_CATEGORY(obj);

	g_free(self->name);
	if (self->created_at != NULL)
		g_date_time_unref(self->created_at);
	if (self->updated_at != NULL)
		g_date_time_unref(self->updated_at);

	G_OBJECT_CLASS(harvest_invoice_item_category_parent_class)->finalize(obj);
}

static void
harvest_invoice_item_category_get_property(
	GObject *obj, guint prop_id, GValue *val, GParamSpec *pspec)
{
	HarvestInvoiceItemCategory *self = HARVEST_INVOICE_ITEM_CATEGORY(obj);

	switch (prop_id) {
	case PROP_ID:
		g_value_set_int(val, self->id);
		break;
	case PROP_NAME:
		g_value_set_string(val, self->name);
		break;
	case PROP_USE_AS_SERVICE:
		g_value_set_boolean(val, self->use_as_service);
		break;
	case PROP_USE_AS_EXPENSE:
		g_value_set_boolean(val, self->use_as_expense);
		break;
	case PROP_CREATED_AT:
		g_value_set_boxed(val, self->created_at);
		break;
	case PROP_UPDATED_AT:
		g_value_set_boxed(val, self->updated_at);
		break;
	default:
		G_OBJECT_WARN_INVALID_PROPERTY_ID(obj, prop_id, pspec);
	}
}

static void
harvest_invoice_item_category_set_property(
	GObject *obj, guint prop_id, const GValue *val, GParamSpec *pspec)
{
	HarvestInvoiceItemCategory *self = HARVEST_INVOICE_ITEM_CATEGORY(obj);

	switch (prop_id) {
	case PROP_ID:
		self->id = g_value_get_int(val);
		break;
	case PROP_NAME:
		g_free(self->name);
		self->name = g_value_dup_string(val);
		break;
	case PROP_USE_AS_SERVICE:
		self->use_as_service = g_value_get_boolean(val);
		break;
	case PROP_USE_AS_EXPENSE:
		self->use_as_expense = g_value_get_boolean(val);
		break;
	case PROP_CREATED_AT:
		if (self->created_at != NULL)
			g_date_time_unref(self->created_at);
		self->created_at = g_value_dup_boxed(val);
		break;
	case PROP_UPDATED_AT:
		if (self->updated_at != NULL)
			g_date_time_unref(self->updated_at);
		self->updated_at = g_value_dup_boxed(val);
		break;
	default:
		G_OBJECT_WARN_INVALID_PROPERTY_ID(obj, prop_id, pspec);
	}
}

static void
harvest_invoice_item_category_class_init(HarvestInvoiceItemCategoryClass *klass)
{
	GObjectClass *obj_class = G_OBJECT_CLASS(klass);

	obj_class->finalize		= harvest_invoice_item_category_finalize;
	obj_class->get_property = harvest_invoice_item_category_get_property;
	obj_class->set_property = harvest_invoice_item_category_set_property;

	obj_properties[PROP_ID]
		= g_param_spec_int("id", _("ID"), ("Unique ID for the invoice item category."), 0, INT_MAX,
			0, G_PARAM_CONSTRUCT | G_PARAM_READWRITE | G_PARAM_STATIC_STRINGS);
	obj_properties[PROP_NAME]
		= g_param_spec_string("name", _("name"), ("The name of the invoice item category."), NULL,
			G_PARAM_CONSTRUCT | G_PARAM_READWRITE | G_PARAM_STATIC_STRINGS);
	obj_properties[PROP_USE_AS_SERVICE]
		= g_param_spec_boolean("use_as_service", _("Use as Service"),
			("Whether this invoice item category is used for billable hours when generating an "
			 "invoice."),
			FALSE, G_PARAM_CONSTRUCT | G_PARAM_READWRITE | G_PARAM_STATIC_STRINGS);
	obj_properties[PROP_USE_AS_EXPENSE]
		= g_param_spec_boolean("use_as_expense", _("Use as Expense"),
			("Whether this invoice item category is used for expenses when generating an invoice."),
			FALSE, G_PARAM_CONSTRUCT | G_PARAM_READWRITE | G_PARAM_STATIC_STRINGS);
	obj_properties[PROP_CREATED_AT] = g_param_spec_boxed("created_at", _("Created At"),
		_("Date and time the invoice item category was created."), G_TYPE_DATE_TIME,
		G_PARAM_CONSTRUCT | G_PARAM_READWRITE | G_PARAM_STATIC_STRINGS);
	obj_properties[PROP_UPDATED_AT] = g_param_spec_boxed("updated_at", _("Updated At"),
		_("Date and time the invoice item category was last updated."), G_TYPE_DATE_TIME,
		G_PARAM_CONSTRUCT | G_PARAM_READWRITE | G_PARAM_STATIC_STRINGS);

	g_object_class_install_properties(obj_class, N_PROPS, obj_properties);
}

static void
harvest_invoice_item_category_init(G_GNUC_UNUSED HarvestInvoiceItemCategory *self)
{}

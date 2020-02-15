#include "config.h"

#include <glib-object.h>
#include <glib/gi18n-lib.h>

#include "harvest-glib/http/request/harvest-paged-request.h"
#include "harvest-glib/http/request/harvest-request.h"

typedef struct _HarvestPagedRequestPrivate
{
	GVariant *page;		// unsigned int
	GVariant *per_page; // unsigned int
} HarvestPagedRequestPrivate;

G_DEFINE_ABSTRACT_TYPE_WITH_PRIVATE(
	HarvestPagedRequest, harvest_paged_request, HARVEST_TYPE_REQUEST)

enum HarvestPagedRequestProps
{
	PROP_0,
	PROP_PAGE,
	PROP_PER_PAGE,
	N_PROPS,
};

static GParamSpec *obj_properties[N_PROPS];

static void
harvest_paged_request_get_property(GObject *obj, guint prop_id, GValue *val, GParamSpec *pspec)
{
	HarvestPagedRequest *self		 = HARVEST_PAGED_REQUEST(obj);
	HarvestPagedRequestPrivate *priv = harvest_paged_request_get_instance_private(self);

	switch (prop_id) {
	case PROP_PAGE:
		g_value_set_variant(val, priv->page);
		break;
	case PROP_PER_PAGE:
		g_value_set_variant(val, priv->per_page);
		break;
	default:
		G_OBJECT_WARN_INVALID_PROPERTY_ID(obj, prop_id, pspec);
	}
}

static void
harvest_paged_request_set_property(
	GObject *obj, guint prop_id, const GValue *val, GParamSpec *pspec)
{
	HarvestPagedRequest *self		 = HARVEST_PAGED_REQUEST(obj);
	HarvestPagedRequestPrivate *priv = harvest_paged_request_get_instance_private(self);

	switch (prop_id) {
	case PROP_PAGE:
		g_variant_unref(priv->page);
		priv->page = g_value_get_variant(val);
		break;
	case PROP_PER_PAGE:
		g_variant_unref(priv->per_page);
		priv->per_page = g_value_get_variant(val);
		break;
	default:
		G_OBJECT_WARN_INVALID_PROPERTY_ID(obj, prop_id, pspec);
	}
}

static void
harvest_paged_request_finalize(GObject *obj)
{
	HarvestPagedRequest *self		 = HARVEST_PAGED_REQUEST(obj);
	HarvestPagedRequestPrivate *priv = harvest_paged_request_get_instance_private(self);

	g_variant_unref(priv->page);
	g_variant_unref(priv->per_page);

	G_OBJECT_CLASS(harvest_paged_request_parent_class)->finalize(obj);
}

static char *
harvest_paged_request_serialize_query_params(HarvestPagedRequest *self)
{
	HarvestPagedRequestPrivate *priv = harvest_paged_request_get_instance_private(self);

	g_autoptr(GString) query_params = g_string_new(NULL);
	if (priv->page != NULL)
		g_string_append_printf(query_params, "&%u", g_variant_get_uint32(priv->page));
	if (priv->per_page != NULL)
		g_string_append_printf(query_params, "&%u", g_variant_get_uint32(priv->per_page));

	return g_strdup(query_params->str);
}

static void
harvest_paged_request_class_init(HarvestPagedRequestClass *klass)
{
	GObjectClass *obj_class		   = G_OBJECT_CLASS(klass);
	HarvestRequestClass *req_class = HARVEST_REQUEST_CLASS(klass);

	obj_class->finalize				  = harvest_paged_request_finalize;
	obj_class->get_property			  = harvest_paged_request_get_property;
	obj_class->set_property			  = harvest_paged_request_set_property;
	req_class->serialize_query_params = harvest_paged_request_serialize_query_params;

	obj_properties[PROP_PAGE]	  = g_param_spec_variant("page", _("Page"),
		_("Page number of the results to retrieve."), G_VARIANT_TYPE_UINT32, NULL,
		G_PARAM_CONSTRUCT | G_PARAM_READWRITE | G_PARAM_STATIC_STRINGS);
	obj_properties[PROP_PER_PAGE] = g_param_spec_variant("per-page", _("Per Page"),
		_("Number of results to return per page."), G_VARIANT_TYPE_UINT32, NULL,
		G_PARAM_CONSTRUCT | G_PARAM_READWRITE | G_PARAM_STATIC_STRINGS);

	g_object_class_install_properties(obj_class, N_PROPS, obj_properties);
}

static void
harvest_paged_request_init(G_GNUC_UNUSED HarvestPagedRequest *self)
{}

void
harvest_paged_request_next_page(HarvestPagedRequest *self)
{
	HarvestPagedRequestPrivate *priv = harvest_paged_request_get_instance_private(self);

	g_object_set(self, "page", g_variant_new_uint32(g_variant_get_uint32(priv->page) + 1), NULL);
}

void
harvest_paged_request_prev_page(HarvestPagedRequest *self)
{
	HarvestPagedRequestPrivate *priv = harvest_paged_request_get_instance_private(self);

	g_object_set(self, "page", g_variant_new_uint32(g_variant_get_uint32(priv->page) - 1), NULL);
}

void
harvest_paged_request_set_page(HarvestPagedRequest *self, const unsigned int page)
{
	g_object_set(self, "page", g_variant_new_uint32(page), NULL);
}

void
harvest_paged_request_set_per_page(HarvestPagedRequest *self, const unsigned int per_page)
{
	g_object_set(self, "per-page", g_variant_new_uint32(per_page), NULL);
}

#include "config.h"

#include <glib-object.h>
#include <glib/gi18n-lib.h>
#include <json-glib/json-glib.h>

#include "harvest-glib/http/harvest-http-enum-types.h"
#include "harvest-glib/http/harvest-http.h"
#include "harvest-glib/http/request/harvest-request.h"
#include "harvest-glib/http/response/harvest-response-metadata.h"
#include "harvest-glib/http/response/harvest-response.h"

typedef struct _HarvestRequestPrivate
{
	HttpMethod http_method;
	char *endpoint;
	GValue *data;
	HarvestResponseMetadata *response_metadata;
} HarvestRequestPrivate;

G_DEFINE_ABSTRACT_TYPE_WITH_PRIVATE(HarvestRequest, harvest_request, G_TYPE_OBJECT)

enum HarvestRequestSignals
{
	SIGNAL_QUEUED,
	SIGNAL_COMPLETED,
	N_SIGNALS,
};

static guint obj_signals[N_SIGNALS];

enum HarvestRequestProps
{
	PROP_0,
	PROP_HTTP_METHOD,
	PROP_ENDPOINT,
	PROP_DATA,
	PROP_RESPONSE_METADATA,
	N_PROPS,
};

static GParamSpec *obj_properties[N_PROPS];

static void
harvest_request_finalize(GObject *obj)
{
	HarvestRequest *self		= HARVEST_REQUEST(obj);
	HarvestRequestPrivate *priv = harvest_request_get_instance_private(self);

	g_free(priv->endpoint);
	if (priv->data != NULL)
		g_value_unset(priv->data);
	if (priv->response_metadata != NULL)
		g_object_unref(priv->response_metadata);

	G_OBJECT_CLASS(harvest_request_parent_class)->finalize(obj);
}

static void
harvest_request_get_property(GObject *obj, guint prop_id, GValue *val, GParamSpec *pspec)
{
	HarvestRequest *self		= HARVEST_REQUEST(obj);
	HarvestRequestPrivate *priv = harvest_request_get_instance_private(self);

	switch (prop_id) {
	case PROP_HTTP_METHOD:
		g_value_set_enum(val, (gint) priv->http_method);
		break;
	case PROP_ENDPOINT:
		g_value_set_string(val, priv->endpoint);
		break;
	case PROP_DATA:
		g_value_set_boxed(val, priv->data);
		break;
	case PROP_RESPONSE_METADATA:
		g_value_set_object(val, priv->response_metadata);
		break;
	default:
		G_OBJECT_WARN_INVALID_PROPERTY_ID(obj, prop_id, pspec);
	}
}

static void
harvest_request_set_property(GObject *obj, guint prop_id, const GValue *val, GParamSpec *pspec)
{
	HarvestRequest *self		= HARVEST_REQUEST(obj);
	HarvestRequestPrivate *priv = harvest_request_get_instance_private(self);

	switch (prop_id) {
	case PROP_HTTP_METHOD:
		priv->http_method = (HttpMethod) g_value_get_enum(val);
		break;
	case PROP_ENDPOINT:
		g_free(priv->endpoint);
		priv->endpoint = g_value_dup_string(val);
		break;
	case PROP_DATA:
		if (priv->data != NULL)
			g_value_unset(priv->data);
		priv->data = g_value_dup_boxed(val);
		break;
	case PROP_RESPONSE_METADATA:
		if (priv->response_metadata != NULL)
			g_object_unref(priv->response_metadata);
		priv->response_metadata = g_value_dup_object(val);
		break;
	default:
		G_OBJECT_WARN_INVALID_PROPERTY_ID(obj, prop_id, pspec);
	}
}

static void
harvest_request_class_init(HarvestRequestClass *klass)
{
	GObjectClass *obj_class = G_OBJECT_CLASS(klass);

	obj_class->finalize		= harvest_request_finalize;
	obj_class->get_property = harvest_request_get_property;
	obj_class->set_property = harvest_request_set_property;

	obj_signals[SIGNAL_QUEUED]	  = g_signal_new("queued", G_TYPE_FROM_CLASS(klass),
		   G_SIGNAL_RUN_FIRST, 0, NULL, NULL, NULL, G_TYPE_NONE, 0);
	obj_signals[SIGNAL_COMPLETED] = g_signal_new("completed", G_TYPE_FROM_CLASS(klass),
		G_SIGNAL_RUN_FIRST, 0, NULL, NULL, NULL, G_TYPE_NONE, 1, HARVEST_TYPE_RESPONSE);

	obj_properties[PROP_HTTP_METHOD] = g_param_spec_enum("http-method", _("HTTP Method"),
		_("The HTTP method by which to send the request."), HTTP_TYPE_METHOD, HTTP_METHOD_GET,
		G_PARAM_WRITABLE | G_PARAM_CONSTRUCT);
	obj_properties[PROP_ENDPOINT]	 = g_param_spec_string("endpoint", _("Endpoint"),
		   _("The server endpoint to send the request to."), NULL,
		   G_PARAM_WRITABLE | G_PARAM_CONSTRUCT);
	obj_properties[PROP_DATA]
		= g_param_spec_boxed("data", _("Data"), _("The data to send in the body of the request."),
			G_TYPE_VALUE, G_PARAM_WRITABLE | G_PARAM_CONSTRUCT);
	obj_properties[PROP_RESPONSE_METADATA] = g_param_spec_object("response-metadata", _("Response"),
		_("An object containing meta information of the response."), HARVEST_TYPE_RESPONSE_METADATA,
		G_PARAM_WRITABLE | G_PARAM_CONSTRUCT);

	g_object_class_install_properties(obj_class, N_PROPS, obj_properties);
}

static void
harvest_request_init(G_GNUC_UNUSED HarvestRequest *self)
{}

HttpMethod
harvest_request_get_http_method(HarvestRequest *self)
{
	g_return_val_if_fail(HARVEST_IS_REQUEST(self), HTTP_METHOD_GET);

	HarvestRequestPrivate *priv = harvest_request_get_instance_private(self);

	return priv->http_method;
}

const char *
harvest_request_get_endpoint(HarvestRequest *self)
{
	g_return_val_if_fail(HARVEST_IS_REQUEST(self), NULL);

	HarvestRequestPrivate *priv = harvest_request_get_instance_private(self);

	return priv->endpoint;
}

char *
harvest_request_get_query_params(HarvestRequest *self)
{
	g_return_val_if_fail(HARVEST_IS_REQUEST(self), NULL);

	HarvestRequestClass *klass = HARVEST_REQUEST_GET_CLASS(self);
	if (klass->serialize_query_params == NULL)
		return NULL;

	return klass->serialize_query_params(self);
}

GValue *
harvest_request_get_data(HarvestRequest *self)
{
	g_return_val_if_fail(HARVEST_IS_REQUEST(self), NULL);

	HarvestRequestPrivate *priv = harvest_request_get_instance_private(self);

	return priv->data;
}

HarvestResponseMetadata *
harvest_request_get_response_metadata(HarvestRequest *self)
{
	g_return_val_if_fail(HARVEST_IS_REQUEST(self), NULL);

	HarvestRequestPrivate *priv = harvest_request_get_instance_private(self);

	return priv->response_metadata;
}

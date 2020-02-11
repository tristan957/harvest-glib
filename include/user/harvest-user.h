#pragma once

#if !defined(__HARVEST_HEADER_INTERNAL__) && !defined(__HARVEST_COMPILATION__)
#	error "Only <harvest-glib/harvest.h> can be included directly."
#endif

#include <glib-object.h>

#include "http/api/harvest-api-client.h"
#include "http/request/harvest-request.h"
#include "http/response/harvest-response.h"

G_BEGIN_DECLS

#define HARVEST_TYPE_USER (harvest_user_get_type())
G_DECLARE_FINAL_TYPE(HarvestUser, harvest_user, HARVEST, USER, GObject)

HarvestResponse *harvest_user_get_me(HarvestApiClient *client) G_GNUC_WARN_UNUSED_RESULT;
void harvest_user_get_me_async(
	HarvestApiClient *client, HarvestCompletedCallback *callback, gpointer user_data);
const char *harvest_user_get_first_name(HarvestUser *user);
const char *harvest_user_get_last_name(HarvestUser *user);

G_END_DECLS

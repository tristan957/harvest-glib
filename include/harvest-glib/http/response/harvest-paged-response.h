#pragma once

#if !defined(__HARVEST_HEADER_INTERNAL__) && !defined(__HARVEST_COMPILATION__)
#	error "Only <harvest-glib/harvest.h> can be included directly."
#endif

#include <glib-object.h>

#include "harvest-glib/http/response/harvest-response.h"

G_BEGIN_DECLS

#define HARVEST_TYPE_PAGED_RESPONSE (harvest_paged_response_get_type())
G_DECLARE_DERIVABLE_TYPE(
	HarvestPagedResponse, harvest_paged_response, HARVEST, PAGED_RESPONSE, HarvestResponse)

struct _HarvestPagedResponseClass
{
	HarvestResponseClass parent_class;
};

G_END_DECLS

#pragma once

#if !defined(__HARVEST_HEADER_INTERNAL__) && !defined(__HARVEST_COMPILATION__)
#	error "Only <harvest-glib/harvest.h> can be included directly."
#endif

#include <glib-object.h>

#include "harvest-glib/http/request/harvest-request.h"

G_BEGIN_DECLS

#define HARVEST_TYPE_PAGED_REQUEST (harvest_paged_request_get_type())
G_DECLARE_DERIVABLE_TYPE(
	HarvestPagedRequest, harvest_paged_request, HARVEST, PAGED_REQUEST, HarvestRequest)

struct _HarvestPagedRequestClass
{
	HarvestRequestClass parent_class;
};

void harvest_paged_request_next_page(HarvestPagedRequest *self);
void harvest_paged_request_prev_page(HarvestPagedRequest *self);
void harvest_paged_request_set_page(HarvestPagedRequest *self, const unsigned int page);
void harvest_paged_request_set_per_page(HarvestPagedRequest *self, const unsigned int per_page);

G_END_DECLS

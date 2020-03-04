#pragma once

#if !defined(__HARVEST_HEADER_INTERNAL__) && !defined(__HARVEST_COMPILATION__)
#	error "Only <harvest-glib/harvest.h> can be included directly."
#endif

#include <glib-object.h>

G_BEGIN_DECLS

GType harvest_invoice_state_get_type(void);
#define HARVEST_TYPE_INVOICE_STATE (harvest_invoice_state_get_type())

GType harvest_invoice_payment_term_get_type(void);
#define HARVEST_TYPE_INVOICE_PAYMENT_TERM (harvest_invoice_payment_term_get_type())

G_END_DECLS

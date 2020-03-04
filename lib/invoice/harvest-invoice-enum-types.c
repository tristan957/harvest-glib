#include <gio/gio.h>

#include "harvest-glib/invoice/harvest-invoice-enum-types.h"
#include "harvest-glib/invoice/harvest-invoice.h"

#define C_ENUM(v)  ((gint) v)
#define C_FLAGS(v) ((guint) v)

GType
harvest_invoice_state_get_type(void)
{
	static volatile gsize gtype_id = 0;
	// clang-format off
	static const GEnumValue values[] = {
		{ C_ENUM(HARVEST_INVOICE_STATE_DRAFT), "HARVEST_INVOICE_STATE_DRAFT", "draft" },
		{ C_ENUM(HARVEST_INVOICE_STATE_OPEN), "HARVEST_INVOICE_STATE_OPEN", "open" },
		{ C_ENUM(HARVEST_INVOICE_STATE_PAID), "HARVEST_INVOICE_STATE_PAID", "paid" },
		{ C_ENUM(HARVEST_INVOICE_STATE_CLOSED), "HARVEST_INVOICE_STATE_CLOSED", "closed" },
		{ 0, NULL, NULL }
	};
	// clang-format on

	if (g_once_init_enter(&gtype_id)) {
		GType new_type
			= g_enum_register_static(g_intern_static_string("HarvestInvoiceState"), values);
		g_once_init_leave(&gtype_id, new_type);
	}

	return (GType) gtype_id;
}

GType
harvest_invoice_payment_term_get_type(void)
{
	static volatile gsize gtype_id = 0;
	// clang-format off
	static const GEnumValue values[] = {
		{ C_ENUM(HARVEST_INVOICE_PAYMENT_TERM_UPON_RECEIPT), "HARVEST_INVOICE_PAYMENT_TERM_UPON_RECEIPT", "upon receipt" },
		{ C_ENUM(HARVEST_INVOICE_PAYMENT_TERM_NET_15), "HARVEST_INVOICE_PAYMENT_TERM_NET_15", "net 15" },
		{ C_ENUM(HARVEST_INVOICE_PAYMENT_TERM_NET_30), "HARVEST_INVOICE_PAYMENT_TERM_NET_30", "net 30" },
		{ C_ENUM(HARVEST_INVOICE_PAYMENT_TERM_NET_45), "HARVEST_INVOICE_PAYMENT_TERM_NET_45", "net 45" },
		{ C_ENUM(HARVEST_INVOICE_PAYMENT_TERM_NET_60), "HARVEST_INVOICE_PAYMENT_TERM_NET_60", "net 60" },
		{ C_ENUM(HARVEST_INVOICE_PAYMENT_TERM_CUSTOM), "HARVEST_INVOICE_PAYMENT_TERM_CUSTOM", "custom" },
		{ 0, NULL, NULL }
	};
	// clang-format on

	if (g_once_init_enter(&gtype_id)) {
		GType new_type
			= g_enum_register_static(g_intern_static_string("HarvestInvoicePaymentTerm"), values);
		g_once_init_leave(&gtype_id, new_type);
	}

	return (GType) gtype_id;
}

#include "init.h"

#include <glib.h>
#include <libsoup/soup.h>

#include "harvest-glib/harvest.h"

static HarvestApiClient *CLIENT;
static HarvestUser *USER;

static void
test_harvest_get_me(void)
{
	g_autoptr(HarvestResponse) res = harvest_user_get_me(CLIENT);
	USER						   = HARVEST_USER(g_value_dup_object(res->body));

	g_assert_no_error(res->err);
}

static void
test_list_active_project_assignments(void)
{
	g_assert_nonnull(USER);

	g_autoptr(HarvestResponse) res
		= harvest_user_list_active_project_assignments(CLIENT, harvest_user_get_id(USER));

	g_assert_no_error(res->err);
}

int
main(int argc, char *argv[])
{
	g_test_init(&argc, &argv, NULL);

	CLIENT = initialize_environment();

	g_test_add_func("/user/me", test_harvest_get_me);
	g_test_add_func("/user/project_assignments", test_list_active_project_assignments);

	return g_test_run();
}

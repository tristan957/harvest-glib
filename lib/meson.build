harvest_glib_config_h = configuration_data({
    'gettext_package': 'harvest-glib',
})

configure_file(
    input: 'config.h.in',
    output: 'config.h',
    configuration: harvest_glib_config_h,
)

harvest_glib_sources = [
    'client/harvest-client.c',
    'common/harvest-common.c',
    'common/harvest-creator.c',
    'company/harvest-company-enum-types.c',
    'company/harvest-company.c',
    'company/requests/harvest-get-company-request.c',
    'estimate/harvest-estimate-enum-types.c',
    'estimate/harvest-estimate-item-category.c',
    'estimate/harvest-estimate-line-item.c',
    'estimate/harvest-estimate.c',
    'http/api/harvest-api-client.c',
    'http/harvest-http-enum-types.c',
    'http/request/harvest-paged-request.c',
    'http/request/harvest-request.c',
    'http/response/harvest-links.c',
    'http/response/harvest-paged-response.c',
    'http/response/harvest-response-metadata.c',
    'http/response/harvest-response.c',
    'invoice/harvest-invoice-enum-types.c',
    'invoice/harvest-invoice-item-category.c',
    'invoice/harvest-invoice-line-item.c',
    'invoice/harvest-invoice.c',
    'project/harvest-project-task-assignment.c',
    'project/harvest-project-user-assignment.c',
    'project/harvest-project.c',
    'task/harvest-task.c',
    'time-entry/harvest-time-entry.c',
    'time-entry/requests/harvest-late-request.c',
    'user/harvest-user-project-assignment.c',
    'user/harvest-user.c',
    'user/requests/harvest-user-list-active-project-assignments-request.c',
    'user/requests/harvest-users-me-request.c',
    'user/responses/harvest-user-list-active-project-assignments-response.c',
]

harvest_glib_c_args = [
    '-D__HARVEST_COMPILATION__',
    '-DG_LOG_DOMAIN="harvest-glib"',
]

if get_option('buildtype') == 'release'
    harvest_glib_c_args += [
        '-DG_DISABLE_ASSERT',
        '-DG_DISABLE_CHECKS',
        '-DG_DISABLE_CAST_CHECKS',
    ]
elif get_option('buildtype').startswith('debug')
    harvest_glib_c_args += [
        '-DG_ENABLE_DEBUG',
    ]
endif

harvest_glib_dependencies = [
    libgio_dep,
    json_glib_dep,
    libsoup_dep,
]

include_root = join_paths('..', 'include')

harvest_glib = library(
    'harvest-glib',
    harvest_glib_sources,
    version: meson.project_version(),
    c_args: harvest_glib_c_args,
    dependencies: harvest_glib_dependencies,
    include_directories: include_directories(include_root),
    install: true,
)

harvest_glib_dep = declare_dependency(
    link_with: harvest_glib,
    version: meson.project_version(),
    include_directories: include_directories(join_paths(include_root))
)

pkg.generate(
	harvest_glib,
	description: 'GLib-based library for interacting with the Harvest API.',
	filebase: 'harvest-glib-@0@.@1@'.format(harvest_glib_major_version, harvest_glib_minor_version),
	name: 'harvest-glib',
	version: meson.project_version(),
    requires: [
        libsoup_dep,
    ],
	url: 'https://git.sr.ht/~tristan957/harvest-glib',
)

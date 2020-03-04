component_public_headers = [
	'harvest-company-enum-types.h',
    'harvest-company.h',
]

request_public_headers = [
	'requests/harvest-get-company-request.h',
]

component_header_subdir = join_paths(harvest_glib_header_subdir, 'company')
requests_header_subdir = join_paths(component_header_subdir, 'requests')

install_headers(component_public_headers, subdir: component_header_subdir)
install_headers(request_public_headers, subdir: requests_header_subdir)

component_public_headers = [
	'harvest-user-project-assignment.h',
	'harvest-user.h',
]

request_public_headers = [
	'requests/harvest-user-list-active-project-assignments-request.h',
	'requests/harvest-users-me-request.h',
]

response_public_headers = [
	'responses/harvest-user-list-active-project-assignments-response.h'
]

component_header_subdir = join_paths(harvest_glib_header_subdir, 'user')
requests_header_subdir = join_paths(component_header_subdir, 'requests')

install_headers(component_public_headers, subdir: component_header_subdir)
install_headers(request_public_headers, subdir: requests_header_subdir)

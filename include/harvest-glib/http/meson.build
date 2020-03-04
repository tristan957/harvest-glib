component_public_headers = [
	'harvest-http-enum-types.h',
	'harvest-http.h',
]

api_public_headers = [
	'api/harvest-api-client.h',
]

request_public_headers = [
	'request/harvest-paged-request.h',
	'request/harvest-request.h',
]

response_public_headers = [
	'response/harvest-links.h',
	'response/harvest-paged.h',
	'response/harvest-response-metadata.h',
	'response/harvest-response.h',
]

component_header_subdir = join_paths(harvest_glib_header_subdir, 'http')
api_header_subdir = join_paths(component_header_subdir, 'api')
request_header_subdir = join_paths(component_header_subdir, 'request')
response_header_subdir = join_paths(component_header_subdir, 'response')

install_headers(component_public_headers, subdir: component_header_subdir)
install_headers(api_public_headers, subdir: api_header_subdir)
install_headers(request_public_headers, subdir: request_header_subdir)
install_headers(response_public_headers, subdir: response_header_subdir)

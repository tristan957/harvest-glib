project(
	'harvest-glib',
    'c',
	version: '1.0.0',
    license: [
        'LGPL-3.0',
    ],
    default_options: [
        'c_std=gnu18',
        'buildtype=debugoptimized',
    ],
)

add_project_arguments(
    '-Wno-incompatible-pointer-types',
    language: 'c',
)

version_components = meson.project_version().split('.')

harvest_glib_major_version = version_components[0]
harvest_glib_minor_version = version_components[1]
harvest_glib_patch_version = version_components[2]

cc = meson.get_compiler('c')

gnome = import('gnome')
pkg = import('pkgconfig')

libgio_dep = dependency('gio-2.0', version: '>= 2.62.1', required: true, fallback: ['gio', 'libgio_dep'])
json_glib_dep = dependency('json-glib-1.0', version: '>= 1.4.4', required: true, fallback: ['json-glib', 'json_glib_dep'])
libsoup_dep = dependency('libsoup-2.4', version: '>= 2.68.1', required: true, fallback: ['libsoup', 'libsoup_dep'])

subdir('include')
subdir('lib')
if get_option('tests')
    subdir('tests')
endif

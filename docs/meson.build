subdir('xml')

docpath = join_paths(get_option('prefix'), get_option('datadir'), 'gtk-doc/html')
glib_prefix = libgio_dep.get_pkgconfig_variable('prefix')
glib_docpath = join_paths(glib_prefix, 'share/gtk-doc/html')

gnome.gtkdoc(
	'harvest-glib',
	main_sgml: 'harvest-glib-docs.xml',
	src_dir: join_paths(meson.source_root(), 'include', 'harvest-glib'),
	gobject_typesfile: 'harvest-glib.types',
	dependencies: harvest_glib_dep,
	scan_args: [
		'--rebuild-types',
	],
	fixxref_args: [
		'--html-dir=@0@'.format(docpath),
		'--extra-dir=@0@'.format(join_paths(glib_docpath, 'glib')),
		'--extra-dir=@0@'.format(join_paths(glib_docpath, 'gobject')),
		'--extra-dir=@0@'.format(join_paths(glib_docpath, 'libsoup-2.4'))
	],
	install: true
)

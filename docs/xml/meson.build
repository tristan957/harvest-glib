ent_conf = configuration_data()
ent_conf.set('PACKAGE', 'Harvest-GLib')
ent_conf.set('PACKAGE_BUGREPORT', 'https://todo.sr.ht/~tristan957/harvest-glib')
ent_conf.set('PACKAGE_NAME', 'Harvest-GLib')
ent_conf.set('PACKAGE_STRING', 'harvest-glib')
ent_conf.set('PACKAGE_TARNAME', 'harvest-glib-' + meson.project_version())
ent_conf.set('PACKAGE_URL', 'https://git.sr.ht/~tristan957/harvest-glib')
ent_conf.set('PACKAGE_VERSION', meson.project_version())
ent_conf.set('PACKAGE_API_VERSION', meson.project_version())

configure_file(
	input: 'gtkdocentities.ent.in',
	output: 'gtkdocentities.ent',
	configuration: ent_conf
)

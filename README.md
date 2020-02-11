[![builds.sr.ht status](https://builds.sr.ht/~tristan957/harvest-glib.svg)](https://builds.sr.ht/~tristan957/harvest-glib?)

# harvest-glib

GLib-based library for interacting with the Harvest API.

## API Support

### V2

* `/company`
* `/users/me`

## Contributing

This project uses the [Meson](https://mesonbuild.com) build system.

It has the following dependencies:

* `glib`
* `json-glib`
* `libsoup`

Refer to the root meson.build for version information. The dependency versions
maybe able to be tuned to lower versions, but I have not tested them.

### Building

```text
meson build
ninja -C build
```

### Testing

Make sure at least the following environment variables are defined before running
the tests.

* `HARVEST_API_ACCESS_TOKEN={access_token}`
* `HARVEST_API_CONTACT_EMAIL={contact_email}`
* `HARVEST_API_ACCOUNT_ID={account_id}`

```text
ninja test -C build
```

### Installing

```text
ninja install -C build
```

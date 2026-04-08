# roadmap

- [x] rewrite cmake -> mason
- [x] use coda for project manifest
- [ ] add library support
	- [ ] compile with $ as prefix, which will be replaced with the version when pulling
		($std$print)
		- [ ] only need major, major -> semver remap saved in coda manifest in root
	- [ ] correctly replace $ with major in manifest
	- [ ] imlement name -> registry lookup function, by using the defined urls in manifest

- [ ] implement memory model
	- [ ] implement c interop
	- [ ] write c memory management functions
	- [ ] implement structs and classes

- [ ] implement basic types (primitives)
- [ ] implement barrel files with _ prefix for private
	- [ ] barreling causes all symbols to be in the top package

- [ ] implement symbol scan for lambdas
- [ ] make compiler$ interface
- [ ] make std library

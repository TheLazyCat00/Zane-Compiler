# roadmap

- [x] rewrite cmake -> mason
- [x] use coda for project manifest
- [ ] add library support
	- [ ] correctly prefix with version at pull time
	- [ ] correctly prefix package occurrences during compilation
	- [ ] imlement name -> package lookup function, by using the defined urls in manifest

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

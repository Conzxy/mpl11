
# Simple Makefile forwarding to the build directory.

.PHONY: all gen-cmake doc test

# Suppress the output of the forwarding of commands.
${VERBOSE}.SILENT:

all:
	make -C build $@

%:
	make -C build $@

doc:
	make -C build $@ $(args)

test:
	make -C build $@ $(args)

gen-cmake:
	rm -rf build; mkdir build
	cd build; cmake ..; cd ..

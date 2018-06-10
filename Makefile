all: compile

compile:
	meson builddir
	cd builddir ; ninja

check:
	cd builddir ; ninja test

install:
	cd builddir ; ninja install

.PHONY: all compile


all: lib test	

.PHONY: lib clean dist-clean test
lib:
	$(MAKE) -C c3cpp

test: lib
	$(MAKE) -C test

clean:
	$(MAKE) -C c3cpp clean
	$(MAKE) -C test clean

dist-clean: clean
	$(MAKE) -C c3cpp dist-clean
	$(MAKE) -C test dist-clean
	rm -f libc3cpp* c3cpp_test

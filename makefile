ifeq ($(PREFIX),)
    PREFIX := /usr
endif

all: dirs gtkui.so
	cp gtkui.h build/gtkui.h
	cp gtkui.pc build/gtkui.pc

dirs:
	mkdir -p build

gtkui.so: dirs gtkui.o
	gcc -shared build/gtkui.o -o build/libgtkui.so

gtkui.o: dirs
	gcc -c -Wall -Wextra -Werror -fpic `pkg-config --cflags gtk+-3.0` gtkui.c -o build/gtkui.o

clean:
	rm -rf build/

install:
	install -m 644 build/gtkui.h $(PREFIX)/include/gtkui.h
	install -m 644 build/gtkui.so $(PREFIX)/lib/gtkui.h
	install -m 644 build/gtkui.pc $(PREFIX)/pkgconfig/gtkui.pc

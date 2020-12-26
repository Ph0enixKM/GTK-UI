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
	install -m 644 build/libgtkui.so $(PREFIX)/lib/libgtkui.so
	install -m 644 build/gtkui.pc $(PREFIX)/lib/pkgconfig/gtkui.pc

uninstall:
	rm $(PREFIX)/include/gtkui.h
	rm $(PREFIX)/lib/libgtkui.so
	rm $(PREFIX)/lib/pkgconfig/gtkui.pc

DEB_PATH := build/gtkui_$(GTK_UI_DEB_VERSION)
build_deb:
	@echo "Building .deb package $${GTK_UI_DEB_VERSION:?Undefined variable GTK_UI_DEB_VERSION}"
	mkdir -p $(DEB_PATH)
	mkdir -p $(DEB_PATH)/DEBIAN
	mkdir -p $(DEB_PATH)/usr/include
	mkdir -p $(DEB_PATH)/usr/lib/pkgconfig
	sed s/__VERSION__/$(GTK_UI_DEB_VERSION)/ control.template > $(DEB_PATH)/DEBIAN/control
	cp build/gtkui.h $(DEB_PATH)/usr/include/gtkui.h
	cp build/libgtkui.so $(DEB_PATH)/usr/lib/libgtkui.so
	cp build/gtkui.pc $(DEB_PATH)/usr/lib/pkgconfig/gtkui.pc
	dpkg-deb --build $(DEB_PATH) build
	mv $(DEB_PATH)_any.deb $(DEB_PATH).deb

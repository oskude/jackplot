APP        = jackplot
APPDEPS    = jack gl glu glfw3
APPCFLAGS  = `pkg-config --cflags $(APPDEPS)`
APPLDFLAGS = `pkg-config --libs $(APPDEPS)`
PREFIX    ?= /usr/local

.PHONY: all install clean archlinux

all: $(APP)

%.o: code/%.c
	$(CC) -c $(CFLAGS) $(CPPFLAGS) $(APPCFLAGS) $< -o $@

%: code/%.c
	$(CC) $(CFLAGS) $(CPPFLAGS) $(APPCFLAGS) $(APPLDFLAGS) $^ -o $@

install: $(APP)
	install -Dm755 $(APP) $(DESTDIR)$(PREFIX)/bin/$(APP)

clean:
	rm -f $(APP) *.o $(APP).trace $(APP).apng
	rm -rf distro/archlinux/{pkg,src,$(APP),*.pkg.*}

archlinux:
	cd distro/archlinux;\
		makepkg -f

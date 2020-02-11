PROG       = jackplot
MYCFLAGS   = `pkg-config --cflags jack gl glu glfw3`
MYLDFLAGS  = `pkg-config --libs jack gl glu glfw3`
PREFIX    ?= /usr/local

.PHONY: all clean install archlinux

all: $(PROG)

%.o: %.c
	$(CC) -c $(CFLAGS) $(CPPFLAGS) ${MYCFLAGS} $< -o $@

%: %.c
	$(CC) $(CFLAGS) $(CPPFLAGS) ${MYCFLAGS} ${MYLDFLAGS} $^ -o $@

clean:
	rm -f $(PROG) *.o $(PROG).trace
	rm -rf distro/archlinux/{pkg,src,$(PROG),*.pkg.*}

install: $(PROG)
	install -Dm755 $(PROG) $(DESTDIR)$(PREFIX)/bin/$(PROG)

archlinux:
	cd distro/archlinux;\
		makepkg -f

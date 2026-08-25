# Talk Calendar Makefile
CC ?= gcc
PKGCONFIG = $(shell which pkg-config)

CFLAGS = $(shell $(PKGCONFIG) --cflags gtk4 libadwaita-1)
LIBS = $(shell $(PKGCONFIG) --libs gtk4 libadwaita-1) -lsqlite3

SRC = main.c calendarevent.c dbmanager.c diphone.c dictionary.c synthesizer.c
OBJS = $(SRC:.c=.o)

all: talkcalendar

%.o: %.c
	$(CC) -c -o $(@F) $(CFLAGS) $<

talkcalendar: $(OBJS)
	$(CC) -o $(@F) $(OBJS) $(LIBS)

clean:
	rm -f $(OBJS)
	rm -f talkcalendar




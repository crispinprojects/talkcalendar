# Calendar Makefile
# Alan Crispin
# July 2025
CC ?= gcc
PKGCONFIG = $(shell which pkg-config)
CFLAGS = $(shell $(PKGCONFIG) --cflags gtk4)
LIBS = $(shell $(PKGCONFIG) --libs gtk4) -lsqlite3

SRC = main.c customcalendar.c calendarevent.c dbmanager.c

OBJS = $(SRC:.c=.o)

all: talkcalendar


%.o: %.c
	$(CC) -c -o $(@F) $(CFLAGS) $<


talkcalendar: $(OBJS)
	$(CC) -o $(@F) $(OBJS) $(LIBS)

clean:
	rm -f $(OBJS)
	rm -f talkcalendar

install:
	echo "Installing is not supported"

run:
	./talkcalendar



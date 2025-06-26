# Updated Talk Calendar Makefile for use with GNOME Builder IDE
# Alan Crispin
# June 2025
CC ?= gcc
PKGCONFIG = $(shell which pkg-config)
CFLAGS = $(shell $(PKGCONFIG) --cflags gtk4)
# Turn on all warnings (-Wall) use debugging information (-g) and maximum optimization (-O3)
CFLAGS += -Wall
CFLAGS += -g
CFLAGS += -O3
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
# Builder will call this target to install an application before running
install:
	echo "Installing is not supported"
# Builder uses this target to run Talk Caldendar
# Use configure project and setup a run command
run:
	./talkcalendar



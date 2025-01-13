#--------------------------------------------------------------
# Talk Calendar Makefile
# Author: Alan Crispin <crispinalan@gmail.com> 
# Date: February 2024
# Changelog: 0.01
#----------------------------------------------------------------

CC ?= gcc
PKGCONFIG = $(shell which pkg-config)
CFLAGS = $(shell $(PKGCONFIG) --cflags gtk4)
LIBS = $(shell $(PKGCONFIG) --libs gtk4) -lm -lasound -lsqlite3 -lnotify

SRC = main.c displayitem.c calendarevent.c customcalendar.c diphone.c dictionary.c dbmanager.c

OBJS = $(SRC:.c=.o)

all: talkcalendar


%.o: %.c
	$(CC) -c -o $(@F) $(CFLAGS) $<


talkcalendar: $(OBJS)
	$(CC) -o $(@F) $(OBJS) $(LIBS)

clean:
	rm -f $(OBJS)
	rm -f talkcalendar


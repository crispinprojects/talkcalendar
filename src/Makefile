#--------------------------------------------------------------
# Talk Calendar Makefile (Debian Bookworm)
# Author: Alan Crispin <crispinalan@gmail.com> 
# Date: May 2025
# Changelog: 0.03
#----------------------------------------------------------------

CC ?= gcc
PKGCONFIG = $(shell which pkg-config)
CFLAGS = $(shell $(PKGCONFIG) --cflags gtk4)
LIBS = $(shell $(PKGCONFIG) --libs gtk4) -lm -lsqlite3 -lasound

SRC = main.c displayitem.c calendarevent.c customcalendar.c dictionary.c dbmanager.c wordrules.c rawplayer.c

OBJS = $(SRC:.c=.o)

all: talkcalendar


%.o: %.c
	$(CC) -c -o $(@F) $(CFLAGS) $<


talkcalendar: $(OBJS)
	$(CC) -o $(@F) $(OBJS) $(LIBS)

clean:
	rm -f $(OBJS)
	rm -f talkcalendar



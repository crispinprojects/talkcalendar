#--------------------------------------------------------------
# Talk Calendar Makefile (Debian Bookworm)
# Author: Alan Crispin <crispinalan@gmail.com> 
# Date: March 2025
# Changelog: 0.03 flite
#----------------------------------------------------------------

CC ?= gcc
PKGCONFIG = $(shell which pkg-config)
CFLAGS = $(shell $(PKGCONFIG) --cflags gtk4)
LIBS = $(shell $(PKGCONFIG) --libs gtk4) -lm -lsqlite3 -lflite_usenglish -lflite_cmulex -lflite -lflite_cmu_us_kal16 -lflite_cmu_us_rms

SRC = main.c displayitem.c calendarevent.c customcalendar.c dbmanager.c

OBJS = $(SRC:.c=.o)

all: talkcalendar_flite


%.o: %.c
	$(CC) -c -o $(@F) $(CFLAGS) $<


talkcalendar_flite: $(OBJS)
	$(CC) -o $(@F) $(OBJS) $(LIBS)

clean:
	rm -f $(OBJS)
	rm -f talkcalendar_flite



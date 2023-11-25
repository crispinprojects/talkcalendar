CC ?= gcc
PKGCONFIG = $(shell which pkg-config)
CFLAGS = $(shell $(PKGCONFIG) --cflags gtk4)
LIBS = $(shell $(PKGCONFIG) --libs gtk4) -lm -lasound -lsqlite3

SRC = main.c displayitem.c calendarevent.c customcalendar.c diphone.c wavcat.c dictionary.c dbmanager.c

OBJS = $(SRC:.c=.o)

all: talkingcalendar


%.o: %.c
	$(CC) -c -o $(@F) $(CFLAGS) $<


talkingcalendar: $(OBJS)
	$(CC) -o $(@F) $(OBJS) $(LIBS)

clean:
	rm -f $(OBJS)
	rm -f talkingcalendar


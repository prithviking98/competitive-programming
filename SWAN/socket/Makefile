#
# Makefile for the GBT-RRI MBR socket communication framework
#
# Created by Jayanth Chennamangalam
#

CC = g++
CFLAGS = -g -Wall
LFLAGS_X11 = -L/usr/X11R6/lib -lX11
LFLAGS_XML = -lxml2
DMBR_REMOTE = -DMBR_REMOTE -UMBR_LOCAL
DMBR_LOCAL = -UMBR_REMOTE -DMBR_LOCAL
DMBR_SET = -DMBR_SET -UMBR_GET -UMBR_DO
DMBR_GET = -UMBR_SET -DMBR_GET -UMBR_DO
DMBR_DO = -UMBR_SET -UMBR_GET -DMBR_DO
SRCDIR = .
IDIR = .
BINDIR = $(HOME)/bin
REMBINDIR = $(BINDIR)
LOCBINDIR = $(BINDIR)
DELCMD = rm

all: mbrmakever \
	 mbr_version.o \
	 mbr_common.o \
	 mbr_config.o \
	 mbr_set.o \
	 mbr_get.o \
	 mbr_do.o \
	 mbr_serialport.o \
	 mbrset \
	 mbrget \
	 mbrdo \
	 mbrmcd \
	 mbrdasd \
	 mbrrunterms \
	 mbrlivedas \
	 tags

mbrmakever: $(SRCDIR)/mbr_makever.cpp
	$(CC) $(CFLAGS) $(SRCDIR)/mbr_makever.cpp -o $(IDIR)/$@
	$(IDIR)/mbrmakever
	$(DELCMD) $(IDIR)/mbrmakever

mbr_version.o: $(SRCDIR)/mbr_version.cpp
	$(CC) -c $(CFLAGS) $(SRCDIR)/mbr_version.cpp -o $(IDIR)/$@

mbr_common.o: $(SRCDIR)/mbr_common.cpp
	$(CC) -c $(CFLAGS) $(SRCDIR)/mbr_common.cpp -o $(IDIR)/$@

mbr_config.o: $(SRCDIR)/mbr_config.cpp
	$(CC) -c $(CFLAGS) $(SRCDIR)/mbr_config.cpp -o $(IDIR)/$@

mbr_set.o: $(SRCDIR)/mbr_set.cpp
	$(CC) -c $(CFLAGS) $(DMBR_LOCAL) $(DMBR_SET) $(SRCDIR)/mbr_set.cpp \
		-o $(IDIR)/$@

mbr_get.o: $(SRCDIR)/mbr_get.cpp
	$(CC) -c $(CFLAGS) $(DMBR_LOCAL) $(DMBR_GET) $(SRCDIR)/mbr_get.cpp \
		-o $(IDIR)/$@

mbr_do.o: $(SRCDIR)/mbr_do.cpp
	$(CC) -c $(CFLAGS) $(DMBR_LOCAL) $(DMBR_DO) $(SRCDIR)/mbr_do.cpp \
		-o $(IDIR)/$@

mbr_serialport.o: $(SRCDIR)/mbr_serialport.cpp
	$(CC) -c $(CFLAGS) $(DMBR_LOCAL) $(SRCDIR)/mbr_serialport.cpp \
		-o $(IDIR)/$@

mbrset: $(SRCDIR)/mbr_command.cpp
	$(CC) $(CFLAGS) $(DMBR_REMOTE) $(DMBR_SET) $(SRCDIR)/mbr_command.cpp \
		$(IDIR)/mbr_version.o $(IDIR)/mbr_common.o $(IDIR)/mbr_config.o \
		$(LFLAGS_XML) -o $(REMBINDIR)/mbrset
	$(CC) $(CFLAGS) $(DMBR_LOCAL) $(DMBR_SET) $(SRCDIR)/mbr_command.cpp \
		$(IDIR)/mbr_version.o $(IDIR)/mbr_common.o $(IDIR)/mbr_set.o \
		$(IDIR)/mbr_serialport.o $(IDIR)/mbr_config.o $(LFLAGS_XML) \
		-o $(LOCBINDIR)/mbrsetlocal

mbrget: $(SRCDIR)/mbr_command.cpp
	$(CC) $(CFLAGS) $(DMBR_REMOTE) $(DMBR_GET) $(SRCDIR)/mbr_command.cpp \
		$(IDIR)/mbr_version.o $(IDIR)/mbr_common.o $(IDIR)/mbr_config.o \
		$(LFLAGS_XML) -o $(REMBINDIR)/mbrget
	$(CC) $(CFLAGS) $(DMBR_LOCAL) $(DMBR_GET) $(SRCDIR)/mbr_command.cpp \
		$(IDIR)/mbr_version.o $(IDIR)/mbr_common.o $(IDIR)/mbr_get.o \
		$(IDIR)/mbr_config.o $(LFLAGS_XML) -o $(LOCBINDIR)/mbrgetlocal

mbrdo: $(SRCDIR)/mbr_command.cpp
	$(CC) $(CFLAGS) $(DMBR_REMOTE) $(DMBR_DO) $(SRCDIR)/mbr_command.cpp \
		$(IDIR)/mbr_version.o $(IDIR)/mbr_common.o $(IDIR)/mbr_config.o \
		$(LFLAGS_XML) -o $(REMBINDIR)/mbrdo
	$(CC) $(CFLAGS) $(DMBR_LOCAL) $(DMBR_DO) $(SRCDIR)/mbr_command.cpp \
		$(IDIR)/mbr_version.o $(IDIR)/mbr_common.o $(IDIR)/mbr_do.o \
		$(IDIR)/mbr_serialport.o $(IDIR)/mbr_set.o $(IDIR)/mbr_config.o \
		$(LFLAGS_XML) -o $(LOCBINDIR)/mbrdolocal

mbrmcd: $(SRCDIR)/mbr_mcd.cpp
	$(CC) $(CFLAGS) $(SRCDIR)/mbr_mcd.cpp $(IDIR)/mbr_version.o \
		$(IDIR)/mbr_common.o $(IDIR)/mbr_config.o $(LFLAGS_XML) -o $(BINDIR)/$@

mbrdasd: $(SRCDIR)/mbr_dasd.cpp
	$(CC) $(CFLAGS) $(SRCDIR)/mbr_dasd.cpp $(IDIR)/mbr_version.o \
		$(IDIR)/mbr_common.o $(IDIR)/mbr_serialport.o $(IDIR)/mbr_config.o \
		$(IDIR)/mbr_get.o $(LFLAGS_XML) -o $(BINDIR)/$@

mbrrunterms: $(SRCDIR)/mbr_runterms.cpp
	$(CC) $(CFLAGS) $(SRCDIR)/mbr_runterms.cpp $(IDIR)/mbr_version.o \
		$(LFLAGS_X11) -o $(BINDIR)/$@

mbrlivedas: $(SRCDIR)/mbr_livedas.cpp
	$(CC) $(CFLAGS) $(SRCDIR)/mbr_livedas.cpp $(IDIR)/mbr_version.o \
		$(IDIR)/mbr_common.o $(IDIR)/mbr_config.o $(LFLAGS_XML) \
		-o $(BINDIR)/$@

tags: $(SRCDIR)/*.cpp $(SRCDIR)/*.h
	ctags *.cpp *.h

install:
	@echo Nothing to install.

clean:
	$(DELCMD) $(IDIR)/mbr_version.o
	$(DELCMD) $(IDIR)/mbr_common.o
	$(DELCMD) $(IDIR)/mbr_config.o
	$(DELCMD) $(IDIR)/mbr_set.o
	$(DELCMD) $(IDIR)/mbr_get.o
	$(DELCMD) $(IDIR)/mbr_do.o
	$(DELCMD) $(IDIR)/mbr_serialport.o


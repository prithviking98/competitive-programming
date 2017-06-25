#
# Makefile for the GBT-RRI MBR data acquisition programs
#
# Created by Jayanth Chennamangalam
#

CC = g++
CFLAGS = -g -Wall
LFLAGS = -lpcap -lxml2
INCDIR = $(HOME)/src/socket
SRCDIR = .
MCSRCDIR = $(HOME)/src/socket
IDIR = .
BINDIR = $(HOME)/bin
DELCMD = rm

all: mbrmakever \
	 mbr_version.o \
	 mbr_common.o \
	 mbr_config.o \
	 mbr_serialport.o \
	 das_shm.o \
	 mbracquire \
	 mbracqsniff \
	 tags

mbrmakever: $(SRCDIR)/mbr_makever.cpp
	$(CC) $(CFLAGS) $(SRCDIR)/mbr_makever.cpp -I$(INCDIR) -o $(IDIR)/$@
	$(IDIR)/mbrmakever
	$(DELCMD) $(IDIR)/mbrmakever

mbr_version.o: $(SRCDIR)/mbr_version.cpp
	$(CC) -c $(CFLAGS) $(SRCDIR)/mbr_version.cpp -o $(IDIR)/$@

mbr_common.o: $(MCSRCDIR)/mbr_common.cpp
	$(CC) -c $(CFLAGS) $(MCSRCDIR)/mbr_common.cpp -I$(INCDIR) -o $(IDIR)/$@

mbr_config.o: $(MCSRCDIR)/mbr_config.cpp
	$(CC) -c $(CFLAGS) $(MCSRCDIR)/mbr_config.cpp -I$(INCDIR) -o $(IDIR)/$@

mbr_serialport.o: $(MCSRCDIR)/mbr_serialport.cpp
	$(CC) -c $(CFLAGS) $(MCSRCDIR)/mbr_serialport.cpp -I$(INCDIR) -o $(IDIR)/$@

das_shm.o: $(SRCDIR)/das_shm.c
	$(CC) -c $(CFLAGS) $(SRCDIR)/das_shm.c -o $(IDIR)/$@

mbracquire: $(SRCDIR)/mbr_acquire.cpp
	$(CC) $(CFLAGS) $(SRCDIR)/mbr_acquire.cpp $(IDIR)/mbr_version.o \
		$(IDIR)/das_shm.o $(IDIR)/mbr_common.o $(IDIR)/mbr_serialport.o \
		$(IDIR)/mbr_config.o -I$(INCDIR) $(LFLAGS) -o $(BINDIR)/$@

mbracqsniff: $(SRCDIR)/mbr_acqsniff.cpp
	$(CC) $(CFLAGS) $(SRCDIR)/mbr_acqsniff.cpp $(IDIR)/mbr_version.o \
		$(IDIR)/mbr_common.o $(IDIR)/das_shm.o -I$(INCDIR) -o $(BINDIR)/$@

tags: $(SRCDIR)/*.cpp $(SRCDIR)/*.h
	ctags *.cpp *.c *.h $(MCSRCDIR)/mbr_common.* $(MCSRCDIR)/mbr_config.* \
		$(MCSRCDIR)/mbr_serialport.*

install:
	@echo Nothing to install.

clean:
	$(DELCMD) $(IDIR)/mbr_version.o
	$(DELCMD) $(IDIR)/mbr_common.o
	$(DELCMD) $(IDIR)/mbr_config.o
	$(DELCMD) $(IDIR)/mbr_serialport.o
	$(DELCMD) $(IDIR)/das_shm.o


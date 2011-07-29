# Makefile for Irrlicht Examples
# It's usually sufficient to change just the target name and source file list
# and be sure that CXX is set to a valid compiler
Target = tdm
Sources = main.cpp

# general compiler settings
IRRDIR = ../irrlicht-1.5.2
KLANGDIR = ../irrKlang-1.3.0
CXX = g++
CPPFLAGS = -I$(IRRDIR)/include -I/usr/X11R6/include -I$(KLANGDIR)/include
CXXFLAGS = -O3 -ffast-math
#CXXFLAGS = -g -Wall -W

#default target is Linux
all: all_linux

ifeq ($(HOSTTYPE), x86_64)
LIBSELECT=64
endif

# target specific settings
all_linux: LDFLAGS = -L/usr/X11R6/lib$(LIBSELECT) $(KLANGDIR)/bin/linux-gcc/libIrrKlang.so -L$(IRRDIR)/lib/Linux -lIrrlicht -lGL -lGLU -lXxf86vm -lXext -lX11 $(KLANGDIR)/bin/linux-gcc/libIrrKlang.so -pthread 
all_linux clean_linux: SYSTEM=Linux
all_win32: LDFLAGS = -L../../lib/Win32-gcc -lIrrlicht -lopengl32 -lglu32 -lm
all_win32 clean_win32: SYSTEM=Win32-gcc
all_win32 clean_win32: SUF=.exe
# name of the binary - only valid for targets which set SYSTEM
DESTPATH = ./$(Target)$(SUF)

all_linux all_win32:
	$(warning Building...)
	$(CXX) $(CPPFLAGS) $(CXXFLAGS) $(Sources) -o $(DESTPATH) $(LDFLAGS)

clean: clean_linux clean_win32
	$(warning Cleaning...)

clean_linux clean_win32:
	@$(RM) $(DESTPATH)

.PHONY: all all_win32 clean clean_linux clean_win32

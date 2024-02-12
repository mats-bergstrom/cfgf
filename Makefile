######################### -*- Mode: Makefile-Gmake -*- ########################
## Copyright (C) 2024, Mats Bergstrom
## 
## File name       : Makefile
## Description     : build cfgf library
## 
## Author          : Mats Bergstrom
## Created On      : Mon Feb 12 18:07:14 2024
## 
## Last Modified By: Mats Bergstrom
## Last Modified On: Mon Feb 12 18:43:37 2024
## Update Count    : 10
###############################################################################

LDFLAGS = -L.
LDLIBS  = -lcfgf
CFLAGS  = -I.

.PHONY: clean

all: libcfgf.a

libcfgf.a: cfgf.o
	ar crv libcfgf.a cfgf.o

t-cfgf: t-cfgf.o


clean:
	rm -f libcfgf.a cfgf.o t-cfgf.o t-cfgf *~

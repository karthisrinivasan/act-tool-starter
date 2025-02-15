#-------------------------------------------------------------------------
#
#  Copyright (c) 2025 Karthi Srinivasan
#
#  This program is free software; you can redistribute it and/or
#  modify it under the terms of the GNU General Public License
#  as published by the Free Software Foundation; either version 2
#  of the License, or (at your option) any later version.
#
#  This program is distributed in the hope that it will be useful,
#  but WITHOUT ANY WARRANTY; without even the implied warranty of
#  MERCHANTABILITY or FITNESS FOR A PARTICULAR PURPOSE.  See the
#  GNU General Public License for more details.
#
#  You should have received a copy of the GNU General Public License
#  along with this program; if not, write to the Free Software
#  Foundation, Inc., 51 Franklin Street, Fifth Floor,
#  Boston, MA  02110-1301, USA.
#
#-------------------------------------------------------------------------
BINARY=testbin.$(EXT) 

TARGETS=$(BINARY)
TARGETLIBS=libactstarterpass_$(EXT).so

CPPSTD=c++20

OBJS1=main.o

OBJS2=starter_engine.o

OBJS=$(OBJS1) $(OBJS2)

TARGETCONF=starter.conf

SHOBJS=starter_pass.os

SRCS=$(OBJS:.o=.cc) $(SHOBJS:.os=.cc)

SUBDIRS=starter

include $(ACT_HOME)/scripts/Makefile.std

# EXPRLIB=-lexpropt_sh $(ACT_HOME)/lib/libabc.so

STARTERLIB=-lactstarter

$(BINARY): $(LIB) $(OBJS1) $(ACTDEPEND)
	$(CXX) $(SH_EXE_OPTIONS) $(CFLAGS) $(OBJS1) -o $(BINARY) $(SHLIBACTPASS)

$(TARGETLIBS): $(SHOBJS)
	$(ACT_HOME)/scripts/linkso $(TARGETLIBS) $(SHOBJS) $(SHLIBACTPASS) $(EXPRLIB) $(STARTERLIB)

debug: obj_main start_lldb

obj_main:
	@if [ -d $(EXT) -a -f $(EXT)/main.o ] ; \
	then \
		(mv $(EXT)/main.o main.o); \
	fi

start_lldb:
	@if [ -x ${BINARY} ] ; \
	then \
		(lldb ./$(BINARY)); \
	fi

-include Makefile.deps

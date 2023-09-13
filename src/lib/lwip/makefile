# 
# Copyright(C) 2011-2016 Pedro H. Penna <pedrohenriquepenna@gmail.com> 
# Copyright(C) 2023 Leon Junio Martins Ferreira	<leondev.martins@gmail.com> 
#
# This file is part of Nanvix.
#
# Nanvix is free software: you can redistribute it and/or modify
# it under the terms of the GNU General Public License as published by
# the Free Software Foundation, either version 3 of the License, or
# (at your option) any later version.
#
# Nanvix is distributed in the hope that it will be useful,
# but WITHOUT ANY WARRANTY; without even the implied warranty of
# MERCHANTABILITY or FITNESS FOR A PARTICULAR PURPOSE.  See the
# GNU General Public License for more details.
#
# You should have received a copy of the GNU General Public License
# along with Nanvix.  If not, see <http://www.gnu.org/licenses/>.
#

# C source files.
C_SRC = $(wildcard *.c)           \
      $(wildcard api/*.c)      \
	  $(wildcard apps/altcp_tls/*.c)   \
	  $(wildcard apps/http/*.c)   \
	  $(wildcard apps/lwiperf/*.c)   \
	  $(wildcard apps/mnds/*.c)   \
	  $(wildcard apps/mqtt/*.c)   \
	  $(wildcard apps/netbiosns/*.c)   \
      $(wildcard apps/smtp/*.c)   \
	  $(wildcard apps/snmp/*.c)   \
	  $(wildcard apps/sntp/*.c)   \
	  $(wildcard apps/tftp/*.c)   \
	  $(wildcard core/*.c)   \
	  $(wildcard core/ipv4/*.c)   \
	  $(wildcard core/ipv6/*.c)   \
	  $(wildcard netif/ppp/*.c)   \
	  $(wildcard netif/*.c)   \
	  $(wildcard netif/ppp/polarssl/*.c)   \

# Object files.
OBJ = $(C_SRC:.c=.o)   \

# Library name.
LIB = lwip.a

# Builds the C library.
all: $(OBJ)
	$(AR) $(ARFLAGS) $(LIBDIR)/$(LIB) $^

# Builds object file from C source file.
%.o: %.c
	$(CC) $< $(CFLAGS) -c -o $@

# Cleans compilation files.
clean:
	@rm -f $(LIBDIR)/$(LIB)
	@rm -f $(OBJ)

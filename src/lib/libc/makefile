# 
# Copyright(C) 2011-2016 Pedro H. Penna <pedrohenriquepenna@gmail.com> 
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
      $(wildcard assert/*.c)      \
      $(wildcard ctype/*.c)       \
      $(wildcard dirent/*.c)      \
      $(wildcard errno/*.c)       \
      $(wildcard fcntl/*.c)       \
      $(wildcard signal/*.c)      \
      $(wildcard stdio/*.c)       \
      $(wildcard stdlib/*.c)      \
      $(wildcard string/*.c)      \
      $(wildcard stropts/*.c)     \
      $(wildcard sys/times/*.c)   \
      $(wildcard sys/sem/*.c)     \
      $(wildcard sys/stat/*.c)    \
      $(wildcard sys/utsname/*.c) \
      $(wildcard sys/wait/*.c)    \
      $(wildcard termios/*.c)     \
      $(wildcard unistd/*.c)      \
      $(wildcard utime/*.c)       \
      $(wildcard lwip/*.c)           \
      $(wildcard lwip/api/*.c)      \
	$(wildcard lwip/apps/altcp_tls/*.c)   \
	$(wildcard lwip/apps/http/*.c)   \
      $(wildcard lwip/apps/lwiperf/*.c)     \
	$(wildcard lwip/apps/mnds/*.c)   \
	$(wildcard lwip/apps/mqtt/*.c)   \
	$(wildcard lwip/apps/netbiosns/*.c)   \
      $(wildcard lwip/apps/smtp/*.c)   \
	$(wildcard lwip/apps/snmp/*.c)   \
	$(wildcard lwip/apps/sntp/*.c)   \
	$(wildcard lwip/apps/tftp/*.c)   \
	$(wildcard lwip/core/*.c)   \
	$(wildcard lwip/core/ipv4/*.c)   \
	$(wildcard lwip/core/ipv6/*.c)   \
	$(wildcard lwip/netif/ppp/*.c)   \
	$(wildcard lwip/netif/*.c)   \
	$(wildcard lwip/netif/ppp/polarssl/*.c)   \

# Assembly source files.
ASM_SRC = $(wildcard signal/*.S) \

# Object files.
OBJ = $(ASM_SRC:.S=.o) \
	  $(C_SRC:.c=.o)   \

# Library name.
LIB = libc.a

# Builds the C library.
all: $(OBJ)
	$(AR) $(ARFLAGS) $(LIBDIR)/$(LIB) $^

# Builds object file from C source file.
%.o: %.c
	$(CC) $< $(CFLAGS) -c -o $@

# Builds object file from assembly source file.
%.o: %.S
	$(CC) $< $(CFLAGS) -c $(ASMFLAGS) -o $@

# Cleans compilation files.
clean:
	@rm -f $(LIBDIR)/$(LIB)
	@rm -f $(OBJ)

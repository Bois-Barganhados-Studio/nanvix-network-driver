/*
 * Copyright(C) 2011-2015 Pedro H. Penna <pedrohenriquepenna@gmail.com>
 *              2015-2015 Davidson Francis <davidsondfgl@gmail.com>
 * 
 * This file is part of Nanvix.
 * 
 * Nanvix is free software; you can redistribute it and/or modify
 * it under the terms of the GNU General Public License as published by
 * the Free Software Foundation; either version 3 of the License, or
 * (at your option) any later version.
 * 
 * Nanvix is distributed in the hope that it will be useful,
 * but WITHOUT ANY WARRANTY; without even the implied warranty of
 * MERCHANTABILITY or FITNESS FOR A PARTICULAR PURPOSE. See the
 * GNU General Public License for more details.
 * 
 * You should have received a copy of the GNU General Public License
 * along with Nanvix. If not, see <http://www.gnu.org/licenses/>.
 */


#include <dev/tty.h>
#include <stropts.h>
#include <termios.h>

/*
 * Sets the parameters associated with the terminal
 */
int tcsetattr(int fd, int optional_actions, 
	const struct termios *termiosp)
{
	struct set_termios_attr sta;
	sta.optional_actions = optional_actions;
	sta.termiosp = termiosp;

	return (ioctl(fd, TTY_SETS, &sta));
}
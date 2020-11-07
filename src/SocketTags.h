/**
 * This file is part of piESocket.
 * Copyright (c) 2020 Mateusz Mirosławski.
 *
 * piESocket is free software: you can redistribute it and/or modify
 * it under the terms of the GNU General Public License as published by
 * the Free Software Foundation; either version 3 of the License, or
 * (at your option) any later version.
 *
 * piESocket is distributed in the hope that it will be useful,
 * but WITHOUT ANY WARRANTY; without even the implied warranty of
 * MERCHANTABILITY or FITNESS FOR A PARTICULAR PURPOSE.  See the
 * GNU General Public License for more details.
 *
 * You should have received a copy of the GNU General Public License
 * along with piESocket.  If not, see <http://www.gnu.org/licenses/>.
 */

#ifndef SRC_SOCKETTAGS_H_
#define SRC_SOCKETTAGS_H_

#include <onhSHMcpp/ShmServer.h>

/**
 * Socket tag structure
 */
typedef struct {
	/// Trigger tag
	onh::PDTag<bool> trigger;
	/// Trigger lock tag
	onh::PDTag<bool> triggerLock;
	/// Not ack flag (informs that alarm is not ack)
	onh::PDTag<bool> alarmNotAck;
	/// Socket relay tag
	onh::PDTag<bool> out;
	/// Alarm Tag
	onh::PDTag<bool> alarm;
	/// Locked state Tag
	onh::PDTag<bool> locked;
} SocketTags;

#endif /* SRC_SOCKETTAGS_H_ */

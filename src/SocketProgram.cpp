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

#include "SocketProgram.h"

SocketProgram::SocketProgram()
{
}

SocketProgram::~SocketProgram() {
}

void SocketProgram::run(SocketTags& tags, ESocket& prog, onh::PDTag<bool>& extOff) {

	// Attach inputs
	prog.setNotAck(tags.alarmNotAck);
	prog.setTriggerLock(tags.triggerLock);
	prog.setIn(tags.trigger);
	prog.setOff(extOff);

	// Run logic
	prog.run();

	// Attach outputs
	tags.trigger = false;
	tags.out = prog.getOut();
	tags.alarm = prog.getAlarm();
	tags.locked = prog.isLocked();
}

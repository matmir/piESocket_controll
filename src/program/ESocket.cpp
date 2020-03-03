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

#include "ESocket.h"

ESocket::ESocket(unsigned long int switchDelay):
	trigger(false), oldTrigger(false), triggerLock(false), locked(false), out(false), alarm(false), isAlarmNotAck(false), switchProt(switchDelay)
{
}

ESocket::~ESocket() {
}

void ESocket::run() {

	// Update lock flag
	if (alarm || isAlarmNotAck || triggerLock) {
		locked = true;
	} else {
		locked = false;
	}

	// Reset alarm
	if (alarm && isAlarmNotAck) {
		if (switchProt.delayPassed()) {
			alarm = false;
		}
	}

	// Change state?
	if ((trigger != oldTrigger) && !locked) {

		// Check delay protection
		if (switchProt.delayPassed()) {

			// Change output value
			out = trigger;

			// Remember trigger value
			oldTrigger = trigger;

			// Start protection delay
			switchProt.startDelay();

		} else {

			// Set alarm
			alarm = true;
			locked = true;

			// Restart delay
			switchProt.stopDelay();
			switchProt.startDelay();
		}
	}
}

void ESocket::setTrigger(bool trig) {

	trigger = trig;
}

void ESocket::setTriggerLock(bool lck) {

	triggerLock = lck;
}

void ESocket::setNotAck(bool notAck) {

	isAlarmNotAck = notAck;
}

bool ESocket::getOut() {

	return out;
}

bool ESocket::getAlarm() {

	return alarm;
}

bool ESocket::isLocked() {

	return locked;
}

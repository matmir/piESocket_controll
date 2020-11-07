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
	trigger(false),
	oldIn(false),
	triggerLock(false),
	locked(false),
	out(false),
	alarm(false),
	isAlarmNotAck(false),
	goOFF(false),
	oldOff(false),
	switchProt(switchDelay)
{
}

ESocket::~ESocket() {
}

void ESocket::setOutput(bool oVal) {

	// Check delay protection
	if (switchProt.delayPassed()) {

		// Change output value
		out = oVal;

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

void ESocket::updateLockFlag() {

	bool fl = false;

	// Alarm is active
	if (alarm || isAlarmNotAck) {
		fl = true;
	}

	// Lock is triggered
	if (triggerLock) {
		fl = true;
	}

	// Go OFF activated but delay is working
	if (goOFF && !switchProt.delayPassed()) {
		fl = true;
	}

	locked = fl;
}

void ESocket::run() {

	// Update lock flag
	updateLockFlag();

	// Reset alarm
	if (alarm && isAlarmNotAck) {
		if (switchProt.delayPassed()) {
			alarm = false;
		}
	}

	// Update trigger
	if (locked) {
		trigger = false;
	}

	// Change state
	if (trigger && !goOFF) {

		trigger = false;

		// Invert state
		setOutput(!out);
	}

	// Go OFF
	if (goOFF && !locked) {
		setOutput(false);
		goOFF = false;
	}
}

void ESocket::setIn(bool inp) {

	if (inp && !oldIn) {
		trigger = true;
	}

	oldIn = inp;
}

void ESocket::setTriggerLock(bool lck) {

	triggerLock = lck;
}

void ESocket::setNotAck(bool notAck) {

	isAlarmNotAck = notAck;
}

bool ESocket::getOut() const {

	return out;
}

bool ESocket::getAlarm() const {

	return alarm;
}

bool ESocket::isLocked() const {

	return locked;
}

void ESocket::setOff(bool off) {

	if (out && off && !oldOff) {
		goOFF = true;
	}

	oldOff = off;
}

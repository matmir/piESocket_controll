/**
 * This file is part of openNetworkHMI.
 * Copyright (c) 2020 Mateusz Mirosławski.
 *
 * openNetworkHMI is free software: you can redistribute it and/or modify
 * it under the terms of the GNU General Public License as published by
 * the Free Software Foundation; either version 3 of the License, or
 * (at your option) any later version.
 *
 * openNetworkHMI is distributed in the hope that it will be useful,
 * but WITHOUT ANY WARRANTY; without even the implied warranty of
 * MERCHANTABILITY or FITNESS FOR A PARTICULAR PURPOSE.  See the
 * GNU General Public License for more details.
 *
 * You should have received a copy of the GNU General Public License
 * along with openNetworkHMI.  If not, see <http://www.gnu.org/licenses/>.
 */

#include "Delay.h"
#include <thread>

using namespace onh;

Delay::Delay(unsigned int msec):
	itsMsec(msec), delayStarted(false), waitPoint(std::chrono::steady_clock::now())
{
}

Delay::~Delay()
{
}

void Delay::startDelay() {

	// Check if delay is already running
	if (delayStarted) {
		throw Exception("Timer already running", "Delay::startDelay");
	}

	// Get start time
	std::chrono::time_point<std::chrono::steady_clock> start = std::chrono::steady_clock::now();

	// Calculate finish time point
	waitPoint = start + std::chrono::milliseconds(itsMsec);

	// Set delay started flag
	delayStarted = true;
}

void Delay::setDelay(unsigned int msec) {

	itsMsec = msec;
}

bool Delay::delayPassed() {

	bool ret = false;

	// Check if delay is running
	if (delayStarted) {

		std::chrono::time_point<std::chrono::steady_clock> tp = std::chrono::steady_clock::now();
		std::chrono::duration<double, std::milli> tmp = tp - waitPoint;

		ret = (tmp.count() < 0)?(false):(true);

		if (ret)
			delayStarted = false;

	} else {
		ret = true;
	}

	return ret;
}

void Delay::stopDelay() {

	delayStarted = false;
}

void Delay::wait() {

    // Check if delay is already running
	if (delayStarted) {
		throw Exception("Timer already running", "Delay::wait");
	}

	// Sleep for milliseconds
	std::this_thread::sleep_for(std::chrono::milliseconds(itsMsec));
}

void Delay::waitAfterStart() {

	// Check if delay is running
	if (delayStarted) {

		// Sleep till reach time point
		std::this_thread::sleep_until(waitPoint);

		delayStarted = false;

	} else {
		throw Exception("Timer is not started", "Delay::waitAfterStart");
	}
}

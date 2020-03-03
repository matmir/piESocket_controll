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

using namespace onh;

Delay::Delay(unsigned long int msec):
		itsMsec(msec), timerCreated(false), delayStarted(false), timerid(NULL)
{
	// Prepare signal structure
	sev.sigev_notify = SIGEV_NONE;
	sev.sigev_signo = SIGRTMIN;
	sev.sigev_value.sival_ptr = timerid;

	// Create timer
	if (timer_create(CLOCK_REALTIME, &sev, &timerid) == 0) {
		timerCreated = true;
	}

}

Delay::~Delay()
{
	if (timerCreated) {
		timer_delete(timerid);
	}
}

void Delay::startDelay() {

	// Check if timer is created
	if (!timerCreated) {
		throw Exception("Timer is not created", "Delay::startDelay");
	}

	// Check if delay is already running
	if (delayStarted) {
		throw Exception("Timer already running", "Delay::startDelay");
	}

	// Seconds
	long int seconds = itsMsec / 1000;
	// milliseconds
	long int ms = itsMsec % 1000;
	// nanoseconds
	long nst = ms * 1000000;

	// Start the timer
	its.it_value.tv_sec = seconds;
	its.it_value.tv_nsec = nst;
	// one shot timer
	its.it_interval.tv_sec = 0;
	its.it_interval.tv_nsec = 0;

	// Set timer time
	if (timer_settime(timerid, 0, &its, NULL) == -1) {
		throw Exception("Error while set timer time", "Delay::startDelay");
	}

	// Set delay started flag
	delayStarted = true;
}

void Delay::setDelay(unsigned long int msec) {

	itsMsec = msec;
}

bool Delay::delayPassed() {

	struct itimerspec cts;

	bool ret = false;

	// Check if timer is created
	if (!timerCreated) {
		throw Exception("Timer is not created", "Delay::delayPassed");
	}

	// Check if delay is running
	if (delayStarted) {

		// Get timer time
		if (timer_gettime(timerid, &cts) == 0) {

			// Check values
			if ((cts.it_value.tv_sec == 0) && (cts.it_value.tv_nsec == 0)) {

				ret = true;
				delayStarted = false;

			} else {

				ret = false;

			}

		} else { // error
			throw Exception("Error while get timer time", "Delay::delayPassed");
		}

	} else {
		ret = true;
	}

	return ret;
}

void Delay::stopDelay() {

	// Check if timer is created
	if (!timerCreated) {
		throw Exception("Timer is not created", "Delay::stopDelay");
	}

	// Start the timer
	its.it_value.tv_sec = 0;
	its.it_value.tv_nsec = 0;
	// one shot timer
	its.it_interval.tv_sec = 0;
	its.it_interval.tv_nsec = 0;

	// Set timer time
	if (timer_settime(timerid, 0, &its, NULL) == -1) {
		throw Exception("Error while set timer time", "Delay::stopDelay");
	}

	delayStarted = false;
}

void Delay::wait() {

    // Check if delay is already running
	if (delayStarted) {
		throw Exception("Timer already running", "Delay::wait");
	}

    // Convert to nanoseconds
    long int ns = itsMsec*1000000;
    // Seconds
    long int seconds = ns / 1000000000L;
    // nanoseconds
    long nst = ns % 1000000000L;

    // Configure time structure
    struct timespec time1 = {0};
    time1.tv_sec = seconds;
    time1.tv_nsec = nst;

    // Sleep
    nanosleep(&time1, (struct timespec *)NULL);
}

void Delay::waitAfterStart() {

	struct itimerspec cts;

	// Check if timer is created
	if (!timerCreated) {
		throw Exception("Timer is not created", "Delay::waitAfterStart");
	}

	// Check if delay is running
	if (delayStarted) {

		// Get timer time
		if (timer_gettime(timerid, &cts) == 0) {

			// Check values
			if ((cts.it_value.tv_sec == 0) && (cts.it_value.tv_nsec == 0)) {

				stopDelay();

			} else {

				// Configure time structure
				struct timespec time1 = {0};
				time1.tv_sec = cts.it_value.tv_sec;
				time1.tv_nsec = cts.it_value.tv_nsec;

				// Sleep rest of the time
				nanosleep(&time1, (struct timespec *)NULL);
				stopDelay();
			}

		} else { // error
			throw Exception("Error while get timer time", "Delay::waitAfterStart");
		}

	} else {
		throw Exception("Timer is not started", "Delay::waitAfterStart");
	}
}

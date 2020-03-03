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

#include "Application.h"
#include "utils/Delay.h"
#include <iostream>

Application::Application(const std::string &smem, bool *exSignal):
	shmServer(smem), exitProg(false), exitSignal(exSignal), T1(0), T2(0), T3(0), T4(0)
{
	// Prepare tags for Socket 1
	T1 = new SocketTags{
		shmServer.getTag<bool>({onh::PDA_MEMORY, 10, 0}), // Trigger
		shmServer.getTag<bool>({onh::PDA_MEMORY, 11, 0}), // Trigger Lock
		shmServer.getTag<bool>({onh::PDA_MEMORY, 12, 0}), // Ack alarm
		shmServer.getTag<bool>({onh::PDA_OUTPUT, 10, 0}), // Output relay
		shmServer.getTag<bool>({onh::PDA_OUTPUT, 11, 0}), // Output alarm
		shmServer.getTag<bool>({onh::PDA_OUTPUT, 12, 0}), // Output Locked state
	};

	// Prepare tags for Socket 2
	T2 = new SocketTags{
		shmServer.getTag<bool>({onh::PDA_MEMORY, 10, 1}), // Trigger
		shmServer.getTag<bool>({onh::PDA_MEMORY, 11, 1}), // Trigger Lock
		shmServer.getTag<bool>({onh::PDA_MEMORY, 12, 1}), // Ack alarm
		shmServer.getTag<bool>({onh::PDA_OUTPUT, 10, 1}), // Output relay
		shmServer.getTag<bool>({onh::PDA_OUTPUT, 11, 1}), // Output alarm
		shmServer.getTag<bool>({onh::PDA_OUTPUT, 12, 1}), // Output Locked state
	};

	// Prepare tags for Socket 3
	T3 = new SocketTags{
		shmServer.getTag<bool>({onh::PDA_MEMORY, 10, 2}), // Trigger
		shmServer.getTag<bool>({onh::PDA_MEMORY, 11, 2}), // Trigger Lock
		shmServer.getTag<bool>({onh::PDA_MEMORY, 12, 2}), // Ack alarm
		shmServer.getTag<bool>({onh::PDA_OUTPUT, 10, 2}), // Output relay
		shmServer.getTag<bool>({onh::PDA_OUTPUT, 11, 2}), // Output alarm
		shmServer.getTag<bool>({onh::PDA_OUTPUT, 12, 2}), // Output Locked state
	};

	// Prepare tags for Socket 4
	T4 = new SocketTags{
		shmServer.getTag<bool>({onh::PDA_MEMORY, 10, 3}), // Trigger
		shmServer.getTag<bool>({onh::PDA_MEMORY, 11, 3}), // Trigger Lock
		shmServer.getTag<bool>({onh::PDA_MEMORY, 12, 3}), // Ack alarm
		shmServer.getTag<bool>({onh::PDA_OUTPUT, 10, 3}), // Output relay
		shmServer.getTag<bool>({onh::PDA_OUTPUT, 11, 3}), // Output alarm
		shmServer.getTag<bool>({onh::PDA_OUTPUT, 12, 3}), // Output Locked state
	};

	// Init GPIO
	initGPIO();
}

Application::~Application() {
	if (T1)
		delete T1;
	if (T2)
		delete T2;
	if (T3)
		delete T3;
	if (T4)
		delete T4;
}

void Application::run() {

	// Delay 50ms
	onh::Delay d(50);

	while (!exitProg && !(*exitSignal)) {

		try {

			// Parse client commands
			shmServer.parseClientCommand();

			// Call socket programs
			eSocketProgram();

			// Set outputs
			setOutputs();

			// Copy process data to SHM
			shmServer.copyProcessData();

			// Check exit flag
			exitProg = shmServer.isExitFlag();

			d.wait();

		} catch(std::exception &e) {

			exitProg = true;
			std::cout << e.what() << std::endl;
		}
	}
}

void Application::initGPIO() {

	#ifdef __arm__
		// Open GPIO bank
		output_chip = gpiod_chip_open_by_number(0);

		// Open GPIO line
		output_K1 = gpiod_chip_get_line(output_chip, 21);
		output_K2 = gpiod_chip_get_line(output_chip, 20);
		output_K3 = gpiod_chip_get_line(output_chip, 16);
		output_K4 = gpiod_chip_get_line(output_chip, 12);
		if (output_chip == NULL || output_K1 == NULL || output_K2 == NULL || output_K3 == NULL || output_K4 == NULL) {
			std::cout << "ERROR\n";

			throw onh::Exception("Can not open GPIO line");
		}

		// Output configuration
		gpiod_line_request_output(output_K1, "socket1", GPIOD_LINE_ACTIVE_STATE_HIGH);
		gpiod_line_request_output(output_K2, "socket2", GPIOD_LINE_ACTIVE_STATE_HIGH);
		gpiod_line_request_output(output_K3, "socket3", GPIOD_LINE_ACTIVE_STATE_HIGH);
		gpiod_line_request_output(output_K4, "socket4", GPIOD_LINE_ACTIVE_STATE_HIGH);

		// Set relays OFF
		gpiod_line_set_value(output_K1, 1);
		gpiod_line_set_value(output_K2, 1);
		gpiod_line_set_value(output_K3, 1);
		gpiod_line_set_value(output_K4, 1);
	#endif
}

void Application::eSocketProgram() {

	// Socket 1
	S1.setNotAck(T1->alarmNotAck);
	S1.setTriggerLock(T1->triggerLock);
	S1.setTrigger(T1->trigger);
	S1.run();
	T1->out = S1.getOut();
	T1->alarm = S1.getAlarm();
	T1->locked = S1.isLocked();

	// Socket 2
	S2.setNotAck(T2->alarmNotAck);
	S2.setTriggerLock(T2->triggerLock);
	S2.setTrigger(T2->trigger);
	S2.run();
	T2->out = S2.getOut();
	T2->alarm = S2.getAlarm();
	T2->locked = S2.isLocked();

	// Socket 3
	S3.setNotAck(T3->alarmNotAck);
	S3.setTriggerLock(T3->triggerLock);
	S3.setTrigger(T3->trigger);
	S3.run();
	T3->out = S3.getOut();
	T3->alarm = S3.getAlarm();
	T3->locked = S3.isLocked();

	// Socket 4
	S4.setNotAck(T4->alarmNotAck);
	S4.setTriggerLock(T4->triggerLock);
	S4.setTrigger(T4->trigger);
	S4.run();
	T4->out = S4.getOut();
	T4->alarm = S4.getAlarm();
	T4->locked = S4.isLocked();
}

void Application::setOutputs() {

	#ifdef __arm__
		// Check Relay 1
		if (T1->out) {
			gpiod_line_set_value(output_K1, 0);
		} else {
			gpiod_line_set_value(output_K1, 1);
		}

		// Check Relay 2
		if (T2->out) {
			gpiod_line_set_value(output_K2, 0);
		} else {
			gpiod_line_set_value(output_K2, 1);
		}

		// Check Relay 3
		if (T3->out) {
			gpiod_line_set_value(output_K3, 0);
		} else {
			gpiod_line_set_value(output_K3, 1);
		}

		// Check Relay 4
		if (T4->out) {
			gpiod_line_set_value(output_K4, 0);
		} else {
			gpiod_line_set_value(output_K4, 1);
		}
	#endif
}

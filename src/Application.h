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

#ifndef SRC_APPLICATION_H_
#define SRC_APPLICATION_H_

#include <onhSHMcpp/ShmServer.h>
#include <gpiod.h>
#include "program/ESocket.h"

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

class Application {

	public:

		/**
		 * Application constructor
		 *
		 * @param smem Shared memory region name
		 * @param exSignal Exit signal flag handle
		 */
		Application(const std::string &smem, bool *exSignal);

		/**
		 * Copy constructor - inactive
		 */
		Application(const Application&) = delete;

		virtual ~Application();

		/**
		 * Assignment operator - inactive
		 */
		Application& operator=(const Application&) = delete;

		/**
		 * Run application program
		 */
		void run();

	private:
		/// SHM server
		onh::ShmServer shmServer;

		/// Exit program flag
		bool exitProg;

		/// Handle for exit signal flag
		bool *exitSignal;

		/// GPIO data
		struct gpiod_chip *output_chip;
		struct gpiod_line *output_K1;
		struct gpiod_line *output_K2;
		struct gpiod_line *output_K3;
		struct gpiod_line *output_K4;

		/// Electric socket program
		ESocket S1, S2, S3, S4;

		/// Electric socket tags
		SocketTags *T1, *T2, *T3, *T4;

		/**
		 * Initialize GPIO device
		 */
		void initGPIO();

		/**
		 * Call electric socket programs
		 */
		void eSocketProgram();

		/**
		 * Set physical outputs
		 */
		void setOutputs();
};

#endif /* SRC_APPLICATION_H_ */

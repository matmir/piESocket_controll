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

#ifndef SRC_PROGRAM_ESOCKET_H_
#define SRC_PROGRAM_ESOCKET_H_

#include "../utils/Delay.h"

	/**
	 * Electric socket control class
	 */
	class ESocket {

		public:

			/**
			 * Default constructor
			 *
			 * @param switchDelay Switch delay protection time (default 5s)
			 */
			ESocket(unsigned long int switchDelay = 5000);

			/**
			 * Copy constructor - inactive
			 */
			ESocket(const ESocket&) = delete;

			virtual ~ESocket();

			/**
			 * Assignment operator - inactive
			 */
			ESocket& operator=(const ESocket&) = delete;

			/**
			 * Run socket program
			 */
			void run();

			/**
			 * Set socket input flag
			 *
			 * @param inp Input value
			 */
			void setIn(bool inp);

			/**
			 * Set socket trigger lock flag
			 *
			 * @param lck Lock flag
			 */
			void setTriggerLock(bool lck);

			/**
			 * Set alarm acknowledgment flag (true - alarm is not ack)
			 *
			 * @param ack
			 */
			void setNotAck(bool notAck);

			/**
			 * Get output flag
			 *
			 * @return Output flag
			 */
			bool getOut() const;

			/**
			 * Get alarm flag (too fast state change)
			 *
			 * @return Alarm flag
			 */
			bool getAlarm() const;

			/**
			 * Get socket lock state
			 *
			 * @return Socket Lock state
			 */
			bool isLocked() const;

			/**
			 * Turn socket OFF
			 */
			void setOff(bool off);

		private:

			/// Change socket state
			bool trigger;

			/// Input old value
			bool oldIn;

			/// Trigger lock flag
			bool triggerLock;

			/// Socket locked flag (can not change state)
			bool locked;

			/// Output flag
			bool out;

			/// Alarm flag (too fast state change)
			bool alarm;

			/// Alarm not acknowledgment flag
			bool isAlarmNotAck;

			/// Run socket to OFF state
			bool goOFF;

			/// Old off input value
			bool oldOff;

			/// Switch protection
			onh::Delay switchProt;

			/**
			 * Set output socket state
			 *
			 * @param oVal Output value
			 */
			void setOutput(bool oVal);

			/**
			 * Update internal lock flag
			 */
			void updateLockFlag();
	};

#endif /* SRC_PROGRAM_ESOCKET_H_ */

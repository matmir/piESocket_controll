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

#ifndef SRC_UTILS_DELAY_H_
#define SRC_UTILS_DELAY_H_

#include <signal.h>
#include <time.h>
#include "Exception.h"

namespace onh {

	/**
	 * Delay class
	 */
	class Delay {
        public:

            /**
             * Constructor
             *
             * @param msec Number of milliseconds
             */
            Delay(unsigned long int msec);

            /**
             * Copy constructor - inactive
             * @param
             */
            Delay(const Delay&) = delete;

            virtual ~Delay();

            /**
			 * Assign operator - inactive
			 */
            Delay& operator=(const Delay&) = delete;

            /**
             * Start delay
             */
            void startDelay();

            /**
             * Set delay time
             *
             * @param msec Number of milliseconds
             */
            void setDelay(unsigned long int msec);

            /**
             * Check if delay passed
             *
             * @return True if delay passed
             */
            bool delayPassed();

            /**
             * Stop delay
             */
            void stopDelay();

            /**
             * Wait until delay is passed
             */
            void wait();

            /**
             * Wait rest time after timer started
             */
            void waitAfterStart();

        private:

            /// Configured delay time (milliseconds)
            unsigned long int itsMsec;

            /// Flag informs that timer is created
            bool timerCreated;

            /// Flag informs that delay is started
            bool delayStarted;

            /// Timer structure
            timer_t timerid;

            /// Signal structure
            struct sigevent sev;

            /// Timer settings structure
            struct itimerspec its;
	};

}

#endif /* SRC_UTILS_DELAY_H_ */

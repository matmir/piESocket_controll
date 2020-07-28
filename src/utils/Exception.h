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

#ifndef SRC_UTILS_EXCEPTION_H
#define SRC_UTILS_EXCEPTION_H

#include <exception>
#include <string>

namespace onh {

    /**
     * Base exception class
     */
    class Exception: public std::exception {

        public:

            Exception();
            virtual ~Exception() noexcept;

            /**
             * Exception constructor with message
             *
             * @param exceptionMSG Exception additional info
             */
            Exception(const std::string& exceptionMSG);

            /**
             * Exception constructor with message and function name
             *
             * @param exceptionMSG Exception additional info
             * @param funcName Function from which exception was thrown
             */
            Exception(const std::string& exceptionMSG, const std::string& funcName);

            /**
             * Get exception message
             *
             * @return Exception message
             */
            virtual const char* what() const noexcept;

        protected:
            /// String with the error message
            std::string errorMessage;

            /// Function from which exception was thrown
            std::string functionName;

            /// Full error message
            std::string allMessage;
    };

}

#endif // SRC_UTILS_EXCEPTION_H

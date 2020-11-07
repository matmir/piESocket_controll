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

#ifndef SRC_SOCKETPROGRAM_H_
#define SRC_SOCKETPROGRAM_H_

#include "program/ESocket.h"
#include "SocketTags.h"

	/**
	 * Socket control program
	 */
	class SocketProgram {

		public:

			SocketProgram();
			virtual ~SocketProgram();

			/**
			 * Run socket program
			 *
			 * @param tags Socket Tags structure
			 * @param prog Socket program
			 * @param extOff External off signal
			 */
			static void run(SocketTags& tags, ESocket& prog, onh::PDTag<bool>& extOff);
	};

#endif /* SRC_SOCKETPROGRAM_H_ */

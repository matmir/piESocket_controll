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

#include <iostream>
#include <signal.h>
#include <string.h>

#include "Application.h"

using namespace std;

bool exitSignal;

// Exit signal function
void term(int signum) {

	exitSignal = true;
}

int main() {

	exitSignal = false;

	// --------------------- PROGRAM TERMINATION --------------------------
	struct sigaction action;
	memset(&action, 0, sizeof(struct sigaction));
	action.sa_handler = term;
	sigaction(SIGTERM, &action, NULL);

	try {

		// Run app
		Application app("piESocket_SHM", &exitSignal);
		app.run();

	} catch (onh::Exception &e) {

		std::cout << e.what() << std::endl;
	}


	return 0;
}

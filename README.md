piESocket controll program
=======

Program for controlling electric sockets connected to Raspberry Pi and communicate with openNetworkHMI system.

INSTALATION
===========

	git clone https://github.com/matmir/piESocket_controll.git
	cd piESocket_controll
	mkdir build          # Directory with build output
	cd build
	cmake ..             # Generate build script
	make                 # Build application

To build application with tests add option:

	cmake -DWithTest=true ..

Project site: https://opennetworkhmi.net/index.php?s=piESocket

License
=======

Software is licensed on GPLv3 license.
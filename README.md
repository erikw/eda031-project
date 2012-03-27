# EDA031 Project - News System
A project in the course [EDA031](http://cs.lth.se/eda031) C++ Programming at Lund University 2012. The goal is to design and implement a news system with a server and client; much like the good old Usenet but more lightweight. 

For further documentation; visit [doc/](https://github.com/erikw/eda031_project/tree/master/doc).

## How to build and run
Compile and run by typing the following commands:

	$cd eda031_project/build/
	$make help
	$make
	$server/server_main [--db (memory | file)] [--port portnum] &
	$client/client_main [--host hostname] [--port portnum]
	news> help
	news> <commmand>
	.
	.
	news> <commmand>
	.
	.
	^D

The commands and the results produced corresponds to the functional requirements described in the specification. Type `make help` for more instructions about compilation. The paramters defaults to
* db:=file
* port:=1025
* host:=localhost

##Contributors

[Oscar Olsson](https://github.com/DrunkenInfant)

[Erik Westrup](https://github.com/erikw)

[Joachim Nelson](https://github.com/pimpimmi)

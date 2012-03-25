# EDA031 Project - News System
A project in the course [EDA031](http://cs.lth.se/eda031) C++ Programming at Lund University 2012. The goal is to design and implement a news system with a server and client; much like the good old Usenet but more lightweight. 

For further documentation; visit [doc/](https://github.com/erikw/eda031_project/tree/master/doc).

## How to build and run
Compile and run by typing the following commands:

	$cd eda031_project/build/
	$make
	$server/server_main [--db (memory | file)] [--port portnum] &
	$client/client_main [--host hostname] [--port portnum]
	> <query>
	<result>
	> <query>
	.
	.
	.
	^D

With \<query\> and \<result\> as described in the specification.

##Contributors

[Oscar Olsson](https://github.com/DrunkenInfant)

[Erik Westrup](https://github.com/erikw)

[Joachim Nelson](https://github.com/pimpimmi)

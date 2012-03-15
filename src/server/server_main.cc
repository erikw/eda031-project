#include <iostream>
#include <cstdlib>
#include "connection.h"
#include "server.h"

using namespace net;
using std::clog;

int main() {
	clog << "Server started." << std::endl;
	server::Server serv(1025);
	return EXIT_SUCCESS;
}

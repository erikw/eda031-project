#include <iostream>
#include <string>
#include <cstdlib>
#include <cstring>

using namespace std;
//using namespace net;

const unsigned int default_port = 1025;
const string default_host = "localhost";
unsigned int port;

bool read_args(unsigned int &port, string &host, size_t argc, char **argv);

int main(int argc, char **argv) {
	string host;
	if (!read_args(port, host, argc, argv)) {
		return EXIT_FAILURE;
	}
	clog << "Client started. Connecting to " << host << ":" << port << "." << std::endl;

	// TODO connect to server and read user commands.

	clog << "Client terminating." << endl;
	return EXIT_SUCCESS;
}

const char *arg_usage = "Usage: $client_main [--host hostname] [--port portnum]";

bool read_args(unsigned int &port, string &host, size_t argc, char **argv) {
	port = default_port;
	host = default_host;
	bool error = false;
	if (argc == 1) {
		// Use defaults.
	} else if (!(argc == 3 || argc == 5)) {
		error = true;
		cerr << arg_usage << endl;
	} else {
		for (size_t i = 1; i < argc; i += 2) {
			if (!strcmp(argv[i], "--host")) {
				host = argv[i + 1];
			} else if (!strcmp(argv[i], "--port")) {
				unsigned int read_port = atoi(argv[i + 1]);
					if (read_port == 0 || read_port < 1025) {
						error = true;
						cerr << "Port must be > 1024" << endl;
					} else {
						port = read_port;
					}
			} else {
				error = true;
				cerr << "Parameter \"" << argv[i] << "\" is unrecognized." << endl;
				cerr << arg_usage << endl;
			}
		}
	}
	return !error;
}

#include <iostream>
#include <sstream>
#include <cstdlib>
#include <cstring>

#include "server/server.h"
#include "net/connection.h"
#include "net/messagehandler.h"
#include "db/database.h"
#include "db/memory_db.h"

using namespace std;
using namespace net;
using namespace server;
using namespace db;

const unsigned int default_port = 1025;
const string default_db = "memory";

bool read_args(unsigned int &port, string &db_type, size_t argc, char **argv); 

int main(int argc, char **argv) {
	unsigned int port;
	string db_type;
	if (!read_args(port, db_type, argc, argv)) {
		return EXIT_FAILURE;
	}

	clog << "Starting server on port " << port << " with a " << db_type << " database..." << endl;
	Server server(port);
	if (!server.isReady()) {
		cerr << "Server could not be initialized correctly." << endl;
		return EXIT_FAILURE;
	} else {
		cout << "Server is running." << endl;
	}

	Database *database;
	if (db_type == "memory") {
		database  = new MemoryDB();
	} else {
		//database = new Filedb(); // TODO not implemented.
	}
	MessageHandler message_handler(*database);

	while (true) {
		Connection *connection = server.waitForActivity();
		if (connection) {
			try {
				Query *query; // TODO who deallocates, me I guess?
				try {
					query = message_handler.recieve_query(*connection);

				} catch (const IllegalCommandException &ice) {
					// TODO
				}

				query->execute();

			} catch (const ConnectionClosedException &cce) {
				// TODO delete this connection.
			}

		} else {
			clog << "New incoming connection." << endl;
			server.registerConnection(new Connection());
		}
	}


	delete database; // TODO will this happen if server is quited with interrupt signal?
	return EXIT_SUCCESS;
}

const char *arg_usage = "Usage: $server_main [--db (memory | file)] [--port portnum]";

bool read_args(unsigned int &port, string &db_type, size_t argc, char **argv) {
	port = default_port;
	db_type = default_db;
	bool error = false;
	if (argc == 1) {
		// Use defaults.
	} else if (!(argc == 3 || argc == 5)) {
		error = true;
		cerr << arg_usage << endl;
	} else {
		for (size_t i = 1; i < argc; i += 2) {
			if (!strcmp(argv[i], "--db")) {
				if (!strcmp(argv[i + 1], "memory") || !strcmp(argv[i + 1], "file")) {
					db_type = argv[i + 1];
				 } else {
					 error = true;
					 cerr << "The database type \"" << argv[i + 1] << "\"is not recognized." << endl;
				 }
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

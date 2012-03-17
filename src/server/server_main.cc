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

// Usage: $server_main [--db (memory | file) --port portnum]
int main(int argc, char **argv) {
	unsigned int port = default_port;
	string db_type = default_db;
	if (argc == 1) {
		// Do nothing, using defaults.
	} else if (argc == 5) {
		cout << argv[1] << " : " << argv[2] << endl;
		if (!strcmp(argv[1], "--db") && (!strcmp(argv[2], "memory") || !strcmp(argv[2], "file"))) {
			db_type = argv[2];
		} else {
			cerr << "Bad database parameters." << endl;
			return EXIT_FAILURE;

		}
		if (!(!strcmp(argv[3], "--port") && (port = atoi(argv[4])) && port > 1024)) {
			cerr << "Bad port option (must be > 1024)." << endl;
			return EXIT_FAILURE;
		}
	} else {
		cerr << "Usage: $server_main [--db (memory | file) --port portnum]" << endl;
		return EXIT_FAILURE;
	}

	Server server(port);
	clog << "Server started on port " << port << " with a " << db_type << " database." << endl;
	if (!server.isReady()) {
		cerr << "Server could not be initialized correctly." << endl;
		return EXIT_FAILURE;
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

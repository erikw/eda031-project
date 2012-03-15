#include <iostream>
#include <cstdlib>
#include "connection.h"
#include "server.h"
#include "database.h"
#include "memory_db.h"
#include "messagehandler.h"

using namespace std;
using namespace net;
using namespace server;
using namespace db;

const unsigned int default_port = 1025;
const string default_db = "memory";

// Usage: $server_main [--db (memory | file) --port portnum]
int main(int argc, char **argv) {
	clog << "Server started." << endl;
	unsigned int port;
	string db_type;
	if (argc == 1) {
		port = default_port;
		db_type = default_db;
	} else if (argc == 4) {
		string db_str;
		if (!(cin >> db_str && db_str == "--db" && cin >> db_type && (db_type == "memory" || db_type == "file"))) {
			cerr << "Bad database parameters.";
			return EXIT_FAILURE;
		}
		string port_str;
		if (!(cin >> port_str && port_str == "--port" && cin >> port && port > 1024)) {
			cerr << "Bad port option (must be > 1024)." << endl;
			return EXIT_FAILURE;
		} 
	} else {
		cerr << "Usage: $server_main [--db (memory | file) --port portnum]" << endl;
		return EXIT_FAILURE;
	}

	clog << "Using port " << port << "and a database type " << db_type << "." << endl;
	Server server(port);
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

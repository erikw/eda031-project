#ifndef MESSAGEHANDLERCLIENT_H
#define MESSAGEHANDLERCLIENT_H

#include <string>
#include "net/connection.h"
#include "db/result.h"
#include "db/database.h"

namespace net {
	struct IllegalCommandException {};

	class MessageHandlerClient {
	public:
		MessageHandlerClient();
		db::Result* recieve_result(Connection &con) throw(IllegalCommandException, ConnectionClosedException);
		// void print_result(db::Result &res);
	private:
		db::Result *read_list_ng(Connection &con) throw(IllegalCommandException, ConnectionClosedException);
		db::Result *read_create_ng(Connection &con) throw(IllegalCommandException, ConnectionClosedException);
		db::Result *read_delete_ng(Connection &con) throw(IllegalCommandException, ConnectionClosedException);
		db::Result *read_list_art(Connection &con) throw(IllegalCommandException, ConnectionClosedException);
		db::Result *read_create_art(Connection &con) throw(IllegalCommandException, ConnectionClosedException);
		db::Result *read_delete_art(Connection &con) throw(IllegalCommandException, ConnectionClosedException);
		db::Result *read_get_art(Connection &con) throw(IllegalCommandException, ConnectionClosedException);

		std::string read_string(Connection &con) throw (IllegalCommandException, ConnectionClosedException);
		int read_num(Connection &con) throw (IllegalCommandException, ConnectionClosedException);
		int read_int(Connection &con) throw (ConnectionClosedException);
	};
}

#endif

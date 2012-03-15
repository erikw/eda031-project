#ifndef MESSAGEHANDLER_H
#define MESSAGEHANDLER_H

#include <string>
#include "connection.h"
#include "result.h"
#include "query.h"
#include "database.h"

namespace net {
	struct IllegalCommandException {};
	
	class MessageHandler {
	public:
		MessageHandler(db::Database& database);
		db::Query* recieve_query(Connection& con) throw(IllegalCommandException, ConnectionClosedException);
		void send_result(db::Result& res) ;
	private:
		db::Query* read_list_ng(Connection& con) throw(IllegalCommandException, ConnectionClosedException);
		db::Query* read_create_ng(Connection& con) throw(IllegalCommandException, ConnectionClosedException);
		db::Query* read_delete_ng(Connection& con) throw(IllegalCommandException, ConnectionClosedException);
		db::Query* read_list_art(Connection& con) throw(IllegalCommandException, ConnectionClosedException);
		db::Query* read_create_art(Connection& con) throw(IllegalCommandException, ConnectionClosedException);
		db::Query* read_delete_art(Connection& con) throw(IllegalCommandException, ConnectionClosedException);
		db::Query* read_get_art(Connection& con) throw(IllegalCommandException, ConnectionClosedException);

		std::string read_string(Connection& con) throw (IllegalCommandException, ConnectionClosedException);
		int read_num(Connection& con) throw (IllegalCommandException, ConnectionClosedException);
		int read_int(Connection& con) throw (ConnectionClosedException);

		db::Database db;
	};
}

#endif

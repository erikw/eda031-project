
#ifndef MESSAGEHANDLER_H
#define MESSAGEHANDLER_H

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
			db::Database db;
	};
}



#endif

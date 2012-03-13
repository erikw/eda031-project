
#ifndef MESSAGEHANDLER_H
#define MESSAGEHANDLER_H

#include "connection.h"
#include "result.h"
#include "query.h"

namespace net {
	struct IllegalCommandException {}
	
	class MessageHandler {
		public:
			MessageHandler(Database& database);
			Query* recieve_query(Connection& con) const throw(IllegalCommandException, ConnectionClosedException);
			void send_result(Result& res) const;
		private:
			Query* read_list_ng(Connection& con) const throw(IllegalCommandException, ConnectionClosedException);
			Database db;
	};
}



#endif

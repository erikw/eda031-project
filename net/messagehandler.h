#ifndef MESSAGEHANDLER_H
#define MESSAGEHANDLER_H

#include "connection.h"
#include "result.h"
#include "query.h"

namespace {
	
	class MessageHandler {
	public:
		MessageHandler(Connection& con);
		Query &recieve_message();
		void send_result(Result& res);
	private:
		Connection con;
	};
}


#endif

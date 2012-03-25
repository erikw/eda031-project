#ifndef SERVERMESSAGEINTERPRETER_H
#define SERVERMESSAGEINTERPRETER_H

#include "net/connectionclosedexception.h"
#include "net/messagehandler.h"
#include "db/query.h"
#include "net/protocol.h"

namespace server {

	class ServerMessageInterpreter {
	public:
		db::Query *recieve_query(net::MessageHandler &mh) throw(net::IllegalCommandException, net::ConnectionClosedException);
	private:
		db::Query *read_list_ng(net::MessageHandler &mh) throw(net::IllegalCommandException, net::ConnectionClosedException);
		db::Query *read_create_ng(net::MessageHandler &mh) throw(net::IllegalCommandException, net::ConnectionClosedException);
		db::Query *read_delete_ng(net::MessageHandler &mh) throw(net::IllegalCommandException, net::ConnectionClosedException);
		db::Query *read_list_art(net::MessageHandler &mh) throw(net::IllegalCommandException, net::ConnectionClosedException);
		db::Query *read_create_art(net::MessageHandler &mh) throw(net::IllegalCommandException, net::ConnectionClosedException);
		db::Query *read_delete_art(net::MessageHandler &mh) throw(net::IllegalCommandException, net::ConnectionClosedException);
		db::Query *read_get_art(net::MessageHandler &mh) throw(net::IllegalCommandException, net::ConnectionClosedException);
	};
}

#endif






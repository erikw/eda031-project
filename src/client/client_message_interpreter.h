#ifndef CLIENTMESSAGEINTERPRETER_H
#define CLIENTMESSAGEINTERPRETER_H

#include <string>
#include "net/messagehandler.h"
#include "db/result.h"
#include "db/database.h"

namespace client {
	class ClientMessageInterpreter {
	public:
		ClientMessageInterpreter();
		db::Result* recieve_result(net::MessageHandler &mh) throw(net::IllegalCommandException, net::ConnectionClosedException);
	private:
		db::Result *read_list_ng(net::MessageHandler &mh) throw(net::IllegalCommandException, net::ConnectionClosedException);
		db::Result *read_create_ng(net::MessageHandler &mh) throw(net::IllegalCommandException, net::ConnectionClosedException);
		db::Result *read_delete_ng(net::MessageHandler &mh) throw(net::IllegalCommandException, net::ConnectionClosedException);
		db::Result *read_list_art(net::MessageHandler &mh) throw(net::IllegalCommandException, net::ConnectionClosedException);
		db::Result *read_create_art(net::MessageHandler &mh) throw(net::IllegalCommandException, net::ConnectionClosedException);
		db::Result *read_delete_art(net::MessageHandler &mh) throw(net::IllegalCommandException, net::ConnectionClosedException);
		db::Result *read_get_art(net::MessageHandler &mh) throw(net::IllegalCommandException, net::ConnectionClosedException);
	};
}

#endif

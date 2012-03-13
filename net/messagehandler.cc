#include "messagehandler.h"
#include "protocol.h"
#include "listngquery.h"

namespace net {

	using namespace db;
	MessageHandler::MessageHandler(Database& database) : db(database) {}

	Query* MessageHandler::recieve_query(Connection& con) throw(IllegalCommandException, ConnectionClosedException){
		char command_type = con.read();
		Query *query;
		switch (command_type) {
			case Protocol::COM_LIST_NG:
				query = read_list_ng(con);
				break;
			case Protocol::COM_CREATE_NG:
				break;
			case Protocol::COM_DELETE_NG:
				break;
			case Protocol::COM_LIST_ART:
				break;
			case Protocol::COM_CREATE_ART:
				break;
			case Protocol::COM_DELETE_ART:
				break;
			case Protocol::COM_GET_ART:
				break;
			case Protocol::COM_END:
				break;
		}
	}

	Query* MessageHandler::read_list_ng(Connection& con) throw (IllegalCommandException, ConnectionClosedException){
		char end_command = con.read();
		if(end_command != Protocol::COM_END)
			throw IllegalCommandException();
		return new ListNGQuery(db);
	}
}

#include "messagehandler.h"

namespace net {

	MessageHandler::MessageHandler(Database& database) : db(database) {}

	Query* MessageHandler::recieve_query(Connection& con) throw(IllegalCommandExcption, ConnectionClosedException){
		char command_type = con.read();
		Query *query;
		switch (command_type) {
			case COM_LIST_NG:
				query = read_list_ng(conn);
				break;
			case COM_CREATE_NG:
				break;
			case COM_DELETE_NG:
				break;
			case COM_LIST_ART:
				break;
			case COM_CREATE_ART:
				break;
			case COM_DELETE_ART:
				break;
			case COM_GET_ART:
				break;
			case COM_END:
				break;
		}
	}

	Query* MessageHandler::read_list_ng(Connection& con) throw (IllegalCommandExcption, ConnectionClosedException){
		char end_command = con.read();
		if(end_command != COM_END)
			throw IllegalCommandException();
		return new ListNGQuery(db);
	}
}

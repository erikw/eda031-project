#include "server/server_message_interpreter.h"

#include "db/create_art_query.h"
#include "db/create_ng_query.h"
#include "db/delete_art_query.h"
#include "db/delete_ng_query.h"
#include "db/get_art_query.h"
#include "db/list_art_query.h"
#include "db/list_ng_query.h"
#include "net/protocol.h"

using namespace db;
using namespace net;
using namespace std;

namespace server {
	Query *ServerMessageInterpreter::recieve_query(MessageHandler &mh) throw(IllegalCommandException, ConnectionClosedException){
		unsigned char command_type = mh.read_byte();
		Query *query;
		switch (command_type) {
			case Protocol::COM_LIST_NG:
				query = read_list_ng(mh);
				break;
			case Protocol::COM_CREATE_NG:
				query = read_create_ng(mh);
				break;
			case Protocol::COM_DELETE_NG:
				query = read_delete_ng(mh);
				break;
			case Protocol::COM_LIST_ART:
				query = read_list_art(mh);
				break;
			case Protocol::COM_CREATE_ART:
				query = read_create_art(mh);
				break;
			case Protocol::COM_DELETE_ART:
				query = read_delete_art(mh);
				break;
			case Protocol::COM_GET_ART:
				query = read_get_art(mh);
				break;
			default:
				throw IllegalCommandException();
		}
		return query;
	}

	Query *ServerMessageInterpreter::read_list_ng(MessageHandler &mh) throw (IllegalCommandException, ConnectionClosedException){
		char end_command = mh.read_byte();
		if (end_command != Protocol::COM_END)
			throw IllegalCommandException();
		return new ListNGQuery();
	}

	Query *ServerMessageInterpreter::read_create_ng(MessageHandler &mh) throw (IllegalCommandException, ConnectionClosedException){
		string ng_name = mh.read_string();
		char end_command = mh.read_byte();
		if (end_command != Protocol::COM_END)
			throw IllegalCommandException();
		return new CreateNGQuery(ng_name);
	}

	Query *ServerMessageInterpreter::read_delete_ng(MessageHandler &mh) throw (IllegalCommandException, ConnectionClosedException){
		int ng_id = mh.read_num();
		char end_command = mh.read_byte();
		if (end_command != Protocol::COM_END)
			throw IllegalCommandException();
		return new DeleteNGQuery(ng_id);
	}

	Query *ServerMessageInterpreter::read_list_art(MessageHandler &mh) throw (IllegalCommandException, ConnectionClosedException){
		int ng_id = mh.read_num();
		char end_command = mh.read_byte();
		if (end_command != Protocol::COM_END)
			throw IllegalCommandException();
		return new ListArtQuery(ng_id);
	}

	Query *ServerMessageInterpreter::read_create_art(MessageHandler &mh) throw (IllegalCommandException, ConnectionClosedException){
		int ng_id = mh.read_num();
		string title = mh.read_string();
		string author = mh.read_string();
		string text = mh.read_string();
		char end_command = mh.read_byte();
		if (end_command != Protocol::COM_END)
			throw IllegalCommandException();
		return new CreateArtQuery(ng_id, title, author, text);
	}

	Query *ServerMessageInterpreter::read_delete_art(MessageHandler &mh) throw (IllegalCommandException, ConnectionClosedException){
		int ng_id = mh.read_num();
		int art_id = mh.read_num();
		char end_command = mh.read_byte();
		if (end_command != Protocol::COM_END)
			throw IllegalCommandException();
		return new DeleteArtQuery(ng_id, art_id);
	}

	Query* ServerMessageInterpreter::read_get_art(MessageHandler &mh) throw (IllegalCommandException, ConnectionClosedException){
		int ng_id = mh.read_num();
		int art_id = mh.read_num();
		char end_command = mh.read_byte();
		if (end_command != Protocol::COM_END)
			throw IllegalCommandException();
		return new GetArtQuery(ng_id, art_id);
	}
}

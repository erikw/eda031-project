#include "messagehandler.h"
#include "protocol.h"
#include "listngquery.h"
#include "createngquery.h"
#include "deletengquery.h"
#include "listartquery.h"
#include "createartquery.h"
#include "deleteartquery.h"
#include "getartquery.h"

namespace net {
	using namespace db;
	using namespace std;
	MessageHandler::MessageHandler(Database& database) : db(database) {}

	Query* MessageHandler::recieve_query(Connection& con) throw(IllegalCommandException, ConnectionClosedException){
		unsigned char command_type = con.read();
		Query *query;
		switch (command_type) {
			case Protocol::COM_LIST_NG:
				query = read_list_ng(con);
				break;
			case Protocol::COM_CREATE_NG:
				query = read_create_ng(con);
				break;
			case Protocol::COM_DELETE_NG:
				query = read_delete_ng(con);
				break;
			case Protocol::COM_LIST_ART:
				query = read_list_art(con);
				break;
			case Protocol::COM_CREATE_ART:
				query = read_create_art(con);
				break;
			case Protocol::COM_DELETE_ART:
				query = read_delete_art(con);
				break;
			case Protocol::COM_GET_ART:
				query = read_get_art(con);
				break;
			default:
				throw IllegalCommandException();
		}
	}

	Query* MessageHandler::read_list_ng(Connection& con) throw (IllegalCommandException, ConnectionClosedException){
		char end_command = con.read();
		if (end_command != Protocol::COM_END)
			throw IllegalCommandException();
		return new ListNGQuery(db);
	}

	Query* MessageHandler::read_create_ng(Connection& con) throw (IllegalCommandException, ConnectionClosedException){
		string ng_name = this->read_string(con);
		char end_command = con.read();
		if (end_command != Protocol::COM_END)
			throw IllegalCommandException();
		return new CreateNGQuery(db, ng_name);
	}

	Query* MessageHandler::read_delete_ng(Connection& con) throw (IllegalCommandException, ConnectionClosedException){
		int ng_id = this->read_num(con);
		char end_command = con.read();
		if (end_command != Protocol::COM_END)
			throw IllegalCommandException();
		return new DeleteNGQuery(db, ng_id);
	}

	Query* MessageHandler::read_list_art(Connection& con) throw (IllegalCommandException, ConnectionClosedException){
		int ng_id = this->read_num(con);
		char end_command = con.read();
		if (end_command != Protocol::COM_END)
			throw IllegalCommandException();
		return new ListArtQuery(db, ng_id);
	}

	Query* MessageHandler::read_create_art(Connection& con) throw (IllegalCommandException, ConnectionClosedException){
		int ng_id = this->read_num(con);
		string title = this->read_string(con);
		string author = this->read_string(con);
		string text = this->read_string(con);
		char end_command = con.read();
		if (end_command != Protocol::COM_END)
			throw IllegalCommandException();
		return new CreateArtQuery(db, ng_id, title, author, text);
	}

	Query* MessageHandler::read_delete_art(Connection& con) throw (IllegalCommandException, ConnectionClosedException){
		int ng_id = this->read_num(con);
		int art_id = this->read_num(con);
		char end_command = con.read();
		if (end_command != Protocol::COM_END)
			throw IllegalCommandException();
		return new DeleteArtQuery(db, ng_id, art_id);
	}

	Query* MessageHandler::read_get_art(Connection& con) throw (IllegalCommandException, ConnectionClosedException){
		int ng_id = this->read_num(con);
		int art_id = this->read_num(con);
		char end_command = con.read();
		if (end_command != Protocol::COM_END)
			throw IllegalCommandException();
		return new GetArtQuery(db, ng_id, art_id);
	}

	string MessageHandler::read_string(Connection& con) throw (IllegalCommandException, ConnectionClosedException){
		if (con.read() != Protocol::PAR_STRING)
			throw IllegalCommandException();
		int size = read_int(con);
		string str;
		while(size > 0){
			str += con.read();
			--size;
		}
		return str;
	}

	int MessageHandler::read_num(Connection& con) throw (IllegalCommandException, ConnectionClosedException){
		if(con.read() != Protocol::PAR_NUM)
			throw IllegalCommandException();
		unsigned int num = read_int(con);
		return num;
	}

	int MessageHandler::read_int(Connection& con) throw (ConnectionClosedException){
		unsigned int res;
		for(unsigned char i = 0; i < 4; ++i){
			unsigned char tmp = con.read();
			res <<= 8;
			res += tmp;
		}
		return res;
	}

	void MessageHandler::send_result(db::Result result) { // TODO Does not this one needsa a connection (and thorw some exceptions?)

	}
}

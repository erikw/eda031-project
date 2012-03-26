#include "client/client_message_interpreter.h"
#include "net/protocol.h"
#include "db/list_ng_result.h"
#include "db/create_ng_result.h"
#include "db/delete_ng_result.h"
#include "db/list_art_result.h"
#include "db/create_art_result.h"
#include "db/delete_art_result.h"
#include "db/get_art_result.h"


namespace client {
	using namespace db;
	using namespace net;
	using namespace std;
	ClientMessageInterpreter::ClientMessageInterpreter(){}

	Result *ClientMessageInterpreter::recieve_result(MessageHandler &mh) throw(IllegalCommandException, ConnectionClosedException){
		unsigned char command_type = mh.read_byte();
		Result *result;
		switch (command_type) {
			case Protocol::ANS_LIST_NG:
				result = read_list_ng(mh);
				break;
			case Protocol::ANS_CREATE_NG:
				result = read_create_ng(mh);
				break;
			case Protocol::ANS_DELETE_NG:
				result = read_delete_ng(mh);
				break;
			case Protocol::ANS_LIST_ART:
				result = read_list_art(mh);
				break;
			case Protocol::ANS_CREATE_ART:
				result = read_create_art(mh);
				break;
			case Protocol::ANS_DELETE_ART:
				result = read_delete_art(mh);
				break;
			case Protocol::ANS_GET_ART:
				result = read_get_art(mh);
				break;
			default:
				throw IllegalCommandException();
		}
		return result;
	}

	Result *ClientMessageInterpreter::read_list_ng(MessageHandler &mh) throw (IllegalCommandException, ConnectionClosedException){
		int size = mh.read_num();
		vector<pair<int, string> > results;		
		while (size > 0){
			int id = mh.read_num();
			string title = mh.read_string();
			results.push_back(make_pair(id, title));
			--size;
		}
		char end_command = mh.read_byte();
		if (end_command != Protocol::ANS_END)
			throw IllegalCommandException();
		return new ListNGResult(results);
	}

	Result *ClientMessageInterpreter::read_create_ng(MessageHandler &mh) throw (IllegalCommandException, ConnectionClosedException){
		char ans = mh.read_byte();
		if (ans == Protocol::ANS_NAK)
			ans = mh.read_byte();
		char end_command = mh.read_byte();
		if (end_command != Protocol::ANS_END)
			throw IllegalCommandException();
		return new CreateNGResult(ans);
	}

	Result *ClientMessageInterpreter::read_delete_ng(MessageHandler &mh) throw (IllegalCommandException, ConnectionClosedException){
		char ans = mh.read_byte();
		if (ans == Protocol::ANS_NAK)
			ans = mh.read_byte();
		char end_command = mh.read_byte();
		if (end_command != Protocol::ANS_END)
			throw IllegalCommandException();
		return new DeleteNGResult(ans);
	}

	Result *ClientMessageInterpreter::read_list_art(MessageHandler &mh) throw (IllegalCommandException, ConnectionClosedException){
		if (mh.read_byte() == Protocol::ANS_ACK){
			int size = mh.read_num();
			vector<pair<int, string> > results;		
			while (size > 0){
				int id = mh.read_num();
				string title = mh.read_string();
				results.push_back(make_pair(id, title));
				--size;
			}
			char end_command = mh.read_byte();
			if (end_command != Protocol::ANS_END)
				throw IllegalCommandException();
			return new ListArtResult(results);
		}
		char err_message = mh.read_byte();
		char end_command = mh.read_byte();
		if (end_command != Protocol::ANS_END)
			throw IllegalCommandException();
		return new ListArtResult(err_message);
	}

	Result *ClientMessageInterpreter::read_create_art(MessageHandler &mh) throw (IllegalCommandException, ConnectionClosedException){
		char ans = mh.read_byte();
		if (ans == Protocol::ANS_NAK)
			ans = mh.read_byte();
		char end_command = mh.read_byte();
		if (end_command != Protocol::ANS_END)
			throw IllegalCommandException();
		return new CreateArtResult(ans);
	}

	Result *ClientMessageInterpreter::read_delete_art(MessageHandler &mh) throw (IllegalCommandException, ConnectionClosedException){
		char ans = mh.read_byte();
		if (ans == Protocol::ANS_NAK)
			ans = mh.read_byte();
		char end_command = mh.read_byte();
		if (end_command != Protocol::ANS_END)
			throw IllegalCommandException();
		return new DeleteArtResult(ans);
	}

	Result* ClientMessageInterpreter::read_get_art(MessageHandler &mh) throw (IllegalCommandException, ConnectionClosedException){
		if (mh.read_byte() == Protocol::ANS_ACK){
			string title = mh.read_string();
			string author = mh.read_string();
			string text = mh.read_string();
			char end_command = mh.read_byte();
			if (end_command != Protocol::ANS_END)
				throw IllegalCommandException();
			return new GetArtResult(title, author, text);
		}
		char err_message = mh.read_byte();
		char end_command = mh.read_byte();
		if (end_command != Protocol::ANS_END)
			throw IllegalCommandException();
		return new GetArtResult(err_message);
	}
}

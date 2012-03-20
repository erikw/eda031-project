#include "net/messagehandler_client.h"
#include "net/protocol.h"
#include "db/list_ng_result.h"
#include "db/create_ng_result.h"
#include "db/delete_ng_result.h"
#include "db/list_art_result.h"
#include "db/create_art_result.h"
#include "db/delete_art_result.h"
#include "db/get_art_result.h"

namespace net {
	using namespace db;
	using namespace std;
	MessageHandlerClient::MessageHandlerClient(){}

	Result *MessageHandlerClient::recieve_result(Connection &con) throw(IllegalCommandException, ConnectionClosedException){
		unsigned char command_type = con.read();
		Result *result;
		switch (command_type) {
			case Protocol::ANS_LIST_NG:
				result = read_list_ng(con);
				break;
			case Protocol::ANS_CREATE_NG:
				result = read_create_ng(con);
				break;
			case Protocol::ANS_DELETE_NG:
				result = read_delete_ng(con);
				break;
			case Protocol::ANS_LIST_ART:
				result = read_list_art(con);
				break;
			case Protocol::ANS_CREATE_ART:
				result = read_create_art(con);
				break;
			case Protocol::ANS_DELETE_ART:
				result = read_delete_art(con);
				break;
			case Protocol::ANS_GET_ART:
				result = read_get_art(con);
				break;
			default:
				throw IllegalCommandException();
		}
		return result;
	}

	Result *MessageHandlerClient::read_list_ng(Connection &con) throw (IllegalCommandException, ConnectionClosedException){
		int size = this->read_num(con);
		vector<pair<int, string> > results;		
		while (size > 0){
			results.push_back(make_pair(this->read_num(con), this->read_string(con)));
			--size;
		}
		char end_command = con.read();
		if (end_command != Protocol::COM_END)
			throw IllegalCommandException();
		return new ListNGResult(results);
	}

	Result *MessageHandlerClient::read_create_ng(Connection &con) throw (IllegalCommandException, ConnectionClosedException){
		char ans = con.read();
		if (ans == Protocol::ANS_NAK)
			ans = con.read();
		char end_command = con.read();
		if (end_command != Protocol::COM_END)
			throw IllegalCommandException();
		return new CreateNGResult(ans);
	}

	Result *MessageHandlerClient::read_delete_ng(Connection &con) throw (IllegalCommandException, ConnectionClosedException){
		char ans = con.read();
		if (ans == Protocol::ANS_NAK)
			ans = con.read();
		char end_command = con.read();
		if (end_command != Protocol::COM_END)
			throw IllegalCommandException();
		return new DeleteNGResult(ans);
	}

	Result *MessageHandlerClient::read_list_art(Connection &con) throw (IllegalCommandException, ConnectionClosedException){
		if (con.read() == Protocol::ANS_ACK){
			int size = this->read_num(con);
			vector<pair<int, string> > results;		
			while (size > 0){
				results.push_back(make_pair(this->read_num(con), this->read_string(con)));
				--size;
			}
			char end_command = con.read();
			if (end_command != Protocol::COM_END)
				throw IllegalCommandException();
			return new ListArtResult(results);
		}
		char err_message = con.read();
		char end_command = con.read();
		if (end_command != Protocol::COM_END)
			throw IllegalCommandException();
		return new ListArtResult(err_message);
	}

	Result *MessageHandlerClient::read_create_art(Connection &con) throw (IllegalCommandException, ConnectionClosedException){
		char ans = con.read();
		if (ans == Protocol::ANS_NAK)
			ans = con.read();
		char end_command = con.read();
		if (end_command != Protocol::COM_END)
			throw IllegalCommandException();
		return new CreateArtResult(ans);
	}

	Result *MessageHandlerClient::read_delete_art(Connection &con) throw (IllegalCommandException, ConnectionClosedException){
		char ans = con.read();
		if (ans == Protocol::ANS_NAK)
			ans = con.read();
		char end_command = con.read();
		if (end_command != Protocol::COM_END)
			throw IllegalCommandException();
		return new DeleteArtResult(ans);
	}

	Result* MessageHandlerClient::read_get_art(Connection &con) throw (IllegalCommandException, ConnectionClosedException){
		if (con.read() == Protocol::ANS_ACK){
			string title = this->read_string(con);
			string author = this->read_string(con);
			string text = this->read_string(con);
			char end_command = con.read();
			if (end_command != Protocol::COM_END)
				throw IllegalCommandException();
			return new GetArtResult(title, author, text);
		}
		char err_message = con.read();
		char end_command = con.read();
		if (end_command != Protocol::COM_END)
			throw IllegalCommandException();
		return new GetArtResult(err_message);
	}

	string MessageHandlerClient::read_string(Connection &con) throw (IllegalCommandException, ConnectionClosedException){
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

	int MessageHandlerClient::read_num(Connection &con) throw (IllegalCommandException, ConnectionClosedException){
		if(con.read() != Protocol::PAR_NUM)
			throw IllegalCommandException();
		unsigned int num = read_int(con);
		return num;
	}

	int MessageHandlerClient::read_int(Connection &con) throw (ConnectionClosedException){
		unsigned int res;
		for(unsigned char i = 0; i < 4; ++i){
			unsigned char tmp = con.read();
			res <<= 8;
			res += tmp;
		}
		return res;
	}

}

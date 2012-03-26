#include "net/messagehandler.h"

#include "net/protocol.h"
#include "net/connection.h"

using namespace std;
using namespace net;

namespace net {
	MessageHandler::MessageHandler(Connection &conn) : con(conn) {}


	unsigned char MessageHandler::read_byte() throw (ConnectionClosedException){
		return con.read();
	}

	string MessageHandler::read_string() throw (IllegalCommandException, ConnectionClosedException){
		if (con.read() != Protocol::PAR_STRING)
			throw IllegalCommandException();
		int size = read_int();
		string str;
		while(size > 0){
			str += con.read();
			--size;
		}
		return str;
	}

	int MessageHandler::read_num() throw (IllegalCommandException, ConnectionClosedException){
		if(con.read() != Protocol::PAR_NUM)
			throw IllegalCommandException();
		unsigned int num = read_int();
		return num;
	}

	int MessageHandler::read_int() throw (ConnectionClosedException){
		unsigned int res;
		for(unsigned char i = 0; i < 4; ++i){
			unsigned char tmp = con.read();
			res <<= 8;
			res += tmp;
		}
		return res;
	}

	void MessageHandler::print_byte(const unsigned char &b) throw(ConnectionClosedException){
		con.write(b);
	}

	void MessageHandler::print_num(const int &num) throw(ConnectionClosedException){
		con.write(Protocol::PAR_NUM);
		print_int(num);
	}

	void MessageHandler::print_int(const int &num) throw(ConnectionClosedException){
		con.write((num >> 24) & 0xFF);
		con.write((num >> 16) & 0xFF);
		con.write((num >> 8) & 0xFF);
		con.write(num & 0xFF);
	}

	void MessageHandler::print_string(const string &str) throw(ConnectionClosedException){
		con.write(Protocol::PAR_STRING);
		print_int(str.size());
		for (size_t i = 0; i < str.size(); ++i) {
			con.write(str[i]);
		}
	}
}

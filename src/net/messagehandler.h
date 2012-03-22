#ifndef MESSAGEHANDLER_H
#define MESSAGEHANDLER_H

#include <string>
#include "net/connection.h"

namespace net {
    struct IllegalCommandException {};

	class MessageHandler {
	public:
		MessageHandler(net::Connection &conn);
		unsigned char read_byte() throw (ConnectionClosedException);
		std::string read_string() throw (IllegalCommandException, ConnectionClosedException);
		int read_num() throw (IllegalCommandException, ConnectionClosedException);
		int read_int() throw (ConnectionClosedException);
		void print_byte(const unsigned char &b) throw (ConnectionClosedException);
		void print_string(const std::string &s) throw (ConnectionClosedException);
		void print_num(const int &num) throw (ConnectionClosedException);
		void print_int(const int &i) throw (ConnectionClosedException);
    private:
		net::Connection &con;
	};
}

#endif

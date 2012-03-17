#ifndef RESULT_H
#define RESULT_H
#include "net/connection.h"
#include "net/connectionclosedexception.h"
#include <string>

namespace db {
	class Result {
	public:
		virtual void printToConnection(net::Connection &conn) = 0;
		void print_int(net::Connection &con, const int &num) throw(net::ConnectionClosedException);
		void print_string(net::Connection &con, const std::string &str) throw(net::ConnectionClosedException);
	};
}

#endif

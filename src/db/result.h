#ifndef RESULT_H
#define RESULT_H
#include <string>
#include "net/connection.h"
#include "net/connectionclosedexception.h"

namespace db {
	class Result {
	public:
		virtual ~Result() {}
		virtual void printToConnection(net::Connection &conn) throw(net::ConnectionClosedException) = 0;
		void print_num(net::Connection &con, const int &num) throw(net::ConnectionClosedException);
		void print_string(net::Connection &con, const std::string &str) throw(net::ConnectionClosedException);
	private:
		void print_int(net::Connection &con, const int &num) throw(net::ConnectionClosedException);
	};
}

#endif

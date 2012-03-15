#ifndef RESULT_H
#define RESULT_H
#include "connection.h"
#include "connectionclosedexception.h"
#include <string>

namespace db {
	class Result{
	public:
		Result();
		virtual void printToConnection(net::Connection& conn) throw(ConnectionClodesException)= 0;
		void print_int(net::Connection& con, const int& num) throw(net::ConnectionClosedException);
		void print_string(net::Connection& con, const std::string& str) throw(net::ConnectionClosedException);
	};
}

#endif

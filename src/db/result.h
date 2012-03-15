#ifndef RESULT_H
#define RESULT_H
#include "connection.h"
#include "connectionclosedexception.h"

namespace db {
	class Result{
	public:
		Result();
		virtual void printToConnection(net::Connection& conn) throw(ConnectionClodesException)= 0;
	};
}

#endif

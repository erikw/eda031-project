#ifndef RESULT_H
#define RESULT_H
#include "connection.h"

namespace db {
	class Result{
	public:
		Result();
		virtual void printToConnection(net::Connection& conn);
	};
}

#endif

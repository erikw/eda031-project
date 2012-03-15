#ifndef DELETENGRESULT_H
#define DELETENGRESULT_H

#include "connectionclosedexception.h"
#include "result.h"
#include "connection.h"

namespace db {
	class DeleteNGResult : public Result{
	public:
		DeleteNGResult(unsigned char mess) : message(mess) {};
		void printToConnection(net::Connection& conn) throw(ConnectionClosedException);
	private:
		unsigned char message;
		
	};
}

#endif

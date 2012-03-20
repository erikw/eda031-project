#ifndef CREATENGRESULT_H
#define CREATENGRESULT_H

#include "db/result.h"
#include "net/connectionclosedexception.h"
#include "net/connection.h"

namespace db {
	class CreateNGResult : public Result {
	public:
		CreateNGResult(unsigned char mess) : message(mess) {}
		void printToConnection(net::Connection &conn) throw(net::ConnectionClosedException);
		void printToCout();
	private:
		unsigned char message;
	};
}

#endif

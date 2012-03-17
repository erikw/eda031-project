#ifndef DELETENGRESULT_H
#define DELETENGRESULT_H

#include "db/result.h"
#include "net/connectionclosedexception.h"
#include "net/connection.h"

namespace db {
	class DeleteNGResult : public Result {
	public:
		DeleteNGResult(unsigned char mess) : message(mess) {};
		void printToConnection(net::Connection &conn) throw(net::ConnectionClosedException);
	private:
		unsigned char message;
		
	};
}

#endif

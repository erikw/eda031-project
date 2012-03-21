#ifndef CREATEARTRESULT_H
#define CREATEARTRESULT_H

#include "db/result.h"
#include "net/connectionclosedexception.h"
#include "net/connection.h"

namespace db {
	class CreateArtResult : public Result {
	public:
		CreateArtResult(unsigned char mess) : message(mess) {};
		void printToConnection(net::Connection &conn) throw(net::ConnectionClosedException);
		void printToCout();
	private:
		unsigned char message;
	};
}

#endif

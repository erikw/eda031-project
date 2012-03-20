#ifndef CREATEARTRESULT_H
#define CREATEARTRESULT_H

#include "db/result.h"
#include "net/connectionclosedexception.h"
#include "net/connection.h"

namespace db {
	class CreateArtResult : public Result {
	public:
		CreateArtResult(int mess) : message(mess) {};
		void printToConnection(net::Connection &conn) throw(net::ConnectionClosedException);
		void printToCout();
	private:
		int message;
	};
}

#endif

#ifndef CREATEARTRESULT_H
#define CREATEARTRESULT_H

#include "connectionclosedexception.h"
#include "result.h"
#include "connection.h"

namespace db {
	class CreateArtResult : public Result {
		public:
			CreateArtResult(int mess) : message(mess) {};
			void printToConnection(net::Connection& conn) throw(ConnectionClosedException);
		private:
			int message;
	};
}

#endif

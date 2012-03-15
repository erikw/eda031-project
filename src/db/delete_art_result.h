#ifndef DELETEARTRESULT_H
#define DELETEARTRESULT_H

#include "connectionclosedexception.h"
#include "result.h"
#include "connection.h"

namespace db {
	class DeleteArtResult : public Result{
		public:
			DeleteArtResult(int mess) : message(mess) {};
			void printToConnection(net::Connection& conn) throw(ConnectionClosedException);
		private:
			int message;
	};
}

#endif

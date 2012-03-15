#ifndef CREATENGRESULT_H
#define CREATENGRESULT_H

#include "connectionclosedexception.h"
#include "result.h"
#include "connection.h"

namespace db {
	class CreateNGResult : public Result {
		public:
			CreateNGResult(unsigned char mess) : message(mess) {};
			void printToConnection(net::Connection& conn) throw(ConnectionClosedException);
		private:
			unsigned char message;
	};
}

#endif

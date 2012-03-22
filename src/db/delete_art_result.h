#ifndef DELETEARTRESULT_H
#define DELETEARTRESULT_H

#include "net/messagehandler.h"
#include "net/connectionclosedexception.h"
#include "db/result.h"

namespace db {
	class DeleteArtResult : public Result {
	public:
		DeleteArtResult(int mess) : message(mess) {};
		void printToConnection(net::MessageHandler &mh) throw(net::ConnectionClosedException);
		void printToCout();
	private:
		int message;
	};
}

#endif

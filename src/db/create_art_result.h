#ifndef CREATEARTRESULT_H
#define CREATEARTRESULT_H

#include "db/result.h"
#include "net/connectionclosedexception.h"
#include "net/messagehandler.h"

namespace db {
	class CreateArtResult : public Result {
	public:
		CreateArtResult(unsigned char mess) : message(mess) {};
		void printToConnection(net::MessageHandler &mh) throw(net::ConnectionClosedException);
		void printToCout();
	private:
		unsigned char message;
	};
}

#endif

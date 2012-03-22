#ifndef RESULT_H
#define RESULT_H
#include <string>
#include "net/messagehandler.h"
#include "net/connectionclosedexception.h"

namespace db {
	class Result {
	public:
		virtual ~Result() {}
		virtual void printToConnection(net::MessageHandler &mh) throw(net::ConnectionClosedException) = 0;
		virtual void printToCout() = 0;
	};
}

#endif

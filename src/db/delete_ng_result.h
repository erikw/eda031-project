#ifndef DELETENGRESULT_H
#define DELETENGRESULT_H

#include "db/result.h"
#include "net/connectionclosedexception.h"
#include "net/messagehandler.h"

namespace db {
	class DeleteNGResult : public Result {
	public:
		DeleteNGResult(unsigned char mess) : message(mess) {};
		void printToConnection(net::MessageHandler &mh) throw(net::ConnectionClosedException);
		void printToCout();
	private:
		unsigned char message;

	};
}

#endif

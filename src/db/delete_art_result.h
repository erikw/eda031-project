#ifndef DELETEARTRESULT_H
#define DELETEARTRESULT_H

#include <iostream>

#include "net/messagehandler.h"
#include "net/connectionclosedexception.h"
#include "db/result.h"

namespace db {
	class DeleteArtResult : public Result {
	public:
		explicit DeleteArtResult(int mess) : message(mess) {};
		void printToConnection(net::MessageHandler &mh) throw(net::ConnectionClosedException);
	private:
		void toString(std::ostream &out) const;

		int message;
	};
}

#endif

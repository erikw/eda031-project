#ifndef CREATEARTRESULT_H
#define CREATEARTRESULT_H

#include <iostream>

#include "db/result.h"
#include "net/connectionclosedexception.h"
#include "net/messagehandler.h"

namespace db {
	class CreateArtResult : public Result {
	public:
		CreateArtResult(unsigned char mess) : message(mess) {};
		void printToConnection(net::MessageHandler &mh) throw(net::ConnectionClosedException);
	private:
		void toString(std::ostream &out) const;
		unsigned char message;
	};
}

#endif

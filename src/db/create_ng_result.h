#ifndef CREATENGRESULT_H
#define CREATENGRESULT_H

#include <iostream>

#include "db/result.h"
#include "net/connectionclosedexception.h"
#include "net/messagehandler.h"

namespace db {
	class CreateNGResult : public Result {
	public:
		CreateNGResult(unsigned char mess) : message(mess) {}
		void printToConnection(net::MessageHandler &mh) throw(net::ConnectionClosedException);
	private:
		void toString(std::ostream &out) const;

		unsigned char message;
	};
}

#endif

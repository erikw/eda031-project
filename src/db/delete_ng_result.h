#ifndef DELETENGRESULT_H
#define DELETENGRESULT_H

#include <iostream>

#include "db/result.h"
#include "net/connectionclosedexception.h"
#include "net/messagehandler.h"

namespace db {
	class DeleteNGResult : public Result {
	public:
		explicit DeleteNGResult(unsigned char mess) : message(mess) {};
		void printToConnection(net::MessageHandler &mh) throw(net::ConnectionClosedException);
	private:
		void toString(std::ostream &out) const;

		unsigned char message;

	};
}

#endif

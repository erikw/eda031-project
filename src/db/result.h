#ifndef RESULT_H
#define RESULT_H

#include <string>
#include <iostream>

#include "net/messagehandler.h"
#include "net/connectionclosedexception.h"

namespace db {
	class Result {
		friend std::ostream &operator<<(std::ostream &out, const Result &res);
	public:
		virtual ~Result() {}
		virtual void printToConnection(net::MessageHandler &mh) throw(net::ConnectionClosedException) = 0;
		// Print the result in a readable format.
		virtual void toString(std::ostream &out) const = 0;
	};
}

#endif

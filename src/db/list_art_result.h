#ifndef LISTARTRESULT_H
#define LISTARTRESULT_H

#include <string>
#include <vector>
#include <iostream>

#include "db/result.h"
#include "net/messagehandler.h"
#include "net/protocol.h"
#include "net/connectionclosedexception.h"

namespace db {
	class ListArtResult : public Result {
	public:
		ListArtResult(unsigned char err_message) : message(err_message) {};
		ListArtResult(std::vector<std::pair<int, std::string> > art) : message(net::Protocol::ANS_ACK), articles(art) {};
		void printToConnection(net::MessageHandler &mh) throw(net::ConnectionClosedException);
	private:
		void toString(std::ostream &out) const;

		unsigned char message;
		std::vector<std::pair<int, std::string> > articles;
	};
}

#endif

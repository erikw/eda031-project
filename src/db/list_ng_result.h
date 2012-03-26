#ifndef LISTNGRESULT_H
#define LISTNGRESULT_H

#include <string>
#include <vector>
#include <iostream>

#include "db/result.h"
#include "net/connectionclosedexception.h"
#include "net/messagehandler.h"

namespace db {
	class ListNGResult : public Result {
	public:
		explicit ListNGResult(std::vector<std::pair<size_t, std::string> > ng) : news_groups(ng) {}
		void printToConnection(net::MessageHandler &mh) throw(net::ConnectionClosedException);
	private:
		void toString(std::ostream &out) const;

		std::vector<std::pair<size_t, std::string> > news_groups;
	};
}

#endif

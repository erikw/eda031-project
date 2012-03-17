#ifndef LISTNGRESULT_H
#define LISTNGRESULT_H

#include <string>
#include <vector>

#include "db/result.h"
#include "net/connectionclosedexception.h"
#include "net/connection.h"

namespace db {
	class ListNGResult : public Result {
	public:
		ListNGResult(unsigned char err_message) : message(err_message) {}
		ListNGResult(std::vector<std::pair<int, std::string> > ng) : news_groups(ng) {}
		void printToConnection(net::Connection &conn) throw(net::ConnectionClosedException);
	private:
		unsigned char message;
		std::vector<std::pair<int, std::string> > news_groups;
	};
}

#endif

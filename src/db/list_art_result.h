#ifndef LISTARTRESULT_H
#define LISTARTRESULT_H

#include "result.h"
#include "connection.h"
#include <string>
#include <vector>

namespace db {
	class ListArtResult : public Result{
	public:
		ListArtResult(int err_message) : message(err_message) {};
		ListArtResult(std::vector<std::pair<int, std::string> > art) : articles(art) {};
		void printToConnection(net::Connection& conn);
	private:
		int message;
		std::vector<std::pair<int, std::string> > articles;
	};
}

#endif

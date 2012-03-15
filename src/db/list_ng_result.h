#ifndef LISTNGRESULT_H
#define LISTNGRESULT_H

#include "result.h"
#include "connection.h"
#include <string>
#include <vector>

namespace db {
	class ListNGResult : public Result{
	public:
		ListNGResult(int err_message) : message(err_message) {};
		ListNGResult(std::vector<std::pair<int, std::string> > ng) : news_groups(ng) {};
		void printToConnection(net::Connection& conn);
	private:
		int message;
		std::vector<std::pair<int, std::string> > news_groups;
	};
}

#endif

#ifndef GETARTRESULT_H
#define GETARTRESULT_H

#include "result.h"
#include <string>
#include "connection.h"

namespace db {
	class GetArtResult : public Result{
	public:
		GetArtResult(int err_message) : message(err_message) {};
		GetArtResult(std::string ti, std::string au, std::string te) : 
				title(te), author(au), text(te) {};
		void printToConnection(net::Connection& conn);
	private:
		int message;
		std::string title;
		std::string author;
		std::string text;
	};
}

#endif

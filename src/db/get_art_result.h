#ifndef GETARTRESULT_H
#define GETARTRESULT_H

#include "result.h"
#include <string>
#include "connection.h"
#include "connectionclosedexception.h"
#include "protocol.h"

namespace db {
	class GetArtResult : public Result{
	public:
		GetArtResult(unsigned char err_msg) : message(err_msg) {};
		GetArtResult(std::string ti, std::string au, std::string te) : 
				title(te), author(au), text(te) , message(net::Protocol::ANS_ACK){};
		void printToConnection(net::Connection& conn);
	private:
		unsigned char message;
		std::string title;
		std::string author;
		std::string text;
	};
}

#endif

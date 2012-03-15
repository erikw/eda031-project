#ifndef CREATEARTRESULT_H
#define CREATEARTRESULT_H

#include "result.h"
#include "connection.h"

namespace db {
	class CreateArtResult : public Result {
		public:
			CreateArtResult(int mess) : message(mess) {};
			void printToConnection(net::Connection& conn);
		private:
			int message;
	};
}

#endif

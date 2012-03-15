#ifndef CREATENGRESULT_H
#define CREATENGRESULT_H

#include "result.h"
#include "connection.h"

namespace db {
	class CreateNGResult : public Result {
		public:
			CreateNGResult(int mess) : message(mess) {};
			void printToConnection(net::Connection& conn);
		private:
			int message;
	};
}

#endif

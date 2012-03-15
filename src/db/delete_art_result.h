#ifndef DELETEARTRESULT_H
#define DELETEARTRESULT_H

#include "result.h"
#include "connection.h"

namespace db {
	class DeleteArtResult : public Result{
		public:
			DeleteArtResult(int mess) : message(mess) {};
			void printToConnection(net::Connection& conn);
		private:
			int message;
	};
}

#endif
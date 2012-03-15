#ifndef DELETEARTRESULT_H
#define DELETEARTRESULT_H

#include "result.h"

namespace db {
	class DeleteArtResult : public Result{
		public:
			DeleteArtResult(int mess) : message(mess) {};
			printToConnection(Connection& conn);
		private:
			int message;
	};
}

#endif

#ifndef CREATEARTRESULT_H
#define CREATEARTRESULT_H

#include "result.h"

namespace db {
	class CreateArtResult : public Result {
		public:
			CreateArtResult(int mess) : message(mess) {};
			printToConnection(Connection& conn);
		private:
			int message;
	};
}

#endif

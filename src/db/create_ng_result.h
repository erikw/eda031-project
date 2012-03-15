#ifndef CREATENGRESULT_H
#define CREATENGRESULT_H

#include "result.h"

namespace db {
	class CreateNGResult : public Result {
		public:
			CreateNGResult(int mess) : message(mess) {};
			printToConnection(Connection& conn);
		private:
			int message;
	};
}

#endif

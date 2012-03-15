#ifndef DELETENGRESULT_H
#define DELETENGRESULT_H

#include "result.h"

namespace db {
	class DeleteNGResult : public Result{
	public:
		DeleteNGResult(int mess) : message(mess) {};
		printToConnection(Connection& conn);
	private:
		int message;
		
	};
}

#endif

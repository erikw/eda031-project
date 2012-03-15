#ifndef DELETENGRESULT_H
#define DELETENGRESULT_H

#include "result.h"
#include "connection.h"

namespace db {
	class DeleteNGResult : public Result{
	public:
		DeleteNGResult(int mess) : message(mess) {};
		void printToConnection(net::Connection& conn);
	private:
		int message;
		
	};
}

#endif

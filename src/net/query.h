#ifndef QUERY_H
#define QUERRY_H

#include "result.h"
#include "databaseabs.h"

namespace net {
	class Query {
	public:
		Query(DatabaseAbs& db);
		Result execute();
	private:
		DatabaseAbs db;
	}
}

#endif

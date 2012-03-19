#ifndef QUERY_H
#define QUERY_H

#include "db/result.h"
#include "db/database.h"

namespace db {
	class Query {
	public:
		Query(Database& db) : database(db) {}
		virtual Result *execute() = 0;
	protected:
		Database &database;
	};
}

#endif

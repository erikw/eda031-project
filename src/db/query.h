#ifndef QUERY_H
#define QUERY_H

#include "db/result.h"
#include "db/database.h"

namespace db {
	class Query {
	public:
		Query(Database& database) : db(database) {}
		virtual Result *execute() = 0;
	private:
		Database &db;
	};
}

#endif

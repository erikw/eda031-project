
#ifndef QUERY_H
#define QUERRY_H

#include "result.h"
#include "databaseabs.h"

namespace server {
	class Query {
		public:
			Query(Database& database) : db(database) {}
			virtual Result* execute() = 0;
		private:
			Database db;
	}
}


#endif

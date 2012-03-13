
#ifndef LISTNGQUERY_H
#define LISTNGQUERY_H

#include "query.h"

namespace server {
	class ListNGQuery : public Query {
		public:
			ListNGQuery(Database& db) {Query(db)}
			Result* execute();
	}

}


#endif

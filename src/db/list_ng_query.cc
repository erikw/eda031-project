#include "db/list_ng_query.h"

namespace db {
	Result *ListNGQuery::execute() { 
		return database.list_ng();
	}
}

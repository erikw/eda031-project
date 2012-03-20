#include <string>

#include "db/create_ng_query.h"

namespace db {
	Result *CreateNGQuery::execute() {
		return database.create_ng(newsgroup_name);
	}
}

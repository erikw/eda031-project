#include "db/delete_ng_query.h"
#include "db/result.h"

namespace db {
	Result *DeleteNGQuery::execute() {
		return database.delete_ng(newsgroup_id);
	}
}

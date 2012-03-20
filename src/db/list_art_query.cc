#include "db/list_art_query.h"
#include "db/result.h"

namespace db {
	Result *ListArtQuery::execute() {
		return database.list_art(newsgroup_id);
	}
}

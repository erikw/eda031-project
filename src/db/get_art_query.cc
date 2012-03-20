#include "db/get_art_query.h"
#include "db/result.h"

namespace db {
	Result *GetArtQuery::execute() {
		return database.get_art(newsgroup_id, article_id);
	}
}

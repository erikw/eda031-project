#include "db/delete_art_query.h"
#include "db/result.h"

namespace db {
	Result *DeleteArtQuery::execute() {
		return database.delete_art(newsgroup_id, article_id);
	}
}

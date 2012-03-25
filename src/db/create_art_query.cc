#include "db/create_art_query.h"
#include "db/result.h"

namespace db {
	Result *CreateArtQuery::execute() {
		return database.create_art(newsgroup_id, art_title, art_author, art_text);
	}
}

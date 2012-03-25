#include "db/list_art_query.h"
#include "db/result.h"
#include "net/protocol.h"

namespace db {
    using namespace net;

	Result *ListArtQuery::execute() {
		return database.list_art(newsgroup_id);
	}
}

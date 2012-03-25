#include "db/list_art_query.h"
#include "db/result.h"
#include "net/protocol.h"

namespace db {
    using namespace net;

	Result *ListArtQuery::getResult(Database &database) {
		return database.list_art(newsgroup_id);
	}

	void ListArtQuery::send(MessageHandler &mh){
		mh.print_byte(Protocol::COM_LIST_ART);
		mh.print_int(newsgroup_id);
		mh.print_byte(Protocol::COM_END);
    }
}

#include "db/delete_art_query.h"

#include "db/result.h"
#include "net/protocol.h"

namespace db {
    using namespace net;

	Result *DeleteArtQuery::getResult(Database &database) {
		return database.delete_art(newsgroup_id, article_id);
	}


	void DeleteArtQuery::send(MessageHandler &mh) {
		mh.print_byte(Protocol::COM_DELETE_ART);
		mh.print_num(newsgroup_id);
		mh.print_num(article_id);
		mh.print_byte(Protocol::COM_END);
    }
}

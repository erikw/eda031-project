#include "db/get_art_query.h"
#include "db/result.h"
#include "net/protocol.h"

namespace db {
    using namespace net;

	Result *GetArtQuery::getResult(Database &database) {
		return database.get_art(newsgroup_id, article_id);
	}

	void GetArtQuery::send(MessageHandler &mh){
		mh.print_byte(Protocol::COM_GET_ART);
		mh.print_int(newsgroup_id);
		mh.print_int(article_id);
		mh.print_byte(Protocol::COM_END);
    }
}

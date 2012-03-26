#include "db/create_art_query.h"

#include "db/result.h"
#include "net/protocol.h"

namespace db {
    using namespace net;

	Result *CreateArtQuery::getResult(Database &database) {
		return database.create_art(newsgroup_id, art_title, art_author, art_text);
	}

	void CreateArtQuery::send(MessageHandler &mh) {
		mh.print_byte(Protocol::COM_CREATE_ART);
		mh.print_num(newsgroup_id);
		mh.print_string(art_title);
		mh.print_string(art_author);
		mh.print_string(art_text);
		mh.print_byte(Protocol::COM_END);
    }
}

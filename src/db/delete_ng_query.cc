#include "db/delete_ng_query.h"
#include "db/result.h"
#include "net/protocol.h"

namespace db {
    using namespace net;

	Result *DeleteNGQuery::getResult(Database &database) {
		return database.delete_ng(newsgroup_id);
	}

	void DeleteNGQuery::send(MessageHandler &mh){
		mh.print_byte(Protocol::COM_DELETE_NG);
		mh.print_int(newsgroup_id);
		mh.print_byte(Protocol::COM_END);
    }
}

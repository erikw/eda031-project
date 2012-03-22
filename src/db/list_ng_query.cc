#include "db/list_ng_query.h"
#include "net/protocol.h"

namespace db {
    using namespace net;

	Result *ListNGQuery::getResult(Database &database) {
		return database.list_ng();
	}

	void ListNGQuery::send(MessageHandler &mh){
		mh.print_byte(Protocol::COM_LIST_NG);
		mh.print_byte(Protocol::COM_END);
    }
}

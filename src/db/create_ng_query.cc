#include <string>

#include "db/create_ng_query.h"
#include "net/protocol.h"

namespace db {
    using namespace net;

	Result *CreateNGQuery::getResult(Database &database) {
		return database.create_ng(newsgroup_name);
	}

	void CreateNGQuery::send(MessageHandler &mh){
        mh.print_byte(Protocol::COM_CREATE_NG);
        mh.print_string(newsgroup_name);
        mh.print_byte(Protocol::COM_END);
    }
}

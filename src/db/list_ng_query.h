#ifndef LISTNGQUERY_H
#define LISTNGQUERY_H

#include "db/query.h"
#include "net/messagehandler.h"

namespace db {
	class ListNGQuery : public Query {
	public:
		ListNGQuery() {}
		Result *getResult(Database &db);
		void send(net::MessageHandler &mh);
	};
}

#endif

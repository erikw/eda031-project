#ifndef QUERY_H
#define QUERY_H

#include "db/result.h"
#include "db/database.h"
#include "net/messagehandler.h"

namespace db {
	class Query {
	public:
		Query() {}
		virtual ~Query() {}
		virtual Result *getResult(Database &db) = 0;
		virtual void send(net::MessageHandler &mh) = 0;
	};
}

#endif

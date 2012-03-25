#ifndef DELETENGQUERY_H
#define DELETENGQUERY_H

#include "db/query.h"
#include "db/result.h"
#include "net/messagehandler.h"

namespace db {
	class DeleteNGQuery : public Query {
	public:
		DeleteNGQuery(int ng_id) : newsgroup_id(ng_id) {}
		Result *getResult(Database &db);
		void send(net::MessageHandler &mh);
	private:
		int newsgroup_id;
	};

}

#endif

#ifndef LISTARTQUERY_H
#define LISTARTQUERY_H

#include "db/query.h"
#include "net/messagehandler.h"

namespace db {
	class ListArtQuery : public Query {
	public:
		ListArtQuery(int ng_id) : newsgroup_id(ng_id) {}
        Result *getResult(Database &db);
		void send(net::MessageHandler& mh);
	private:
		int newsgroup_id;
	};
}

#endif

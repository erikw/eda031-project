#ifndef GETARTQUERY_H
#define GETARTQUERY_H

#include "db/query.h"
#include "db/result.h"
#include "net/messagehandler.h"

namespace db {
	class GetArtQuery : public Query {
	public:
		GetArtQuery(size_t ng_id, size_t art_id) : newsgroup_id(ng_id), article_id(art_id) {}
		Result *getResult(Database &db);
		void send(net::MessageHandler &mh);
	private:
		size_t newsgroup_id;
		size_t article_id;
	};
}

#endif

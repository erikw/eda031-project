#ifndef DELETEARTQUERY_H
#define DELETEARTQUERY_H

#include "db/query.h"
#include "db/result.h"
#include "net/messagehandler.h"

namespace db {
	class DeleteArtQuery : public Query {
	public:
		DeleteArtQuery(int ng_id, int art_id) : newsgroup_id(ng_id), article_id(art_id) {}
		Result *getResult(Database &db);
		void send(net::MessageHandler& mh);
	private:
		int newsgroup_id;
		int article_id;
	};
}

#endif

#ifndef DELETEARTQUERY_H
#define DELETEARTQUERY_H

#include "db/query.h"
#include "db/result.h"

namespace db {
	class DeleteArtQuery : public Query {
	public:
		DeleteArtQuery(Database& db, int ng_id, int art_id) : Query(db), newsgroup_id(ng_id), article_id(art_id) {}
		Result *execute();
	private:
		int newsgroup_id;
		int article_id;
	};
}

#endif

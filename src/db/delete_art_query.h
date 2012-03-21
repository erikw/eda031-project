#ifndef DELETEARTQUERY_H
#define DELETEARTQUERY_H

#include "db/query.h"
#include "db/result.h"

namespace db {
	class DeleteArtQuery : public Query {
	public:
		DeleteArtQuery(Database& db, size_t ng_id, size_t art_id) : Query(db), newsgroup_id(ng_id), article_id(art_id) {}
		Result *execute();
	private:
		size_t newsgroup_id;
		size_t article_id;
	};
}

#endif

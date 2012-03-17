#ifndef GETARTQUERY_H
#define GETARTQUERY_H

#include "db/query.h"
#include "db/result.h"

namespace db {
	class GetArtQuery : public Query {
	public:
		GetArtQuery(Database& db, int ng_id, int art_id) : Query(db), newsgroup_id(ng_id), article_id(art_id) {}
		Result *execute();
	private:
		int newsgroup_id;
		int article_id;
	};

}

#endif

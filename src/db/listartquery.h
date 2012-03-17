#ifndef LISTARTQUERY_H
#define LISTARTQUERY_H

#include "query.h"

namespace db {
	class ListArtQuery : public Query {
	public:
		ListArtQuery(Database &db, int ng_id) : Query(db), newsgroup_id(ng_id) {}
		Result *execute();
	private:
		int newsgroup_id;
	};
}

#endif

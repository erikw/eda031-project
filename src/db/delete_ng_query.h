#ifndef DELETENGQUERY_H
#define DELETENGQUERY_H

#include "db/query.h"
#include "db/result.h"

namespace db {
	class DeleteNGQuery : public Query {
	public:
		DeleteNGQuery(Database &db, int ng_id) : Query(db), newsgroup_id(ng_id) {}
		Result *execute();
	private:
		int newsgroup_id;
	};

}

#endif

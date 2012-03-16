#ifndef CREATENGQUERY_H
#define CREATENGQUERY_H

#include <string>

namespace db {
	class CreateNGQuery : public Query {
		public:
			CreateNGQuery(Database &database, std::string ng_name) : Query(database), newsgroup_name(ng_name) {}
			Result *execute();
		private:
			std::string newsgroup_name;
	};
}

#endif

#ifndef CREATEARTQUERY_H
#define CREATEARTQUERY_H

#include "query.h"

namespace db {
	class CreateArtQuery : public Query {
		public:
			CreateArtQuery(Database &db, int ng_id, std::string title, std::string author, std::string text) :
			Query(db), newsgroup_id(ng_id), art_title(title), art_author(author), art_text(text) {}
			Result *execute();
		private:
			int newsgroup_id;
			std::string art_title;
			std::string art_author;
			std::string art_text;
	};
}

#endif

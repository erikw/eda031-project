#ifndef CREATEARTQUERY_H
#define CREATEARTQUERY_H

#include "db/query.h"
#include "net/messagehandler.h"
namespace db {
	class CreateArtQuery : public Query {
	public:
		CreateArtQuery(size_t ng_id, std::string title, std::string author, std::string text) :
		newsgroup_id(ng_id), art_title(title), art_author(author), art_text(text) {}
		Result *getResult(Database &db);
		void send(net::MessageHandler &mh);
	private:
		size_t newsgroup_id;
		std::string art_title;
		std::string art_author;
		std::string art_text;
	};
}

#endif

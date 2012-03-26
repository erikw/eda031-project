#ifndef CREATENGQUERY_H
#define CREATENGQUERY_H

#include <string>

#include "db/query.h"
#include "db/result.h"
#include "net/messagehandler.h"

namespace db {
	class CreateNGQuery : public Query {
	public:
		explicit CreateNGQuery(std::string ng_name) : newsgroup_name(ng_name) {}
		Result *getResult(Database &db);
		void send(net::MessageHandler &mh);
	private:
		std::string newsgroup_name;
	};
}

#endif

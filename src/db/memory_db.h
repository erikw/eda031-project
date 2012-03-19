#ifndef PRIMDB_H
#define PRIMDB_H

#include <string>
#include <map>
#include "db/result.h"
#include "db/database.h"


namespace db {
	class MemoryDB : public Database {
	public:
		MemoryDB() : ng_count(0) {}
		Result *list_ng();
		Result *create_ng(std::string ng_name);
		Result *delete_ng(int ng_id);
		Result *list_art(int ng_id);
		Result *create_art(int ng_id, std::string title, std::string author, std::string text);
		Result *delete_art(int ng_id, int art_id);
		Result *get_art(int ng_id, int art_id);

	private:
		struct Article {
			std::string title;
			std::string author;
			std::string text;
		};

		struct NewsGroup {
			NewsGroup() : art_count(0) {}

			int art_count;
			std::string name;
			std::map<int, Article> articles;
		};

		int ng_count;
		std::map<int,NewsGroup> news_groups;
	};
}

#endif

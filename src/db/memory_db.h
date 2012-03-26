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
		Result *list_ng() const;
		Result *create_ng(std::string ng_name);
		Result *delete_ng(size_t ng_id);
		Result *list_art(size_t ng_id) const;
		Result *create_art(size_t ng_id, const std::string &title, const std::string &author, const std::string &text);
		Result *delete_art(size_t ng_id, size_t art_id);
		Result *get_art(size_t ng_id, size_t art_id) const;

	private:
		struct Article {
			std::string title;
			std::string author;
			std::string text;
		};

		struct NewsGroup {
			NewsGroup() : art_count(0) {}

			size_t art_count;
			std::string name;
			std::map<size_t, Article> articles;
		};

		size_t ng_count;
		std::map<size_t, NewsGroup> news_groups;
	};
}

#endif

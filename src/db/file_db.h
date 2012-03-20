#ifndef FILEDB_H
#define FILEDB_H

#include <string>
#include <map>

#include "db/result.h"
#include "db/database.h"
#include "db/directory.h"


namespace db {
	class FileDB : public Database {
	public:
		FileDB();
		Result *list_ng();
		Result *create_ng(std::string ng_name);
		Result *delete_ng(int ng_id);
		Result *list_art(int ng_id);
		Result *create_art(int ng_id, std::string title, std::string author, std::string text);
		Result *delete_art(int ng_id, int art_id);
		Result *get_art(int ng_id, int art_id);

	private:
		size_t count_ng();

		static const std::string DB_ROOT;
		Directory dir;
		int ng_count;
	};

}

#endif

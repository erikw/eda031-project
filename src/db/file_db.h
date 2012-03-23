#ifndef FILEDB_H
#define FILEDB_H

#include <string>
#include <algorithm>

#include "db/result.h"
#include "db/database.h"
#include "db/directory.h"

namespace db {
	class FileDB : public Database {
	public:
		FileDB() : root_dir(DB_ROOT) {}

		Result *list_ng();
		Result *create_ng(std::string ng_name);
		Result *delete_ng(size_t ng_id);
		Result *list_art(size_t ng_id);
		Result *create_art(size_t ng_id, std::string title, std::string author, std::string text);
		Result *delete_art(size_t ng_id, size_t art_id);
		Result *get_art(size_t ng_id, size_t art_id);

	private:
		size_t next_id();

		// Split the stored news group name to (pair) components.
		 void split_ng(std::vector<std::pair<size_t, std::string> > &pairs, const std::vector<std::string> &full_names) const;

		//  Check if a news group with the given name exists.
		template<typename U>
		bool exists_ng(const U&);

		//  Check if an article in a specific group exists.
		bool exists_art(const std::string &ng_name, const std::string &art_name);

		// Return the full name "id_name".
		std::string get_ng_name(size_t ng_idconst) const; 

		// The root directory for all files.
		static const std::string DB_ROOT;
		
		// The name file where ng_count is stored. One file like this for each news group too.
		static const std::string DB_INFO_NAME;	

		// Directory entry to the db_root.
		Directory root_dir; 		

		template<typename T>
		//struct compare_ng {};
		struct compare_ng : std::binary_function<std::pair<size_t, std::string>, const T, bool> {};
	};
}

#endif

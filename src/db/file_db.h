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
		// Read the id count for the given path. Is article ID count for all path != DB_ROOT.
		size_t read_id_cnt(const string &path); 

		// Increment the number in the DB_INFO_FILE at the given path.
		void increment_id_cnt(const string &path); 

		std::parir<size_t, std::string> split_ng(std::vector<strig> full_names);


		//  Check if a news group with the given name exists.
		bool exists_ng(const string &ng_name);

		// Return the full name "id_name".
		std::string get_ng_name(size_t ng_idconst std::string &ng_name); 

		bool exists_art(const string &art_name);

		// The root directory for all files.
		static const std::string DB_ROOT;	
		
		// The name file where ng_count is stored. One file like this for each news group too.
		static const std::string DB_INFO_NAME;	
		// Directory entry to the db_root.
		Directory dir_root; 		
	};
}

#endif

#ifndef FILEDB_H
#define FILEDB_H

#include <string>
#include <algorithm>

#include "db/result.h"
#include "db/database.h"
#include "db/directory.h"
#include "db/file_ng.h"
#include "test/test_db.h"

namespace db {
	class FileDB : public Database {
		friend void test::tear_down();
	public:
		FileDB();
		Result *list_ng();
		Result *create_ng(std::string ng_name);
		Result *delete_ng(size_t ng_id);
		Result *list_art(size_t ng_id);
		Result *create_art(size_t ng_id, const std::string &title, const std::string &author, const std::string &text);
		Result *delete_art(size_t ng_id, size_t art_id);
		Result *get_art(size_t ng_id, size_t art_id);

	private:
		// Read and increment ID counter.
		size_t next_id();

		// Read news groups from DB_INFO_NAME.
		void read_ngs(std::vector<std::pair<size_t, std::string> > &news_groups);

		//  Check if a news group with the given name exists.
		// T is news group name or ID.
		template<typename I>
		bool exists_ng(const I&);

		// Exception.
		struct InexistingNG {};

		// Get a news group by name or ID.
		template<typename I>
		FileNG get_ng(const I &identifier) throw(InexistingNG);

		//  Check if an article in a specific group exists.
		bool exists_art(const std::string &ng_name, const std::string &art_name);

		// Return the full name "id_name".
		std::string get_ng_name(size_t ng_idconst) const; 

		template<typename T>
		struct find_ng : std::binary_function<std::pair<size_t, std::string>, const T, bool> {};

		template<typename T, typename U>
		struct compare_pair_first : std::binary_function<std::pair<T, U>, std::pair<T, U>, bool> {
			bool operator()(const std::pair<T, U> &lhs, const std::pair<T, U> &rhs) const {
				if (lhs.first < rhs.first) {
					return true;
				} else if (rhs.first < lhs.first) {
					return false;
				} else { // Equal
					return false;
				}
			}
		};



		// The root directory for all files.
		static const std::string DB_ROOT;
		
		// The name file where ng_count is stored. One file like this for each news group too.
		static const std::string DB_INFO_NAME;	


		// Directory entry to the db_root.
		Directory root_dir; 		
	};
}

#endif

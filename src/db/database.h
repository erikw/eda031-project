#ifndef DATABASEABS_H
#define DATABASEABS_H

#include "db/result.h"
#include <string>
namespace db {

	class Database {
	public:
		virtual ~Database() {};
		virtual Result *list_ng() = 0;
		virtual Result *create_ng(std::string ng_name) = 0;
		virtual Result *delete_ng(size_t ng_id) = 0;
		virtual Result *list_art(size_t ng_id) = 0;
		virtual Result *create_art(size_t ng_id, const std::string &title, const std::string &author,const std::string &text) = 0;
		virtual Result *delete_art(size_t ng_id, size_t art_id) = 0;
		virtual Result *get_art(size_t ng_id, size_t art_id) = 0;
	};
}

#endif	


#ifndef DATABASEABS_H
#define DATABASEABS_H

#include "result.h"
#include <string>
namespace db {

	class Database {
	public:
		virtual ~Database();
		virtual Result *list_ng() = 0;
		virtual Result *create_ng(std::string ng_name) = 0;
		virtual Result *delete_ng(const int &ng_id) = 0;
		virtual Result *list_art(const int &ng_id) = 0;
		virtual Result *create_art(const int &ng_id, std::string title, std::string author, std::string text) = 0;
		virtual Result *delete_art(const int &ng_id, const int &art_id) = 0;
		virtual Result *get_art(const int &ng_id, const int &art_id) = 0;
	};
}
#endif	


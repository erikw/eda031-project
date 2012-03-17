#ifndef DATABASEABS_H
#define DATABASEABS_H

#include "result.h"
#include <string>
namespace db {

	class Database {
	public:
		virtual ~Database() {  };
		virtual Result *list_ng() = 0;
		virtual Result *create_ng(std::string ng_name) = 0;
		virtual Result *delete_ng(int ng_id) = 0;
		virtual Result *list_art(int ng_id) = 0;
		virtual Result *create_art(int ng_id, std::string title, std::string author, std::string text) = 0;
		virtual Result *delete_art(int ng_id, int art_id) = 0;
		virtual Result *get_art(int ng_id, int art_id) = 0;
	};
}

#endif	


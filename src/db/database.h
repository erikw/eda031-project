#ifndef DATABASEABS_H
#define DATABASEABS_H

#include "result.h"
#include <string>
namespace db {

	class Database {
		public:
			virtual Result list_ng(){}
			virtual Result create_ng(std::string ng_name){}
			virtual Result delete_ng(const int& ng_id){}
			virtual Result list_art(const int& ng_id){}
			virtual Result create_art(const int& ng_id, std::string title,
						std::string author, std::string text){}
			virtual Result delete_art(const int& ng_id, const int& art_id){}
			virtual Result get_art(const int& ng_id, const int& art_id){}
	};
}
#endif	


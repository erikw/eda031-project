#ifndef PRIMDB_H
#define PRIMDB_H

#include <string>
#include <map>
#include "result.h"
#include "database.h"


namespace db {
	class MemoryDb : public Database{
		MemoryDb() : ng_count(0){}
		Result* list_ng();
		Result* create_ng(std::string ng_name);
		Result* delete_ng(const int& ng_id);
		Result* list_art(const int& ng_id);
		Result* create_art(const int& ng_id, std::string title,
						std::string author, std::string text);
		Result* delete_art(const int& ng_id, const int& art_id);
		Result* get_art(const int& ng_id, const int& art_id);
	private:
		
		struct Article{
			std::string title;
			std::string author;
			std::string text;
		}; 
		struct NewsGroup{
			NewsGroup() : art_count(0){};			
			int art_count;
			std::string name;
			std::map<int,Article> articles;		
		};

		int ng_count;
		std::map<int,NewsGroup> news_groups;

	};
		
}
#endif

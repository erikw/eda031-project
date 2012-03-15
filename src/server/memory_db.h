#ifndef DATABASEABS_H
#define DATABASEABS_H

#include <string>
#include <map>

namespace server {
	class Primdb : public DatabaseAbs{
		Primdb() : art_id(0), ng_id(0){};
		result list_ng(){}
		result create_ng(const std::string& ng_name){}
		result delete_ng(const int& ng_id){}
		result list_art(const int& ng_id){}
		result create_art(const int& ng_id, const string& title, 
						const string& author, const string& text){}
		result delete_art(const int& ng_id, const int& art_id){}
		result get_art(const int& ng_id, const int& art_id){}
	private:
		int art_id;
		int ng_id;
		struct Article{
			string title;
			string author;
			string text;
		};
		struct NewsGroup{
			string name;
			map<int,Article> articles;		
		};
		map<int,NewsGroup> news_groups;
}

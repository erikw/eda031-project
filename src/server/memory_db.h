#ifndef DATABASEABS_H
#define DATABASEABS_H

#include <string>
#include <map>

namespace server {
	class Primdb : public DatabaseAbs {
	public:
		Primdb() : art_id(0), ng_id(0){};
		Result *list_ng(){}
		Result *create_ng(const std::string& ng_name){ return 0; }
		Result *delete_ng(const int& ng_id){return 0; }
		Result *list_art(const int& ng_id){return 0; }
		Result *create_art(const int& ng_id, const string& title, const string& author, const string& text){return 0; }
		Result *delete_art(const int& ng_id, const int& art_id){return 0; }
		Result *get_art(const int& ng_id, const int& art_id){return 0; }
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

#ifndef DATABASEABS_H
#define DATABASEABS_H

#include "result.h"

namespace server {

class DatabaseAbs {
	public:
		virtual result list_ng(){}
		virtual result create_ng(const std::string& ng_name){}
		virtual result delete_ng(const int& ng_id){}
		virtual result list_art(const int& ng_id){}
		virtual result create_art(const int& ng_id, const string& title, 
						const string& author, const string& text){}
		virtual result delete_art(const int& ng_id, const int& art_id){}
		virtual result get_art(const int& ng_id, const int& art_id){}
	private:
}
		


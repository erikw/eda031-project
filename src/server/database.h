#ifndef DATABASEABS_H
#define DATABASEABS_H

#include "result.h"

namespace server {

class DatabaseAbs {
	public:
		virtual result list_ng() = 0;
		virtual result create_ng(const std::string& ng_name) = 0;
		virtual result delete_ng(const int& ng_id) = 0;
		virtual result list_art(const int& ng_id) = 0;
		virtual result create_art(const int& ng_id, const string& title, const string& author, const string& text) = 0;
		virtual result delete_art(const int& ng_id, const int& art_id) = 0;
		virtual result get_art(const int& ng_id, const int& art_id) = 0;
	private:
}
		


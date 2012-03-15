#ifndef DATABASEABS_H
#define DATABASEABS_H

#include "result.h"

namespace server {

	class DatabaseAbs {
	public:
		virtual db::Result *list_ng() = 0;
		virtual db::Result *create_ng(const std::string& ng_name) = 0;
		virtual db::Result *delete_ng(const int& ng_id) = 0;
		virtual db::Result *list_art(const int& ng_id) = 0;
		virtual db::Result *create_art(const int& ng_id, const string& title, const string& author, const string& text) = 0;
		virtual db::Result *delete_art(const int& ng_id, const int& art_id) = 0;
		virtual db::Result *get_art(const int& ng_id, const int& art_id) = 0;
	protected:
	private:
	};
		
}

#endif

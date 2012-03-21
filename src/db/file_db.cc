#include <string>

#include "db/file_db.h"
#include "db/result.h"
#include "net/protocol.h"
#include "db/directory.h"

#include "db/list_ng_result.h"
#include "db/create_ng_result.h"
#include "db/delete_ng_result.h"
#include "db/list_art_result.h"
#include "db/create_art_result.h"
#include "db/delete_art_result.h"
#include "db/get_art_result.h"

using namespace std;
using namespace net;

namespace db {
	const string FileDB::DB_ROOT = "news_db";
	//const string FileDB::DB_ROOT = "db/news_db";
	const string FileDB::DB_INFO_NAME = "db_info";

	Result *FileDB::list_ng() {
		
		return 0;
	}

	Result *FileDB::create_ng(string ng_name) {
		return 0;
	}

	Result *FileDB::delete_ng(size_t ng_id) {
		return 0;
	}

	Result *FileDB::list_art(size_t ng_id) {
		return 0;
	}

	Result *FileDB::create_art(size_t ng_id, std::string title, std::string author, std::string text) {
		return 0;
	}

	Result *FileDB::delete_art(size_t ng_id, size_t art_id) {
		return 0;
	}

	Result *FileDB::get_art(size_t ng_id, size_t art_id) {
		return 0;
	}

	//size_t FileDB::count_ng() {
		//return distance(dir.begin(), dir.end()) - 2; // '.' and '..'. // TODO is it so?
	//}
}

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

	FileDB::FileDB() : dir(DB_ROOT) {
		// TODO create if DB_ROOT does not exists?
		ng_count = count_ng();
	}

	const string FileDB::DB_ROOT = "./news_db";

	Result *FileDB::list_ng() {
		return 0;
	}

	Result *FileDB::create_ng(string ng_name) {
		return 0;
	}

	Result *FileDB::delete_ng(int ng_id) {
		return 0;
	}

	Result *FileDB::list_art(int ng_id) {
		return 0;
	}

	Result *FileDB::create_art(int ng_id, std::string title, std::string author, std::string text) {
		return 0;
	}

	Result *FileDB::delete_art(int ng_id, int art_id) {
		return 0;
	}

	Result *FileDB::get_art(int ng_id, int art_id) {
		return 0;
	}

	size_t FileDB::count_ng() {
		return distance(dir.begin(), dir.end()) - 2; // '.' and '..'.
	}
}

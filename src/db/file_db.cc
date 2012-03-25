#include <string>
#include <vector>
#include <iostream>
#include <sstream>
#include <utility>

#include "db/file_db.h"
#include "db/file_art.h"
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
#include "db/file_ng.h"

using namespace std;
using namespace net;

namespace db {
	const string FileDB::DB_ROOT = "news_db";
	const string FileDB::DB_INFO_NAME = "db_info";

	Result *FileDB::list_ng() {
		vector<string> dir_content = root_dir.list_content();
		vector<pair<size_t, string> > news_groups;
		split_ng(news_groups, dir_content);
		return new ListNGResult(news_groups);
	}

	Result *FileDB::create_ng(string ng_name) {
		Result *result = 0;
		if (exists_ng(ng_name)) {
			result = new CreateNGResult(static_cast<unsigned char>(Protocol::ERR_NG_ALREADY_EXISTS));

		} else {
			ostringstream ostr;
			ostr << DB_ROOT << "/" << next_id() << "_" << ng_name;
			string ng_file_path = ostr.str();

			FileNG ng((Directory(ng_file_path)));
			result = new CreateNGResult(static_cast<unsigned char>(Protocol::ANS_ACK));
		}
		return result;
	}

	Result *FileDB::delete_ng(size_t ng_id) {
		Result *result = 0;
		try {
			FileNG ng = get_ng(ng_id);
			ng.del_ng();
			result = new DeleteNGResult(static_cast<unsigned char>(Protocol::ANS_ACK));
		} catch (const InexistingNG &ing) {
			result = new DeleteNGResult(static_cast<unsigned char>(Protocol::ERR_NG_DOES_NOT_EXIST));
		}

		return result;
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
		Result *result = 0;
		try {
			FileNG ng = get_ng(ng_id);
			FileArt *art = ng.get_art(art_id);
			result =  new GetArtResult(art->get_title(), art->get_author(), art->get_text());
			delete art;
		} catch (const InexistingNG &ing) {
			result =  new GetArtResult(static_cast<unsigned char>(Protocol::ERR_NG_DOES_NOT_EXIST));
		} catch (const FileNG::InexistingArticle &ina) {
			result =  new GetArtResult(static_cast<unsigned char>(Protocol::ERR_ART_DOES_NOT_EXIST));
		}
		return result;
	}

	void FileDB::split_ng(vector<pair<size_t, string> > &pairs, const vector<string> &full_names) const {
		for (vector<string>::const_iterator it = full_names.begin(); it != full_names.end(); ++it) {
			string full_name = *it;
			string::size_type skid_pos = full_name.find_first_of('_');
			string str_id = full_name.substr(0, skid_pos);
			string name = full_name.substr(skid_pos + 1); // Skip skid.

			size_t id = 0;
			istringstream iss(str_id);
			if (!(iss >> id))
				cerr << "Bad ID for newsgroup found: \"" << str_id << "\"" << endl;
			
			pairs.push_back(make_pair(id, name));
		}
	}

	template<typename I>
	bool FileDB::exists_ng(const I &identifier) {
		vector<string> dir_content = root_dir.list_content();
		vector<pair<size_t, string> > news_groups;
		split_ng(news_groups, dir_content);
		vector<pair<size_t, string> >::iterator found = find_if(news_groups.begin(), news_groups.end(), bind2nd(compare_ng<I>(), identifier));
		return found != news_groups.end();
	}
	
	template<typename I>
	FileNG FileDB::get_ng(const I &identifier) throw(InexistingNG) {
		vector<string> dir_content = root_dir.list_content();
		vector<pair<size_t, string> > news_groups;
		split_ng(news_groups, dir_content);
		vector<pair<size_t, string> >::iterator found = find_if(news_groups.begin(), news_groups.end(), bind2nd(compare_ng<I>(), identifier));
		if (found != news_groups.end()) {
			ostringstream ostr;
			ostr << root_dir.get_path() << "/" << found->first << "_" << found->second;
			return FileNG(Directory(ostr.str()));
		} else {
			throw InexistingNG();
		}
	}

	size_t FileDB::next_id() {
		return 1;
	}

	template<>
	struct FileDB::compare_ng<size_t> : std::binary_function<std::pair<size_t, std::string>, const size_t, bool> {
		bool operator()(std::pair<size_t, std::string> &ng, const size_t id) const {
			return ng.first == id;
		}
	};

	template<>
	struct FileDB::compare_ng<std::string> : std::binary_function<std::pair<size_t, std::string>, const std::string, bool> {
		bool operator()(std::pair<size_t, std::string> &ng, const std::string name) const {
			return ng.second == name;
		}
	};
}

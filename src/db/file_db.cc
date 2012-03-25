#include <string>
#include <vector>
#include <iostream>
#include <fstream>
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


	// Must be declared before usage since there is no general template, 
	// only specializations.
	template<>
	struct FileDB::compare_ng<size_t> : binary_function<pair<size_t, string>, const size_t, bool> {
		bool operator()(pair<size_t, string> &ng, const size_t id) const {
			return ng.first == id;
		}
	};

	template<>
	struct FileDB::compare_ng<string> : binary_function<pair<size_t, string>, const string, bool> {
		bool operator()(pair<size_t, string> &ng, const string name) const {
			return ng.second == name;
		}
	};
	FileDB::FileDB() : root_dir(DB_ROOT) {
		if (!root_dir.file_exists(DB_INFO_NAME)){
			ofstream info(root_dir.full_path(DB_INFO_NAME).c_str());
			if (info){
				info << 0;
				info.close();
			} else {
				exit(EXIT_FAILURE);
			}
		}
	}

	Result *FileDB::list_ng() {
		vector<pair<size_t, string> > news_groups;
		read_ngs(news_groups);
		return new ListNGResult(news_groups);
	}

	Result *FileDB::create_ng(string ng_name) {
		Result *result = 0;
		if (exists_ng(ng_name)) {
			result = new CreateNGResult(static_cast<unsigned char>(Protocol::ERR_NG_ALREADY_EXISTS));

		} else {
			ostringstream ostr;
			ostr << next_id();
			string id_str = ostr.str();

			ofstream ofs;
			ofs.open(root_dir.full_path(DB_INFO_NAME).c_str(), ofstream::out | ofstream::app);
		vector<pair<size_t, string> > news_groups;
			ofs << id_str << " " << ng_name << endl;
			ofs.close();

			string ng_file_path = root_dir.full_path(id_str);
			FileNG ng((Directory(ng_file_path)));
			result = new CreateNGResult(static_cast<unsigned char>(Protocol::ANS_ACK));
		}
		return result;
	}

	Result *FileDB::delete_ng(size_t ng_id) {
		Result *result = 0;
		try {
			FileNG ng = get_ng(ng_id);

			ifstream ifst((root_dir.full_path(DB_INFO_NAME)).c_str());
			size_t id;
			ifst >> id;
			ifst.close();
			vector<pair<size_t, string> > news_groups; 
			read_ngs(news_groups);
			binder2nd<compare_ng<size_t> > comp = bind2nd<compare_ng<size_t>, size_t>(compare_ng<size_t>(), ng_id);
			vector<pair<size_t, string> >::iterator end = remove_if(news_groups.begin(), news_groups.end(), comp);;
			ofstream ofst((root_dir.full_path(DB_INFO_NAME)).c_str());
			ofst << id << endl;
			for (vector<pair<size_t, string> >::const_iterator it = news_groups.begin(); it != end; ++it) {
				ofst << it->first << " " << it->second << endl;
			}
			ofst.close();
			ng.del_ng();
			result = new DeleteNGResult(static_cast<unsigned char>(Protocol::ANS_ACK));
		} catch (const InexistingNG &ing) {
			result = new DeleteNGResult(static_cast<unsigned char>(Protocol::ERR_NG_DOES_NOT_EXIST));
		}

		return result;
	}

	Result *FileDB::list_art(size_t ng_id) {
		Result *result = 0;
		try {
			FileNG ng = get_ng(ng_id);	
			result = new ListArtResult(ng.list_arts());
		} catch (const InexistingNG &ing) {
			result = new ListArtResult(static_cast<unsigned char>(Protocol::ERR_NG_DOES_NOT_EXIST));
		}
		return result;
	}

	Result *FileDB::create_art(size_t ng_id, const string &title, const string &author, const string &text) {
		Result *result = 0;
		try {
			FileNG ng = get_ng(ng_id);
			ng.add_art(title, author, text);
			result =  new CreateArtResult(static_cast<unsigned char>(Protocol::ANS_ACK));
		} catch (const InexistingNG &ing) {
			result =  new CreateArtResult(static_cast<unsigned char>(Protocol::ERR_NG_DOES_NOT_EXIST));
		}
		return result;
	}

	Result *FileDB::delete_art(size_t ng_id, size_t art_id) {
		Result *result = 0;
		try {
			FileNG ng = get_ng(ng_id);
			ng.del_art(art_id);
			result =  new DeleteArtResult(static_cast<unsigned char>(Protocol::ANS_ACK));
		} catch (const InexistingNG &ing) {
			result =  new DeleteArtResult(static_cast<unsigned char>(Protocol::ERR_NG_DOES_NOT_EXIST));
		} catch (const FileNG::InexistingArticle &ina) {
			result = new DeleteArtResult(static_cast<unsigned char>(Protocol::ERR_ART_DOES_NOT_EXIST));
		}
		return result;
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

	size_t FileDB::next_id() { // TODO should be possible to do with only fstream. I tried with seekp(0) after reading etc. but did not work.
		ifstream ifst((root_dir.full_path(DB_INFO_NAME)).c_str());
		size_t id;
		ifst >> id;
		ifst.close();
		vector<pair<size_t, string> > news_groups; // TODO should not be needed to rewrite while file.
		read_ngs(news_groups);
		++id;
		ofstream ofst((root_dir.full_path(DB_INFO_NAME)).c_str());
		ofst << id << endl;
		for (vector<pair<size_t, string> >::const_iterator it = news_groups.begin(); it != news_groups.end(); ++it) {
			ofst << it->first << " " << it->second << endl;
		}
		ofst.close();
		return id;
	}

	void FileDB::read_ngs(std::vector<std::pair<size_t, std::string> > &news_groups) {
		ifstream ifst((root_dir.full_path(DB_INFO_NAME)).c_str());
		string line;
		getline(ifst, line); // Skip id counter.
		while (getline(ifst, line)) {
			istringstream istr(line);
			size_t id;
			istr >> id;
			istr >> noskipws;
			string ng_name = string((istream_iterator<char>(istr)), istream_iterator<char>());
			// Trim spaces.
			ng_name.erase(ng_name.begin(), find_if(ng_name.begin(), ng_name.end(), not1(ptr_fun<int, int>(isspace))));
			news_groups.push_back(make_pair(id, ng_name));
		}
	}

	template<typename I>
	bool FileDB::exists_ng(const I &identifier) {
		vector<pair<size_t, string> > news_groups;
		read_ngs(news_groups);
		vector<pair<size_t, string> >::iterator found = find_if(news_groups.begin(), news_groups.end(), bind2nd(compare_ng<I>(), identifier));
		return found != news_groups.end();
	}
	
	template<typename I>
	FileNG FileDB::get_ng(const I &identifier) throw(InexistingNG) {
		vector<pair<size_t, string> > news_groups;
		read_ngs(news_groups);
		vector<pair<size_t, string> >::iterator found = find_if(news_groups.begin(), news_groups.end(), bind2nd(compare_ng<I>(), identifier));
		if (found != news_groups.end()) {
			ostringstream ostr;
			ostr << found->first;
			//return FileNG(Directory(ostr.str()));
			return FileNG(Directory(root_dir.full_path(ostr.str())));
		} else {
			throw InexistingNG();
		}
	}
}

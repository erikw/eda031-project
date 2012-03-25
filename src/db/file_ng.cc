#include <cstdlib>
#include <fstream>
#include <sstream>
#include <algorithm>

#include "db/file_ng.h"
#include "db/directory.h"
#include "db/file_art.h"

using namespace std; //TODO placing this below in ns db, will it be used in all ns db in other files?

namespace db {
	const string FileNG::NG_INFO_NAME = "db_info";

	FileNG::FileNG(Directory d) : dir(d) {
		if (!dir.file_exists(NG_INFO_NAME)){
			ofstream info(dir.full_path(NG_INFO_NAME).c_str());
			if (info){
				info << 0;
				info.close();
			} else {
				exit(EXIT_FAILURE);
			}
		}
	}

	vector<pair<size_t, string> > FileNG::list_arts() {
		vector<string> files = dir.list_files();
		vector<string>::iterator end = remove_if(files.begin(), files.end(), bind2nd(equal_to<string>(), NG_INFO_NAME));
		vector<pair<size_t, string> > articles;
		for (vector<string>::iterator it = files.begin(); it != end; ++it){
			string file_name = *it;

			istringstream istr(file_name);
			size_t id;
			istr >> id;

			ifstream input(dir.full_path(file_name).c_str());
			string id_str;
			string title;
			getline(input, title); 
			articles.push_back(make_pair(id, title));
		}
		return articles;
	}

	FileArt *FileNG::get_art(size_t id) throw(InexistingArticle) {
		ostringstream ostr;
		ostr << id;
		string file_name = ostr.str();
		if (dir.file_exists(file_name)) {
			ifstream ifs(dir.full_path(file_name).c_str());
			FileArt *article;
			article = new FileArt();
			ifs >> *article;
			ifs.close();
			return article;
		}  else {
			throw InexistingArticle();
		}
	}

	void FileNG::add_art(const string &title, const string &author, const string &text) {
		size_t id = next_id();
		FileArt article(title, author, text);
		ostringstream ostr;
		ostr << id; 
		ofstream ofs(dir.full_path(ostr.str()).c_str());
		ofs << article;
		ofs.close();
	}

	void FileNG::del_art(size_t id) {
		ostringstream ostr;
		ostr << id;
		dir.delete_file(ostr.str());
	}

	void FileNG::del_ng() {
		dir.delete_dir();
	}

	size_t FileNG::next_id() { // TODO should be possible to do with only fstream. I tried with seekp(0) after reading etc. but did not work.
		ifstream ifst((dir.full_path(NG_INFO_NAME)).c_str());
		size_t id;
		ifst >> id;
		ifst.close();
		++id;
		ofstream ofst((dir.full_path(NG_INFO_NAME)).c_str());
		ofst << id << endl;
		ofst.close();
		return id;
	}
}

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
			getline(input, id_str); // Skipping first line.
			string title;
			getline(input, title); 
			articles.push_back(make_pair(id, title));
		}
		return articles;
	}

	FileArt *FileNG::get_art(size_t id) {
		FileArt *article = 0;
		ostringstream ostr;
		ostr << id;
		string file_name = ostr.str();
		if (dir.file_exists(file_name)) {
			ifstream ifs(dir.full_path(file_name).c_str());
			article = new FileArt();
			ifs >> *article;
			ifs.close();
		} 
		return article;
	}

	void FileNG::del_art(size_t id) {
		ostringstream ostr;
		ostr << id;
		dir.delete_file(ostr.str());
	}

	void FileNG::del_ng() {
		dir.delete_dir();
	}
}

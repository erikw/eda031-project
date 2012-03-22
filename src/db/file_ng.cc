#include <cstdlib>
#include <fstream>
#include <sstream>
#include <algorithm>

#include "db/file_ng.h"
#include "db/directory.h"

using namespace std; //TODO

namespace db {
	const string FileNG::NG_INFO_NAME = "db_info";

	FileNG::FileNG(Directory d) : dir(d) {
		if(!dir.file_exists(NG_INFO_NAME)){
			ofstream info((dir.get_path() + "/" + NG_INFO_NAME).c_str());
			if (info){
				info << 0;
				info.close();
			} else {
				exit(EXIT_FAILURE);
			}
		}
	}

	vector<pair<size_t, string> > FileNG::list_arts() {
		vector<string> files = dir.list_content();
		vector<string>::iterator end = remove_if(files.begin(), files.end(), bind2nd(equal_to<string>(), NG_INFO_NAME));
		vector<pair<size_t, string> > articles;
		for(vector<string>::iterator it = files.begin(); it != end; ++it){
			string file_name = *it;

			istringstream istr(file_name);
			size_t id;
			istr >> id;

			ifstream input((dir.get_path() + "/" + file_name).c_str());
			string title;
			getline(input, title);
			articles.push_back(make_pair(id, title));
		}
		return articles;
	}
}

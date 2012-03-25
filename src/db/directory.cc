#include <sys/types.h>
#include <sys/stat.h>
#include <dirent.h>
#include <errno.h>
#include <cstdio>
#include <cstring>
#include <cstdlib>
#include <string>
#include <iostream>
#include <sstream>
#include <algorithm>

#include "db/directory.h"

using namespace std;

namespace db {
	Directory::Directory(const string &p) : path(p) {
		closedir(open_dir()); // Create and check access.
	}
	Directory::iterator Directory::begin() { 
		return DirIterator(open_dir()); 
	}

	std::vector<std::string> Directory::list_files() {
		return list_type(DT_REG);
	}

	std::vector<std::string> Directory::list_dirs() {
		return list_type(DT_DIR);
	}

	void Directory::mk_dir(const std::string &name) {
		mk_dir_helper(path + "/" + name);
	}

	void Directory::delete_dir() {
		//errno = 0;
		//if (remove(path.c_str()) != 0) {
			//ostringstream ostr;
			//ostr << "Error deleting  \"" << full_name << "\"";
			//perror(ostr.str().c_str());
		//}
		delete_file("");
	}

	void Directory::delete_file(const string &file_name) {
		errno = 0;
		string full_name = path + "/" + file_name;
		if (remove(full_name.c_str()) != 0 ) {
			ostringstream ostr;
			ostr << "Error deleting  \"" << full_name << "\"";
			perror(ostr.str().c_str());
		}
	}

	bool Directory::file_exists(const string &file_name) {
		return find_if(begin(), end(), bind2nd(equal_file_name(), file_name)) != end();
	}

	void Directory::mk_dir_helper(std::string full_path) {
		errno = 0;
		mkdir(full_path.c_str(), 0777); // Whatever perms in umask.
		if (errno) {
			ostringstream ostr;
			ostr << "Error creating directory \"" << full_path << "\"";
			perror(ostr.str().c_str());
			exit(errno); // Unrecoverable.
		} else {
			clog << "Directory \"" << path << "\" is mkdir'd." << endl;
		}
	}

	DIR *Directory::open_dir() {
		errno = 0;
		DIR *dir = opendir(path.c_str()); // Check for availability of the directory.
		if (!dir) {
			ostringstream ostr;
			ostr << "Error opening path \"" << path << "\"";
			perror(ostr.str().c_str());
			if (errno == ENOENT) { // No directory.
				mk_dir_helper(path);
				dir = opendir(path.c_str());
			} else {
				exit(errno); // Unrecoverable.
			}
		}
		return dir;
	}

	vector<string> Directory::list_type(unsigned int ent_type) {
		vector<string> contents;
		for (Directory::iterator it = begin(); it != end(); ++it) {
			dirent *entity = *it;
			if (entity->d_type == ent_type && strcmp(entity->d_name, ".") && strcmp(entity->d_name, "..")) {
				contents.push_back(entity->d_name);
			}
		}
		return contents;
	}
}

#include <sys/types.h>
#include <sys/stat.h>
#include <dirent.h>
#include <errno.h>
#include <cstdio>
#include <cstdlib>
#include <string>
#include <iostream>
#include <sstream>

#include "db/directory.h"

using namespace std;

namespace db {
	Directory::Directory(const string &p) : path(p) {
		errno = 0;
		dir = opendir(path.c_str());
		if (!dir) {
			ostringstream ostr;
			ostr << "Error opening path \"" << path << "\"";
			perror(ostr.str().c_str());
			
			if (errno == ENOENT) { // No directory.
				errno = 0;
				mkdir(p.c_str(), 0777); // Whatever perms in umask.
				clog << "Directory \"" << path << "\" is mkdir'd." << endl;
				dir = opendir(path.c_str());
				if (errno)
					exit(errno); // Unrecoverable.
			} else {
				exit(errno); // Unrecoverable.
			}
		}
	}

	std::vector<string> Directory::list_content() {
		return vector<string>();
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
}

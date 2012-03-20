#include <sys/types.h>
#include <sys/stat.h>
#include <dirent.h>
#include <errno.h>
#include <cstdio>
#include <string>
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
			// TODO throw exception?
			
			if (errno == ENOENT) { // No directory.
				mkdir(p.c_str(), 0x777); // What ever perms in umask.
			}
			
		}
	}
}


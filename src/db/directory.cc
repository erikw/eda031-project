#include <sys/types.h>
#include <dirent.h>
#include <errno.h>
#include <cstdio>
#include <string>
#include <sstream>

#include "db/directory.h"

using namespace std;

namespace db {
	Directory::Directory(const string &p) : path(p) {
		dir = opendir(path.c_str());
		if (!dir) {
			ostringstream ostr;
			ostr << "Error opening path \"" << path << "\"";
			perror(ostr.str().c_str());
			// TODO throw exception.
		}
	}
}


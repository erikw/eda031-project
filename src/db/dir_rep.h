#ifndef DIR_REP_H
#define DIR_REP_H

#include <sys/types.h>
#include <dirent.h>

namespace db {
	struct DirRep {
		friend class DirIterator;
	public:
		explicit DirRep(DIR *d) : dir(d), ref_count(1) {}
		~DirRep() { closedir(dir); }

	private:
		DIR *dir;
		size_t ref_count;
	};
}

#endif

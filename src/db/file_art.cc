#include <iostream>

#include "db/file_art.h"

using namespace std;

namespace db {

	istream &operator>>(istream &in, FileArt &file_art) {

		return in;
	}

	ostream &operator<<(ostream &out, const FileArt &file_art) {
		return out;
	}
}

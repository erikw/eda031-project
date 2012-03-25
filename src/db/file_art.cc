#include <iostream>
#include <sstream>
#include <iterator>
#include <algorithm>
#include <string>

#include "db/file_art.h"

using namespace std;

namespace db {
	istream &operator>>(istream &in, FileArt &file_art) {
		string id_str; // TODO id should not be saved in the file, redundant.
		getline(in, id_str);
		istringstream istr(id_str);
		istr >> file_art.id;
		getline(in, file_art.title);
		getline(in, file_art.author);
		//in.unset(ios::noskipws);
		in >> noskipws;
		file_art.text = string((istream_iterator<char>(in)), istream_iterator<char>());
		return in;
	}

	ostream &operator<<(ostream &out, const FileArt &file_art) {
		out << file_art.id << endl;
		out << file_art.title << endl;
		out << file_art.author << endl;
		out << file_art.text;
		return out;
	}
}

#include <iostream>

#include "db/result.h"

using namespace std;

namespace db {
	ostream &operator<<(ostream &out, const Result &res) {
		res.toString(out); // Dynamic binding.
		return out;
	}
}

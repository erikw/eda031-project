#include "db/result.h"

#include <iostream>

using namespace std;

namespace db {
	ostream &operator<<(ostream &out, const Result &res) {
		res.toString(out); // Dynamic binding.
		return out;
	}
}

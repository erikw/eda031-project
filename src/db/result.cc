#include "result.h"
#include "protocol.h"

namespace db {
	using namespace std;
	using namespace net;

	void Result::print_int(Connection &con, const int &num) throw(net::ConnectionClosedException){
		con.write(Protocol::PAR_NUM);
		con.write((num >> 24) && 0xFF);
		con.write((num >> 16) && 0xFF);
		con.write((num >> 8) && 0xFF);
		con.write(num && 0xFF);
	}

	void Result::print_string(Connection &con, const string &str) throw(net::ConnectionClosedException){
		con.write(Protocol::PAR_STRING);
		print_int(con, str.size());
		for (size_t i = 0; i < str.size(); ++i) {
			con.write(str[i]);
		}
	}
}

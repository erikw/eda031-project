#include "db/result.h"
#include "net/protocol.h"

namespace db {
	using namespace std;
	using namespace net;

	void Result::print_num(Connection &con, const int &num) throw(ConnectionClosedException){
		con.write(Protocol::PAR_NUM);
		print_int(con, num);
	}

	void Result::print_int(Connection &con, const int &num) throw(ConnectionClosedException){
		con.write((num >> 24) & 0xFF);
		con.write((num >> 16) & 0xFF);
		con.write((num >> 8) & 0xFF);
		con.write(num & 0xFF);
	}

	void Result::print_string(Connection &con, const string &str) throw(ConnectionClosedException){
		con.write(Protocol::PAR_STRING);
		print_int(con, str.size());
		for (size_t i = 0; i < str.size(); ++i) {
			con.write(str[i]);
		}
	}
}

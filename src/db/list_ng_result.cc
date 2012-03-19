#include <string>
#include <vector>

#include "db/list_ng_result.h"
#include "net/connectionclosedexception.h"
#include "net/protocol.h"

using namespace net;
using namespace std;

namespace db {
	void ListNGResult::printToConnection(Connection &conn) throw (net::ConnectionClosedException) {
		conn.write(Protocol::ANS_LIST_NG);
		print_num(conn, news_groups.size());
		for (size_t i = 0; i < news_groups.size(); ++i) {
			pair<int, string> ng = news_groups[i];
			print_num(conn, ng.first);
			print_string(conn, ng.second);
		}
		conn.write(Protocol::ANS_END);
	}
}

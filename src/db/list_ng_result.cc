#include "list_ng_result.h"
#include <string>
#include <vector>

using namespace net;
using namespace std;

namespace db {
	ListNGResult::printToConnection(Connection& conn){
		conn.write(Protocol::ANS_LIST_NG);
		print_int(conn, news_groups.size());
		for(int i = 0; i < news_groups.size(); ++i){
			pair<int, string> ng = news_groups[i];
			print_int(conn, ng.first);
			print_string(conn, ng.second);
		}
		conn.write(Protocol::ANS_END);
	}
}

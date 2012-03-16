#include "list_art_result.h"
#include <string>
#include <vector>

using namespace net;
using namespace std;

namespace db {
	void ListArtResult::printToConnection(Connection& conn) {
		conn.write(Protocol::ANS_LIST_ART);
		if (message==Protocol::ANS_NACK) {
			conn.write(Protocol::ANS_NACK);
			conn.write(message);
		} else {
			conn.write(Protocol::ANS_ACK);
			print_int(conn, articles.size());
			for (int i = 0; i < articles.size(); ++i) {
				pair<int, string> art = articles[i];
				print_int(conn, art.first);
				print_string(conn, art.second);
			}
		}	
		conn.write(Protocol::ANS_END);
	}
}

#include <string>
#include <vector>

#include "db/list_art_result.h"
#include "net/protocol.h"
#include "net/connectionclosedexception.h"

using namespace net;
using namespace std;

namespace db {
	void ListArtResult::printToConnection(Connection& conn) throw (net::ConnectionClosedException){
		conn.write(Protocol::ANS_LIST_ART);
		if (message == Protocol::ANS_NAK) {
			conn.write(Protocol::ANS_NAK);
			conn.write(message);
		} else {
			conn.write(Protocol::ANS_ACK);
			print_num(conn, articles.size());
			for (size_t i = 0; i < articles.size(); ++i) {
				pair<int, string> art = articles[i];
				print_num(conn, art.first);
				print_string(conn, art.second);
			}
		}	
		conn.write(Protocol::ANS_END);
	}
}

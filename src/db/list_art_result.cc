#include "list_art_result.h"
#include <string>
#include <vector>
#include "protocol.h"
#include "connectionclosedexception.h"

using namespace net;
using namespace std;

namespace db {
	void ListArtResult::printToConnection(Connection& conn) throw (ConnectionClosedException){
		conn.write(Protocol::ANS_LIST_ART);
		if (message==Protocol::ANS_NAK) {
			conn.write(Protocol::ANS_NAK);
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

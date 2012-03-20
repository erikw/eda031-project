#include <string>
#include <vector>
#include <iostream>

#include "db/list_art_result.h"
#include "net/protocol.h"
#include "net/connectionclosedexception.h"


namespace db {

using namespace net;
using namespace std;

	void ListArtResult::printToConnection(Connection& conn) throw (ConnectionClosedException){
		conn.write(Protocol::ANS_LIST_ART);
		if (message != Protocol::ANS_ACK) {
			conn.write(Protocol::ANS_NAK);
			conn.write(message);
		} else {
			conn.write(Protocol::ANS_ACK);
			print_num(conn, articles.size());
			
			for (vector<pair<int, string> >::iterator iter = articles.begin(); iter != articles.end(); ++iter) {
				vector<pair<int, string> >::value_type art = *iter;
				print_num(conn, art.first);
				print_string(conn, art.second);
			}
		}	
		conn.write(Protocol::ANS_END);
	}
}

#include <string>
#include <vector>
#include <iostream>

#include "db/list_ng_result.h"
#include "net/connectionclosedexception.h"
#include "net/protocol.h"

using namespace net;
using namespace std;

namespace db {
	void ListNGResult::printToConnection(MessageHandler &mh) throw (net::ConnectionClosedException) {
		mh.print_byte(Protocol::ANS_LIST_NG);
		mh.print_num(news_groups.size());
		for (size_t i = 0; i < news_groups.size(); ++i) {
			pair<int, string> ng = news_groups[i];
			mh.print_num(ng.first);
			mh.print_string(ng.second);
		}
		mh.print_byte(Protocol::ANS_END);
	}

	void ListNGResult::toString(ostream &out) const {
		pair<int, string> current_pair;
		for (size_t i = 0; i < news_groups.size(); ++i) {
			current_pair = news_groups[i];
			out << current_pair.first << ". " << current_pair.second << endl;
		}
	}

}

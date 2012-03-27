#include "db/list_art_result.h"

#include <string>
#include <vector>
#include <iostream>

#include "net/protocol.h"
#include "net/connectionclosedexception.h"

using namespace net;
using namespace std;

namespace db {
	void ListArtResult::printToConnection(MessageHandler &mh) throw (ConnectionClosedException){
		mh.print_byte(Protocol::ANS_LIST_ART);
		if (message != Protocol::ANS_ACK) {
			mh.print_byte(Protocol::ANS_NAK);
			mh.print_byte(message);
		} else {
			mh.print_byte(Protocol::ANS_ACK);
			mh.print_num(articles.size());

			for (vector<pair<size_t, string> >::iterator iter = articles.begin(); iter != articles.end(); ++iter) {
				vector<pair<size_t, string> >::value_type art = *iter;
				mh.print_num(art.first);
				mh.print_string(art.second);
			}
		}
		mh.print_byte(Protocol::ANS_END);
	}


	void ListArtResult::toString(ostream &out) const {
		if (message != Protocol::ANS_ACK){
			out << "ERROR: Newsgroup doesn't exist.";
		} else if (articles.size() > 0) {
			pair<size_t, string> current_pair;
			for (size_t i = 0; i < articles.size(); ++i) {
				current_pair = articles[i];
				out << current_pair.first << ". " << current_pair.second;
				if (i < (articles.size() - 1)) {
					out << endl;
				}
			}
		} else {
			out << "No articles.";
		}
	}

}

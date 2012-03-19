#include <iostream>
#include "db/get_art_result.h"
#include "net/connectionclosedexception.h"
#include "net/protocol.h"

namespace db {
	using namespace net;
	
	void GetArtResult::printToConnection(Connection &con) throw(net::ConnectionClosedException) {
		con.write(Protocol::ANS_GET_ART);
		if (message != Protocol::ANS_ACK){
			con.write(Protocol::ANS_NAK);
			con.write(message);
		} else {
			std::cout << "HERE" << std::endl;
			std::cout << "title: " << title << std::endl;
			std::cout << "author: " << author << std::endl;
			std::cout << "text: " << text << std::endl;
			con.write(Protocol::ANS_ACK);
			print_string(con, title);
			print_string(con, author);
			print_string(con, text);
		}
		con.write(Protocol::ANS_END);
	}
}

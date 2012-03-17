#include <string>

#include "db/delete_ng_result.h"
#include "net/connectionclosedexception.h"
#include "net/protocol.h"

using namespace net;
using namespace std;

namespace db {
	void DeleteNGResult::printToConnection(Connection &conn) throw (ConnectionClosedException) {
		conn.write(Protocol::ANS_DELETE_NG);		
		if(message!=Protocol::ANS_ACK)
			conn.write(Protocol::ANS_NAK);
		conn.write(message);
		conn.write(Protocol::ANS_END);
	}
}

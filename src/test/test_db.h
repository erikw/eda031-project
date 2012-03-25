#ifndef TEST_DB_H
#define TEST_DB_H

#include <string>
#include <vector>

#include "db/database.h"
#include "net/connection.h"

namespace test {
	class MockConnection : public net::Connection {
		public:
			MockConnection() {}
			virtual ~MockConnection() {}
			virtual bool isConnected() const {
				return true;
			}

			virtual void write(unsigned char ch) const throw(net::ConnectionClosedException) {
				output.push_back(ch);
			}
			
			virtual unsigned char read() const throw(net::ConnectionClosedException) {
				return 0;
			}

			std::vector<char> get_output() {
				return output;
			}

			void clear_output(){
				output.clear();
			}

		private:
			size_t read_at;
			mutable std::vector<char> output;
	};

	enum {MEMORY_DB, FILE_DB};

	extern	db::Database *dbp;
	extern	MockConnection *con;
	extern char db_type;

	template<typename T>
	void assertEquals(const std::string &if_neq, const T &expected, const T &value);
	void convert(std::vector<char> &out, unsigned int num);
	void convert(std::vector<char> &out, std::string str);


	void set_up();
	void tear_down();

	void test_create_ng();
	void test_create_exist_ng();
	void test_list_ng();
	void test_list_no_ng();
	void test_delete_ng();
	void test_delete_nonexist_ng();
	void test_create_art();
	void test_create_no_ng_art();
	void test_list_art();
	void test_list_no_art();
	void test_list_no_ng_art();
	void test_get_art();
	void test_get_no_art();
	void test_get_art_no_ng() ;
	void test_delete_art();
	void test_delete_art_no_ng();
	void test_delete_art_no_art();
}

#endif

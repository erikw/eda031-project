#include <iostream>
#include "memory_db.h"
#include "protocol.h"
#include "list_ng_result.h"
#include "create_ng_result.h"
#include "delete_ng_result.h"
#include "list_art_result.h"
#include "create_art_result.h"
#include "delete_art_result.h"
#include "get_art_result.h"
#include <map>
#include <vector>
using namespace std;
using namespace net;

namespace db {

		Result* MemoryDb::list_ng(){
			vector<pair<int, string> > temp_ng_list;
			for(map<int,NewsGroup>::iterator it = news_groups.begin(); it!=news_groups.end(); ++it)
				temp_ng_list.push_back(make_pair(it->first,it->second.name));
			return new ListNGResult(temp_ng_list);
		}

		Result* MemoryDb::create_ng(string ng_name){
			for(map<int,NewsGroup>::iterator it = news_groups.begin(); it!=news_groups.end(); ++it)
				if(it->second.name==ng_name)
					return new CreateNGResult(Protocol::ERR_NG_ALREADY_EXISTS);
			NewsGroup ng;
			ng.name = ng_name;
			news_groups[++ng_count] = ng;
			return new CreateNGResult(Protocol::ANS_ACK);
		}

		Result* MemoryDb::delete_ng(const int& ng_id){
			if(news_groups.erase(ng_id)==0)
				return new DeleteNGResult(Protocol::ERR_NG_DOES_NOT_EXIST);
			return new DeleteNGResult(Protocol::ANS_ACK);
		}

		Result* MemoryDb::list_art(const int& ng_id){
			if(news_groups.find(ng_id)==news_groups.end())
				return new ListArtResult(Protocol::ERR_NG_DOES_NOT_EXIST);
			vector<pair<int, string> > temp_art_list;
			map<int,Article> art_map = news_groups[ng_id].articles;
			for(map<int,Article>::iterator it = art_map.begin(); it != art_map.end(); ++it)
				temp_art_list.push_back(make_pair(it->first,it->second.title));
			return new ListArtResult(temp_art_list);

		}

		Result* MemoryDb::create_art(const int& ng_id, string title,
						string author, string text){
			if(news_groups.find(ng_id)==news_groups.end())
				return new CreateArtResult(Protocol::ERR_NG_DOES_NOT_EXIST);
			Article art;
			int art_id = ++news_groups[ng_id].art_count;
			art.author = author;
			art.title = title;
			art.text = text;
			news_groups[ng_id].articles[art_id] = art;
			return new CreateArtResult(Protocol::ANS_ACK);
		}

		Result* MemoryDb::delete_art(const int& ng_id, const int& art_id){
			if(news_groups.find(ng_id) == news_groups.end())
				return new DeleteArtResult(Protocol::ERR_NG_DOES_NOT_EXIST);
			if(news_groups[ng_id].articles.erase(art_id) == 0)
				return new DeleteArtResult(Protocol::ERR_ART_DOES_NOT_EXIST);
			return new DeleteArtResult(Protocol::ANS_ACK);
			
		}

		Result* MemoryDb::get_art(const int& ng_id, const int& art_id){
			if(news_groups.find(ng_id) == news_groups.end())
				return new GetArtResult(Protocol::ERR_NG_DOES_NOT_EXIST);
			map<int, Article> &temp_art = news_groups[ng_id].articles;
			map<int, Article>::iterator it = temp_art.find(art_id);
			if(it == temp_art.end())
				return new GetArtResult(Protocol::ERR_ART_DOES_NOT_EXIST);
			return new GetArtResult(it->second.title, it->second.author, it->second.text);
		}
}
#define CPPHTTPLIB_OPENSSL_SUPPORT
#include "httplib.h"
#include "json.hpp"
#include "client.h"
#include "sharding.h"
#include <iostream>
#include <websocketpp/config/asio_client.hpp>


#define active true


using websocketpp::lib::placeholders::_1;
using websocketpp::lib::placeholders::_2;
using websocketpp::lib::bind;

typedef websocketpp::config::asio_tls_client::message_type::ptr message_ptr;
typedef websocketpp::lib::shared_ptr<boost::asio::ssl::context> context_ptr;
typedef websocketpp::client<websocketpp::config::asio_tls_client> client;
typedef client::connection_ptr connection_ptr;

/*std::string token;
const std::string url = "wss://gateway.discord.gg/?v=6&encoding=json";
DiscPPlus::Bot bot;
unsigned short hbInterval = 41250;
client c; */

std::vector<DiscPPlus::Shard> DiscPPlus::Client::AddShard(DiscPPlus::Bot bot, int id, int total) {
	std::vector<DiscPPlus::Shard> shardList;
	return shardList;
}

#include "httplib.h"
#include "json.hpp"
#include "client.h"
#include <iostream> 
#include <websocketpp/config/asio_client.hpp>
#include <websocketpp/client.hpp>

using websocketpp::lib::placeholders::_1;
using websocketpp::lib::placeholders::_2;
using websocketpp::lib::bind;

typedef websocketpp::config::asio_tls_client::message_type::ptr message_ptr;
typedef websocketpp::lib::shared_ptr<boost::asio::ssl::context> context_ptr;
typedef websocketpp::client<websocketpp::config::asio_tls_client> client;
typedef client::connection_ptr connection_ptr;
using nlohmann::json;



void DiscPPlus::Bot::SetStats(client* c, websocketpp::connection_hdl hdl, message_ptr msg, std::string token) {
	DiscPPlus::Bot::c = c;
	DiscPPlus::Bot::hdl = hdl;
	DiscPPlus::Bot::msg = msg;
	DiscPPlus::Bot::token = token;
}


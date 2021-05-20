#include "httplib.h"
#include "json.hpp"
#include "Client.h"
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




void DiscPPlus::bot::SetStats(client* c, websocketpp::connection_hdl hdl, message_ptr msg, std::string token) {
	DiscPPlus::bot::c = c;
	DiscPPlus::bot::hdl = hdl;
	DiscPPlus::bot::msg = msg;
	DiscPPlus::bot::token = token;
}
#pragma once
#include <iostream>
#include "json.hpp"
#include <websocketpp/config/asio_client.hpp>
#include <websocketpp/client.hpp>

using websocketpp::lib::placeholders::_1;
using websocketpp::lib::placeholders::_2;
using websocketpp::lib::bind;

typedef websocketpp::config::asio_tls_client::message_type::ptr message_ptr;
typedef websocketpp::lib::shared_ptr<boost::asio::ssl::context> context_ptr;
typedef websocketpp::client<websocketpp::config::asio_tls_client> client;
typedef client::connection_ptr connection_ptr;

namespace DiscPPlus 
{
	class Bot
	{
	public:
		client* c;
		message_ptr msg;
		websocketpp::connection_hdl hdl;
		std::string token;
	public:
		void SetStats(client* c, websocketpp::connection_hdl hdl, message_ptr msg, std::string token);
	};
	class Channel {
	public:
		void Send(std::string msg, DiscPPlus::Bot bot);
		std::string id;
	};
	class Author {
	public:
		std::string name;
		std::string mention;
		std::string id;
	};
	class Message 
	{
	public:
		std::string content;
		bool embed;
		Channel channel;
		Author author;
	};
	class Client
	{
	public:
		bool establishConnection(std::string token);
		void sendWSReq(nlohmann::json payload, std::string wsUrl);
	};
	class Commands
	{
	public:
		void OnMsg(Message msg, Bot bot);
		void OnTyping(Author);
	};
}
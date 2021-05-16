#pragma once
#include <iostream>
#include "json.hpp"
#include <websocketpp/config/asio_client.hpp>
#include <websocketpp/client.hpp>

typedef websocketpp::client<websocketpp::config::asio_tls_client> client;

namespace DiscPPlus 
{
	class Client
	{
	public: 
		bool establishConnection();
		void sendWSReq(nlohmann::json payload, std::string wsUrl);
	};
}
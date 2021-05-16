#pragma once
#include <iostream>
#include "json.hpp"

namespace DiscPPlus 
{
	class Client
	{
	public: 
		bool establishConnection();
		void sendWSReq(nlohmann::json payload, std::string wsUrl);
	};
}
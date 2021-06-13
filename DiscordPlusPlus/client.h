#pragma once
#include <iostream>
#include "json.hpp"
#include "sharding.h"
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

	class Embed 
	{
	public:
		nlohmann::json payload;
		void SetTitle(std::string title);
		void AddField(std::string name, std::string value, bool inlin=false);
		void SetColor(int color);
		void SetDesc(std::string desc);
		void SetAuthor(std::string name, std::string url = "", std::string icon_url = "", std::string proxy_icon_url = "");
		void SetFooter(std::string text, std::string icon_url = "", std::string proxy_icon_url = "");
	};
	class Bot
	{
	public:
		client* c;
		message_ptr msg;
		websocketpp::connection_hdl hdl;
		std::string token;
		void SetStats(client* c, websocketpp::connection_hdl hdl, message_ptr msg, std::string token);
	};
	class Channel {
	public:
		void Send(std::string msg, DiscPPlus::Bot bot);
		void SendEmbed(DiscPPlus::Embed, DiscPPlus::Bot bot);
		void GetGuild();
		void SendSpecial(nlohmann::json payload, DiscPPlus::Bot bot);
		std::string id;
	};
	class Author {
	public:
		std::string name;
		std::string mention;
		std::string id;
		void CreateDM(Bot bot);
		void AddRole(std::string role);
		void RemoveRole(std::string role);
		bool HasPerms(std::string perm);
		Channel channel;
	};
	class Emoji 
	{
	public:
		std::string name;
		std::string roles;
		std::string id;
		bool reqColon;
		bool managed;
		bool animated;
		bool available;
		void from_json(nlohmann::json j);
	};
	class Role
	{

	};
	class Guild
	{
	public:
		std::string name;
		std::string id;
		std::string icon;
		std::string desc;
		std::string splash;
		std::string discoverySplash;
		int memCount;
		int presenceCount;
		std::vector<std::string> features;
		std::vector<Emoji> emojis;
		std::vector<Role> roles;

	};
	class Client
	{
	public:
		bool establishConnection(std::string token);
		bool establishShardConnection(std::string token, nlohmann::json ID);
		void sendWSReq(nlohmann::json payload, std::string wsUrl);
		void sendShardWSReq(nlohmann::json payload = "", std::string wsUrl = "");
		std::vector<DiscPPlus::Shard> AddShard(DiscPPlus::Bot bot, int id, int total);
	};
	class Message
	{
	public:
		std::string content;
		bool embed;
		Channel channel;
		Author author;
		Guild GetGuild(DiscPPlus::Bot bot);
		std::string guildId;
	};
	class Commands
	{
	public:
		void OnMsg(Message msg, Bot bot);
		void OnTyping(Author user, Channel channel);
		void Ban(std::string authid);
		void Kick(std::string authid);
	};
}

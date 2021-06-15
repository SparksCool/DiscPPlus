#define CPPHTTPLIB_OPENSSL_SUPPORT
#include "httplib.h"
#include "json.hpp"
#include "client.h"
#include <iostream>


using DiscPPlus::Commands;
using nlohmann::json;


// create a dm with author not doing this can result in a crash
void DiscPPlus::Author::CreateDM(Bot bot) {
    httplib::Client cli("https://discord.com");
    const std::string path = std::string("/api/v6/users/@me/channels");
    json payload;
    payload["recipient_id"] = id;
    try
    {
        cli.set_default_headers({
            {"Authorization", "Bot " + bot.token}
            });
        std::cout << id << '\n';
        auto res = cli.Post(path.c_str(), payload.dump(), "application/json");
        if (res) {
            std::cout << res->status << '\n';
            std::cout << res->body << '\n';
            channel.id = json::parse(res->body)["id"];
        }
    }
    catch (std::exception& e)
    {
        std::cerr << "Connection failed, error: " << e.what() << '\n';
        return;
    }
    catch (...) {
        std::cerr << "UNKNOWN ERROR OCCURED";
    }
}
// add a guild role
void DiscPPlus::Author::AddRole(std::string role)
{
}
// remove a guild role
void DiscPPlus::Author::RemoveRole(std::string role)
{
}
// check if member has permissions
bool DiscPPlus::Author::HasPerms(std::string perm)
{
    return false;
}
// get guild a message was sent in
DiscPPlus::Guild DiscPPlus::Message::GetGuild(DiscPPlus::Bot bot)
{
    const std::string path = std::string("/api/v6/guilds/" + guildId);
    Guild gld;

    httplib::Client cli("https://discord.com");
    json msg;
    try
    {
        cli.set_default_headers({
            {"Authorization", "Bot " + bot.token}
            });
        auto res = cli.Get((path + "?with_counts=true").c_str());
        if (res) {
            msg = json::parse(std::string(res->body.c_str()));
            std::cout << res->status << '\n';
            std::cout << msg.dump(2) << '\n';
            gld.name = msg["name"];
            gld.id = msg["id"];
            gld.icon = msg["icon"];
            if (!msg["description"].is_null()) {
                gld.desc = msg["description"];
            }
            if (!msg["splash"].is_null()) {
                gld.splash = msg["splash"];
            }
            if (!msg["discovery_splash"].is_null()) {
                gld.discoverySplash = msg["discovery_splash"];
            }
            gld.memCount = msg["approximate_member_count"];
            gld.presenceCount = msg["approximate_presence_count"];

        }
        return gld;
    }
    catch (std::exception& e)
    {
        std::cerr << "Connection failed, error: " << e.what() << '\n';
        return Guild();
    }
    catch (...) {
        std::cerr << "UNKNOWN ERROR OCCURED";
    }
    return gld;
}

// send a embed object
void DiscPPlus::Channel::SendEmbed(DiscPPlus::Embed embed, DiscPPlus::Bot bot) {
    const json payload = embed.payload;
    const std::string channel = id;
    const std::string path = std::string("/api/v6/channels/" + channel + "/messages");

    httplib::Client cli("https://discord.com");

    try
    {
        cli.set_default_headers({
            {"Authorization", "Bot " + bot.token}
            });
        std::cout << channel << '\n';
        auto res = cli.Post(path.c_str(), payload.dump(), "application/json");
        if (res) {
            std::cout << res->status << '\n';
            std::cout << res->body << '\n';
        }
    }
    catch (std::exception& e)
    {
        std::cerr << "Connection failed, error: " << e.what() << '\n';
        return;
    }
    catch (...) {
        std::cerr << "UNKNOWN ERROR OCCURED";
    }
}
// sends a special json to discord with default auth headers
void DiscPPlus::Channel::SendSpecial(json payload, DiscPPlus::Bot bot) {
    const std::string channel = id;
    const std::string path = std::string("/api/v6/channels/" + channel + "/messages");

    //, payload.dump(), "application/json"
//Authorization: Bot ${botToken}
    httplib::Client cli("https://discord.com");

    try
    {
        cli.set_default_headers({
            {"Authorization", "Bot " + bot.token}
            });
        std::cout << channel << '\n';
        auto res = cli.Post(path.c_str(), payload.dump(), "application/json");
        if (res) {
            std::cout << res->status << '\n';
            std::cout << res->body << '\n';
        }
    }
    catch (std::exception& e)
    {
        std::cerr << "Connection failed, error: " << e.what() << '\n';
        return;
    }
    catch (...) {
        std::cerr << "UNKNOWN ERROR OCCURED";
    }
}
// Gets guild a Channel is in
void DiscPPlus::Channel::GetGuild()
{
}
// Bans a member using author id as args
void DiscPPlus::Commands::Ban(std::string authid, DiscPPlus::Bot bot) {
    
}
// Kicks a member using author id as args
void DiscPPlus::Commands::Kick(std::string authid, DiscPPlus::Bot bot, std::string guildid) {
    const std::string path = std::string("/api/v6/guilds/" + guildid + "/members/" + authid);
    json payload;


    httplib::Client cli("https://discord.com");

    try
    {
        payload["reason"] = "";
        cli.set_default_headers({
            {"Authorization", "Bot " + bot.token}
            });
        std::cout << authid << '\n';
        auto res = cli.Delete(path.c_str());
        if (res) {
            std::cout << res->status << '\n';
            std::cout << res->body << '\n';
        }
    }
    catch (std::exception& e)
    {
        std::cerr << "Connection failed, error: " << e.what() << '\n';
        return;
    }
    catch (...) {
        std::cerr << "UNKNOWN ERROR OCCURED";
    }
}
void DiscPPlus::Emoji::from_json(json j)
{
}

// Sends a message from the bot
void DiscPPlus::Channel::Send(std::string msg, DiscPPlus::Bot bot) {
    json payload;
    payload["content"] = msg;
    payload["tts"] = false;
    const std::string channel = id;
    const std::string path = std::string("/api/v6/channels/" + channel + "/messages");

    httplib::Client cli("https://discord.com");

    try
    {
        cli.set_default_headers({
            {"Authorization", "Bot " + bot.token}
            });
        std::cout << channel << '\n';
        auto res = cli.Post(path.c_str(), payload.dump(), "application/json");
        if (res) {
            std::cout << res->status << '\n';
            std::cout << res->body << '\n';
        }
    }
    catch (std::exception& e)
    {
        std::cerr << "Connection failed, error: " << e.what() << '\n';
        return;
    }
    catch (...) {
        std::cerr << "UNKNOWN ERROR OCCURED";
    }

}

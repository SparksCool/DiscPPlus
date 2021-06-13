#define CPPHTTPLIB_OPENSSL_SUPPORT
#include "httplib.h"
#include "json.hpp"
#include "client.h"
#include <iostream>


using DiscPPlus::Commands;
using nlohmann::json;



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

void DiscPPlus::Author::AddRole(std::string role)
{
}

void DiscPPlus::Author::RemoveRole(std::string role)
{
}

bool DiscPPlus::Author::HasPerms(std::string perm)
{
    return false;
}

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
void DiscPPlus::Channel::GetGuild()
{
}

void DiscPPlus::Commands::Ban(std::string authid) {

}
void DiscPPlus::Commands::Kick(std::string authid) {

}
void DiscPPlus::Emoji::from_json(json j)
{
}
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

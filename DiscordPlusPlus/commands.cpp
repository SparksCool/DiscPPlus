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

void DiscPPlus::Channel::SendEmbed(DiscPPlus::Embed embed, DiscPPlus::Bot bot) {
    const json payload = embed.payload;
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

void DiscPPlus::Channel::Send(std::string msg, DiscPPlus::Bot bot) {
    json payload;
    payload["content"] = msg;
    payload["tts"] = false;
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

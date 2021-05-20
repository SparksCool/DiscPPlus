#define CPPHTTPLIB_OPENSSL_SUPPORT
#include "httplib.h"
#include "json.hpp"
#include "Client.h"
#include <iostream>


using DiscPPlus::Commands;
using nlohmann::json;

void DiscPPlus::Commands::SendMsg(std::string msg, std::string channel, DiscPPlus::bot bot) {
	json payload;
	payload["content"] = msg;
    payload["tts"] = false;
    std::string path = std::string("/api/v6/channels/" + channel + "/messages");

        //, payload.dump(), "application/json"
    //Authorization: Bot ${botToken}
    httplib::Client cli("https://discord.com");

    try 
    {
        cli.set_default_headers({
            {"Authorization", "Bot "+bot.token}
        });
        std::cout << channel << '\n';
        auto res = cli.Post(path.c_str() , payload.dump(), "application/json");
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
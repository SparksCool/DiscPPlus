#define CPPHTTPLIB_OPENSSL_SUPPORT
#include "httplib.h"
#include "json.hpp"
#include "Client.h"
#include <iostream>
#include <websocketpp/config/asio_client.hpp>
#include <websocketpp/client.hpp>
#define active true

namespace json = nlohmann;

using websocketpp::lib::placeholders::_1;
using websocketpp::lib::placeholders::_2;
using websocketpp::lib::bind;

typedef websocketpp::config::asio_tls_client::message_type::ptr message_ptr;
typedef websocketpp::lib::shared_ptr<boost::asio::ssl::context> context_ptr;
typedef websocketpp::client<websocketpp::config::asio_tls_client> client;
typedef client::connection_ptr connection_ptr;



// This message handler will be invoked once for each incoming message. It
// prints the message and then sends a copy of the message back to the server.
void on_message(client* c, websocketpp::connection_hdl hdl, message_ptr msg) {
    std::cout << "on_message called with hdl: " << hdl.lock().get()
        << " and message: " << msg->get_payload()
        << std::endl;


    websocketpp::lib::error_code ec;

    c->send(hdl, msg->get_payload(), msg->get_opcode(), ec);
    if (ec) {
        std::cout << "Echo failed because: " << ec.message() << std::endl;
    }
}



std::int64_t hbInterval = 4500;



bool DiscPPlus::Client::establishConnection()
{
    bool result{};
    client c;
    c.set_tls_init_handler([this](websocketpp::connection_hdl) {
        return websocketpp::lib::make_shared<boost::asio::ssl::context>(boost::asio::ssl::context::tlsv1);
    });
    std::string url = "wss://gateway.discord.gg/?v=8&encoding=json";
    json::json const payload = {}; // data we are sending
    try
    {
        // getting gateway
        httplib::Client cli("https://discord.com");

        auto res = cli.Get("/api/v8/gateway");
        if (res) {
            std::cout << res->status << '\n';
            std::cout << res->body << '\n';
        }

        // establishing a WSS connection so we can get opcode 10 and begin the heartbeat

        c.set_access_channels(websocketpp::log::alevel::all);
        c.clear_access_channels(websocketpp::log::alevel::frame_payload);

        c.init_asio();

        c.set_message_handler(bind(&on_message, &c, ::_1, ::_2));

        websocketpp::lib::error_code ec;
        client::connection_ptr con = c.get_connection(url, ec);
        if (ec) {
            std::cout << "could not create connection because: " << ec.message() << std::endl;
            return 0;
        }

        c.connect(con);
        c.run();


    }
    catch (const std::exception& e)
    {
        std::cerr << "Connection failed, error: " << e.what() << '\n';
        result = false;
    }
    result = false;
    




    while (active) {
        std::cout << "loop begin beginning in " << hbInterval << " milliseconds" << "\n";
        std::this_thread::sleep_for(std::chrono::milliseconds(hbInterval));
        std::cout << "loop reset" << "\n";
    }


    return result;
    std::cout << "loop end" << "\n";
}


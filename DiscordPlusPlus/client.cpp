#define CPPHTTPLIB_OPENSSL_SUPPORT
#include "httplib.h"
#include "json.hpp"
#include "client.h"
#include <iostream>
#include <websocketpp/config/asio_client.hpp>
#define active true
using websocketpp::lib::placeholders::_1;
using websocketpp::lib::placeholders::_2;
using websocketpp::lib::bind;
typedef websocketpp::config::asio_tls_client::message_type::ptr message_ptr;
typedef websocketpp::lib::shared_ptr<boost::asio::ssl::context> context_ptr;
typedef websocketpp::client<websocketpp::config::asio_tls_client> client;
typedef client::connection_ptr connection_ptr;
std::string Token = "";
const std::string url = "wss://gateway.discord.gg/?v=6&encoding=json";
DiscPPlus::Bot bot;
nlohmann::json hbAck = nlohmann::json::parse(R"({"op": 1,"d": null})"); // heartbeat
nlohmann::json ID = nlohmann::json::parse("{\"op\": 2,\"d\": {\"token\":\"\", \"properties\": { \"$os\": \"Windows\", \"$browser\": \"discpp\", \"$device\": \"discpp\"}, \"status\": \"dnd\"}}"); // identify packet
unsigned short hbInterval = 41250;
client c;
client cli;
bool go = true;
std::thread sh;

void sendHeartbeat(client* c, websocketpp::connection_hdl hdl, message_ptr msg) {
    while (go) {
        try {
            std::this_thread::sleep_for(std::chrono::milliseconds(hbInterval));
            if(go)
            c->send(hdl, hbAck.dump(), websocketpp::frame::opcode::text);
            std::cout << "heartbeat sent" << "\n";
        }
        catch(...){
            // do nothing
        }
    }
}

// This message handler will be invoked once for each incoming message. It
// prints the message and then sends a copy of the message back to the server.
void on_message(client* c, websocketpp::connection_hdl hdl, message_ptr msg) {
    bot.SetStats(c, hdl, msg, Token);
    nlohmann::json jsg = nlohmann::json::parse(msg->get_payload()); // getting payload sent to us from discord
    short int opcode = jsg["op"]; // opcode recived from payload
    DiscPPlus::Commands Command;
    DiscPPlus::Message message;
    DiscPPlus::Client clint;
    hbAck["d"] = jsg["s"];
    

    std::cout << "on_message called with hdl: " << hdl.lock().get()
        << " and message: " << msg->get_payload()
        << std::endl;
    // a switch case statement to determine what response we should send back
    // depending on the opcode
    switch (opcode) {
        case 10 :
            hbInterval = jsg["d"]["heartbeat_interval"];
            std::cout << "New Hearbeat Interval is: " << hbInterval << std::endl;
            c->send(hdl, ID.dump(), websocketpp::frame::opcode::text);
            sh = std::thread(sendHeartbeat, c, hdl, msg);
            std::cout << "payload: " << hbAck.dump() << " and " << ID.dump() <<" was sent" << "\n";
            break;
        case 11 :
            std::cout << "payload: " << hbAck.dump() << " was sent" << "\n";
            break;
        case 7 :
            go = false;        
            clint.establishConnection(Token);
            break;
        case 0 : 
            if (jsg["t"] == "MESSAGE_CREATE") {
                message.content = jsg["d"]["content"];
                message.channel.id = jsg["d"]["channel_id"];
                message.author.id = jsg["d"]["author"]["id"];
                message.author.name = jsg["d"]["author"]["username"];
                message.author.mention = "<@!" + message.author.id + ">";
                message.author.channel.id = message.author.id;
                message.embed = false; //jsg["d"][];
                message.guildId = jsg["d"]["guild_id"];
                

                Command.OnMsg(message, bot);
            }
            break;
        default :
            break;
    }

    

}
void on_close(client* c, websocketpp::connection_hdl hdl) {
    try {
        // establishing a WSS connection so we can get opcode 10 and begin the heartbeat

        websocketpp::lib::error_code ec;
        client::connection_ptr con = c->get_connection(url, ec);
        std::cout << "con altered" << '\n';



        if (ec) {
            std::cout << "could not create connection because: " << ec.message() << std::endl;
            return;
        }

        std::cout << "Client is attempting connection" << '\n';
        c->connect(con);
        c->get_alog().write(websocketpp::log::alevel::app, "Connecting to " + url);
        std::cout << "Client has connected and is attempting to run" << '\n';
        c->run();
        std::cout << "Client has connected and has ran" << '\n';
    }
    catch (const std::exception& e)
    {
        std::cerr << "Connection failed, error: " << e.what() << '\n';
        return;
    }
}
void DiscPPlus::Client::sendWSReq(nlohmann::json payload="", std::string wsUrl="") {
    try {
        // establishing a WSS connection so we can get opcode 10 and begin the heartbeat

        
        websocketpp::lib::error_code ec;
        client::connection_ptr con = c.get_connection(wsUrl, ec);
        std::cout << "con altered" << '\n';
        


        if (ec) {
            std::cout << "could not create connection because: " << ec.message() << std::endl;
            return;
        }
        if (payload != "") {
            con->send(payload.dump(), websocketpp::frame::opcode::text);
        }

        std::cout << "Client is attempting connection" << '\n';
        c.connect(con);
        c.get_alog().write(websocketpp::log::alevel::app, "Connecting to " + wsUrl);
        std::cout << "Client has connected and is attempting to run" << '\n';
        c.run();
        std::cout << "Client has connected and has ran" << '\n';
    }
    catch (const std::exception& e)
    {
        std::cerr << "Connection failed, error: " << e.what() << '\n';
        return;
    }
} // CLEAN CODE!
void DiscPPlus::Client::sendShardWSReq(nlohmann::json payload, std::string wsUrl) {
    try {
        // establishing a WSS connection so we can get opcode 10 and begin the heartbeat


        websocketpp::lib::error_code ec;
        client::connection_ptr con = cli.get_connection(wsUrl, ec);
        std::cout << "con altered" << '\n';



        if (ec) {
            std::cout << "could not create connection because: " << ec.message() << std::endl;
            return;
        }
        if (payload != "") {
            con->send(payload.dump(), websocketpp::frame::opcode::text);
        }

        std::cout << "Client is attempting connection" << '\n';
        cli.connect(con);
        cli.get_alog().write(websocketpp::log::alevel::app, "Connecting to " + wsUrl);
        std::cout << "Client has connected and is attempting to run" << '\n';
        cli.run();
        std::cout << "Client has connected and has ran" << '\n';
    }
    catch (const std::exception& e)
    {
        std::cerr << "Connection failed, error: " << e.what() << '\n';
        return;
    }
} // CLEAN CODE!
bool DiscPPlus::Client::establishConnection(std::string token)
{
    Token = token;
    ID = nlohmann::json::parse("{\"op\": 2,\"d\": {\"token\":\""+ token +"\", \"properties\": { \"$os\": \"Windows\", \"$browser\": \"discpp\", \"$device\": \"discpp\"}, \"status\": \"dnd\"}}");
    bool result{};
    c.init_asio();
    c.set_tls_init_handler([this](websocketpp::connection_hdl) {
        return websocketpp::lib::make_shared<boost::asio::ssl::context>(boost::asio::ssl::context::tlsv1);
    });
    c.set_access_channels(websocketpp::log::alevel::all);
    c.set_error_channels(websocketpp::log::elevel::all);


    //c.clear_access_channels(websocketpp::log::alevel::frame_payload);


    c.set_message_handler(bind(&on_message, &c, ::_1, ::_2));


    try
    {
        // getting gateway
        httplib::Client cli("https://discord.com");

        auto res = cli.Get("/api/v8/gateway");
        if (res) {
            std::cout << res->status << '\n';
            std::cout << res->body << '\n';
        }
        sendWSReq("", url);


    }
    catch (const std::exception& e)
    {
        std::cerr << "Connection failed, error: " << e.what() << '\n';
        result = false;
    }
    result = false;
    





    return result;
    std::cout << "loop end" << "\n";
}
bool DiscPPlus::Client::establishShardConnection(std::string token, nlohmann::json ID) {

    bool result{};
    client cil;
    cil.init_asio();
    cil.set_tls_init_handler([this](websocketpp::connection_hdl) {
        return websocketpp::lib::make_shared<boost::asio::ssl::context>(boost::asio::ssl::context::tlsv1);
    });
    cil.set_access_channels(websocketpp::log::alevel::all);
    cil.set_error_channels(websocketpp::log::elevel::all);


    //c.clear_access_channels(websocketpp::log::alevel::frame_payload);
    cil.set_message_handler(bind(&on_message, &c, ::_1, ::_2));
    try
    {
        
        sendShardWSReq("", url);
    }
    catch (const std::exception& e)
    {
        std::cerr << "Connection failed, error: " << e.what() << '\n';
        result = false;
    }
    result = false;
    return result;
    std::cout << "loop end" << "\n";
}


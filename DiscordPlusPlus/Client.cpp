#define CPPHTTPLIB_OPENSSL_SUPPORT
#include <boost/beast/core.hpp>
#include <boost/beast/websocket.hpp>
#include <boost/asio/connect.hpp>
#include <boost/asio/ip/tcp.hpp>
#include <cstdlib>
#include "httplib.h"
#include "Client.h"
#include <iostream>
#include <string>


namespace beast = boost::beast;         // from <boost/beast.hpp>
namespace http = beast::http;           // from <boost/beast/http.hpp>
namespace websocket = beast::websocket; // from <boost/beast/websocket.hpp>
namespace net = boost::asio;            // from <boost/asio.hpp>
using tcp = boost::asio::ip::tcp;       // from <boost/asio/ip/tcp.hpp>




bool active = true;
std::int64_t hbInterval = 4500;



bool DiscPPlus::Client::establishConnection()
{


    bool result{};
    while (active) {
        std::cout << "loop begin pinging in " << hbInterval << " milliseconds" << "\n";
        std::this_thread::sleep_for(std::chrono::milliseconds(hbInterval));



        try
        {
            httplib::Client cli("https://discord.com");

            auto res = cli.Get("/api/v8/gateway");
            if (res) {
                std::cout << res->status << '\n';
                std::cout << res->body << '\n';
            }

            auto const payload = ""; // data we are sending
            std::string host = "gateway.discord.gg"; // host we are sending it to
            auto const port = "443"; // port we are sending it on
            net::io_context ioc; // needed for IO
            tcp::resolver resolver(ioc); // resolver?
            websocket::stream<tcp::socket> ws(ioc); // starting a stream i assume
            auto const results = resolver.resolve(host, port); // gets results from resolver
            auto ep = net::connect(ws.next_layer(), results);

            host += ':' + std::to_string(ep.port());
            ws.set_option(websocket::stream_base::decorator(
                [](websocket::request_type& req)
            {
                req.set(http::field::user_agent,
                    std::string(BOOST_BEAST_VERSION_STRING) +
                    " websocket-client-coro");
            }));

            ws.handshake(host, "/?v=8&encoding=json/?v=4");
            ws.write(net::buffer(std::string(payload)));
            beast::flat_buffer buffer2;
            ws.read(buffer2);
            ws.close(websocket::close_code::normal);
            std::cout << beast::make_printable(buffer2.data()) << std::endl;






        }
        catch (const std::exception& e)
        {
            std::cerr << "Connection failed, error: " << e.what() << '\n';
            result = false;
        }
        result = false;
        std::cout << "loop reset" << "\n";
    }


    return result;
    std::cout << "loop end" << "\n";
}


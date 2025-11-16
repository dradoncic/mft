#pragma once
#include <simdjson.h>

#include <boost/asio.hpp>
#include <boost/beast.hpp>
#include <boost/beast/ssl.hpp>
#include <boost/beast/websocket.hpp>
#include <deque>
#include <nlohmann/json.hpp>

#include "iws.h"
#include "subscription/isub.h"

namespace beast = boost::beast;
namespace http = beast::http;
namespace websocket = beast::websocket;
namespace net = boost::asio;
namespace ip = boost::asio::ip;

class BeastWSConnector : public IWSConnector
{
   public:
    BeastWSConnector(boost::asio::io_context& ioc,
                     boost::asio::ssl::context& ssl_ctx);

    void connect(const std::string& host, const std::string& port,
                 const std::vector<SubscriptionRequest>& reqs) override;
    void close() override;
    void send(const std::string& msg) override;

   private:
    void on_resolve(beast::error_code ec,
                    ip::tcp::resolver::results_type results);
    void on_connect(beast::error_code ec);
    void on_ssl_handshake(beast::error_code ec);
    void on_handshake(beast::error_code ec);
    void on_read(beast::error_code ec, size_t bytes_transferred);
    void do_write();

    net::io_context& ioc_;
    net::ssl::context& ssl_ctx_;
    websocket::stream<beast::ssl_stream<ip::tcp::socket>> ws_;
    ip::tcp::resolver resolver_;

    beast::flat_buffer read_buffer_;
    std::string write_buffer_;
    std::deque<std::string> write_queue_;
    bool writing_ = false;

    std::string host_;
    std::string port_;
    std::vector<std::string> products_;
    std::string channel_;
};

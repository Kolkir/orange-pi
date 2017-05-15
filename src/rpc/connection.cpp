#include "connection.h"

#include <boost/bind.hpp>

Connection::pointer Connection::create(boost::asio::io_service& io_service) {
    return pointer(new Connection(io_service));
}

boost::asio::ip::tcp::socket&Connection::get_socket() {
    return socket;
}

void Connection::start() {
    //message = make_daytime_string();

    boost::asio::async_write(socket,
                             boost::asio::buffer(message),
                             boost::bind(&Connection::handle_write,
                                       shared_from_this(),
                                       boost::asio::placeholders::error,
                                       boost::asio::placeholders::bytes_transferred));
}

Connection::Connection(boost::asio::io_service& io_service)
    : socket(io_service) {

}

void Connection::handle_write(const boost::system::error_code&, size_t) {

}

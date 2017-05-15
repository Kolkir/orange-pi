#ifndef CONNECTION_H
#define CONNECTION_H

#include <boost/asio.hpp>

#include <memory>

class Connection : public std::enable_shared_from_this<Connection> {
public:
    typedef std::shared_ptr<Connection> pointer;

    static pointer create(boost::asio::io_service& io_service);

    boost::asio::ip::tcp::socket& get_socket();

    void start();

private:
    Connection(boost::asio::io_service& io_service);

    void handle_write(const boost::system::error_code& /*error*/,
                      size_t /*bytes_transferred*/);

private:
    boost::asio::ip::tcp::socket socket;
    std::string message;
};

#endif // CONNECTION_H

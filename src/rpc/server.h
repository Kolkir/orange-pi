#ifndef SERVER_H
#define SERVER_H

#include "connection.h"

#include <boost/asio.hpp>

class Server {
public:
  Server(boost::asio::io_service& io_service, int port);

private:
  void start_accept();

  void handle_accept(Connection::pointer new_connection,
                     const boost::system::error_code& error);

private:

  boost::asio::ip::tcp::acceptor acceptor;
};

#endif // SERVER_H

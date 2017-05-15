#include "server.h"

#include <boost/asio.hpp>
#include <boost/program_options.hpp>

#include <iostream>

int main(int argc, char* argv[]) {
    namespace po = boost::program_options;
    try {
        po::options_description desc("General options");
        int port;
        desc.add_options()
            ("help,h", "Show help")
            ("port,p", po::value<int>(&port)->required(), "Set the server port");

        po::variables_map vm;
        po::store(po::parse_command_line(argc, argv, desc), vm);

        if (vm.count("help")) {
            std::cout << desc << "\n";
            return false;
        }

        po::notify(vm);

        boost::asio::io_service io_service;
        Server server(io_service, port);
        io_service.run();
    } catch (std::exception& e) {
        std::cerr << e.what() << std::endl;
    }

    return 0;
}

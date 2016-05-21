#include <iostream>
#include <SFML/Network.hpp>

int main()
{
    std::string serverIp("127.0.0.1");

    std::cout << "Enter server's IP address : ";
    std::cin >> serverIp;

    std::cout << "Connecting to server " << serverIp << " on port 22625..." << std::endl;

    sf::TcpSocket socket;

    if(socket.connect(sf::IpAddress(serverIp), 22625, sf::seconds(10.f)) != sf::TcpSocket::Status::Done)
    {
        std::cerr << "Could not connect to server " << serverIp << "." << std::endl;
        return 1;
    }

    std::cout << "Connected." << std::endl;

    sf::Packet packet;
    std::string message("");

    socket.receive(packet);
    packet >> message;
    std::cout << "Message received : \"" << message << "\"." << std::endl;
    std::cout << "Press enter to quit..." << std::endl;

    char c;
    std::cin >> c;

    return 0;
}

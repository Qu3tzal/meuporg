#include <iostream>
#include <SFML/Network.hpp>

int main()
{
    sf::UdpSocket socket;
    if(socket.bind(22625) != sf::UdpSocket::Status::Done)
    {
        std::cerr << "Could not bind on port 22625." << std::endl;
        return 1;
    }

    std::cout << "Waiting for client to connect..." << std::endl;

    sf::Packet packet;
    sf::IpAddress ipAddress;
    short unsigned int port(0);

    socket.receive(packet, ipAddress, port);

    std::cout << "[" << ipAddress.toString() << "] connected." << std::endl;

    sf::Packet answer;
    answer << "HELLO";

    socket.send(answer, ipAddress, port);

    std::cout << "'HELLO' sent." << std::endl;

    return 0;
}

#include <iostream>
#include <SFML/Network.hpp>

int main()
{
    std::string serverIp("127.0.0.1");

    std::cout << "Enter server's IP address : ";
    std::cin >> serverIp;

    std::cout << "Sending message to server " << serverIp << " on port 22625..." << std::endl;

    sf::UdpSocket socket;
    sf::Packet packet;
    packet << "HI";

    socket.send(packet, sf::IpAddress(serverIp), 22625);
    std::cout << "Message sent." << std::endl;

    sf::Packet answer;
    std::string message("");
    sf::IpAddress ip;
    short unsigned int port;

    socket.receive(answer, ip, port);
    answer >> message;
    std::cout << "Message received : \"" << message << "\"." << std::endl;
    std::cout << "Press enter to quit..." << std::endl;

    std::cin.get();
    std::cin.get();

    return 0;
}

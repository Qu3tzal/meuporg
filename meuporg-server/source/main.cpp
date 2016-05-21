#include <iostream>
#include <SFML/Network.hpp>

int main()
{
    sf::TcpListener listener;
    if(listener.listen(22625) != sf::TcpListener::Status::Done)
    {
        std::cerr << "Could not listen to port 22625." << std::endl;
        return 1;
    }

    std::cout << "Waiting for clients on port 22625..." << std::endl;

    sf::TcpSocket socket;
    listener.accept(socket);

    std::cout << "[" << socket.getRemoteAddress().toString() << "] connected." << std::endl;
    std::cout << "> ";

    std::string message;
    std::getline(std::cin, message);

    sf::Packet packet;
    packet << message;

    socket.send(packet);
    socket.disconnect();

    return 0;
}

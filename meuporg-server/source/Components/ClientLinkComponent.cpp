#include "ClientLinkComponent.hpp"

ClientLinkComponent::ClientLinkComponent(unsigned int ownerId)
     : kantan::Component(std::string("ClientLink"), ownerId)
     , client(nullptr)
     , dbid(-1)
{}

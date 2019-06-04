#include "ClientLinkComponent.hpp"

ClientLinkComponent::ClientLinkComponent(unsigned long long ownerId)
     : kantan::Component(std::string("ClientLink"), ownerId)
     , client(nullptr)
     , dbid(-1)
{}

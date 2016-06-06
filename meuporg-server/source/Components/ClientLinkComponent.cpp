#include "ClientLinkComponent.hpp"

ClientLinkComponent::ClientLinkComponent(std::size_t ownerId)
     : kantan::Component(std::string("ClientLink"), ownerId)
     , client(nullptr)
{}

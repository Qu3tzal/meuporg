#include "BonusComponent.hpp"

BonusComponent::BonusComponent(std::size_t ownerId)
     : kantan::Component(std::string("BasicStats"), ownerId)
{
    effect = [](BasicStatsComponent* bsc){
        // Do nothing by default.
    };
}

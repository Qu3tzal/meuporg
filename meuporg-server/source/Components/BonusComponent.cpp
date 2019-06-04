#include "BonusComponent.hpp"

BonusComponent::BonusComponent(unsigned int ownerId)
     : kantan::Component(std::string("BasicStats"), ownerId)
{
    effect = [](BasicStatsComponent* bsc){
        // Do nothing by default.
    };
}

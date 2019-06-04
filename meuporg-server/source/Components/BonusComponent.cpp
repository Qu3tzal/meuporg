#include "BonusComponent.hpp"

BonusComponent::BonusComponent(unsigned long long ownerId)
     : kantan::Component(std::string("BasicStats"), ownerId)
{
    effect = [](BasicStatsComponent* bsc){
        // Do nothing by default.
    };
}

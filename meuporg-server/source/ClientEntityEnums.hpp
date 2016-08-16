#ifndef CLIENTENTITYENUMS_HPP_INCLUDED
#define CLIENTENTITYENUMS_HPP_INCLUDED

namespace ClientSide
{
    enum EntityType
    {
        ENTITYTYPE_PLAYER,
        ENTITYTYPE_NPC,
        ENTITYTYPE_MONSTER
    };

    enum PlayerStates
    {
        PLAYERSTATE_IDLE,
        PLAYERSTATE_WALKING
    };

    enum NPCStates
    {
        NPCSTATE_IDLE,
        NPCSTATE_WALKING
    };

    enum MonsterStates
    {
        MONSTERSTATE_IDLE,
        MONSTERSTATE_WALKING
    };
};

#endif // CLIENTENTITYENUMS_HPP_INCLUDED

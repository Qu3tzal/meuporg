#ifndef CLIENTENTITYENUMS_HPP_INCLUDED
#define CLIENTENTITYENUMS_HPP_INCLUDED

namespace ClientSide
{
    enum EntityType
    {
        ENTITYTYPE_PLAYER,
        ENTITYTYPE_NPC,
        ENTITYTYPE_MONSTER,
        ENTITYTYPE_BULLET
    };

    enum PlayerStates
    {
        PLAYERSTATE_IDLE,
        PLAYERSTATE_WALKING,
        PLAYERSTATE_DEAD
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

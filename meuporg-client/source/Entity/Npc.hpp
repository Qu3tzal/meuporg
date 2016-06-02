#ifndef NPC_HPP
#define NPC_HPP

#include "Entity.hpp"

class Npc : public Entity
{
    public:
        Npc(kantan::TextureHolder* textures);
        virtual ~Npc();

    protected:

    private:
};

#endif // NPC_HPP

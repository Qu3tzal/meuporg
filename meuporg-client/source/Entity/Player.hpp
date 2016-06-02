#ifndef PLAYER_HPP
#define PLAYER_HPP

#include "Entity.hpp"

class Player : public Entity
{
    public:
        Player(kantan::TextureHolder* textures);
        virtual ~Player();

    protected:

    private:
};

#endif // PLAYER_HPP

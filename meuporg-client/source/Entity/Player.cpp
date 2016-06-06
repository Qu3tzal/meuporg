#include "Player.hpp"

Player::Player(kantan::TextureHolder* textures) : Entity(0, "Player", textures)
{

}

Player::~Player()
{
    //dtor
}

void Player::init()
{
    textures->load(1, "assets/saitama_spritesheet.png");
    sprite.setTexture(textures->get(1));

    // Move down animation
    a_MoveDown.addTextRect(sf::IntRect(16, 8, 31, 48));
    a_MoveDown.addTextRect(sf::IntRect(81, 9, 30, 47));
    a_MoveDown.addTextRect(sf::IntRect(144, 8, 31, 48));
    a_MoveDown.addTextRect(sf::IntRect(208, 9, 30, 47));
    a_MoveDown.setLoop(true);


    // Move up animation
    a_MoveUp.addTextRect(sf::IntRect(16, 200, 31, 48));
    a_MoveUp.addTextRect(sf::IntRect(83, 201, 26, 47));
    a_MoveUp.addTextRect(sf::IntRect(144, 200, 31, 48));
    a_MoveUp.addTextRect(sf::IntRect(210, 201, 26, 47));
    a_MoveUp.setLoop(true);

    // Move Left animation
    a_MoveLeft.addTextRect(sf::IntRect(22, 72, 22, 48));
    a_MoveLeft.addTextRect(sf::IntRect(85, 73, 27, 47));
    a_MoveLeft.addTextRect(sf::IntRect(150, 72, 22, 48));
    a_MoveLeft.addTextRect(sf::IntRect(212, 73, 27, 47));
    a_MoveLeft.setLoop(true);

    // Move Right animation
    a_MoveRight.addTextRect(sf::IntRect(20, 136, 22, 48));
    a_MoveRight.addTextRect(sf::IntRect(80, 137, 27, 47));
    a_MoveRight.addTextRect(sf::IntRect(148, 136, 22, 48));
    a_MoveRight.addTextRect(sf::IntRect(209, 137, 27, 47));
    a_MoveRight.setLoop(true);
}

void Player::update(sf::Time dt)
{

}

void Player::draw(sf::RenderTarget& window, sf::RenderStates states) const
{
    states.transform *= getTransform();
    window.draw(sprite, states);
}

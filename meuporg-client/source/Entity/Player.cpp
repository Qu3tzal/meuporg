#include "Player.hpp"

Player::Player(kantan::TextureHolder* textures, kantan::FontHolder* fonts, std::string name, unsigned int id)
    : Entity(id, name, Entity::Type::PLAYER, textures, fonts)
    , direction(Direction::DOWN)
    , nameText(name, fonts)
{
    std::cout << "name : " << name << std::endl;
}

Player::~Player()
{
    //dtor
}

void Player::init()
{

    sprite.setTexture(textures->get(1));

    // Move down animation
    a_MoveDown.addTextRect(sf::IntRect(16, 8, 31, 48));
    a_MoveDown.addTextRect(sf::IntRect(81, 9, 30, 47));
    a_MoveDown.addTextRect(sf::IntRect(144, 8, 31, 48));
    a_MoveDown.addTextRect(sf::IntRect(208, 9, 30, 47));
    a_MoveDown.setLoop(true);
    a_MoveDown.setSpeed(12);

    // Move up animation
    a_MoveUp.addTextRect(sf::IntRect(16, 200, 31, 48));
    a_MoveUp.addTextRect(sf::IntRect(83, 201, 26, 47));
    a_MoveUp.addTextRect(sf::IntRect(144, 200, 31, 48));
    a_MoveUp.addTextRect(sf::IntRect(210, 201, 26, 47));
    a_MoveUp.setLoop(true);
    a_MoveUp.setSpeed(12);

    // Move Left animation
    a_MoveLeft.addTextRect(sf::IntRect(22, 72, 22, 48));
    a_MoveLeft.addTextRect(sf::IntRect(85, 73, 27, 47));
    a_MoveLeft.addTextRect(sf::IntRect(150, 72, 22, 48));
    a_MoveLeft.addTextRect(sf::IntRect(212, 73, 27, 47));
    a_MoveLeft.setLoop(true);
    a_MoveLeft.setSpeed(12);

    // Move Right animation
    a_MoveRight.addTextRect(sf::IntRect(20, 136, 22, 48));
    a_MoveRight.addTextRect(sf::IntRect(80, 137, 27, 47));
    a_MoveRight.addTextRect(sf::IntRect(148, 136, 22, 48));
    a_MoveRight.addTextRect(sf::IntRect(209, 137, 27, 47));
    a_MoveRight.setLoop(true);
    a_MoveRight.setSpeed(12);
}

void Player::update(sf::Time dt)
{
    Entity::update(dt);

    setDirection();
    switch(direction)
    {
        case Direction::UP :
            if(state == State::WALKING)
            {
                a_MoveUp.update(dt);
            }
            else
            {
                a_MoveUp.reset();
            }

            a_MoveDown.reset();
            a_MoveLeft.reset();
            a_MoveRight.reset();

            sprite.setTextureRect(a_MoveUp.getFrame().first);
            break;
        case Direction::DOWN :
            if(state == State::WALKING)
            {
                a_MoveDown.update(dt);
            }
            else
            {
                a_MoveDown.reset();
            }

            a_MoveUp.reset();
            a_MoveLeft.reset();
            a_MoveRight.reset();

            sprite.setTextureRect(a_MoveDown.getFrame().first);
            break;
        case Direction::LEFT :
            if(state == State::WALKING)
            {
                a_MoveLeft.update(dt);
            }
            else
            {
                a_MoveLeft.reset();
            }
            a_MoveUp.reset();
            a_MoveDown.reset();
            a_MoveRight.reset();

            sprite.setTextureRect(a_MoveLeft.getFrame().first);
            break;
        case Direction::RIGHT :
            if(state == State::WALKING)
            {
                 a_MoveRight.update(dt);
            }
            else
            {
                a_MoveRight.reset();
            }
            a_MoveUp.reset();
            a_MoveLeft.reset();
            a_MoveDown.reset();

            sprite.setTextureRect(a_MoveRight.getFrame().first);
            break;
        default:
            sprite.setTextureRect(a_MoveDown.getFrame().first);
            break;
    }
    //centerOrigin(nameText);
    nameText.setPosition(sprite.getGlobalBounds().width / 2, -30);
}

void Player::setDirection()
{
    if(velocity == sf::Vector2f(0.f, 0.f))
        return;

    velocityNormalized = Entity::normalize(velocity);

    if(std::abs(velocityNormalized.x) > std::abs(velocityNormalized.y))
    {
        if(velocityNormalized.x > 0)
        {
            direction = Direction::RIGHT;
        }
        else
        {
            direction = Direction::LEFT;
        }
    }
    else
    {
        if(velocityNormalized.y > 0 )
        {
            direction = Direction::DOWN;
        }
        else
        {
            direction = Direction::UP;
        }
    }

}

void Player::setState(State state)
{
    this->state = state;
}

void Player::draw(sf::RenderTarget& window, sf::RenderStates states) const
{
    states.transform *= getTransform();
    window.draw(sprite, states);
    window.draw(nameText, states);
}

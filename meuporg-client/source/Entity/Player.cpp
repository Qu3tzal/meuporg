#include "Player.hpp"

Player::Player(kantan::TextureHolder* textures, kantan::FontHolder* fonts, std::string name, unsigned int id)
    : Entity(id, name, Entity::Type::PLAYER, textures, fonts)
    , direction(Direction::DOWN)
    , nameText(name, fonts)
{
    setProperty("HpMax", 1);
    setProperty("Hp", 1);
    setProperty("XpNeeded", 1);
    setProperty("Xp", 0.5);
    setProperty("Level", 1);
    setProperty("Strengh", 0);
    setProperty("Agility", 0);
    setProperty("Resist", 0);
}

Player::~Player()
{
    //dtor
}

void Player::init()
{

    sprite.setTexture(textures->get(ResourceId::ONE_PUNCH_MAN_TEXTURE));

    // Move down animation
    a_MoveDown.addTextRect(sf::IntRect(16, 8, 31, 48));
    a_MoveDown.addTextRect(sf::IntRect(81, 9, 30, 47), sf::Vector2f(-1.f, -1.f));
    a_MoveDown.addTextRect(sf::IntRect(144, 8, 31, 48));
    a_MoveDown.addTextRect(sf::IntRect(208, 9, 30, 47), sf::Vector2f(0.f, -1.f));
    a_MoveDown.setLoop(true);
    a_MoveDown.setSpeed(12);

    // Move up animation
    a_MoveUp.addTextRect(sf::IntRect(16, 200, 31, 48));
    a_MoveUp.addTextRect(sf::IntRect(83, 201, 26, 47), sf::Vector2f( -3.f, -1.f));
    a_MoveUp.addTextRect(sf::IntRect(144, 200, 31, 48));
    a_MoveUp.addTextRect(sf::IntRect(210, 201, 26, 47), sf::Vector2f( -3.f, -1.f));
    a_MoveUp.setLoop(true);
    a_MoveUp.setSpeed(12);

    // Move Left animation
    a_MoveLeft.addTextRect(sf::IntRect(22, 72, 22, 48));
    a_MoveLeft.addTextRect(sf::IntRect(85, 73, 27, 47), sf::Vector2f(0.f, -1.f));
    a_MoveLeft.addTextRect(sf::IntRect(150, 72, 22, 48));
    a_MoveLeft.addTextRect(sf::IntRect(212, 73, 27, 47), sf::Vector2f(0.f, -1.f));
    a_MoveLeft.setLoop(true);
    a_MoveLeft.setSpeed(12);

    // Move Right animation
    a_MoveRight.addTextRect(sf::IntRect(20, 136, 22, 48), sf::Vector2f(-5.f, 0.f));
    a_MoveRight.addTextRect(sf::IntRect(80, 137, 27, 47), sf::Vector2f(0.f, -1.f));
    a_MoveRight.addTextRect(sf::IntRect(148, 136, 22, 48), sf::Vector2f(-4.f, 0.f));
    a_MoveRight.addTextRect(sf::IntRect(209, 137, 27, 47), sf::Vector2f(0.f, -1.f));
    a_MoveRight.setLoop(true);
    a_MoveRight.setSpeed(12);

}

void Player::update(sf::Time dt)
{
    //Entity::update(dt);
    setXpneeded();
    sprite.setOrigin(sf::Vector2f(0.f, 0.f));
    setDirection();
    if(state != State::DEAD)
    {
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
            sprite.setOrigin(a_MoveUp.getFrame().second);
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
            sprite.setOrigin(a_MoveDown.getFrame().second);
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
            sprite.setOrigin(a_MoveLeft.getFrame().second);
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
            sprite.setOrigin(a_MoveRight.getFrame().second);
            break;
        default:
            sprite.setTextureRect(a_MoveDown.getFrame().first);
            sprite.setOrigin(a_MoveDown.getFrame().second);
            break;
        }
    }
    else
    {
        sprite.setTexture(textures->get(ResourceId::GRAVE));
    }

    //centerOrigin(nameText);
    nameText.setPosition(sprite.getGlobalBounds().width / 2 - sprite.getOrigin().x, - (nameText.getheight()) - sprite.getOrigin().y);
    nameText.setHealth(getProperty("Hp"),getProperty("HpMax"));

    for(auto i = damagesText.begin() ; i != damagesText.end();)
    {
        if(i->getColor().a > 1)
        {
            i->setColor(sf::Color(i->getColor().r, i->getColor().g, i->getColor().b, i->getColor().a - 2));
            i->setPosition(- (i->getGlobalBounds().width + 5 ), i->getPosition().y - 1);
            i++;
        }
        else
        {
            damagesText.erase(i);
        }
    }
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

void Player::setXpneeded()
{
    setProperty("XpNeeded", 100);
}

void Player::setState(State state)
{
    this->state = state;
}

void Player::calculatePrecision(sf::Vector2f vect)
{
    //std::cout << distEucli(vect, getPosition()) << std::endl;
}

 void Player::setProperty(std::string name, float value)
 {
     if(name == "Hp")
     {
         float health = m_properties[name];
         if(health != value)
         {

             sf::Text text;
             text.setFont(fonts->get(ResourceId::KENPIXEL));
             text.setCharacterSize(12);


            if(value > health)
            {
                text.setColor(sf::Color(0, 255, 0, 255));
                std::stringstream ss;
                float nb = value - health;
                ss << "+ " << nb;
                text.setString(ss.str());
            }
            else
            {
                text.setColor(sf::Color(255, 0, 0, 255));
                std::stringstream ss;
                float nb = health - value;
                ss << "- " << nb;
                text.setString(ss.str());
            }
            text.setPosition(- (text.getGlobalBounds().width + 5 ), sprite.getGlobalBounds().height / 2);
            damagesText.push_back(text);

         }
     }
    m_properties[name] = value;
 }

float Player::getProperty(std::string name)
{
    return m_properties[name];
}

void Player::draw(sf::RenderTarget& window, sf::RenderStates states) const
{
    states.transform *= getTransform();
    window.draw(sprite, states);
    window.draw(nameText, states);
    for(sf::Text text : damagesText)
        window.draw(text, states);
}

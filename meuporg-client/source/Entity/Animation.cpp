#include "Animation.hpp"

/** Ctor. */
Animation::Animation()
    : m_frame(0)
    , m_elapsed(sf::Time::Zero)
    , m_loop(true)
{}

/** Texture. */
void Animation::addTextRect(sf::IntRect subrect, sf::Vector2f offset)
{
    m_frames.push_back(std::pair<sf::IntRect, sf::Vector2f>(subrect, offset));
}

/** Timing. */
void Animation::setSpeed(sf::Uint64 FPS)
{
    m_interval = sf::seconds(1.f / (float)(FPS));
}

std::size_t Animation::length() const
{
    return m_frames.size();
}

sf::Time Animation::timeLength() const
{
    return m_interval * (float)(m_frames.size());
}

void Animation::setLoop(bool flag)
{
    m_loop = flag;
}

/** Management. */
void Animation::reset()
{
    m_frame = 0;
    m_elapsed = sf::Time::Zero;
}

void Animation::erase(std::size_t frameid)
{
    if(frameid > 0 && frameid < m_frames.size())
    {
        std::vector<std::pair<sf::IntRect, sf::Vector2f>>::iterator itr = m_frames.begin();
        std::advance(itr, frameid);
        m_frames.erase(itr);
    }
}

void Animation::update(sf::Time dt)
{
    m_elapsed += dt;

    if(m_elapsed >= m_interval)
    {
        m_elapsed = sf::Time::Zero;
        nextFrame();
    }
}

std::pair<sf::IntRect, sf::Vector2f> Animation::getFrame() const
{
    return m_frames.at(m_frame);
}

void Animation::nextFrame()
{
    if(m_frame == m_frames.size() - 1)
    {
        if(m_loop)
            m_frame = 0;
    }
    else
    {
        ++m_frame;
    }
}

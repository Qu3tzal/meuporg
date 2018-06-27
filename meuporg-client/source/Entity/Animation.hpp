#ifndef ANIMATION_HPP
#define ANIMATION_HPP

#include <SFML/Graphics.hpp>

/**
    Animation class.
**/
class Animation
{
    public:
        // Ctor.
        Animation();

        /** Texture. */
        // Adds a text rect to the animation.
        void addTextRect(sf::IntRect subrect, sf::Vector2f offset = sf::Vector2f(0.f, 0.f));

        /** Timing. */
        // Sets the speed (in number of frames per second).
        void setSpeed(sf::Uint64 FPS);

        // Returns the number of frames.
        std::size_t length() const;

        // Returns the time, in seconds, of the animation.
        sf::Time timeLength() const;

        // Sets the animation loop.
        void setLoop(bool flag);

        /** Management. */
        // Resets the animation.
        void reset();

        // Erases the frame.
        void erase(std::size_t frameid);

        // Updates the current frame depending on the time.
        void update(sf::Time dt);

        // Returns the current frame data.
        std::pair<sf::IntRect, sf::Vector2f> getFrame() const;

    protected:
        // Goes to the next frame.
        void nextFrame();

    protected:
        // Frames.
        std::vector<std::pair<sf::IntRect, sf::Vector2f>> m_frames;
        std::size_t m_frame;

        // Time.
        sf::Time m_interval, m_elapsed;

        // Flag.
        bool m_loop;
};

#endif // ANIMATION_H

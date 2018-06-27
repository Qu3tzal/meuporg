#include "Event.hpp"

namespace kantan
{
    /// Ctor/Dtor.
    EventData::EventData()
    {
    }

    EventData::~EventData()
    {
    }

    /// Ctor/dtor.
    Event::Event(sf::Uint64 eventType)
        : m_type(eventType)
        , m_data(nullptr)
    {
    }

    Event::~Event()
    {
        if(m_data != nullptr)
            delete m_data;
    }

    /// Event type.
    sf::Uint64 Event::getEventType()
    {
        return m_type;
    }

    /// pollEvent function.
    bool pollEvent(Event& event, std::queue<Event*>& eventQueue)
    {
        if(eventQueue.empty())
        {
            event = Event(0);
            return false;
        }

        event = (*eventQueue.front());
        eventQueue.pop();
        return !eventQueue.empty();
    }

    // Binds the event data pointer.
    void Event::bindEventData(EventData* data)
    {
        m_data = data;
    }
} // namespace kantan.

#ifndef KANTAN_EVENT
#define KANTAN_EVENT

#include <queue>

namespace kantan
{
    /**
        EventData class.
    **/
    class EventData
    {
        public:
            EventData();
            virtual ~EventData();
    };

    /**
        Event class.
    **/
    class Event
    {
        public:
            // Ctor/dtor.
            Event(unsigned int eventType);
            ~Event();

            // Event type.
            unsigned int getEventType();

            // Event data.
            template<typename T>
            T* getEventData();
            void bindEventData(EventData* data);

        protected:
            // Event type.
            unsigned int m_type;

            // Event data.
            EventData* m_data;
    };

    /**
        pollEvent function.
        Polls an event out a std::queue, stick it in the first argument reference and returns true if there is more event to process.
    **/
    bool pollEvent(Event& event, std::queue<Event*>& eventQueue);

    // Returns the event data pointer.
    template<typename T>
    T* Event::getEventData()
    {
        if(m_data)
            return static_cast<T*>(m_data);
        else
            return nullptr;
    }
} // namespace kantan.

#endif // KANTAN_EVENT

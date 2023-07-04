#ifndef TRADUNGEON_EVENT_H
#define TRADUNGEON_EVENT_H

#include <unordered_map>
#include <functional>
#include <memory>

namespace tradungeon
{

// Forward declaration for EventCallbackHandle.
template<typename T>
class Event;

// An RAII style class that removes an event callback at destruction.
template<typename T>
class EventCallbackHandle
{
public:
    EventCallbackHandle(Event<T>* event, int callback_id)
        : m_event(event), m_callback_id(callback_id)
    {}

    ~EventCallbackHandle()
    {
        removeFromEvent();
    }

    void removeFromEvent()
    {
        if (!m_is_removed)
        {
            m_is_removed = true;
            m_event->removeCallback(m_callback_id);
        }
    }

private:
    Event<T>* m_event;
    int m_callback_id;
    bool m_is_removed = false;
};

template<typename T>
using EventCallback = std::function<void(T)>;

template<typename EventInfo>
class Event
{
public:
    // Attach a callback to this event and return an RAII style callback handle.
    // This handle will remove itself from this event on destruction.
    // You can also manually remove callback by calling removeFromEvent().
    //
    // Since the return type usually gets really messy (see the example below!),
    // consider using std::any to store the return value.
    // This will work for most of the case where the callback's lifetime is identical
    // to that of the parent object (the one who created this callback function).
    // 
    // An example typename of return type for Event<std::shared_ptr<SomeBaseClass>> is
    // std::shared_ptr<EventCallbackHandle<std::shared_ptr<SomePolymorphicBaseclass>>>.
    // That is horrible...
    std::shared_ptr<EventCallbackHandle<EventInfo>> addCallback(EventCallback<EventInfo>&& callback)
    {
        auto callback_id = m_next_callback_id++;
        m_callbacks.insert({callback_id, std::move(callback)});

        return std::make_shared<EventCallbackHandle<EventInfo>>(this, callback_id);
    }

    void removeCallback(int callback_id)
    {
        m_callbacks.erase(callback_id);
    }

    void clearCallbacks()
    {
        m_callbacks.clear();
    }

    void signal(EventInfo info)
    {
        for (auto& [id, callback] : m_callbacks)
        {
            callback(info);
        }
    }

private:
    int m_next_callback_id = 0;
    std::unordered_map<int, EventCallback<EventInfo>> m_callbacks;
};

// Specialization for events with no argument.
// Without specialization, Event<void> generates following member function:
//
//    void Event<void>::signal(void info) { /* invoke callbacks */ }
//
// This leads to compiler error because void cannot be used as parameter type.
template<>
class Event<void>
{
public:
    std::shared_ptr<EventCallbackHandle<void>> addCallback(EventCallback<void>&& callback)
    {
        auto callback_id = m_next_callback_id++;
        m_callbacks.insert({callback_id, std::move(callback)});

        return std::make_shared<EventCallbackHandle<void>>(this, callback_id);
    }

    void removeCallback(int callback_id)
    {
        m_callbacks.erase(callback_id);
    }

    void clearCallbacks()
    {
        m_callbacks.clear();
    }

    void signal()
    {
        for (auto& [id, callback] : m_callbacks)
        {
            callback();
        }
    }

private:
    int m_next_callback_id = 0;
    std::unordered_map<int, EventCallback<void>> m_callbacks;
};

} // namespace tradungeon
#endif

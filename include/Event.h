#ifndef TRADUNGEON_EVENT_H
#define TRADUNGEON_EVENT_H

#include <unordered_map>
#include <functional>

namespace tradungeon
{

template<typename T>
using EventCallback = std::function<void(T)>;

template<typename EventInfo>
class Event
{
public:
    int addCallback(EventCallback<EventInfo>&& callback)
    {
        auto callback_id = m_next_callback_id++;
        m_callbacks.insert({callback_id, std::move(callback)});

        return callback_id;
    }

    void removeCallback(int callback_id)
    {
        m_callbacks.erase(callback_id);
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
    int addCallback(EventCallback<void>&& callback)
    {
        auto callback_id = m_next_callback_id++;
        m_callbacks.insert({callback_id, std::move(callback)});

        return callback_id;
    }

    void removeCallback(int callback_id)
    {
        m_callbacks.erase(callback_id);
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

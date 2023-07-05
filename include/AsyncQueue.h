#ifndef TRADUNGEON_ASYNC_QUEUE_H
#define TRADUNGEON_ASYNC_QUEUE_H

#include <queue>
#include <mutex>
#include <optional>

namespace tradungeon
{

template<typename T>
class AsyncQueue
{
public:
    void push(const T& value)
    {
        auto lg = std::lock_guard(m_mutex);
        m_queue.push(value);
    }

    void push(T&& value)
    {
        auto lg = std::lock_guard(m_mutex);
        m_queue.push(std::move(value));
    }

    std::optional<T> pop()
    {
        auto lg = std::lock_guard(m_mutex);
        if (m_queue.empty())
        {
            return {};
        }
        else
        {
            auto value = std::move(m_queue.front());
            m_queue.pop();

            return {std::move(value)};
        }
    }

private:
    std::queue<T> m_queue;
    std::mutex m_mutex;
};

} // namespace tradungeon

#endif

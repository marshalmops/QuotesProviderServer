#ifndef THREADEDQUEUE_H
#define THREADEDQUEUE_H

#include <mutex>
#include <memory>
#include <queue>

template<class T>
class ThreadedQueue
{
public:
    ThreadedQueue()
    {
    
    }
    
    void pushItem(std::unique_ptr<T> &&item)
    {
        std::lock_guard<std::mutex> lock(m_backMutex);
    
        m_items.push(item.release());
    }
    
    std::unique_ptr<T> takeItem()
    {
        std::lock_guard<std::mutex> lock(m_frontMutex);
    
        if (m_items.empty()) return std::unique_ptr<T>(nullptr);
    
        auto elemToGive = std::unique_ptr<T>(m_items.front());
    
        m_items.pop();
    
        return std::move(elemToGive);
    }
    

private:
    std::mutex m_frontMutex;
    std::mutex m_backMutex;

    std::queue<T*> m_items;
};

#endif // THREADEDQUEUE_H

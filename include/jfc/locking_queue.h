// © 2019 Joseph Cameron - All Rights Reserved

#ifndef JFC_MEMORY_LOCKING_QUEUE_H
#define JFC_MEMORY_LOCKING_QUEUE_H

#include <queue>
#include <mutex>

namespace jfc 
{
    /// \brief Thread friendly [locking] queue.
    ///
    /// \detailed Allows concurrent processing of items retrieved from the queue.
    /// queue access however is locking: threads will wait when pushing and or popping.
    ///
    /// \todo write/find a lockless solution and deprecate this one.
    template <typename item_type>
    class locking_queue
    {
        std::mutex m_mutex;
        
        std::queue<item_type> m_queue;
        
    public:
        //! adds a new item to the back of the queue.
        void push(item_type &&item)
        {
            std::lock_guard<std::mutex> lock(m_mutex);
            
            m_queue.push(std::forward<item_type>(item));
        }
        
        //! if size > 0, assigns front to out, pops the front and returns true. otherwise returns false.
        bool pop(item_type &out)
        {
            std::lock_guard<std::mutex> lock(m_mutex);
            
            if (!m_queue.empty())
            {
                out = std::move(m_queue.front());
                
                m_queue.pop();
                
                return true;
            }
            
            return false;
        }
    };
}

#endif


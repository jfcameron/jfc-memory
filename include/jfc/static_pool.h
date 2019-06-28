// © 2019 Joseph Cameron - All Rights Reserved

#ifndef JFC_MEMORY_STATIC_POOL_H
#define JFC_MEMORY_STATIC_POOL_H

#include <array>
#include <functional>
#include <memory>

//TODO: should the pool initialize all up front (as does now) or should it init as needed with option to prealloc? It should init as neede with a preallocation option like stl's vector.

namespace jfc 
{
    /// \brief Object pool of a fixed pool_size. 
    ///
    /// \detailed When get is called, an object with
    /// a reference count of 1 (unused outside the pool) is returned. If
    /// no unused objects exist, a nullptr is returned.
    template<typename value_type, const size_t pool_size> 
    class static_pool final
    {
    public:
        using value_pointer_type = std::shared_ptr<value_type>;
        using collection_type = std::array<value_pointer_type, pool_size>;

    private:
        const collection_type m_Pool;
        
    public:
        //! Try to get an object from the pool, will be null if all objects are in use
        value_pointer_type get() const 
        {
            for (const auto &item : m_Pool) if (item.use_count() == 1) return item;
            
            return {};
        }
        
        static_pool &operator=(const static_pool &) = delete;
        static_pool &operator=(static_pool &&) = default;
    
        static_pool(const std::function<value_type()> &aItemInitializer /*= [](){return T();}*/)
        : m_Pool([this, &aItemInitializer]()
        {
            collection_type pool;

            for (decltype(pool_size) i = 0; i < pool_size; ++i) pool[i] = std::make_shared<value_type>(aItemInitializer());

            return pool;
        }())
        {}  

        static_pool(const static_pool&) = delete;
        static_pool(static_pool&&) = default;
        ~static_pool() = default;
    };
}

#endif

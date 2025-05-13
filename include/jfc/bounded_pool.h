// © Joseph Cameron - All Rights Reserved

#ifndef JFC_BOUNDED_POOL_H
#define JFC_BOUNDED_POOL_H

#include <jfc/dynamic_pool.h>

namespace jfc {
    /// \brief a dynamic pool that will grow to a user-defined limit
    ///
    template<typename value_type_param> class bounded_pool final {
        dynamic_pool<value_type_param> m_DynamicPool;

    public:
        using initializer_type = typename decltype(m_DynamicPool)::initializer_type;
        using pool_type = typename decltype(m_DynamicPool)::pool_type;
        using size_type = typename decltype(m_DynamicPool)::size_type;
        using value_ptr_type = typename decltype(m_DynamicPool)::value_ptr_type;
        using value_type = typename decltype(m_DynamicPool)::value_type;

        //! Get an object from the pool
        [[nodiscard]] value_ptr_type get() const { 
            return m_DynamicPool.size() < m_SizeLimit ? m_DynamicPool.get() : nullptr; 
        }

        //! get number of objects in the pool
        [[nodiscard]] size_type size() const { return m_DynamicPool.size(); }

        //! check whether or not the pool has grown to its limit
        [[nodiscard]] bool full() const { return m_DynamicPool.size() >= m_SizeLimit; }

        //! empties the pool
        void clear() { m_DynamicPool.clear(); }

        //! removes any objects from the pool that are not being used outside of the pool
        void trim() { m_DynamicPool.trim(); }

        //! support move semantics
        bounded_pool &operator=(bounded_pool &&) = default;
        //! support move semantics
        bounded_pool(bounded_pool &&) = default;

        //! construct a pool, by default the object initializer uses the object's default constructor    
        bounded_pool(const size_type aSizeLimit,
            const initializer_type &aObjectInitializer = [](){ return value_type(); })
        : m_SizeLimit(aSizeLimit)
        , m_DynamicPool(aObjectInitializer)
        {}
        
        ~bounded_pool() = default;

    private:
        size_type m_SizeLimit;
    };
}

#endif


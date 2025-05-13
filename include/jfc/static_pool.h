// © Joseph Cameron - All Rights Reserved

#ifndef JFC_STATIC_POOL_H
#define JFC_STATIC_POOL_H

#include <array>
#include <functional>
#include <memory>

namespace jfc {
    /// \brief Object pool with a fixed size, objects in the pool are initialized at construction time
    ///
    template<typename value_type_param, const size_t pool_size> 
    class static_pool final {
    public:
        using size_type = decltype(pool_size);
        using value_type = value_type_param;
        using value_pointer_type = std::shared_ptr<value_type>;
        using collection_type = std::array<value_pointer_type, pool_size>;

    public:
        //! Try to get an object from the pool, returns a nullptr if all objects are in use
        value_pointer_type get() const {
            for (const auto &item : m_Pool) if (item.use_count() == 1) return item;
            return {};
        }

        //! check the size of the pool
        [[nodiscard]] size_type size() const { return pool_size; }
        
        //! support move semantics
        static_pool &operator=(static_pool &&a) = default;
        //! support move semantics
        static_pool(static_pool &&) = default;
   
        static_pool(const std::function<value_type()> &aItemInitializer = [](){return value_type();})
        : m_Pool([this, &aItemInitializer]() {
            collection_type pool;

            for (decltype(pool_size) i = 0; i < pool_size; ++i) 
                pool[i] = std::make_shared<value_type>(aItemInitializer());

            return pool;
        }())
        {}  

        ~static_pool() = default;

    private:
        collection_type m_Pool;
    };
}

#endif


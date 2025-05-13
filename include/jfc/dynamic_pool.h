// © Joseph Cameron - All Rights Reserved

#ifndef JFC_DYNAMIC_POOL_H
#define JFC_DYNAMIC_POOL_H

#include <algorithm>
#include <functional>
#include <memory>
#include <vector>

namespace jfc {
    /// \brief Object pool of variable length. 
    ///
    template<typename value_type_param> class dynamic_pool final {
    public:
        using initializer_type = std::function<value_type_param()>;            
        using pool_type = std::vector<std::shared_ptr<value_type_param>>;
        using size_type = typename pool_type::size_type;
        using value_ptr_type = typename pool_type::value_type;
        using value_type = value_type_param;

        //! Get an object from the pool
        [[nodiscard]] value_ptr_type get() const {
            for (const auto &object : m_Pool) if (object.use_count() == 1) return object;
            m_Pool.push_back(std::make_shared<value_type>(m_Initializer()));
            return m_Pool.back();
        }

        //! get number of objects in the pool
        [[nodiscard]] size_type size() const { return m_Pool.size(); }

        //! empties the pool
        void clear() { m_Pool.clear(); }

        //! removes any objects that are currently unused outside of the pool
        void trim() {
            std::remove_if(m_Pool.begin(), m_Pool.end(), [](value_ptr_type aObject) {
                return aObject.use_count() == 1;
            });
        }

        //! support move semantics
        dynamic_pool &operator=(dynamic_pool &&) = default;
        //! support move semantics
        dynamic_pool(dynamic_pool &&) = default;

        //! construct a pool, by default the object initializer uses the object's default constructor    
        dynamic_pool(const initializer_type &aNewObjectInitializer = [](){ return value_type(); })
        : m_Initializer(aNewObjectInitializer)
        {}
        
        ~dynamic_pool() = default;

    private:
        initializer_type m_Initializer;
        pool_type m_Pool; 
    };
}

#endif


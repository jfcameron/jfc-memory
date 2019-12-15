// © 2019 Joseph Cameron - All Rights Reserved

#ifndef JFC_MEMORY_SHARED_PROXY_PTR_H
#define JFC_MEMORY_SHARED_PROXY_PTR_H

#include <functional>
#include <iostream>
#include <memory>
#include <mutex>

namespace jfc
{
    /// \brief shared pointer that delays initialization of its value until the first time its value is used
    template<typename value_type> 
    class shared_proxy_ptr final
    {
    public:
        //! type alias for initializer functor type
        using initializer_type = std::function<value_type *const()>;

    private:
        //! functor called at first dereference to init the value_type
        const initializer_type m_Initializer; 

        //! indicates whether or not pointee is initialized 
        mutable std::once_flag m_IsInitialized; 

        //! internal pointer to the T instance. 
        /// \note mutable type specifier required to allow late instantiation while behind const type. Maintains logical const regardless.
        mutable std::shared_ptr<value_type> m_SharedPtr = {}; 

        //! Initializes the pointer on the first call. Subsequent calls have no effect.
        void initialize() const
        {
            std::call_once(m_IsInitialized, [&]
            {
                m_SharedPtr.reset(m_Initializer()); 
            });
        }

    public:
        //! Check whether or not the shared_proxy_ptr has initialized its internal shared_ptr
        bool initialized() const
        {
            return m_SharedPtr.get() != nullptr;
        }

        //! dereference the pointer, initializing if this was the first time
        value_type *get() const 
        {
            initialize();
            
            return m_SharedPtr.get();
        }

        //! dereference via standard dereference operator
        value_type &operator*() const
        {
            return *get();
        }

        //! deref and access member via arrow operator
        value_type *operator->() const
        {
            return get();
        }

        //! initialize pointee and return copy of internal shared_ptr via implicit cast semantic
        operator std::shared_ptr<value_type>() const
        {
            initialize();
            
            return m_SharedPtr;
        }

        ///! support equality semantics
        bool operator==(const shared_proxy_ptr &a) const
        {
            initialize();

            return m_SharedPtr == a.m_SharedPtr;
        }
        
        ///! support equality semantics
        bool operator!=(const shared_proxy_ptr &a) const
        {
            return !(m_SharedPtr == a.m_SharedPtr);
        }

        //! support move semantics
        shared_proxy_ptr &operator= (shared_proxy_ptr &&a) = default;
        //! support move semantics
        shared_proxy_ptr(shared_proxy_ptr &&) = default;

        //! support copy semantics
        shared_proxy_ptr &operator= (const shared_proxy_ptr &a) = default;
        //! support copy semantics
        shared_proxy_ptr(const shared_proxy_ptr &) = default;

        //! \param aInitializer function used to lazily initialize the value_type instance 
        shared_proxy_ptr(const initializer_type aInitializer) 
        : m_Initializer(aInitializer) 
        {}            

        //! disallow default construction
        shared_proxy_ptr() = delete;

        //! default dtor
        ~shared_proxy_ptr() = default;
    };
}

#endif

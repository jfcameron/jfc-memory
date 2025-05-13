// © Joseph Cameron - All Rights Reserved

#ifndef JFC_LAZY_PTR_H
#define JFC_LAZY_PTR_H

#include <functional>
#include <memory>
#include <mutex>

namespace jfc {
    /// \brief shared pointer that delays initialization of its value until the first time it is dereferenced
    template<typename value_type_param> 
    class lazy_ptr final {
    public:
        using value_type = value_type_param;
        using initializer_type = std::function<value_type *()>;

        //! Check whether or not the lazy_ptr has initialized its internal shared_ptr
        [[nodiscard]] bool initialized() const {
            return m_SharedPtr.get() != nullptr;
        }

        //! dereference the pointer, initializing if this was the first time
        [[nodiscard]] value_type *get() const {
            std::call_once(m_IsInitialized, [&] {
                m_SharedPtr.reset(m_Initializer());
            });
            return m_SharedPtr.get();
        }

        //! dereference via standard dereference operator
        [[nodiscard]]value_type &operator*() const { return *get(); }

        //! deref and access member via arrow operator
        [[nodiscard]] value_type *operator->() const { return get(); }

        //! initialize pointee and return copy of internal shared_ptr via implicit cast semantic
        [[nodiscard]] operator std::shared_ptr<value_type>() const {
            std::call_once(m_IsInitialized, [&] {
                m_SharedPtr.reset(m_Initializer());
            });
            return m_SharedPtr;
        }

        ///! support equality semantics
        [[nodiscard]] bool operator==(const lazy_ptr &a) const { return m_SharedPtr == a.m_SharedPtr; }
        ///! support equality semantics
        [[nodiscard]] bool operator!=(const lazy_ptr &a) const { return !(m_SharedPtr == a.m_SharedPtr); }

        //! support move semantics
        lazy_ptr &operator=(lazy_ptr &&a) = default;
        //! support move semantics
        lazy_ptr(lazy_ptr &&) = default;

        //! support copy semantics
        lazy_ptr &operator=(const lazy_ptr &a) = default;
        //! support copy semantics
        lazy_ptr(const lazy_ptr &) = default;

        //! \param aInitializer function used to lazily initialize the value_type instance 
        lazy_ptr(const initializer_type &aInitializer) 
        : m_Initializer(aInitializer) 
        {}            

        ~lazy_ptr() = default;

    private:
        initializer_type m_Initializer; 
        /// \note mutability necessary to lazily instantiate in a const context
        mutable std::once_flag m_IsInitialized; 
        /// \note mutability necessary to lazily instantiate in a const context
        mutable std::shared_ptr<value_type> m_SharedPtr; 
    };
}

#endif


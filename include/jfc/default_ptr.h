// © 2019 Joseph Cameron - All Rights Reserved

#ifndef JFC_MEMORY_DEFAULT_PTR_H
#define JFC_MEMORY_DEFAULT_PTR_H

#include <memory>

//TODO: replace T with target_type

namespace jfc
{    
    /// \brief a weak pointer that returns a default pointer to T if the target pointer has become null.
    /// \todo rename lock to get. If the internal lock fails, you still get a defualt value.. this is the whole point. should be ptr.get()
    /// TODO replace weak ptr semantics with sharedptr semantics? need to revisit the interface from user perspective.
    template<typename value_type>
    class default_ptr final
    {
        std::weak_ptr<value_type> m_Target; //! Non-owning pointer to T instance
        std::shared_ptr<value_type> m_Default; //! Shared pointer to another instance of T, guaranteed to be valid for lifetime of the default_ptr
            
    public:
        //! Attempt to promote m_Target to a shared_ptr. Returns m_Default if m_Target is null
        std::shared_ptr<value_type> lock() const 
        {
            auto pTarget = m_Target.lock();

            return pTarget ? pTarget : m_Default;
        }
            
        bool operator==(const default_ptr &a) const
        {
            return 
            m_Default == a.m_Default && 
            m_Target.lock() == a.m_Target.lock();
        }

        default_ptr &operator=(const default_ptr &a) = default;
        default_ptr &operator=(default_ptr &&a) = default;

        /// \param aTarget the pointer to attempt to return when lock is called.
        /// \param aDefault the pointer returned by lock if the target is null
        default_ptr(const std::shared_ptr<value_type> &aDefault, const std::shared_ptr<value_type> &aTarget = {})  //TODO: why is there a default value?
        : m_Target(aTarget)
            , m_Default(aDefault)
        {}
            
        default_ptr() = delete;
        default_ptr(const default_ptr &) = default;
        default_ptr(default_ptr &&) = default;
        ~default_ptr() = default;
    };
}

#endif

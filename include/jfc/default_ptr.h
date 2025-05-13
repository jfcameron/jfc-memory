// © Joseph Cameron - All Rights Reserved

#ifndef JFC_DEFAULT_PTR_H
#define JFC_DEFAULT_PTR_H

#include <memory>

namespace jfc {    
    /// \brief a weak_ptr that returns a separate user-defined value if the weak_ptr has gone null
    template<typename value_type_param>
    class default_ptr final {
    public:
        using value_type = value_type_param;

        //! Attempt to return a pointer to m_Target. Returns mDefault if it is null
        [[nodiscard]] std::shared_ptr<value_type> lock() const {
            if (auto pTarget = m_Target.lock()) return pTarget;
            return m_Default;
        }

        /// \brief equality operator
        [[nodiscard]] bool operator==(const default_ptr &a) const {
            return 
                m_Default == a.m_Default && 
                m_Target.lock() == a.m_Target.lock();
        }

        /// \brief support assignment semantics
        default_ptr(const default_ptr &) = default;
        /// \brief support assignment semantics
        default_ptr &operator=(const default_ptr &a) = default;

        /// \brief support move semantics
        default_ptr(default_ptr &&) = default;
        /// \brief support move semantics
        default_ptr &operator=(default_ptr &&a) = default;

        ~default_ptr() = default;

        default_ptr(const std::shared_ptr<value_type> &aDefault, const std::shared_ptr<value_type> &aTarget) 
        : m_Target(aTarget)
        , m_Default(aDefault)
        {}

    private:
        std::weak_ptr<value_type> m_Target; 
        std::shared_ptr<value_type> m_Default; 
    };
}

#endif


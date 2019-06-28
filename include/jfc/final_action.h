// © 2019 joseph cameron - all rights reserved

#ifndef JFC_DATASTRUCTURES_FINAL_ACTION_H
#define JFC_DATASTRUCTURES_FINAL_ACTION_H

//TODO: separarate imp from int

namespace jfc
{
    /// \brief generic raii wrapper for non-pointer types (e.g: OpenGL handles, LibClang cursors)
    ///
    /// \description use this to enforce cleanup of "handles", "indexes" etc. at the end of their life. the various non pointer pointer types seen in C APIs like OpenGL, libclang, etc.
    /// based directly off of the example class of the same name in the RAII section of the CPP Core guidlines: https://github.com/isocpp/CppCoreGuidelines/blob/master/CppCoreGuidelines.md#Re-finally
    /// for pointer types, prefer the standard unique and shared ptr wrappers.
    /// TODO: support a r ref assignement operator. no copy!
    template<typename managed_handle_type>
    class final_action final
    {
    public:
        using deleter_type = std::function<void(managed_handle_type &)>;

    private:
        managed_handle_type m_Item; //!< The wrapped instance of managed_handle_type

        deleter_type m_Deleter; //!< The action to be called at destructor time. This is your opportunity to clean up after managed_handle_type

    public:
        managed_handle_type &get() { return m_Item; }

        final_action<managed_handle_type> &operator=(const final_action<managed_handle_type> &a) = delete;
        
        final_action<managed_handle_type> &operator=(final_action<managed_handle_type> &&a) 
        {
            m_Item = a.m_Item;

            m_Deleter = a.m_Deleter;

            a.m_Deleter = [](managed_handle_type &){};
        }
    
        final_action(final_action &&a)
        : m_Item(a.m_Item)
        , m_Deleter(a.m_Deleter)
        {
            a.m_Deleter = [](managed_handle_type &){};
        }

        /// \brief aItem is the managed handle item, deleter is the functor that cleans up the handle
        final_action(managed_handle_type &&aItem, deleter_type aDeleter)
        : m_Item(aItem)
        , m_Deleter(aDeleter)
        {}

        ~final_action()
        {
            m_Deleter(m_Item);
        }
    };
}

#endif

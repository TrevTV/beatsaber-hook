#ifndef IL2CPP_UTILS_FIELDS
#define IL2CPP_UTILS_FIELDS

#pragma pack(push)

#include "il2cpp-functions.hpp"
#include <optional>
#include "il2cpp-utils-methods.hpp"
#include "il2cpp-utils-classes.hpp"

#if __has_include(<concepts>)
#include <concepts>
#ifndef BS_HOOK_NO_CONCEPTS
#define BS_HOOK_USE_CONCEPTS
#endif
#endif

namespace il2cpp_utils {
    Il2CppClass* GetFieldClass(FieldInfo* field);

    // Returns the FieldInfo for the field of the given class with the given name
    // Created by zoller27osu
    FieldInfo* FindField(Il2CppClass* klass, ::std::string_view fieldName);
    // Wrapper for FindField taking a namespace and class name in place of an Il2CppClass*
    template<class... TArgs>
    FieldInfo* FindField(::std::string_view nameSpace, ::std::string_view className, TArgs&&... params) {
        return FindField(GetClassFromName(nameSpace, className), params...);
    }

    // Wrapper for FindField taking an instance to extract the Il2CppClass* from
    template<class T, class... TArgs>
    #ifndef BS_HOOK_USE_CONCEPTS
    ::std::enable_if_t<!::std::is_convertible_v<T, ::std::string_view>, FieldInfo*>
    #else
    requires (!std::is_convertible_v<T, Il2CppClass*> && !std::is_convertible_v<T, ::std::string_view>) FieldInfo*
    #endif
    FindField(T&& instance, TArgs&&... params) {
        il2cpp_functions::Init();

        auto* klass = RET_0_UNLESS(ExtractClass(instance));
        return FindField(klass, params...);
    }
    template<typename TOut = Il2CppObject*>
    // Gets a value from the given object instance, and FieldInfo, with return type TOut
    // Assumes a static field if instance == nullptr
    // Created by darknight1050, modified by Sc2ad and zoller27osu
    ::std::optional<TOut> GetFieldValue(Il2CppObject* instance, FieldInfo* field) {
        il2cpp_functions::Init();
        RET_NULLOPT_UNLESS(field);

        // Check that the TOut requested by the user matches the field.
        auto* outType = ExtractIndependentType<TOut>();

        TOut out;
        if (instance) {
            il2cpp_functions::field_get_value(instance, field, &out);
        } else { // Fallback to perform a static field set
            il2cpp_functions::field_static_get_value(field, &out);
        }
        return out;
    }

    template<typename TOut = Il2CppObject*, typename T>
    // Gets the value of the field with type TOut and the given name from the given class
    // Adapted by zoller27osu
    ::std::optional<TOut> GetFieldValue(T&& classOrInstance, ::std::string_view fieldName) {
        auto* field = RET_NULLOPT_UNLESS(FindField(classOrInstance, fieldName));
        Il2CppObject* obj = ToIl2CppObject(classOrInstance);  // null is allowed (for T = Il2CppType* or Il2CppClass*)
        return GetFieldValue<TOut>(obj, field);
    }

    template<typename TOut = Il2CppObject*>
    // Gets the value of the static field with the given name from the class with the given nameSpace and className.
    ::std::optional<TOut> GetFieldValue(::std::string_view nameSpace, ::std::string_view className, ::std::string_view fieldName) {
        auto* klass = RET_NULLOPT_UNLESS(GetClassFromName(nameSpace, className));
        return GetFieldValue<TOut>(klass, fieldName);
    }

    // Sets the value of a given field, given an object instance and the FieldInfo.
    // Returns false if it fails
    // Assumes static field if instance == nullptr
    template<class TArg>
    bool SetFieldValue(Il2CppObject* instance, FieldInfo* field, TArg&& value) {
        il2cpp_functions::Init();
        RET_0_UNLESS(field);

        // Ensure supplied value matches field's type
        auto* typ = ExtractType(value);
        RET_0_UNLESS(IsConvertibleFrom(field->type, typ));

        void* val = ExtractValue(value);
        if (instance) {
            il2cpp_functions::field_set_value(instance, field, val);
        } else { // Fallback to perform a static field set
            il2cpp_functions::field_static_set_value(field, val);
        }
        return true;
    }

    // Sets the value of a given field, given a class or instance and the field name.
    // Returns false if it fails
    template<class T, class TArg>
    bool SetFieldValue(T& classOrInstance, ::std::string_view fieldName, TArg&& value) {
        auto* field = RET_0_UNLESS(FindField(classOrInstance, fieldName));
        Il2CppObject* obj = ToIl2CppObject(classOrInstance);  // null is allowed (for T = Il2CppType* or Il2CppClass*)
        RET_0_UNLESS(SetFieldValue(obj, field, value));
        if (obj) RET_0_UNLESS(FromIl2CppObject(obj, classOrInstance));
        return true;
    }

    // Sets the value of the static field with the given name on the class with the given nameSpace and className.
    // Returns false if it fails
    template<class TArg>
    bool SetFieldValue(::std::string_view nameSpace, ::std::string_view className, ::std::string_view fieldName, TArg&& value) {
        auto* klass = RET_0_UNLESS(GetClassFromName(nameSpace, className));
        return SetFieldValue(klass, fieldName, value);
    }

    // Intializes an object (using the given args) fit to be assigned to the given field.
    template<typename... TArgs>
    Il2CppObject* CreateFieldValue(FieldInfo* field, TArgs&& ...args) {
        auto* klass = RET_0_UNLESS(GetFieldClass(field));
        return il2cpp_utils::New(klass, args...);
    }
}

#pragma pack(pop)

#endif

#ifndef IL2CPP_UTILS_PROPERTIES
#define IL2CPP_UTILS_PROPERTIES

#pragma pack(push)

#include "il2cpp-functions.hpp"
#include <optional>
#include "il2cpp-utils-methods.hpp"

namespace il2cpp_utils {
    // Returns the PropertyInfo for the property of the given class with the given name
    // Created by zoller27osu
    const PropertyInfo* FindProperty(Il2CppClass* klass, ::std::string_view propertyName);
    // Wrapper for FindProperty taking a namespace and class name in place of an Il2CppClass*
    const PropertyInfo* FindProperty(::std::string_view nameSpace, ::std::string_view className, ::std::string_view propertyName);
    // Wrapper for FindProperty taking an instance to extract the Il2CppClass* from
    template<class T>
    const PropertyInfo* FindProperty(T&& instance, ::std::string_view propertyName) {
        auto* klass = RET_0_UNLESS(ExtractClass(instance));
        return FindProperty(klass, propertyName);
    }

    template<class TOut = Il2CppObject*, bool checkTypes = true, class T>
    // Gets a value from the given object instance, and PropertyInfo, with return type TOut.
    // Assumes a static property if instance == nullptr
    ::std::optional<TOut> GetPropertyValue(T&& classOrInstance, const PropertyInfo* prop) {
        il2cpp_functions::Init();
        RET_NULLOPT_UNLESS(prop);

        auto* getter = RET_NULLOPT_UNLESS(il2cpp_functions::property_get_get_method(prop));
        return RunMethod<TOut, checkTypes>(classOrInstance, getter);
    }

    template<typename TOut = Il2CppObject*, bool checkTypes = true, typename T>
    // Gets the value of the property with the given name from the given class or instance, and returns it as TOut.
    ::std::optional<TOut> GetPropertyValue(T&& classOrInstance, ::std::string_view propName) {
        auto* prop = RET_NULLOPT_UNLESS(FindProperty(classOrInstance, propName));
        return GetPropertyValue<TOut, checkTypes>(classOrInstance, prop);
    }

    template<typename TOut = Il2CppObject*, bool checkTypes = true>
    // Gets the value of the static property with the given name from the class with the given nameSpace and className.
    ::std::optional<TOut> GetPropertyValue(::std::string_view nameSpace, ::std::string_view className, ::std::string_view propName) {
        auto* klass = RET_0_UNLESS(GetClassFromName(nameSpace, className));
        return GetPropertyValue<TOut, checkTypes>(klass, propName);
    }

    // Sets the value of a given property, given an object instance or class and PropertyInfo
    // Returns false if it fails.
    // Only static properties work with classOrInstance == nullptr
    template<bool checkTypes = true, class T, class TArg>
    bool SetPropertyValue(T& classOrInstance, const PropertyInfo* prop, TArg&& value) {
        il2cpp_functions::Init();
        RET_0_UNLESS(prop);

        auto* setter = RET_0_UNLESS(il2cpp_functions::property_get_set_method(prop));
        return (bool)RunMethod<Il2CppObject*, checkTypes>(classOrInstance, setter, value);
    }

    // Sets the value of a given property, given an object instance or class and property name
    // Returns false if it fails
    template<bool checkTypes = true, class T, class TArg>
    bool SetPropertyValue(T& classOrInstance, ::std::string_view propName, TArg&& value) {
        auto* prop = RET_0_UNLESS(FindProperty(classOrInstance, propName));
        return SetPropertyValue<checkTypes>(classOrInstance, prop, value);
    }

    // Sets the value of a given static property, given the class' namespace and name, and the property name and value.
    // Returns false if it fails
    template<bool checkTypes = true, class TArg>
    bool SetPropertyValue(::std::string_view nameSpace, ::std::string_view className, ::std::string_view propName, TArg&& value) {
        auto* klass = RET_0_UNLESS(GetClassFromName(nameSpace, className));
        return SetPropertyValue<checkTypes>(klass, propName, value);
    }
}

#pragma pack(pop)

#endif

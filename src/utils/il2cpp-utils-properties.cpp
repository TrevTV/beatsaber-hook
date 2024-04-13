#include "../../shared/utils/typedefs.h"
#include "../../shared/utils/il2cpp-utils-properties.hpp"
#include "../../shared/utils/utils.h"
#include <unordered_map>
#include "../../shared/utils/hashing.hpp"

namespace il2cpp_utils {
    static std::unordered_map<std::pair<const Il2CppClass*, std::string>, const PropertyInfo*, hash_pair> classesNamesToPropertiesCache;
    static std::mutex classPropertiesLock;

    const PropertyInfo* FindProperty(Il2CppClass* klass, std::string_view propName) {

        il2cpp_functions::Init();
        RET_0_UNLESS(klass);

        // Check Cache
        auto key = std::pair<Il2CppClass*, std::string>(klass, propName);
        classPropertiesLock.lock();
        auto itr = classesNamesToPropertiesCache.find(key);
        if (itr != classesNamesToPropertiesCache.end()) {
            classPropertiesLock.unlock();
            return itr->second;
        }
        classPropertiesLock.unlock();
        auto prop = il2cpp_functions::class_get_property_from_name(klass, propName.data());
        if (!prop) {
            if (klass->parent != klass) prop = FindProperty(klass->parent, propName);
        }
        classPropertiesLock.lock();
        classesNamesToPropertiesCache.emplace(key, prop);
        classPropertiesLock.unlock();
        return prop;
    }

    const PropertyInfo* FindProperty(std::string_view nameSpace, std::string_view className, std::string_view propertyName) {
        return FindProperty(GetClassFromName(nameSpace, className), propertyName);
    }
}
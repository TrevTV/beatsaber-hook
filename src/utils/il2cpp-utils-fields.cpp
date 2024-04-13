#include "../../shared/utils/typedefs.h"
#include "../../shared/utils/il2cpp-utils-fields.hpp"
#include "../../shared/utils/hashing.hpp"
#include "../../shared/utils/utils.h"
#include <unordered_map>

namespace il2cpp_utils {
    static std::unordered_map<std::pair<const Il2CppClass*, std::string>, FieldInfo*, hash_pair> classesNamesToFieldsCache;
    static std::mutex nameFieldLock;

    FieldInfo* FindField(Il2CppClass* klass, std::string_view fieldName) {
        il2cpp_functions::Init();
        RET_0_UNLESS(klass);

        // Check Cache
        auto key = std::pair<Il2CppClass*, std::string>(klass, fieldName);
        nameFieldLock.lock();
        auto itr = classesNamesToFieldsCache.find(key);
        if (itr != classesNamesToFieldsCache.end()) {
            nameFieldLock.unlock();
            return itr->second;
        }
        nameFieldLock.unlock();
        auto field = il2cpp_functions::class_get_field_from_name(klass, fieldName.data());
        if (!field) {
            if (klass->parent != klass) field = FindField(klass->parent, fieldName);
        }
        nameFieldLock.lock();
        classesNamesToFieldsCache.emplace(key, field);
        nameFieldLock.unlock();
        return field;
    }

    Il2CppClass* GetFieldClass(FieldInfo* field) {
        auto type = RET_0_UNLESS(il2cpp_functions::field_get_type(field));
        return il2cpp_functions::class_from_il2cpp_type(type);
    }
}
#include "../../shared/utils/typedefs.h"
#include "../../shared/utils/il2cpp-utils-classes.hpp"
#include "../../shared/utils/il2cpp-utils-methods.hpp"
#include "../../shared/utils/il2cpp-utils-properties.hpp"
#include "../../shared/utils/il2cpp-utils-fields.hpp"
#include <map>
#include <unordered_map>
#include "../../shared/utils/alphanum.hpp"
#include "shared/utils/gc-alloc.hpp"

namespace il2cpp_utils {
    std::unordered_set<Il2CppClass*> loggedClasses;

    std::string GenericClassStandardName(Il2CppGenericClass* genClass) {
        if (genClass->cached_class) {
            return ClassStandardName(genClass->cached_class);
        }
        if (il2cpp_functions::MetadataCache_GetIndexForTypeDefinition(genClass->cached_class) != kTypeDefinitionIndexInvalid) {
            il2cpp_functions::Init();
            auto* klass = il2cpp_functions::GenericClass_GetClass(genClass);
            return ClassStandardName(klass);
        }
        return "?";
    }

    static std::unordered_map<Il2CppClass*, std::map<std::string, Il2CppGenericClass*, doj::alphanum_less<std::string>>> classToGenericClassMap;
    void BuildGenericsMap() {
        il2cpp_functions::Init();
        auto* metadataReg = RET_V_UNLESS(il2cpp_functions::s_Il2CppMetadataRegistration);

        for (int i=0; i < metadataReg->genericClassesCount; i++) {
            Il2CppGenericClass* genClass = metadataReg->genericClasses[i];
            if (!genClass) continue;
            if (!(genClass->cached_class)) {
            }
            std::string genClassName = GenericClassStandardName(genClass);

            auto* typeDefClass = il2cpp_functions::GlobalMetadata_GetTypeInfoFromTypeDefinitionIndex(il2cpp_functions::MetadataCache_GetIndexForTypeDefinition(genClass->cached_class));
            if (!typeDefClass) continue;

            classToGenericClassMap[typeDefClass][genClassName.c_str()] = genClass;
        }
    }

    void AddTypeToNametoClassHashTable(const Il2CppImage* img, TypeDefinitionIndex index) {
        il2cpp_functions::Init();
        const Il2CppTypeDefinition* typeDefinition = il2cpp_functions::MetadataCache_GetTypeDefinitionFromIndex(index);
        // don't add nested types
        if (typeDefinition->declaringTypeIndex != kTypeIndexInvalid)
            return;

        if (img != il2cpp_functions::get_corlib())
            AddNestedTypesToNametoClassHashTable(img, typeDefinition);
        // GlobalMetadata.cpp shows Il2CppMetadataTypeHandle == Il2CppTypeDefinition const*
        auto handle = reinterpret_cast<Il2CppMetadataTypeHandle>(typeDefinition);
        img->nameToClassHashTable->insert(std::make_pair(std::make_pair(il2cpp_functions::MetadataCache_GetStringFromIndex(typeDefinition->namespaceIndex), il2cpp_functions::MetadataCache_GetStringFromIndex(typeDefinition->nameIndex)), handle));
    }

    void AddNestedTypesToNametoClassHashTable(const Il2CppImage* img, const Il2CppTypeDefinition* typeDefinition) {
        il2cpp_functions::Init();
        for (int i = 0; i < typeDefinition->nested_type_count; ++i) {
            Il2CppClass *klass = il2cpp_functions::MetadataCache_GetNestedTypeFromIndex(typeDefinition->nestedTypesStart + i);
            AddNestedTypesToNametoClassHashTable(img->nameToClassHashTable, il2cpp_functions::MetadataCache_GetStringFromIndex(typeDefinition->namespaceIndex), il2cpp_functions::MetadataCache_GetStringFromIndex(typeDefinition->nameIndex), klass);
        }
    }

    void AddNestedTypesToNametoClassHashTable(Il2CppNameToTypeHandleHashTable* hashTable, const char *namespaze, const std::string& parentName, Il2CppClass *klass) {
        il2cpp_functions::Init();
        std::string name = parentName + "/" + klass->name;
        char *pName = (char*)gc_alloc_specific(name.size() + 1 * sizeof(char));
        strlcpy(pName, name.c_str(), name.length() + 1);

        auto typeDefinition = il2cpp_functions::MetadataCache_GetTypeDefinition(klass);
        // GlobalMetadata.cpp shows Il2CppMetadataTypeHandle == Il2CppTypeDefinition const*
        auto handle = reinterpret_cast<Il2CppMetadataTypeHandle>(typeDefinition);
        hashTable->insert(std::make_pair(std::make_pair(namespaze, (const char*)pName), handle));

        void *iter = NULL;
        while (Il2CppClass *nestedClass = il2cpp_functions::class_get_nested_types(klass, &iter))
            AddNestedTypesToNametoClassHashTable(hashTable, namespaze, name, nestedClass);
    }
}

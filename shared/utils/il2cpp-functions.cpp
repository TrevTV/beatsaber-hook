#include <dlfcn.h>

#include "il2cpp-functions.hpp"
#include "logging.h"
#include "utils.h"  // for IL2CPP_SO_PATH

const Il2CppMetadataRegistration* il2cpp_functions::s_Il2CppMetadataRegistration = nullptr;
MAKE_HOOK_OFFSETLESS(MetadataCache_Register_Hook, void, const Il2CppCodeRegistration* const codeRegistration,
        const Il2CppMetadataRegistration* const metadataRegistration, const Il2CppCodeGenOptions* const codeGenOptions) {
    log(DEBUG, "MetadataCache::Register hook!");
    il2cpp_functions::s_Il2CppMetadataRegistration = metadataRegistration;
    return MetadataCache_Register_Hook(codeRegistration, metadataRegistration, codeGenOptions);
}

// Autogenerated; modified by zoller27osu
// Initializes all of the IL2CPP functions via dlopen and dlsym for use.
void il2cpp_functions::Init() {
    if (initialized) {
        return;
    }
    log(INFO, "il2cpp_functions: Init: Initializing all IL2CPP Functions...");
    dlerror();  // clears existing errors
    void *imagehandle = dlopen(IL2CPP_SO_PATH, RTLD_GLOBAL | RTLD_LAZY);
    if (!imagehandle) {
        log(ERROR, "Failed to dlopen %s: %s!", IL2CPP_SO_PATH, dlerror());
        return;
    }

    long long base = getRealOffset(0), hookAddr;
    log(DEBUG, "base: %llX", base);
    bool multiplesFound = false, allSigScanSuccess = true;
    if ((hookAddr = FindUniquePattern(multiplesFound, base, "f3 0f 1e f8 fd 7b 01 a9 fd 43 00 91 f3 03 00 aa 68 9a 44 39 48 01 10 37",
            "Class::Init"))) {
        *(void**)(&il2cpp_functions::Class_Init) = (void*)hookAddr;
    } else { allSigScanSuccess = false; }

    long long metadataCacheStart = 0;
    if ((hookAddr = FindUniquePattern(multiplesFound, base, "ff 83 01 d1 f6 57 03 a9 f4 4f 04 a9 fd 7b 05 a9 fd 43 01 91 f4 03 01 aa "
            "f3 03 00 aa ", "MetadataCache::Register"))) {
        metadataCacheStart = hookAddr;
        *(void**)(&il2cpp_functions::MetadataCache_Register) = (void*)hookAddr;
    } else { allSigScanSuccess = false; }

    if ((hookAddr = FindUniquePattern(multiplesFound, base, "? ? ? ? ? ? ? f9 ? ? ? ? ? ? ? f9 0a 34 40 f9 08 a1 80 b9 28 01 08 8b "
            "48 01 08 cb 29 85 8b 52 08 fd 42 d3 e9 51 b8 72 00 7d 09 1b c0 03 5f d6", "MetadataCache::GetIndexForTypeDefinition"))) {
        *(void**)(&il2cpp_functions::MetadataCache_GetIndexForTypeDefinition) = (void*)hookAddr;
    } else { allSigScanSuccess = false; }

    if (hookAddr > 0 && metadataCacheStart > 0 && (hookAddr - metadataCacheStart) == (0x8504BC - 0x84DE9C)) {
        log(DEBUG, "Success! Loading remaining MetadataCache addresses from known inter-class offsets!");
        long long adjustedStart = metadataCacheStart - 0x84DE9C;
        *(void**)(&il2cpp_functions::MetadataCache_GetStringFromIndex) = (void*)(adjustedStart + 0x84E5E8);
        *(void**)(&il2cpp_functions::MetadataCache_GetTypeInfoFromTypeIndex) = (void*)(adjustedStart + 0x84F764);
        *(void**)(&il2cpp_functions::MetadataCache_GetTypeInfoFromTypeDefinitionIndex) = (void*)(adjustedStart + 0x84FBA4);
        *(void**)(&il2cpp_functions::MetadataCache_GetTypeDefinitionFromIndex) = (void*)(adjustedStart + 0x84FFBC);
        *(void**)(&il2cpp_functions::MetadataCache_GetExportedTypeFromIndex) = (void*)(adjustedStart + 0x84FFF0);
        *(void**)(&il2cpp_functions::MetadataCache_GetGenericContainerFromIndex) = (void*)(adjustedStart + 0x850018);
        *(void**)(&il2cpp_functions::MetadataCache_GetGenericParameterFromIndex) = (void*)(adjustedStart + 0x850048);
        *(void**)(&il2cpp_functions::MetadataCache_GetNestedTypeFromIndex) = (void*)(adjustedStart + 0x8500BC);
        *(void**)(&il2cpp_functions::MetadataCache_GetRGCTXDefinitionFromIndex) = (void*)(adjustedStart + 0x85015C);
    } else {
        log(DEBUG, "TODO: sig scan other MetadataCache functions!");
        allSigScanSuccess = false;
    }

    if ((hookAddr = FindUniquePattern(multiplesFound, base, "f4 4f be a9 fd 7b 01 a9 fd 43 00 91 f3 03 08 aa", "Type::GetName"))) {
        // cont ? ? ? ? ? ? ? f9 e9 03 01 2a
        *(void**)(&il2cpp_functions::Type_GetName) = (void*)hookAddr;
    } else { allSigScanSuccess = false; }

    if ((hookAddr = FindUniquePattern(multiplesFound, base, "f7 0f 1c f8 f6 57 01 a9 f4 4f 02 a9 fd 7b 03 a9 fd c3 00 91 "
            "f3 03 00 aa ? ? ? ? ? ? ? f9 ? ? ? ? 60 02 40 b9", "GenericClass::GetClass"))) {
        *(void**)(&il2cpp_functions::GenericClass_GetClass) = (void*)hookAddr;
    } else { allSigScanSuccess = false; }

    if (!allSigScanSuccess || multiplesFound) {
        if (!allSigScanSuccess) log(ERROR, "One or more sigscans failed! Aborting!");
        if (multiplesFound) log(ERROR, "One or more sigscans found multiple matches! Aborting!");
        abort();
    }

    *(void**)(&init) = dlsym(imagehandle, "il2cpp_init");
    log(INFO, "Loaded: il2cpp_init, error: %s", dlerror());
    *(void**)(&init_utf16) = dlsym(imagehandle, "il2cpp_init_utf16");
    log(INFO, "Loaded: il2cpp_init_utf16");
    *(void**)(&shutdown) = dlsym(imagehandle, "il2cpp_shutdown");
    log(INFO, "Loaded: il2cpp_shutdown");
    *(void**)(&set_config_dir) = dlsym(imagehandle, "il2cpp_set_config_dir");
    log(INFO, "Loaded: il2cpp_set_config_dir");
    *(void**)(&set_data_dir) = dlsym(imagehandle, "il2cpp_set_data_dir");
    log(INFO, "Loaded: il2cpp_set_data_dir");
    *(void**)(&set_temp_dir) = dlsym(imagehandle, "il2cpp_set_temp_dir");
    log(INFO, "Loaded: il2cpp_set_temp_dir");
    *(void**)(&set_commandline_arguments) = dlsym(imagehandle, "il2cpp_set_commandline_arguments");
    log(INFO, "Loaded: il2cpp_set_commandline_arguments");
    *(void**)(&set_commandline_arguments_utf16) = dlsym(imagehandle, "il2cpp_set_commandline_arguments_utf16");
    log(INFO, "Loaded: il2cpp_set_commandline_arguments_utf16");
    *(void**)(&set_config_utf16) = dlsym(imagehandle, "il2cpp_set_config_utf16");
    log(INFO, "Loaded: il2cpp_set_config_utf16");
    *(void**)(&set_config) = dlsym(imagehandle, "il2cpp_set_config");
    log(INFO, "Loaded: il2cpp_set_config");
    *(void**)(&set_memory_callbacks) = dlsym(imagehandle, "il2cpp_set_memory_callbacks");
    log(INFO, "Loaded: il2cpp_set_memory_callbacks");
    *(void**)(&get_corlib) = dlsym(imagehandle, "il2cpp_get_corlib");
    log(INFO, "Loaded: il2cpp_get_corlib");
    *(void**)(&add_internal_call) = dlsym(imagehandle, "il2cpp_add_internal_call");
    log(INFO, "Loaded: il2cpp_add_internal_call");
    *(void**)(&resolve_icall) = dlsym(imagehandle, "il2cpp_resolve_icall");
    log(INFO, "Loaded: il2cpp_resolve_icall");
    *(void**)(&alloc) = dlsym(imagehandle, "il2cpp_alloc");
    log(INFO, "Loaded: il2cpp_alloc");
    *(void**)(&free) = dlsym(imagehandle, "il2cpp_free");
    log(INFO, "Loaded: il2cpp_free");
    *(void**)(&array_class_get) = dlsym(imagehandle, "il2cpp_array_class_get");
    log(INFO, "Loaded: il2cpp_array_class_get");
    *(void**)(&array_length) = dlsym(imagehandle, "il2cpp_array_length");
    log(INFO, "Loaded: il2cpp_array_length");
    *(void**)(&array_get_byte_length) = dlsym(imagehandle, "il2cpp_array_get_byte_length");
    log(INFO, "Loaded: il2cpp_array_get_byte_length");
    *(void**)(&array_new) = dlsym(imagehandle, "il2cpp_array_new");
    log(INFO, "Loaded: il2cpp_array_new");
    *(void**)(&array_new_specific) = dlsym(imagehandle, "il2cpp_array_new_specific");
    log(INFO, "Loaded: il2cpp_array_new_specific");
    *(void**)(&array_new_full) = dlsym(imagehandle, "il2cpp_array_new_full");
    log(INFO, "Loaded: il2cpp_array_new_full");
    *(void**)(&bounded_array_class_get) = dlsym(imagehandle, "il2cpp_bounded_array_class_get");
    log(INFO, "Loaded: il2cpp_bounded_array_class_get");
    *(void**)(&array_element_size) = dlsym(imagehandle, "il2cpp_array_element_size");
    log(INFO, "Loaded: il2cpp_array_element_size");
    *(void**)(&assembly_get_image) = dlsym(imagehandle, "il2cpp_assembly_get_image");
    log(INFO, "Loaded: il2cpp_assembly_get_image");
    *(void**)(&class_enum_basetype) = dlsym(imagehandle, "il2cpp_class_enum_basetype");
    log(INFO, "Loaded: il2cpp_class_enum_basetype");
    *(void**)(&class_is_generic) = dlsym(imagehandle, "il2cpp_class_is_generic");
    log(INFO, "Loaded: il2cpp_class_is_generic");
    *(void**)(&class_is_inflated) = dlsym(imagehandle, "il2cpp_class_is_inflated");
    log(INFO, "Loaded: il2cpp_class_is_inflated");
    *(void**)(&class_is_assignable_from) = dlsym(imagehandle, "il2cpp_class_is_assignable_from");
    log(INFO, "Loaded: il2cpp_class_is_assignable_from");
    *(void**)(&class_is_subclass_of) = dlsym(imagehandle, "il2cpp_class_is_subclass_of");
    log(INFO, "Loaded: il2cpp_class_is_subclass_of");
    *(void**)(&class_has_parent) = dlsym(imagehandle, "il2cpp_class_has_parent");
    log(INFO, "Loaded: il2cpp_class_has_parent");
    *(void**)(&class_from_il2cpp_type) = dlsym(imagehandle, "il2cpp_class_from_il2cpp_type");
    log(INFO, "Loaded: il2cpp_class_from_il2cpp_type");
    *(void**)(&class_from_name) = dlsym(imagehandle, "il2cpp_class_from_name");
    log(INFO, "Loaded: il2cpp_class_from_name");
    *(void**)(&class_from_system_type) = dlsym(imagehandle, "il2cpp_class_from_system_type");
    log(INFO, "Loaded: il2cpp_class_from_system_type");
    *(void**)(&class_get_element_class) = dlsym(imagehandle, "il2cpp_class_get_element_class");
    log(INFO, "Loaded: il2cpp_class_get_element_class");
    *(void**)(&class_get_events) = dlsym(imagehandle, "il2cpp_class_get_events");
    log(INFO, "Loaded: il2cpp_class_get_events");
    *(void**)(&class_get_fields) = dlsym(imagehandle, "il2cpp_class_get_fields");
    log(INFO, "Loaded: il2cpp_class_get_fields");
    *(void**)(&class_get_nested_types) = dlsym(imagehandle, "il2cpp_class_get_nested_types");
    log(INFO, "Loaded: il2cpp_class_get_nested_types");
    *(void**)(&class_get_interfaces) = dlsym(imagehandle, "il2cpp_class_get_interfaces");
    log(INFO, "Loaded: il2cpp_class_get_interfaces");
    *(void**)(&class_get_properties) = dlsym(imagehandle, "il2cpp_class_get_properties");
    log(INFO, "Loaded: il2cpp_class_get_properties");
    *(void**)(&class_get_property_from_name) = dlsym(imagehandle, "il2cpp_class_get_property_from_name");
    log(INFO, "Loaded: il2cpp_class_get_property_from_name");
    *(void**)(&class_get_field_from_name) = dlsym(imagehandle, "il2cpp_class_get_field_from_name");
    log(INFO, "Loaded: il2cpp_class_get_field_from_name");
    *(void**)(&class_get_methods) = dlsym(imagehandle, "il2cpp_class_get_methods");
    log(INFO, "Loaded: il2cpp_class_get_methods");
    *(void**)(&class_get_method_from_name) = dlsym(imagehandle, "il2cpp_class_get_method_from_name");
    log(INFO, "Loaded: il2cpp_class_get_method_from_name");
    *(void**)(&class_get_name) = dlsym(imagehandle, "il2cpp_class_get_name");
    log(INFO, "Loaded: il2cpp_class_get_name");
    *(void**)(&class_get_namespace) = dlsym(imagehandle, "il2cpp_class_get_namespace");
    log(INFO, "Loaded: il2cpp_class_get_namespace");
    *(void**)(&class_get_parent) = dlsym(imagehandle, "il2cpp_class_get_parent");
    log(INFO, "Loaded: il2cpp_class_get_parent");
    *(void**)(&class_get_declaring_type) = dlsym(imagehandle, "il2cpp_class_get_declaring_type");
    log(INFO, "Loaded: il2cpp_class_get_declaring_type");
    *(void**)(&class_instance_size) = dlsym(imagehandle, "il2cpp_class_instance_size");
    log(INFO, "Loaded: il2cpp_class_instance_size");
    *(void**)(&class_num_fields) = dlsym(imagehandle, "il2cpp_class_num_fields");
    log(INFO, "Loaded: il2cpp_class_num_fields");
    *(void**)(&class_is_valuetype) = dlsym(imagehandle, "il2cpp_class_is_valuetype");
    log(INFO, "Loaded: il2cpp_class_is_valuetype");
    *(void**)(&class_value_size) = dlsym(imagehandle, "il2cpp_class_value_size");
    log(INFO, "Loaded: il2cpp_class_value_size");
    *(void**)(&class_is_blittable) = dlsym(imagehandle, "il2cpp_class_is_blittable");
    log(INFO, "Loaded: il2cpp_class_is_blittable");
    *(void**)(&class_get_flags) = dlsym(imagehandle, "il2cpp_class_get_flags");
    log(INFO, "Loaded: il2cpp_class_get_flags");
    *(void**)(&class_is_abstract) = dlsym(imagehandle, "il2cpp_class_is_abstract");
    log(INFO, "Loaded: il2cpp_class_is_abstract");
    *(void**)(&class_is_interface) = dlsym(imagehandle, "il2cpp_class_is_interface");
    log(INFO, "Loaded: il2cpp_class_is_interface");
    *(void**)(&class_array_element_size) = dlsym(imagehandle, "il2cpp_class_array_element_size");
    log(INFO, "Loaded: il2cpp_class_array_element_size");
    *(void**)(&class_from_type) = dlsym(imagehandle, "il2cpp_class_from_type");
    log(INFO, "Loaded: il2cpp_class_from_type");
    *(void**)(&class_get_type) = dlsym(imagehandle, "il2cpp_class_get_type");
    log(INFO, "Loaded: il2cpp_class_get_type");
    *(void**)(&class_get_type_token) = dlsym(imagehandle, "il2cpp_class_get_type_token");
    log(INFO, "Loaded: il2cpp_class_get_type_token");
    *(void**)(&class_has_attribute) = dlsym(imagehandle, "il2cpp_class_has_attribute");
    log(INFO, "Loaded: il2cpp_class_has_attribute");
    *(void**)(&class_has_references) = dlsym(imagehandle, "il2cpp_class_has_references");
    log(INFO, "Loaded: il2cpp_class_has_references");
    *(void**)(&class_is_enum) = dlsym(imagehandle, "il2cpp_class_is_enum");
    log(INFO, "Loaded: il2cpp_class_is_enum");
    *(void**)(&class_get_image) = dlsym(imagehandle, "il2cpp_class_get_image");
    log(INFO, "Loaded: il2cpp_class_get_image");
    *(void**)(&class_get_assemblyname) = dlsym(imagehandle, "il2cpp_class_get_assemblyname");
    log(INFO, "Loaded: il2cpp_class_get_assemblyname");
    *(void**)(&class_get_rank) = dlsym(imagehandle, "il2cpp_class_get_rank");
    log(INFO, "Loaded: il2cpp_class_get_rank");
    *(void**)(&class_get_bitmap_size) = dlsym(imagehandle, "il2cpp_class_get_bitmap_size");
    log(INFO, "Loaded: il2cpp_class_get_bitmap_size");
    *(void**)(&class_get_bitmap) = dlsym(imagehandle, "il2cpp_class_get_bitmap");
    log(INFO, "Loaded: il2cpp_class_get_bitmap");
    *(void**)(&stats_dump_to_file) = dlsym(imagehandle, "il2cpp_stats_dump_to_file");
    log(INFO, "Loaded: il2cpp_stats_dump_to_file");
    *(void**)(&stats_get_value) = dlsym(imagehandle, "il2cpp_stats_get_value");
    log(INFO, "Loaded: il2cpp_stats_get_value");
    *(void**)(&domain_get) = dlsym(imagehandle, "il2cpp_domain_get");
    log(INFO, "Loaded: il2cpp_domain_get");
    *(void**)(&domain_assembly_open) = dlsym(imagehandle, "il2cpp_domain_assembly_open");
    log(INFO, "Loaded: il2cpp_domain_assembly_open");
    *(void**)(&domain_get_assemblies) = dlsym(imagehandle, "il2cpp_domain_get_assemblies");
    log(INFO, "Loaded: il2cpp_domain_get_assemblies");
    *(void**)(&exception_from_name_msg) = dlsym(imagehandle, "il2cpp_exception_from_name_msg");
    log(INFO, "Loaded: il2cpp_exception_from_name_msg");
    *(void**)(&get_exception_argument_null) = dlsym(imagehandle, "il2cpp_get_exception_argument_null");
    log(INFO, "Loaded: il2cpp_get_exception_argument_null");
    *(void**)(&format_exception) = dlsym(imagehandle, "il2cpp_format_exception");
    log(INFO, "Loaded: il2cpp_format_exception");
    *(void**)(&format_stack_trace) = dlsym(imagehandle, "il2cpp_format_stack_trace");
    log(INFO, "Loaded: il2cpp_format_stack_trace");
    *(void**)(&unhandled_exception) = dlsym(imagehandle, "il2cpp_unhandled_exception");
    log(INFO, "Loaded: il2cpp_unhandled_exception");
    *(void**)(&field_get_flags) = dlsym(imagehandle, "il2cpp_field_get_flags");
    log(INFO, "Loaded: il2cpp_field_get_flags");
    *(void**)(&field_get_name) = dlsym(imagehandle, "il2cpp_field_get_name");
    log(INFO, "Loaded: il2cpp_field_get_name");
    *(void**)(&field_get_parent) = dlsym(imagehandle, "il2cpp_field_get_parent");
    log(INFO, "Loaded: il2cpp_field_get_parent");
    *(void**)(&field_get_offset) = dlsym(imagehandle, "il2cpp_field_get_offset");
    log(INFO, "Loaded: il2cpp_field_get_offset");
    *(void**)(&field_get_type) = dlsym(imagehandle, "il2cpp_field_get_type");
    log(INFO, "Loaded: il2cpp_field_get_type");
    *(void**)(&field_get_value) = dlsym(imagehandle, "il2cpp_field_get_value");
    log(INFO, "Loaded: il2cpp_field_get_value");
    *(void**)(&field_get_value_object) = dlsym(imagehandle, "il2cpp_field_get_value_object");
    log(INFO, "Loaded: il2cpp_field_get_value_object");
    *(void**)(&field_has_attribute) = dlsym(imagehandle, "il2cpp_field_has_attribute");
    log(INFO, "Loaded: il2cpp_field_has_attribute");
    *(void**)(&field_set_value) = dlsym(imagehandle, "il2cpp_field_set_value");
    log(INFO, "Loaded: il2cpp_field_set_value");
    *(void**)(&field_static_get_value) = dlsym(imagehandle, "il2cpp_field_static_get_value");
    log(INFO, "Loaded: il2cpp_field_static_get_value");
    *(void**)(&field_static_set_value) = dlsym(imagehandle, "il2cpp_field_static_set_value");
    log(INFO, "Loaded: il2cpp_field_static_set_value");
    *(void**)(&field_set_value_object) = dlsym(imagehandle, "il2cpp_field_set_value_object");
    log(INFO, "Loaded: il2cpp_field_set_value_object");
    *(void**)(&gc_collect) = dlsym(imagehandle, "il2cpp_gc_collect");
    log(INFO, "Loaded: il2cpp_gc_collect");
    *(void**)(&gc_collect_a_little) = dlsym(imagehandle, "il2cpp_gc_collect_a_little");
    log(INFO, "Loaded: il2cpp_gc_collect_a_little");
    *(void**)(&gc_disable) = dlsym(imagehandle, "il2cpp_gc_disable");
    log(INFO, "Loaded: il2cpp_gc_disable");
    *(void**)(&gc_enable) = dlsym(imagehandle, "il2cpp_gc_enable");
    log(INFO, "Loaded: il2cpp_gc_enable");
    *(void**)(&gc_is_disabled) = dlsym(imagehandle, "il2cpp_gc_is_disabled");
    log(INFO, "Loaded: il2cpp_gc_is_disabled");
    *(void**)(&gc_get_used_size) = dlsym(imagehandle, "il2cpp_gc_get_used_size");
    log(INFO, "Loaded: il2cpp_gc_get_used_size");
    *(void**)(&gc_get_heap_size) = dlsym(imagehandle, "il2cpp_gc_get_heap_size");
    log(INFO, "Loaded: il2cpp_gc_get_heap_size");
    *(void**)(&gc_wbarrier_set_field) = dlsym(imagehandle, "il2cpp_gc_wbarrier_set_field");
    log(INFO, "Loaded: il2cpp_gc_wbarrier_set_field");
    *(void**)(&gchandle_new) = dlsym(imagehandle, "il2cpp_gchandle_new");
    log(INFO, "Loaded: il2cpp_gchandle_new");
    *(void**)(&gchandle_new_weakref) = dlsym(imagehandle, "il2cpp_gchandle_new_weakref");
    log(INFO, "Loaded: il2cpp_gchandle_new_weakref");
    *(void**)(&gchandle_get_target ) = dlsym(imagehandle, "il2cpp_gchandle_get_target ");
    log(INFO, "Loaded: il2cpp_gchandle_get_target ");
    *(void**)(&gchandle_free) = dlsym(imagehandle, "il2cpp_gchandle_free");
    log(INFO, "Loaded: il2cpp_gchandle_free");
    *(void**)(&unity_liveness_calculation_begin) = dlsym(imagehandle, "il2cpp_unity_liveness_calculation_begin");
    log(INFO, "Loaded: il2cpp_unity_liveness_calculation_begin");
    *(void**)(&unity_liveness_calculation_end) = dlsym(imagehandle, "il2cpp_unity_liveness_calculation_end");
    log(INFO, "Loaded: il2cpp_unity_liveness_calculation_end");
    *(void**)(&unity_liveness_calculation_from_root) = dlsym(imagehandle, "il2cpp_unity_liveness_calculation_from_root");
    log(INFO, "Loaded: il2cpp_unity_liveness_calculation_from_root");
    *(void**)(&unity_liveness_calculation_from_statics) = dlsym(imagehandle, "il2cpp_unity_liveness_calculation_from_statics");
    log(INFO, "Loaded: il2cpp_unity_liveness_calculation_from_statics");
    *(void**)(&method_get_return_type) = dlsym(imagehandle, "il2cpp_method_get_return_type");
    log(INFO, "Loaded: il2cpp_method_get_return_type");
    *(void**)(&method_get_declaring_type) = dlsym(imagehandle, "il2cpp_method_get_declaring_type");
    log(INFO, "Loaded: il2cpp_method_get_declaring_type");
    *(void**)(&method_get_name) = dlsym(imagehandle, "il2cpp_method_get_name");
    log(INFO, "Loaded: il2cpp_method_get_name");
    *(void**)(&method_get_from_reflection) = dlsym(imagehandle, "il2cpp_method_get_from_reflection");
    log(INFO, "Loaded: il2cpp_method_get_from_reflection");
    *(void**)(&method_get_object) = dlsym(imagehandle, "il2cpp_method_get_object");
    log(INFO, "Loaded: il2cpp_method_get_object");
    *(void**)(&method_is_generic) = dlsym(imagehandle, "il2cpp_method_is_generic");
    log(INFO, "Loaded: il2cpp_method_is_generic");
    *(void**)(&method_is_inflated) = dlsym(imagehandle, "il2cpp_method_is_inflated");
    log(INFO, "Loaded: il2cpp_method_is_inflated");
    *(void**)(&method_is_instance) = dlsym(imagehandle, "il2cpp_method_is_instance");
    log(INFO, "Loaded: il2cpp_method_is_instance");
    *(void**)(&method_get_param_count) = dlsym(imagehandle, "il2cpp_method_get_param_count");
    log(INFO, "Loaded: il2cpp_method_get_param_count");
    *(void**)(&method_get_param) = dlsym(imagehandle, "il2cpp_method_get_param");
    log(INFO, "Loaded: il2cpp_method_get_param");
    *(void**)(&method_get_class) = dlsym(imagehandle, "il2cpp_method_get_class");
    log(INFO, "Loaded: il2cpp_method_get_class");
    *(void**)(&method_has_attribute) = dlsym(imagehandle, "il2cpp_method_has_attribute");
    log(INFO, "Loaded: il2cpp_method_has_attribute");
    *(void**)(&method_get_flags) = dlsym(imagehandle, "il2cpp_method_get_flags");
    log(INFO, "Loaded: il2cpp_method_get_flags");
    *(void**)(&method_get_token) = dlsym(imagehandle, "il2cpp_method_get_token");
    log(INFO, "Loaded: il2cpp_method_get_token");
    *(void**)(&method_get_param_name) = dlsym(imagehandle, "il2cpp_method_get_param_name");
    log(INFO, "Loaded: il2cpp_method_get_param_name");
    *(void**)(&profiler_install) = dlsym(imagehandle, "il2cpp_profiler_install");
    log(INFO, "Loaded: il2cpp_profiler_install");
    *(void**)(&profiler_set_events) = dlsym(imagehandle, "il2cpp_profiler_set_events");
    log(INFO, "Loaded: il2cpp_profiler_set_events");
    *(void**)(&profiler_install_enter_leave) = dlsym(imagehandle, "il2cpp_profiler_install_enter_leave");
    log(INFO, "Loaded: il2cpp_profiler_install_enter_leave");
    *(void**)(&profiler_install_allocation) = dlsym(imagehandle, "il2cpp_profiler_install_allocation");
    log(INFO, "Loaded: il2cpp_profiler_install_allocation");
    *(void**)(&profiler_install_gc) = dlsym(imagehandle, "il2cpp_profiler_install_gc");
    log(INFO, "Loaded: il2cpp_profiler_install_gc");
    *(void**)(&profiler_install_fileio) = dlsym(imagehandle, "il2cpp_profiler_install_fileio");
    log(INFO, "Loaded: il2cpp_profiler_install_fileio");
    *(void**)(&profiler_install_thread) = dlsym(imagehandle, "il2cpp_profiler_install_thread");
    log(INFO, "Loaded: il2cpp_profiler_install_thread");
    *(void**)(&property_get_flags) = dlsym(imagehandle, "il2cpp_property_get_flags");
    log(INFO, "Loaded: il2cpp_property_get_flags");
    *(void**)(&property_get_get_method) = dlsym(imagehandle, "il2cpp_property_get_get_method");
    log(INFO, "Loaded: il2cpp_property_get_get_method");
    *(void**)(&property_get_set_method) = dlsym(imagehandle, "il2cpp_property_get_set_method");
    log(INFO, "Loaded: il2cpp_property_get_set_method");
    *(void**)(&property_get_name) = dlsym(imagehandle, "il2cpp_property_get_name");
    log(INFO, "Loaded: il2cpp_property_get_name");
    *(void**)(&property_get_parent) = dlsym(imagehandle, "il2cpp_property_get_parent");
    log(INFO, "Loaded: il2cpp_property_get_parent");
    *(void**)(&object_get_class) = dlsym(imagehandle, "il2cpp_object_get_class");
    log(INFO, "Loaded: il2cpp_object_get_class");
    *(void**)(&object_get_size) = dlsym(imagehandle, "il2cpp_object_get_size");
    log(INFO, "Loaded: il2cpp_object_get_size");
    *(void**)(&object_get_virtual_method) = dlsym(imagehandle, "il2cpp_object_get_virtual_method");
    log(INFO, "Loaded: il2cpp_object_get_virtual_method");
    *(void**)(&object_new) = dlsym(imagehandle, "il2cpp_object_new");
    log(INFO, "Loaded: il2cpp_object_new");
    *(void**)(&object_unbox) = dlsym(imagehandle, "il2cpp_object_unbox");
    log(INFO, "Loaded: il2cpp_object_unbox");
    *(void**)(&value_box) = dlsym(imagehandle, "il2cpp_value_box");
    log(INFO, "Loaded: il2cpp_value_box");
    *(void**)(&monitor_enter) = dlsym(imagehandle, "il2cpp_monitor_enter");
    log(INFO, "Loaded: il2cpp_monitor_enter");
    *(void**)(&monitor_try_enter) = dlsym(imagehandle, "il2cpp_monitor_try_enter");
    log(INFO, "Loaded: il2cpp_monitor_try_enter");
    *(void**)(&monitor_exit) = dlsym(imagehandle, "il2cpp_monitor_exit");
    log(INFO, "Loaded: il2cpp_monitor_exit");
    *(void**)(&monitor_pulse) = dlsym(imagehandle, "il2cpp_monitor_pulse");
    log(INFO, "Loaded: il2cpp_monitor_pulse");
    *(void**)(&monitor_pulse_all) = dlsym(imagehandle, "il2cpp_monitor_pulse_all");
    log(INFO, "Loaded: il2cpp_monitor_pulse_all");
    *(void**)(&monitor_wait) = dlsym(imagehandle, "il2cpp_monitor_wait");
    log(INFO, "Loaded: il2cpp_monitor_wait");
    *(void**)(&monitor_try_wait) = dlsym(imagehandle, "il2cpp_monitor_try_wait");
    log(INFO, "Loaded: il2cpp_monitor_try_wait");
    *(void**)(&runtime_invoke) = dlsym(imagehandle, "il2cpp_runtime_invoke");
    log(INFO, "Loaded: il2cpp_runtime_invoke");
    *(void**)(&runtime_invoke_convert_args) = dlsym(imagehandle, "il2cpp_runtime_invoke_convert_args");
    log(INFO, "Loaded: il2cpp_runtime_invoke_convert_args");
    *(void**)(&runtime_class_init) = dlsym(imagehandle, "il2cpp_runtime_class_init");
    log(INFO, "Loaded: il2cpp_runtime_class_init");
    *(void**)(&runtime_object_init) = dlsym(imagehandle, "il2cpp_runtime_object_init");
    log(INFO, "Loaded: il2cpp_runtime_object_init");
    *(void**)(&runtime_object_init_exception) = dlsym(imagehandle, "il2cpp_runtime_object_init_exception");
    log(INFO, "Loaded: il2cpp_runtime_object_init_exception");
    *(void**)(&runtime_unhandled_exception_policy_set) = dlsym(imagehandle, "il2cpp_runtime_unhandled_exception_policy_set");
    log(INFO, "Loaded: il2cpp_runtime_unhandled_exception_policy_set");
    *(void**)(&string_length) = dlsym(imagehandle, "il2cpp_string_length");
    log(INFO, "Loaded: il2cpp_string_length");
    *(void**)(&string_chars) = dlsym(imagehandle, "il2cpp_string_chars");
    log(INFO, "Loaded: il2cpp_string_chars");
    *(void**)(&string_new) = dlsym(imagehandle, "il2cpp_string_new");
    log(INFO, "Loaded: il2cpp_string_new");
    *(void**)(&string_new_len) = dlsym(imagehandle, "il2cpp_string_new_len");
    log(INFO, "Loaded: il2cpp_string_new_len");
    *(void**)(&string_new_utf16) = dlsym(imagehandle, "il2cpp_string_new_utf16");
    log(INFO, "Loaded: il2cpp_string_new_utf16");
    *(void**)(&string_new_wrapper) = dlsym(imagehandle, "il2cpp_string_new_wrapper");
    log(INFO, "Loaded: il2cpp_string_new_wrapper");
    *(void**)(&string_intern) = dlsym(imagehandle, "il2cpp_string_intern");
    log(INFO, "Loaded: il2cpp_string_intern");
    *(void**)(&string_is_interned) = dlsym(imagehandle, "il2cpp_string_is_interned");
    log(INFO, "Loaded: il2cpp_string_is_interned");
    *(void**)(&thread_current) = dlsym(imagehandle, "il2cpp_thread_current");
    log(INFO, "Loaded: il2cpp_thread_current");
    *(void**)(&thread_attach) = dlsym(imagehandle, "il2cpp_thread_attach");
    log(INFO, "Loaded: il2cpp_thread_attach");
    *(void**)(&thread_detach) = dlsym(imagehandle, "il2cpp_thread_detach");
    log(INFO, "Loaded: il2cpp_thread_detach");
    *(void**)(&thread_get_all_attached_threads) = dlsym(imagehandle, "il2cpp_thread_get_all_attached_threads");
    log(INFO, "Loaded: il2cpp_thread_get_all_attached_threads");
    *(void**)(&is_vm_thread) = dlsym(imagehandle, "il2cpp_is_vm_thread");
    log(INFO, "Loaded: il2cpp_is_vm_thread");
    *(void**)(&current_thread_walk_frame_stack) = dlsym(imagehandle, "il2cpp_current_thread_walk_frame_stack");
    log(INFO, "Loaded: il2cpp_current_thread_walk_frame_stack");
    *(void**)(&thread_walk_frame_stack) = dlsym(imagehandle, "il2cpp_thread_walk_frame_stack");
    log(INFO, "Loaded: il2cpp_thread_walk_frame_stack");
    *(void**)(&current_thread_get_top_frame) = dlsym(imagehandle, "il2cpp_current_thread_get_top_frame");
    log(INFO, "Loaded: il2cpp_current_thread_get_top_frame");
    *(void**)(&thread_get_top_frame) = dlsym(imagehandle, "il2cpp_thread_get_top_frame");
    log(INFO, "Loaded: il2cpp_thread_get_top_frame");
    *(void**)(&current_thread_get_frame_at) = dlsym(imagehandle, "il2cpp_current_thread_get_frame_at");
    log(INFO, "Loaded: il2cpp_current_thread_get_frame_at");
    *(void**)(&thread_get_frame_at) = dlsym(imagehandle, "il2cpp_thread_get_frame_at");
    log(INFO, "Loaded: il2cpp_thread_get_frame_at");
    *(void**)(&current_thread_get_stack_depth) = dlsym(imagehandle, "il2cpp_current_thread_get_stack_depth");
    log(INFO, "Loaded: il2cpp_current_thread_get_stack_depth");
    *(void**)(&thread_get_stack_depth) = dlsym(imagehandle, "il2cpp_thread_get_stack_depth");
    log(INFO, "Loaded: il2cpp_thread_get_stack_depth");
    *(void**)(&type_get_object) = dlsym(imagehandle, "il2cpp_type_get_object");
    log(INFO, "Loaded: il2cpp_type_get_object");
    *(void**)(&type_get_type) = dlsym(imagehandle, "il2cpp_type_get_type");
    log(INFO, "Loaded: il2cpp_type_get_type");
    *(void**)(&type_get_class_or_element_class) = dlsym(imagehandle, "il2cpp_type_get_class_or_element_class");
    log(INFO, "Loaded: il2cpp_type_get_class_or_element_class");
    *(void**)(&type_get_name) = dlsym(imagehandle, "il2cpp_type_get_name");
    log(INFO, "Loaded: il2cpp_type_get_name");
    *(void**)(&type_is_byref) = dlsym(imagehandle, "il2cpp_type_is_byref");
    log(INFO, "Loaded: il2cpp_type_is_byref");
    *(void**)(&type_get_attrs) = dlsym(imagehandle, "il2cpp_type_get_attrs");
    log(INFO, "Loaded: il2cpp_type_get_attrs");
    *(void**)(&type_equals) = dlsym(imagehandle, "il2cpp_type_equals");
    log(INFO, "Loaded: il2cpp_type_equals");
    *(void**)(&type_get_assembly_qualified_name) = dlsym(imagehandle, "il2cpp_type_get_assembly_qualified_name");
    log(INFO, "Loaded: il2cpp_type_get_assembly_qualified_name");
    *(void**)(&image_get_assembly) = dlsym(imagehandle, "il2cpp_image_get_assembly");
    log(INFO, "Loaded: il2cpp_image_get_assembly");
    *(void**)(&image_get_name) = dlsym(imagehandle, "il2cpp_image_get_name");
    log(INFO, "Loaded: il2cpp_image_get_name");
    *(void**)(&image_get_filename) = dlsym(imagehandle, "il2cpp_image_get_filename");
    log(INFO, "Loaded: il2cpp_image_get_filename");
    *(void**)(&image_get_entry_point) = dlsym(imagehandle, "il2cpp_image_get_entry_point");
    log(INFO, "Loaded: il2cpp_image_get_entry_point");
    *(void**)(&image_get_class_count) = dlsym(imagehandle, "il2cpp_image_get_class_count");
    log(INFO, "Loaded: il2cpp_image_get_class_count");
    *(void**)(&image_get_class) = dlsym(imagehandle, "il2cpp_image_get_class");
    log(INFO, "Loaded: il2cpp_image_get_class");
    *(void**)(&capture_memory_snapshot) = dlsym(imagehandle, "il2cpp_capture_memory_snapshot");
    log(INFO, "Loaded: il2cpp_capture_memory_snapshot");
    *(void**)(&free_captured_memory_snapshot) = dlsym(imagehandle, "il2cpp_free_captured_memory_snapshot");
    log(INFO, "Loaded: il2cpp_free_captured_memory_snapshot");
    *(void**)(&set_find_plugin_callback) = dlsym(imagehandle, "il2cpp_set_find_plugin_callback");
    log(INFO, "Loaded: il2cpp_set_find_plugin_callback");
    *(void**)(&register_log_callback) = dlsym(imagehandle, "il2cpp_register_log_callback");
    log(INFO, "Loaded: il2cpp_register_log_callback");
    *(void**)(&debugger_set_agent_options) = dlsym(imagehandle, "il2cpp_debugger_set_agent_options");
    log(INFO, "Loaded: il2cpp_debugger_set_agent_options");
    *(void**)(&is_debugger_attached) = dlsym(imagehandle, "il2cpp_is_debugger_attached");
    log(INFO, "Loaded: il2cpp_is_debugger_attached");
    *(void**)(&unity_install_unitytls_interface) = dlsym(imagehandle, "il2cpp_unity_install_unitytls_interface");
    log(INFO, "Loaded: il2cpp_unity_install_unitytls_interface");
    *(void**)(&custom_attrs_from_class) = dlsym(imagehandle, "il2cpp_custom_attrs_from_class");
    log(INFO, "Loaded: il2cpp_custom_attrs_from_class");
    *(void**)(&custom_attrs_from_method) = dlsym(imagehandle, "il2cpp_custom_attrs_from_method");
    log(INFO, "Loaded: il2cpp_custom_attrs_from_method");
    *(void**)(&custom_attrs_get_attr) = dlsym(imagehandle, "il2cpp_custom_attrs_get_attr");
    log(INFO, "Loaded: il2cpp_custom_attrs_get_attr");
    *(void**)(&custom_attrs_has_attr) = dlsym(imagehandle, "il2cpp_custom_attrs_has_attr");
    log(INFO, "Loaded: il2cpp_custom_attrs_has_attr");
    *(void**)(&custom_attrs_construct) = dlsym(imagehandle, "il2cpp_custom_attrs_construct");
    log(INFO, "Loaded: il2cpp_custom_attrs_construct");
    *(void**)(&custom_attrs_free) = dlsym(imagehandle, "il2cpp_custom_attrs_free");
    log(INFO, "Loaded: il2cpp_custom_attrs_free");

    // MANUALLY DEFINED CONST DEFINITIONS
    *(void**)(&class_get_type_const) = dlsym(imagehandle, "il2cpp_class_get_type");
    log(INFO, "Loaded: il2cpp_class_get_type CONST VERSION!");
    *(void**)(&il2cpp_functions::class_get_name_const) = dlsym(imagehandle, "il2cpp_class_get_name");
    log(INFO, "Loaded: il2cpp_class_get_name CONST VERSION!");

    INSTALL_HOOK_DIRECT(MetadataCache_Register_Hook, il2cpp_functions::MetadataCache_Register);

    dlclose(imagehandle);
    initialized = true;
    log(INFO, "il2cpp_functions: Init: Successfully loaded all il2cpp functions!");
    usleep(100000L);
}
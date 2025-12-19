/*
*
* Copyright (C) 2021-2025 Intel Corporation
*
* SPDX-License-Identifier: MIT
*
*/
#ifndef _ZE_CONTEXT_NPU_EXT_H
#define _ZE_CONTEXT_NPU_EXT_H
#if defined(__cplusplus)
#pragma once
#endif

#ifndef ZE_CONTEXT_NPU_EXT_NAME
#define ZE_CONTEXT_NPU_EXT_NAME "ZE_extension_context_npu"
#endif

#if defined(__cplusplus)
extern "C" {
#endif

///////////////////////////////////////////////////////////////////////////////////////////////////////////////////////
/// @brief Supported Context Extension versions
/// 
/// @details
///     - NPU context extension versions contain major and minor attributes, use
///       ::ZE_MAJOR_VERSION and ::ZE_MINOR_VERSION
typedef enum _ze_context_npu_ext_version_t
{
    ZE_CONTEXT_NPU_EXT_VERSION_1_0 = ZE_MAKE_VERSION( 1, 0 ),               ///< version 1.0
    ZE_CONTEXT_NPU_EXT_VERSION_CURRENT = ZE_CONTEXT_NPU_EXT_VERSION_1_0,    ///< latest known version
    ZE_CONTEXT_NPU_EXT_VERSION_FORCE_UINT32 = 0x7fffffff

} ze_context_npu_ext_version_t;

///////////////////////////////////////////////////////////////////////////////////////////////////////////////////////
/// @brief Defines structure types
typedef enum _ze_structure_type_context_npu_ext_t
{
    ZE_STRUCTURE_TYPE_CONTEXT_PROPERTIES_NPU_EXT = 0x1,                     ///< ::_ze_context_desc_npu_ext_t
    ZE_STRUCTURE_TYPE_CONTEXT_FORCE_UINT32 = 0x7fffffff

} ze_structure_type_context_npu_ext_t;

///////////////////////////////////////////////////////////////////////////////////////////////////////////////////////
/// @brief Supported options
typedef uint32_t ze_npu_context_options_t;
typedef enum _ze_npu_context_option_t
{
    ZE_NPU_CONTEXT_OPTION_IDLE_OPTIMIZATIONS = ZE_BIT(0),                   ///< Memory optimizations when device goes idle
                                                                            ///<   1. idle memory optimizations are opt-out
                                                                            ///<   2. driver will deallocate and/or evict memory
                                                                            ///<   3. latency sensitive workloads should consider disabling
    ZE_NPU_CONTEXT_OPTION_FORCE_UINT32 = 0x7fffffff

} ze_npu_context_option_t;

///////////////////////////////////////////////////////////////////////////////////////////////////////////////////////
/// @brief NPU context properties passed in through ze_pfnContextSetProperties_ext_t
typedef struct _ze_context_properties_npu_ext_t
{
    ze_structure_type_context_npu_ext_t stype;                              ///< [in] type of this structure
    const void* pNext;                                                      ///< [in][optional] must be null or a pointer to an extension-specific structure
    ze_npu_context_options_t options;                                       ///< [in] valid combination of ze_npu_context_options_t

} ze_context_properties_npu_ext_t;

///////////////////////////////////////////////////////////////////////////////////////////////////////////////////////
typedef ze_result_t (ZE_APICALL *ze_pfnContextSetProperties_ext_t)(
    ze_context_handle_t hContext,                                           ///< [in] handle of the context
    ze_context_properties_npu_ext_t *ContextProperties                      ///< [in] context properties
    );

///////////////////////////////////////////////////////////////////////////////////////////////////////////////////////
typedef ze_result_t (ZE_APICALL *ze_pfnContextReleaseMemory_ext_t)(
    ze_context_handle_t hContext                                            ///< [in] handle of the context
    );

///////////////////////////////////////////////////////////////////////////////////////////////////////////////////////
/// @brief Table of Context NPU functions pointers
typedef struct _ze_context_npu_dditable_ext_t
{
    // version 1.0
    ze_pfnContextSetProperties_ext_t pfnSetProperties;
    ze_pfnContextReleaseMemory_ext_t pfnReleaseMemory;

} ze_context_npu_dditable_ext_t;


#if defined(__cplusplus)
} // extern "C"
#endif

#endif // _ZE_CONTEXT_NPU_EXT_H

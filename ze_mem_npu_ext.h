/*
*
* Copyright (C) 2026 Intel Corporation
*
* SPDX-License-Identifier: MIT
*
*/
#ifndef _ZE_MEM_NPU_EXT_H
#define _ZE_MEM_NPU_EXT_H
#if defined(__cplusplus)
#pragma once
#endif

#ifndef ZE_MEM_NPU_EXT_NAME
#define ZE_MEM_NPU_EXT_NAME "ZE_extension_mem_npu"
#endif

#if defined(__cplusplus)
extern "C" {
#endif

///////////////////////////////////////////////////////////////////////////////////////////////////////////////////////
/// @brief Supported Memory Extension versions
///
/// @details
///     - NPU memory extension versions contain major and minor attributes, use
///       ::ZE_MAJOR_VERSION and ::ZE_MINOR_VERSION
typedef enum _ze_mem_npu_ext_version_t
{
    ZE_MEM_NPU_EXT_VERSION_1_0 = ZE_MAKE_VERSION( 1, 0 ),                   ///< version 1.0
    ZE_MEM_NPU_EXT_VERSION_CURRENT = ZE_MEM_NPU_EXT_VERSION_1_0,            ///< latest known version
    ZE_MEM_NPU_EXT_VERSION_FORCE_UINT32 = 0x7fffffff

} ze_mem_npu_ext_version_t;

///////////////////////////////////////////////////////////////////////////////////////////////////////////////////////
/// @brief Defines structure types
///
/// @details
///     - These structures are chained onto core memory allocation descriptors next to core structures, so the values
///       are kept outside the ranges used by ::ze_structure_type_t
typedef enum _ze_structure_type_mem_npu_ext_t
{
    ZE_STRUCTURE_TYPE_MEM_USAGE_HINT_NPU_EXT = 0x7E000001,                  ///< ::ze_mem_usage_hint_npu_ext_desc_t
    ZE_STRUCTURE_TYPE_MEM_NPU_FORCE_UINT32 = 0x7fffffff

} ze_structure_type_mem_npu_ext_t;

///////////////////////////////////////////////////////////////////////////////////////////////////////////////////////
/// @brief How the contents of a memory allocation are used by the NPU
typedef enum _ze_npu_mem_usage_t
{
    ZE_NPU_MEM_USAGE_DEFAULT = 0x0,                                         ///< no hint, same as omitting the descriptor
    ZE_NPU_MEM_USAGE_WEIGHTS = 0x1,                                         ///< read-only graph weights; the driver may page
                                                                            ///< the allocation in and out in parts as graphs
                                                                            ///< use them, while keeping one contiguous address range
    ZE_NPU_MEM_USAGE_FORCE_UINT32 = 0x7fffffff

} ze_npu_mem_usage_t;

///////////////////////////////////////////////////////////////////////////////////////////////////////////////////////
/// @brief Memory usage hint
///
/// @details
///     - May be chained into the pNext list of ::ze_host_mem_alloc_desc_t, ::ze_device_mem_alloc_desc_t or
///       ::ze_physical_mem_desc_t, in any position, including together with a memory import descriptor such as
///       ::ze_external_memmap_sysmem_ext_desc_t.
///     - Supported when the driver reports the ::ZE_MEM_NPU_EXT_NAME extension.
///     - The hint does not change the allocation's API semantics: it is freed as one allocation, and host
///       allocations stay host accessible.
///     - Graph arguments bound into a ::ZE_NPU_MEM_USAGE_WEIGHTS allocation should report their extent with
///       ze_graph_argument_size_desc_t (graph extension 1.21), so only the parts they use need to be resident.
///     - Returns ::ZE_RESULT_ERROR_INVALID_ENUMERATION if usage is not a ::ze_npu_mem_usage_t value.
typedef struct _ze_mem_usage_hint_npu_ext_desc_t
{
    ze_structure_type_mem_npu_ext_t stype;                                  ///< [in] ZE_STRUCTURE_TYPE_MEM_USAGE_HINT_NPU_EXT
    const void* pNext;                                                      ///< [in][optional] next memory allocation descriptor
    ze_npu_mem_usage_t usage;                                               ///< [in] how the NPU uses the allocation's contents

} ze_mem_usage_hint_npu_ext_desc_t;

#if defined(__cplusplus)
} // extern "C"
#endif

#endif // _ZE_MEM_NPU_EXT_H

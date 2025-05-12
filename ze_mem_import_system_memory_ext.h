/*
*
* Copyright (C) 2021-2025 Intel Corporation
*
* SPDX-License-Identifier: MIT
*
*/
#ifndef _ZE_MEM_IMPORT_SYSTEM_MEMORY_EXT_H
#define _ZE_MEM_IMPORT_SYSTEM_MEMORY_EXT_H
#if defined(__cplusplus)
#pragma once
#endif

#if defined(__cplusplus)
extern "C" {
#endif

///////////////////////////////////////////////////////////////////////////////
/// @brief Additional allocation descriptor for importing system memory
/// 
/// @details
///     - This structure may be passed to ::zeMemAllocHost, via the `pNext`
///       member of ::ze_host_mem_alloc_desc_t to import memory from
///       a system memory pointer.
typedef struct _ze_external_memory_import_system_memory_t
{
    ze_structure_type_graph_ext_t stype;                                    ///< [in] type of this structure
    const void* pNext;                                                      ///< [in][optional] must be null or a pointer to an extension-specific
                                                                            ///< structure (i.e. contains stype and pNext).
    void* pSystemMemory;                                                    ///< [in] system memory pointer to import; must be page-aligned.
    const uint64_t size;                                                    ///< [in] size of the system memory to import; must be page-aligned

} ze_external_memory_import_system_memory_t;

#define ZE_STRUCTURE_TYPE_EXTERNAL_MEMORY_IMPORT_SYSTEM_MEMORY 0x24        ///< ::ze_external_memory_import_system_memory_t
#define ZE_EXTERNAL_MEMORY_TYPE_FLAG_STANDARD_ALLOCATION 0x100

#if defined(__cplusplus)
} // extern "C"
#endif

#endif // _ZE_MEM_IMPORT_SYSTEM_MEMORY_EXT_H

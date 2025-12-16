/*
*
* Copyright (C) 2021-2025 Intel Corporation
*
* SPDX-License-Identifier: MIT
*
*/
#ifndef _ZE_DRIVER_NPU_EXT_H
#define _ZE_DRIVER_NPU_EXT_H
#if defined(__cplusplus)
#pragma once
#endif

#ifndef ZE_DRIVER_NPU_EXT_NAME
#define ZE_DRIVER_NPU_EXT_NAME "ZE_extension_driver_npu"
#endif

#if defined(__cplusplus)
extern "C" {
#endif

///////////////////////////////////////////////////////////////////////////////////////////////////////////////////////
/// @brief Supported Driver Extension versions
/// 
/// @details
///     - NPU driver extension versions contain major and minor attributes, use
///       ::ZE_MAJOR_VERSION and ::ZE_MINOR_VERSION
typedef enum _ze_driver_npu_ext_version_t
{
    ZE_DRIVER_NPU_EXT_VERSION_1_0 = ZE_MAKE_VERSION( 1, 0 ),                ///< version 1.0
    ZE_DRIVER_NPU_EXT_VERSION_CURRENT = ZE_DRIVER_NPU_EXT_VERSION_1_0,      ///< latest known version
    ZE_DRIVER_NPU_EXT_VERSION_FORCE_UINT32 = 0x7fffffff

} ze_driver_npu_ext_version_t;

///////////////////////////////////////////////////////////////////////////////////////////////////////////////////////
/// @brief Defines structure types
typedef enum _ze_structure_type_driver_npu_ext_t
{
    ZE_STRUCTURE_TYPE_DRIVER_EXTENSION_NPU_EXT = 0x1,                       ///< ::ze_driver_extension_npu_ext_t
    ZE_STRUCTURE_TYPE_DRIVER_FORCE_UINT32 = 0x7fffffff

} ze_structure_type_driver_npu_ext_t;

///////////////////////////////////////////////////////////////////////////////////////////////////////////////////////
/// @brief NPU driver extension passed in through ze_pfnDriverGetExtension_ext_t
typedef struct _ze_driver_extension_npu_ext_t
{
    ze_structure_type_driver_npu_ext_t stype;                               ///< [in] type of this structure
    const void* pNext;                                                      ///< [in][optional] must be null or a pointer to an extension-specific structure
    const char* name;                                                       ///< [in] extension function name
    uint32_t version;                                                       ///< [in] extension function version
    void** ppFunctionAddress;                                               ///< [out] pointer to function pointer

} ze_driver_extension_npu_ext_t;

///////////////////////////////////////////////////////////////////////////////////////////////////////////////////////
typedef ze_result_t (ZE_APICALL *ze_pfnDriverGetExtension_ext_t)(
    ze_driver_handle_t hDriver,                                             ///< [in] handle of the driver
    ze_driver_extension_npu_ext_t* pExtension                               ///< [in,out] pointer to extension structure
    );

///////////////////////////////////////////////////////////////////////////////////////////////////////////////////////
/// @brief Table of DRIVER NPU functions pointers
typedef struct _ze_driver_npu_dditable_ext_t
{
    // version 1.0
    ze_pfnDriverGetExtension_ext_t              pfnGetExtension;

} ze_driver_npu_dditable_ext_t;


#if defined(__cplusplus)
} // extern "C"
#endif

#endif // _ZE_DRIVER_NPU_EXT_H

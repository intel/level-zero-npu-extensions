/*
*
* Copyright (C) 2021-2025 Intel Corporation
*
* SPDX-License-Identifier: MIT
*
*/
#ifndef _ZE_COMMAND_QUEUE_NPU_EXT_H
#define _ZE_COMMAND_QUEUE_NPU_EXT_H
#if defined(__cplusplus)
#pragma once
#endif

#ifndef ZE_COMMAND_QUEUE_NPU_EXT_NAME
#define ZE_COMMAND_QUEUE_NPU_EXT_NAME "ZE_extension_command_queue_npu"
#endif

#if defined(__cplusplus)
extern "C" {
#endif

///////////////////////////////////////////////////////////////////////////////
/// @brief Supported Command Queue Extension versions
/// 
/// @details
///     - NPU command queue extension versions contain major and minor attributes, use
///       ::ZE_MAJOR_VERSION and ::ZE_MINOR_VERSION
typedef enum _ze_command_queue_npu_ext_version_t
{
    ZE_COMMAND_QUEUE_NPU_EXT_VERSION_1_0 = ZE_MAKE_VERSION( 1, 0 ),                     ///< version 1.0
    ZE_COMMAND_QUEUE_NPU_EXT_VERSION_1_1 = ZE_MAKE_VERSION( 1, 1 ),                     ///< version 1.1
    ZE_COMMAND_QUEUE_NPU_EXT_VERSION_CURRENT = ZE_COMMAND_QUEUE_NPU_EXT_VERSION_1_1,    ///< latest known version
    ZE_COMMAND_QUEUE_NPU_EXT_VERSION_FORCE_UINT32 = 0x7fffffff

} ze_command_queue_npu_ext_version_t;

///////////////////////////////////////////////////////////////////////////////
/// @brief Defines structure types
typedef enum _ze_structure_type_command_queue_npu_ext_t
{
    ZE_STRUCTURE_TYPE_COMMAND_QUEUE_DESC_NPU_EXT = 0x1,     ///< ::_ze_command_queue_desc_npu_ext_t
    ZE_STRUCTURE_TYPE_COMMAND_QUEUE_DESC_NPU_EXT_2 = 0x2,   ///< ::_ze_command_queue_desc_npu_ext_2_t

} ze_structure_type_command_queue_npu_ext_t;

///////////////////////////////////////////////////////////////////////////////
/// @brief NPU command queue descriptor npu extension
typedef struct _ze_command_queue_desc_npu_ext_t
{
    ze_structure_type_command_queue_npu_ext_t stype;        ///< [in] type of this structure
    const void* pNext;                                      ///< [in][optional] must be null or a pointer to an extension-specific structure
    bool turbo;                                             ///< [in] command queue context turbo mode

} ze_command_queue_desc_npu_ext_t;


///////////////////////////////////////////////////////////////////////////////
/// @brief Command Queue Workload Type
typedef enum _ze_command_queue_workload_type_t
{
    ZE_WORKLOAD_TYPE_DEFAULT = 0x0,
    ZE_WORKLOAD_TYPE_BACKGROUND = 0x1,

    ZE_WORKLOAD_TYPE_FORCE_UINT32 = 0x7fffffff

} ze_command_queue_workload_type_t;

///////////////////////////////////////////////////////////////////////////////
typedef ze_result_t (ZE_APICALL *ze_pfnCommandQueueSetWorkloadType_ext_t)(
    ze_command_queue_handle_t hCommandQueue,                ///< [in] handle of the device
    ze_command_queue_workload_type_t workloadType           ///< [in] workload type
    );

///////////////////////////////////////////////////////////////////////////////
/// @brief Extension version 1.1
///
/// Adds ::ze_pfnCommandQueueCreate_npu_ext_t to introduce command queue sync mode

///////////////////////////////////////////////////////////////////////////////
/// @brief Supported options to query
typedef uint32_t ze_npu_command_queue_options_t;
typedef enum _ze_npu_command_queue_option_t
{
    ZE_NPU_COMMAND_QUEUE_OPTION_TURBO = ZE_BIT(0),          ///< Enable turbo mode
    ZE_NPU_COMMAND_QUEUE_OPTION_DEVICE_SYNC = ZE_BIT(1),    ///< Device synchronization between submissions on this queue
    ZE_NPU_COMMAND_QUEUE_OPTIONS_FORCE_UINT32 = 0x7fffffff

} ze_npu_command_queue_option_t;

///////////////////////////////////////////////////////////////////////////////
/// @brief NPU command queue descriptor npu extension
typedef struct _ze_command_queue_desc_npu_ext_2_t
{
    ze_structure_type_command_queue_npu_ext_t stype;        ///< [in] type of this structure
    const void* pNext;                                      ///< [in][optional] must be null or a pointer to an extension-specific structure
    ze_npu_command_queue_options_t options;                 ///< [in] valid combination of ze_npu_command_queue_options_t

} ze_command_queue_desc_npu_ext_2_t;

///////////////////////////////////////////////////////////////////////////////
/// @brief Table of Command Queue NPU functions pointers
typedef struct _ze_command_queue_npu_dditable_ext_t
{
    // version 1.0
    ze_pfnCommandQueueSetWorkloadType_ext_t pfnSetWorkloadType;

} ze_command_queue_npu_dditable_ext_t;


#if defined(__cplusplus)
} // extern "C"
#endif

#endif // _ZE_COMMAND_QUEUE_NPU_EXT_H

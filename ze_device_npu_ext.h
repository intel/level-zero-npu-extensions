/*
*
* Copyright (C) 2026 Intel Corporation
*
* SPDX-License-Identifier: MIT
*
*/
#ifndef _ZE_DEVICE_NPU_EXT_H
#define _ZE_DEVICE_NPU_EXT_H
#if defined(__cplusplus)
#pragma once
#endif

#ifndef ZE_DEVICE_NPU_EXT_NAME
#define ZE_DEVICE_NPU_EXT_NAME "ZE_extension_device_npu"
#endif

#if defined(__cplusplus)
extern "C" {
#endif

///////////////////////////////////////////////////////////////////////////////////////////////////////////////////////
/// @brief Supported Device NPU Extension versions
///
/// @details
///     - NPU device extension versions contain major and minor attributes, use
///       ::ZE_MAJOR_VERSION and ::ZE_MINOR_VERSION
typedef enum _ze_device_npu_ext_version_t
{
    ZE_DEVICE_NPU_EXT_VERSION_1_0 = ZE_MAKE_VERSION( 1, 0 ),               ///< version 1.0
    ZE_DEVICE_NPU_EXT_VERSION_CURRENT = ZE_DEVICE_NPU_EXT_VERSION_1_0,     ///< latest known version
    ZE_DEVICE_NPU_EXT_VERSION_FORCE_UINT32 = 0x7fffffff

} ze_device_npu_ext_version_t;

///////////////////////////////////////////////////////////////////////////////////////////////////////////////////////
/// @brief Defines structure types
typedef enum _ze_structure_type_device_npu_ext_t
{
    ZE_STRUCTURE_TYPE_RUNTIME_REQUIREMENTS_GRAPH_DESC = 0x00020043,         ///< ::ze_runtime_requirements_graph_desc_t
    ZE_STRUCTURE_TYPE_VALIDATE_RUNTIME_REQUIREMENTS_OUTPUT = 0x00020044,    ///< ::ze_validate_runtime_requirements_output_t
    ZE_STRUCTURE_TYPE_DEVICE_NPU_EXT_FORCE_UINT32 = 0x7fffffff

} ze_structure_type_device_npu_ext_t;

///////////////////////////////////////////////////////////////////////////////////////////////////////////////////////
/// @brief Describes the graph for which runtime requirements are being gathered
typedef struct _ze_runtime_requirements_graph_desc_t
{
    ze_structure_type_device_npu_ext_t stype;                               ///< [in] must be ZE_STRUCTURE_TYPE_RUNTIME_REQUIREMENTS_GRAPH_DESC
    const void* pNext;                                                      ///< [in][optional] must be null or a pointer to an extension-specific structure
    ze_graph_handle_t requirementsSrc;                                      ///< [in] graph for which the requirements are being gathered

} ze_runtime_requirements_graph_desc_t;

///////////////////////////////////////////////////////////////////////////////////////////////////////////////////////
/// @brief Result of runtime requirements validation
typedef enum _ze_validate_runtime_requirements_result_t
{
    ZE_VALIDATE_RUNTIME_REQUIREMENTS_RESULT_NOT_APPLICABLE = 0,             ///< provided requirements are not applicable to underlying device
    ZE_VALIDATE_RUNTIME_REQUIREMENTS_RESULT_REQUIREMENTS_MET = 1,           ///< provided requirements are met and optimal
    ZE_VALIDATE_RUNTIME_REQUIREMENTS_RESULT_REQUIREMENTS_MET_RECOMPILATION_ADVISABLE = 2,
                                                                            ///< provided requirements are met, but recompilation is advisable
    ZE_VALIDATE_RUNTIME_REQUIREMENTS_RESULT_REQUIREMENTS_NOT_MET = 3,       ///< requirements are not met
    ZE_VALIDATE_RUNTIME_REQUIREMENTS_RESULT_FORCE_UINT32 = 0x7fffffff

} ze_validate_runtime_requirements_result_t;

///////////////////////////////////////////////////////////////////////////////////////////////////////////////////////
/// @brief Output of zeDeviceValidateRuntimeRequirements
typedef struct _ze_validate_runtime_requirements_output_t
{
    ze_structure_type_device_npu_ext_t stype;                               ///< [in] must be ZE_STRUCTURE_TYPE_VALIDATE_RUNTIME_REQUIREMENTS_OUTPUT
    void* pNext;                                                            ///< [in,out][optional] must be null or a pointer to an extension-specific structure
    ze_validate_runtime_requirements_result_t result;                        ///< [out] result of the validation call

} ze_validate_runtime_requirements_output_t;

///////////////////////////////////////////////////////////////////////////////////////////////////////////////////////
/// @brief Gathers runtime requirements for a device
typedef ze_result_t (ZE_APICALL *ze_pfnDeviceGetRuntimeRequirements_t)(
    ze_device_handle_t hDevice,                                             ///< [in] handle of the device
    const void* pObjDesc,                                                   ///< [in] describes the object for which requirements are to be gathered
    size_t* pSize,                                                          ///< [in,out] size of requirements string in bytes
    char* pRequirements                                                     ///< [in,out][optional] holds results of the query
    );

///////////////////////////////////////////////////////////////////////////////////////////////////////////////////////
/// @brief Retrieves requirements producer key
typedef ze_result_t (ZE_APICALL *ze_pfnDeviceGetRuntimeRequirementsKey_t)(
    ze_device_handle_t hDevice,                                             ///< [in] handle of the device
    const char** pKey                                                       ///< [out] returned key
    );

///////////////////////////////////////////////////////////////////////////////////////////////////////////////////////
/// @brief Validates runtime requirements
typedef ze_result_t (ZE_APICALL *ze_pfnDeviceValidateRuntimeRequirements_t)(
    ze_device_handle_t hDevice,                                             ///< [in] handle of the device
    const char* pRequirements,                                              ///< [in] requirements to be validated
    ze_validate_runtime_requirements_output_t* pOut                         ///< [in,out] output of the validation call
    );

///////////////////////////////////////////////////////////////////////////////////////////////////////////////////////
/// @brief Table of Device NPU function pointers
typedef struct _ze_device_npu_dditable_ext_t
{
    // version 1.0
    ze_pfnDeviceGetRuntimeRequirements_t        pfnGetRuntimeRequirements;
    ze_pfnDeviceGetRuntimeRequirementsKey_t     pfnGetRuntimeRequirementsKey;
    ze_pfnDeviceValidateRuntimeRequirements_t   pfnValidateRuntimeRequirements;

} ze_device_npu_dditable_ext_t;

#if defined(__cplusplus)
} // extern "C"
#endif

#endif // _ZE_DEVICE_NPU_EXT_H

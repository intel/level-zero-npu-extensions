/*
*
* Copyright (C) 2021-2023 Intel Corporation
*
* SPDX-License-Identifier: MIT
*
*/
#ifndef _ZE_GRAPH_EXT_H
#define _ZE_GRAPH_EXT_H
#if defined(__cplusplus)
#pragma once
#endif

#include "ze_api.h"
#include "ze_graph_profiling_ext.h"

#ifndef ZE_GRAPH_EXT_NAME
#define ZE_GRAPH_EXT_NAME "ZE_extension_graph"
#endif

#if defined(__cplusplus)
extern "C" {
#endif

///////////////////////////////////////////////////////////////////////////////
/// @brief Supported Graph Extension versions
/// 
/// @details
///     - Graph extension versions contain major and minor attributes, use
///       ::ZE_MAJOR_VERSION and ::ZE_MINOR_VERSION
typedef enum _ze_graph_ext_version_t
{
    ZE_GRAPH_EXT_VERSION_1_0 = ZE_MAKE_VERSION( 1, 0 ),         ///< version 1.0
    ZE_GRAPH_EXT_VERSION_CURRENT = ZE_GRAPH_EXT_VERSION_1_0,    ///< latest known version
    ZE_GRAPH_EXT_VERSION_FORCE_UINT32 = 0x7fffffff

} ze_graph_ext_version_t;

///////////////////////////////////////////////////////////////////////////////
/// @brief Bitfield of supported graph creation input formats
typedef enum _ze_graph_format_t
{
    ZE_GRAPH_FORMAT_NATIVE = 0x1,                   ///< Format is pre-compiled blob (elf, flatbuffers)
    ZE_GRAPH_FORMAT_NGRAPH_LITE = 0x2,              ///< Format is ngraph lite IR

} ze_graph_format_t;

///////////////////////////////////////////////////////////////////////////////
/// @brief Version information
typedef struct _ze_graph_compiler_version_info_t
{
    uint16_t major;
    uint16_t minor;

} ze_graph_compiler_version_info_t;

///////////////////////////////////////////////////////////////////////////////
/// @brief Defines structure types
typedef enum _ze_structure_type_graph_ext_t
{
    ZE_STRUCTURE_TYPE_DEVICE_GRAPH_PROPERTIES = 0x1,    ///< ::ze_device_graph_properties_t
    ZE_STRUCTURE_TYPE_GRAPH_DESC_PROPERTIES = 0x2,      ///< ::ze_graph_desc_t
    ZE_STRUCTURE_TYPE_GRAPH_PROPERTIES = 0x3,           ///< ::ze_graph_properties_t
    ZE_STRUCTURE_TYPE_GRAPH_ARGUMENT_PROPERTIES = 0x4,  ///< ::ze_graph_argument_properties_t
    ZE_STRUCTURE_TYPE_GRAPH_ACTIVATION_KERNEL = 0x5,    ///< ::ze_graph_activation_kernel_t

} ze_structure_type_graph_ext_t;

///////////////////////////////////////////////////////////////////////////////
/// @brief Device graph properties
typedef struct _ze_device_graph_properties_t
{
    ze_structure_type_graph_ext_t stype;                ///< [in] type of this structure
    void* pNext;                                        ///< [in,out][optional] must be null or a pointer to an extension-specific
    ze_graph_ext_version_t graphExtensionVersion;       ///< [out] graph extension version
    ze_graph_compiler_version_info_t compilerVersion;   ///< [out] compiler version
    ze_graph_format_t graphFormatsSupported;            ///< [out] graph formats supported
    uint32_t maxOVOpsetVersionSupported;                ///< [out] max OV opset version supported by the compiler

} ze_device_graph_properties_t;

///////////////////////////////////////////////////////////////////////////////
/// @brief Graph argument properties
typedef enum _ze_graph_argument_precision_t
{
    ZE_GRAPH_ARGUMENT_PRECISION_UNKNOWN = 0x00,

    ZE_GRAPH_ARGUMENT_PRECISION_FP32 = 0x01,
    ZE_GRAPH_ARGUMENT_PRECISION_FP16 = 0x02,
    ZE_GRAPH_ARGUMENT_PRECISION_BF16 = 0x09,

    ZE_GRAPH_ARGUMENT_PRECISION_UINT32 = 0x0A,
    ZE_GRAPH_ARGUMENT_PRECISION_UINT16 = 0x03,
    ZE_GRAPH_ARGUMENT_PRECISION_UINT8 = 0x04,
    ZE_GRAPH_ARGUMENT_PRECISION_UINT4 = 0x0B,

    ZE_GRAPH_ARGUMENT_PRECISION_INT32 = 0x05,
    ZE_GRAPH_ARGUMENT_PRECISION_INT16 = 0x06,
    ZE_GRAPH_ARGUMENT_PRECISION_INT8 = 0x07,
    ZE_GRAPH_ARGUMENT_PRECISION_INT4 = 0x0C,

    ZE_GRAPH_ARGUMENT_PRECISION_BIN = 0x08

} ze_graph_argument_precision_t;

///////////////////////////////////////////////////////////////////////////////
/// @brief Graph argument properties
typedef enum _ze_graph_argument_layout_t
{
    ZE_GRAPH_ARGUMENT_LAYOUT_ANY        = 0x00,

    ZE_GRAPH_ARGUMENT_LAYOUT_NCHW,
    ZE_GRAPH_ARGUMENT_LAYOUT_NHWC,
    ZE_GRAPH_ARGUMENT_LAYOUT_NCDHW,
    ZE_GRAPH_ARGUMENT_LAYOUT_NDHWC,

    ZE_GRAPH_ARGUMENT_LAYOUT_OIHW       = 0x40,

    ZE_GRAPH_ARGUMENT_LAYOUT_C          = 0x60,

    ZE_GRAPH_ARGUMENT_LAYOUT_CHW        = 0x80,

    ZE_GRAPH_ARGUMENT_LAYOUT_HW         = 0xC0,
    ZE_GRAPH_ARGUMENT_LAYOUT_NC,
    ZE_GRAPH_ARGUMENT_LAYOUT_CN,

    ZE_GRAPH_ARGUMENT_LAYOUT_BLOCKED    = 0xC8

} ze_graph_argument_layout_t;

///////////////////////////////////////////////////////////////////////////////
/// @brief Activation Shave Desc (passed through ze_graph_desc pNext)
typedef struct _ze_activation_kernel_desc_t
{
    ze_structure_type_graph_ext_t stype;            ///< [in] type of this structure
    void* pNext;                                    ///< [in,out][optional] must be null or a pointer to an extension-specific
    size_t kernelDataSize;                          ///< [in] Size of kernel data buffer in bytes
    const uint8_t* pKernelData;                     ///< [in] Pointer to kernel data buffer

} ze_activation_kernel_desc_t;

///////////////////////////////////////////////////////////////////////////////
/// @brief Graph descriptor
typedef struct _ze_graph_desc_t
{
    ze_structure_type_graph_ext_t stype;            ///< [in] type of this structure
    void* pNext;                                    ///< [in,out][optional] must be null or a pointer to an extension-specific
    ze_graph_format_t format;                       ///< [in] Graph format passed in with input
    size_t inputSize;                               ///< [in] Size of input buffer in bytes
    const uint8_t* pInput;                          ///< [in] Pointer to input buffer
    const char* pBuildFlags;                        ///< [in][optional] Null terminated string containing build flags. Following options are supported.
                                                    ///< Note: comma delimited, no spaces for precision/layout arguments
                                                    ///< -ze_graph_input_precision:precision,-ze_graph_output_precision:precision
                                                    ///<     UNKNOWN, FP32, FP16, UINT16, UINT8, UINT4, INT32, INT16, INT8, INT4, BIN, BF16
                                                    ///< -ze_graph_input_layout:layout,-ze_graph_output_layout:layout
                                                    ///<     ANY, NCHW, NHWC, NCDHW, NDHWC, OIHW, C, CHW, HW, NC, CN, BLOCKED
                                                    ///< -options:compile options string passed directly to compiler
} ze_graph_desc_t;

///////////////////////////////////////////////////////////////////////////////
/// @brief Example ze_graph_desc pBuildFlags
///
/// -ze_graph_input_precision:UINT8,-ze_graph_input_layout:NCHW,-ze_graph_output_precision:UINT8,-ze_graph_output_layout:NCHW,-options:VPUX_COMPILATION_MODE DefaultHW PERF_COUNT YES
///
///////////////////////////////////////////////////////////////////////////////

///////////////////////////////////////////////////////////////////////////////
/// @brief Graph properties
typedef struct _ze_graph_properties_t
{
    ze_structure_type_graph_ext_t stype;            ///< [in] type of this structure
    void* pNext;                                    ///< [in,out][optional] must be null or a pointer to an extension-specific
    uint32_t numGraphArgs;                          ///< [out] number of graph arguments

} ze_graph_properties_t;

///////////////////////////////////////////////////////////////////////////////
/// @brief Graph argument properties
typedef enum _ze_graph_argument_type_t
{
    ZE_GRAPH_ARGUMENT_TYPE_INPUT,
    ZE_GRAPH_ARGUMENT_TYPE_OUTPUT

} ze_graph_argument_type_t;

///////////////////////////////////////////////////////////////////////////////
#ifndef ZE_MAX_GRAPH_ARGUMENT_NAME
/// @brief Maximum device name string size
#define ZE_MAX_GRAPH_ARGUMENT_NAME  256
#endif // ZE_MAX_GRAPH_ARGUMENT_NAME

///////////////////////////////////////////////////////////////////////////////
#ifndef ZE_MAX_GRAPH_ARGUMENT_DIMENSIONS_SIZE
/// @brief Maximum device name string size
#define ZE_MAX_GRAPH_ARGUMENT_DIMENSIONS_SIZE 5
#endif // ZE_MAX_GRAPH_ARGUMENT_SIZE

///////////////////////////////////////////////////////////////////////////////
/// @brief Graph argument properties
typedef struct _ze_graph_argument_properties_t
{
    ze_structure_type_graph_ext_t stype;                    ///< [in] type of this structure
    void* pNext;                                            ///< [in,out][optional] must be null or a pointer to an extension-specific
    char name[ZE_MAX_GRAPH_ARGUMENT_NAME];                  ///< [out] name from input IR
    ze_graph_argument_type_t type;                          ///< [out] type of graph argument
    uint32_t dims[ZE_MAX_GRAPH_ARGUMENT_DIMENSIONS_SIZE];   ///< [out] tensor dimensions upto 5D
    ze_graph_argument_precision_t networkPrecision;         ///< [out] precision from input IR
    ze_graph_argument_layout_t networkLayout;               ///< [out] layout from input IR
    ze_graph_argument_precision_t devicePrecision;          ///< [out] precision from compiled executable
    ze_graph_argument_layout_t deviceLayout;                ///< [out] layout from compiled executable

} ze_graph_argument_properties_t;

///////////////////////////////////////////////////////////////////////////////
typedef ze_result_t (ZE_APICALL *ze_pfnDeviceGetGraphProperties_ext_t)(
    ze_device_handle_t hDevice,                           ///< [in] handle of the device
    ze_device_graph_properties_t *pDeviceGraphProperties  ///< [out] query result for graph properties of the device
    );

///////////////////////////////////////////////////////////////////////////////
typedef ze_result_t (ZE_APICALL *ze_pfnGraphCreate_ext_t)(
    ze_context_handle_t hContext,                   ///< [in] handle of the context
    ze_device_handle_t hDevice,                     ///< [in] handle of the device
    const ze_graph_desc_t* desc,                    ///< [in] pointer to graph descriptor
    ze_graph_handle_t* phGraph                      ///< [out] pointer to handle of graph object created
    );

///////////////////////////////////////////////////////////////////////////////
typedef ze_result_t (ZE_APICALL *ze_pfnGraphDestroy_ext_t)(
    ze_graph_handle_t hGraph                        ///< [in][release] handle of graph object to destroy
    );

//////////////////////////////////////////////////////////////////////////////
typedef ze_result_t (ZE_APICALL *ze_pfnGraphGetNativeBinary_ext_t)(
    ze_graph_handle_t hGraph,                       ///< [in] handle of the graph object
    size_t* pSize,                                  ///< [in,out] size of native binary in bytes.
    uint8_t* pGraphNativeBinary                     ///< [in,out][optional] byte pointer to native binary
    );

///////////////////////////////////////////////////////////////////////////////
typedef ze_result_t (ZE_APICALL *ze_pfnGraphGetProperties_ext_t)(
    ze_graph_handle_t hGraph,                       ///< [in] handle of the graph object
    ze_graph_properties_t* pGraphProperties         ///< [in,out] query result for graph properties.
    );

///////////////////////////////////////////////////////////////////////////////
typedef ze_result_t (ZE_APICALL *ze_pfnGraphGetArgumentProperties_ext_t)(
    ze_graph_handle_t hGraph,                                       ///< [in] handle of the graph object
    uint32_t argIndex,                                              ///< [in] index of the argument to get properties
    ze_graph_argument_properties_t* pGraphArgumentProperties        ///< [in,out] query result for graph argument properties.
    );

///////////////////////////////////////////////////////////////////////////////
typedef ze_result_t (ZE_APICALL *ze_pfnGraphSetArgumentValue_ext_t)(
    ze_graph_handle_t hGraph,                       ///< [in] handle of the graph object
    uint32_t argIndex,                              ///< [in] index of the argument
    const void* pArgValue                           ///< [in] value to bind to the index
    );

///////////////////////////////////////////////////////////////////////////////
typedef ze_result_t (ZE_APICALL *ze_pfnAppendGraphInitialize_ext_t)(
    ze_command_list_handle_t hCommandList,          ///< [in] handle of the command list
    ze_graph_handle_t hGraph,                       ///< [in] handle of the graph
    ze_event_handle_t hSignalEvent,                 ///< [in][optional] handle of the event to signal on completion 
    uint32_t numWaitEvents,                         ///< [in][optional] number of events to wait on before launching
    ze_event_handle_t* phWaitEvents                 ///< [in][optional] handle of the events to wait on before launching 
    );

///////////////////////////////////////////////////////////////////////////////
typedef ze_result_t (ZE_APICALL *ze_pfnAppendGraphExecute_ext_t)(
    ze_command_list_handle_t hCommandList,              ///< [in] handle of the command list
    ze_graph_handle_t hGraph,                           ///< [in] handle of the graph
    ze_graph_profiling_query_handle_t hProfilingQuery,  ///< [in][optional] handle of profiling query
    ze_event_handle_t hSignalEvent,                     ///< [in][optional] handle of the event to signal on completion
    uint32_t numWaitEvents,                             ///< [in][optional] number of events to wait on before launching
    ze_event_handle_t* phWaitEvents                     ///< [in][optional] handle of the events to wait on before launching
    );

///////////////////////////////////////////////////////////////////////////////
/// @brief Table of Graph functions pointers
typedef struct _ze_graph_dditable_ext_t
{
    ze_pfnGraphCreate_ext_t                                     pfnCreate;
    ze_pfnGraphDestroy_ext_t                                    pfnDestroy;
    ze_pfnGraphGetProperties_ext_t                              pfnGetProperties;
    ze_pfnGraphGetArgumentProperties_ext_t                      pfnGetArgumentProperties; 
    ze_pfnGraphSetArgumentValue_ext_t                           pfnSetArgumentValue;
    ze_pfnAppendGraphInitialize_ext_t                           pfnAppendGraphInitialize;
    ze_pfnAppendGraphExecute_ext_t                              pfnAppendGraphExecute;

    ze_pfnGraphGetNativeBinary_ext_t                            pfnGetNativeBinary;
    ze_pfnDeviceGetGraphProperties_ext_t                        pfnDeviceGetGraphProperties;

} ze_graph_dditable_ext_t;

#if defined(__cplusplus)
} // extern "C"
#endif

#endif // _ZE_GRAPH_EXT_H

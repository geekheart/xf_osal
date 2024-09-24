/**
 * @file xf_osal_internal.h
 * @author cangyu (sky.kirto@qq.com)
 * @brief
 * @version 0.1
 * @date 2024-09-20
 *
 * @copyright Copyright (c) 2024, CorAL. All rights reserved.
 *
 */

#ifndef __XF_OSAL_INTERNAL_H__
#define __XF_OSAL_INTERNAL_H__

/* ==================== [Includes] ========================================== */

#include "cmsis_os2.h"
#include "xf_osal.h"
#include "xf_cmsis_os2_config.h"

#ifdef __cplusplus
extern "C" {
#endif

/* ==================== [Defines] =========================================== */

/* ==================== [Typedefs] ========================================== */

/* ==================== [Global Prototypes] ================================= */

/* ==================== [Macros] ============================================ */

#define TRANSFORM_TO_XF_ERR(x) \
    ((status) == osOK ? XF_OK :        \
    (status) == osErrorTimeout ? XF_ERR_TIMEOUT : \
    (status) == osErrorResource ? XF_ERR_RESOURCE : \
    (status) == osErrorISR ? XF_ERR_ISR : \
    (status) == osErrorParameter ? XF_ERR_INVALID_ARG : \
    (status) == osErrorNoMemory ? XF_ERR_NO_MEM : \
    (status) == osError ? XF_FAIL : XF_FAIL)

#ifdef __cplusplus
} /* extern "C" */
#endif

#endif // __XF_OSAL_INTERNAL_H__

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

/* ==================== [Global Functions] ================================== */

static inline xf_err_t transform_to_xf_err(osStatus_t status)
{
    switch (status) {
    case osOK:
        return XF_OK;
    case osErrorTimeout:
        return XF_ERR_TIMEOUT;
    case osErrorResource:
        return XF_ERR_RESOURCE;
    case osErrorISR:
        return XF_ERR_ISR;
    case osErrorParameter:
        return XF_ERR_INVALID_ARG;
    case osErrorNoMemory:
        return XF_ERR_NO_MEM;
    case osError:
        return XF_FAIL;
    default:
        return XF_FAIL;
    }
}

#ifdef __cplusplus
} /* extern "C" */
#endif

#endif // __XF_OSAL_INTERNAL_H__

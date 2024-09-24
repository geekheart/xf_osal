/**
 * @file xf_osal_semaphore.c
 * @author cangyu (sky.kirto@qq.com)
 * @brief
 * @version 0.1
 * @date 2024-09-20
 *
 * @copyright Copyright (c) 2024, CorAL. All rights reserved.
 *
 */

/* ==================== [Includes] ========================================== */

#include "xf_osal_internal.h"

#if XF_OSAL_SEMAPHORE_IS_ENABLE

/* ==================== [Defines] =========================================== */

/* ==================== [Typedefs] ========================================== */

/* ==================== [Static Prototypes] ================================= */

/* ==================== [Static Variables] ================================== */

/* ==================== [Macros] ============================================ */

/* ==================== [Global Functions] ================================== */

xf_osal_semaphore_t xf_osal_semaphore_create(uint32_t max_count, uint32_t initial_count,
        const xf_osal_semaphore_attr_t *attr)
{
    return (xf_osal_semaphore_t)osSemaphoreNew(max_count, initial_count, (const osSemaphoreAttr_t *)attr);
}

xf_err_t xf_osal_semaphore_acquire(xf_osal_semaphore_t semaphore, uint32_t timeout)
{
    osStatus_t status = osSemaphoreAcquire((osSemaphoreId_t)semaphore, timeout);
    xf_err_t err = TRANSFORM_TO_XF_ERR(status);

    return err;
}

xf_err_t xf_osal_semaphore_release(xf_osal_semaphore_t semaphore)
{
    osStatus_t status = osSemaphoreRelease((osSemaphoreId_t)semaphore);
    xf_err_t err = TRANSFORM_TO_XF_ERR(status);

    return err;
}

uint32_t xf_osal_semaphore_get_count(xf_osal_semaphore_t semaphore)
{
    return osSemaphoreGetCount((osSemaphoreId_t)semaphore);
}

xf_err_t xf_osal_semaphore_delete(xf_osal_semaphore_t semaphore)
{
    osStatus_t status = osSemaphoreDelete((osSemaphoreId_t)semaphore);
    xf_err_t err = TRANSFORM_TO_XF_ERR(status);

    return err;
}

/* ==================== [Static Functions] ================================== */

#endif

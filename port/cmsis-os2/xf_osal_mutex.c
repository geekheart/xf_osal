/**
 * @file xf_osal_mutex.c
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

#if XF_OSAL_MUTEX_IS_ENABLE

/* ==================== [Defines] =========================================== */

/* ==================== [Typedefs] ========================================== */

/* ==================== [Static Prototypes] ================================= */

/* ==================== [Static Variables] ================================== */

/* ==================== [Macros] ============================================ */

/* ==================== [Global Functions] ================================== */

xf_osal_mutex_t xf_osal_mutex_create(const xf_osal_mutex_attr_t *attr)
{
    return (xf_osal_mutex_t)osMutexNew((const osMutexAttr_t *)attr);
}

xf_err_t xf_osal_mutex_acquire(xf_osal_mutex_t mutex, uint32_t timeout)
{
    osStatus_t status = osMutexAcquire((osMutexId_t)mutex, timeout);
    xf_err_t err = transform_to_xf_err(status);

    return err;
}

xf_err_t xf_osal_mutex_release(xf_osal_mutex_t mutex)
{
    osStatus_t status = osMutexRelease((osMutexId_t)mutex);
    xf_err_t err = transform_to_xf_err(status);

    return err;
}

xf_osal_thread_t xf_osal_mutex_get_owner(xf_osal_mutex_t mutex)
{
    return (xf_osal_thread_t)osMutexGetOwner((osMutexId_t)mutex);
}

xf_err_t xf_osal_mutex_delete(xf_osal_mutex_t mutex)
{
    osStatus_t status = osMutexDelete((osMutexId_t)mutex);
    xf_err_t err = transform_to_xf_err(status);

    return err;
}

/* ==================== [Static Functions] ================================== */

#endif

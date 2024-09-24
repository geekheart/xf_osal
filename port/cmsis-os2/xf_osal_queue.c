/**
 * @file xf_osal_queue.c
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

#if XF_OSAL_QUEUE_IS_ENABLE

/* ==================== [Defines] =========================================== */

/* ==================== [Typedefs] ========================================== */

/* ==================== [Static Prototypes] ================================= */

/* ==================== [Static Variables] ================================== */

/* ==================== [Macros] ============================================ */

/* ==================== [Global Functions] ================================== */

xf_osal_queue_t xf_osal_queue_create(uint32_t msg_count, uint32_t msg_size, const xf_osal_queue_attr_t *attr)
{
    return (xf_osal_queue_t)osMessageQueueNew(msg_count, msg_size, (const osMessageQueueAttr_t *)attr);
}

xf_err_t xf_osal_queue_put(xf_osal_queue_t queue, const void *msg_ptr, uint8_t msg_prio, uint32_t timeout)
{
    osStatus_t status = osMessageQueuePut((osMessageQueueId_t) queue, msg_ptr, msg_prio, timeout);
    xf_err_t err = TRANSFORM_TO_XF_ERR(status);

    return err;
}

xf_err_t xf_osal_queue_get(xf_osal_queue_t queue, void *msg_ptr, uint8_t *msg_prio, uint32_t timeout)
{
    osStatus_t status = osMessageQueueGet((osMessageQueueId_t) queue, msg_ptr, msg_prio, timeout);
    xf_err_t err = TRANSFORM_TO_XF_ERR(status);

    return err;
}

uint32_t xf_osal_queue_get_count(xf_osal_queue_t queue)
{
    return osMessageQueueGetCount((osMessageQueueId_t) queue);
}

xf_err_t xf_osal_queue_reset(xf_osal_queue_t queue)
{
    osStatus_t status = osMessageQueueReset((osMessageQueueId_t) queue);
    xf_err_t err = TRANSFORM_TO_XF_ERR(status);

    return err;
}

xf_err_t xf_osal_queue_delete(xf_osal_queue_t queue)
{
    osStatus_t status = osMessageQueueDelete((osMessageQueueId_t) queue);
    xf_err_t err = TRANSFORM_TO_XF_ERR(status);

    return err;
}

/* ==================== [Static Functions] ================================== */

#endif

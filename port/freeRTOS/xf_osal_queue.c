/**
 * @file xf_osal_queue.c
 * @author cangyu (sky.kirto@qq.com)
 * @brief
 * @version 0.1
 * @date 2024-09-11
 *
 * @copyright Copyright (c) 2024, CorAL. All rights reserved.
 *
 */

/* ==================== [Includes] ========================================== */

#include "xf_osal_internal.h"

/* ==================== [Defines] =========================================== */

#if XF_OSAL_QUEUE_IS_ENABLE

/* ==================== [Typedefs] ========================================== */

/* ==================== [Static Prototypes] ================================= */

/* ==================== [Static Variables] ================================== */

/* ==================== [Macros] ============================================ */

/* ==================== [Global Functions] ================================== */

xf_osal_queue_t xf_osal_queue_create(uint32_t msg_count, uint32_t msg_size, const xf_osal_queue_attr_t *attr)
{
    QueueHandle_t hQueue;
    int32_t mem;

    hQueue = NULL;

    if ((IRQ_Context() == 0U) && (msg_count > 0U) && (msg_size > 0U)) {
        mem = -1;

        if (attr != NULL) {
            if ((attr->cb_mem != NULL) && (attr->cb_size >= sizeof(StaticQueue_t)) &&
                    (attr->mq_mem != NULL) && (attr->mq_size >= (msg_count * msg_size))) {
                /* The memory for control block and message data is provided, use static object */
                mem = 1;
            } else {
                if ((attr->cb_mem == NULL) && (attr->cb_size == 0U) &&
                        (attr->mq_mem == NULL) && (attr->mq_size == 0U)) {
                    /* Control block will be allocated from the dynamic pool */
                    mem = 0;
                }
            }
        } else {
            mem = 0;
        }

        if (mem == 1) {
#if (configSUPPORT_STATIC_ALLOCATION == 1)
            hQueue = xQueueCreateStatic(msg_count, msg_size, attr->mq_mem, attr->cb_mem);
#endif
        } else {
            if (mem == 0) {
#if (configSUPPORT_DYNAMIC_ALLOCATION == 1)
                hQueue = xQueueCreate(msg_count, msg_size);
#endif
            }
        }

#if (configQUEUE_REGISTRY_SIZE > 0)
        if (hQueue != NULL) {
            if ((attr != NULL) && (attr->name != NULL)) {
                /* Only non-NULL name objects are added to the Queue Registry */
                vQueueAddToRegistry(hQueue, attr->name);
            }
        }
#endif

    }

    /* Return message queue ID */
    return ((xf_osal_queue_t)hQueue);
}

xf_err_t xf_osal_queue_put(xf_osal_queue_t queue, const void *msg_ptr, uint8_t msg_prio, uint32_t timeout)
{
    QueueHandle_t hQueue = (QueueHandle_t)queue;
    xf_err_t stat;
    BaseType_t yield;

    (void)msg_prio; /* Message priority is ignored */

    stat = XF_OK;

    if (IRQ_Context() != 0U) {
        if ((hQueue == NULL) || (msg_ptr == NULL) || (timeout != 0U)) {
            stat = XF_ERR_INVALID_ARG;
        } else {
            yield = pdFALSE;

            if (xQueueSendToBackFromISR(hQueue, msg_ptr, &yield) != pdTRUE) {
                stat = XF_ERR_RESOURCE;
            } else {
                portYIELD_FROM_ISR(yield);
            }
        }
    } else {
        if ((hQueue == NULL) || (msg_ptr == NULL)) {
            stat = XF_ERR_INVALID_ARG;
        } else {
            if (xQueueSendToBack(hQueue, msg_ptr, (TickType_t)timeout) != pdPASS) {
                if (timeout != 0U) {
                    stat = XF_ERR_TIMEOUT;
                } else {
                    stat = XF_ERR_RESOURCE;
                }
            }
        }
    }

    /* Return execution status */
    return (stat);
}

xf_err_t xf_osal_queue_get(xf_osal_queue_t queue, void *msg_ptr, uint8_t *msg_prio, uint32_t timeout)
{
    QueueHandle_t hQueue = (QueueHandle_t)queue;
    xf_err_t stat;
    BaseType_t yield;

    (void)msg_prio; /* Message priority is ignored */

    stat = XF_OK;

    if (IRQ_Context() != 0U) {
        if ((hQueue == NULL) || (msg_ptr == NULL) || (timeout != 0U)) {
            stat = XF_ERR_INVALID_ARG;
        } else {
            yield = pdFALSE;

            if (xQueueReceiveFromISR(hQueue, msg_ptr, &yield) != pdPASS) {
                stat = XF_ERR_RESOURCE;
            } else {
                portYIELD_FROM_ISR(yield);
            }
        }
    } else {
        if ((hQueue == NULL) || (msg_ptr == NULL)) {
            stat = XF_ERR_INVALID_ARG;
        } else {
            if (xQueueReceive(hQueue, msg_ptr, (TickType_t)timeout) != pdPASS) {
                if (timeout != 0U) {
                    stat = XF_ERR_TIMEOUT;
                } else {
                    stat = XF_ERR_RESOURCE;
                }
            }
        }
    }

    /* Return execution status */
    return (stat);
}

uint32_t xf_osal_queue_get_count(xf_osal_queue_t queue)
{
    QueueHandle_t hQueue = (QueueHandle_t)queue;
    UBaseType_t count;

    if (hQueue == NULL) {
        count = 0U;
    } else if (IRQ_Context() != 0U) {
        count = uxQueueMessagesWaitingFromISR(hQueue);
    } else {
        count = uxQueueMessagesWaiting(hQueue);
    }

    /* Return number of queued messages */
    return ((uint32_t)count);
}

xf_err_t xf_osal_queue_reset(xf_osal_queue_t queue)
{
    QueueHandle_t hQueue = (QueueHandle_t)queue;
    xf_err_t stat;

    if (IRQ_Context() != 0U) {
        stat = XF_ERR_ISR;
    } else if (hQueue == NULL) {
        stat = XF_ERR_INVALID_ARG;
    } else {
        stat = XF_OK;
        (void)xQueueReset(hQueue);
    }

    /* Return execution status */
    return (stat);
}

xf_err_t xf_osal_queue_delete(xf_osal_queue_t queue)
{
    QueueHandle_t hQueue = (QueueHandle_t)queue;
    xf_err_t stat;

#ifndef USE_FreeRTOS_HEAP_1
    if (IRQ_Context() != 0U) {
        stat = XF_ERR_ISR;
    } else if (hQueue == NULL) {
        stat = XF_ERR_INVALID_ARG;
    } else {
#if (configQUEUE_REGISTRY_SIZE > 0)
        vQueueUnregisterQueue(hQueue);
#endif

        stat = XF_OK;
        vQueueDelete(hQueue);
    }
#else
    stat = XF_FAIL;
#endif

    /* Return execution status */
    return (stat);
}

/* ==================== [Static Functions] ================================== */

#endif

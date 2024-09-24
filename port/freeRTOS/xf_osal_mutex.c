/**
 * @file xf_osal_mutex.c
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

#if XF_OSAL_MUTEX_IS_ENABLE

/* ==================== [Defines] =========================================== */

/* ==================== [Typedefs] ========================================== */

/* ==================== [Static Prototypes] ================================= */

/* ==================== [Static Variables] ================================== */

/* ==================== [Macros] ============================================ */

/* ==================== [Global Functions] ================================== */
xf_osal_mutex_t xf_osal_mutex_create(const xf_osal_mutex_attr_t *attr)
{
    SemaphoreHandle_t hMutex;
    uint32_t type;
    uint32_t rmtx;
    int32_t  mem;

    hMutex = NULL;

    if (IRQ_Context() == 0U) {
        if (attr != NULL) {
            type = attr->attr_bits;
        } else {
            type = 0U;
        }

        if ((type & XF_OSAL_MUTEX_RECURSIVE) == XF_OSAL_MUTEX_RECURSIVE) {
            rmtx = 1U;
        } else {
            rmtx = 0U;
        }

        if ((type & XF_OSAL_MUTEX_ROBUST) != XF_OSAL_MUTEX_ROBUST) {
            mem = -1;

            if (attr != NULL) {
                if ((attr->cb_mem != NULL) && (attr->cb_size >= sizeof(StaticSemaphore_t))) {
                    /* The memory for control block is provided, use static object */
                    mem = 1;
                } else {
                    if ((attr->cb_mem == NULL) && (attr->cb_size == 0U)) {
                        /* Control block will be allocated from the dynamic pool */
                        mem = 0;
                    }
                }
            } else {
                mem = 0;
            }

            if (mem == 1) {
#if (configSUPPORT_STATIC_ALLOCATION == 1)
                if (rmtx != 0U) {
#if (configUSE_RECURSIVE_MUTEXES == 1)
                    hMutex = xSemaphoreCreateRecursiveMutexStatic(attr->cb_mem);
#endif
                } else {
                    hMutex = xSemaphoreCreateMutexStatic(attr->cb_mem);
                }
#endif
            } else {
                if (mem == 0) {
#if (configSUPPORT_DYNAMIC_ALLOCATION == 1)
                    if (rmtx != 0U) {
#if (configUSE_RECURSIVE_MUTEXES == 1)
                        hMutex = xSemaphoreCreateRecursiveMutex();
#endif
                    } else {
                        hMutex = xSemaphoreCreateMutex();
                    }
#endif
                }
            }

#if (configQUEUE_REGISTRY_SIZE > 0)
            if (hMutex != NULL) {
                if ((attr != NULL) && (attr->name != NULL)) {
                    /* Only non-NULL name objects are added to the Queue Registry */
                    vQueueAddToRegistry(hMutex, attr->name);
                }
            }
#endif

            if ((hMutex != NULL) && (rmtx != 0U)) {
                /* Set LSB as 'recursive mutex flag' */
                hMutex = (SemaphoreHandle_t)((uint32_t)hMutex | 1U);
            }
        }
    }

    /* Return mutex ID */
    return ((xf_osal_mutex_t)hMutex);
}

xf_err_t xf_osal_mutex_acquire(xf_osal_mutex_t mutex, uint32_t timeout)
{
    SemaphoreHandle_t hMutex;
    xf_err_t stat;
    uint32_t rmtx;

    hMutex = (SemaphoreHandle_t)((uint32_t)mutex & ~1U);

    /* Extract recursive mutex flag */
    rmtx = (uint32_t)mutex & 1U;

    stat = XF_OK;

    if (IRQ_Context() != 0U) {
        stat = XF_ERR_ISR;
    } else if (hMutex == NULL) {
        stat = XF_ERR_INVALID_ARG;
    } else {
        if (rmtx != 0U) {
#if (configUSE_RECURSIVE_MUTEXES == 1)
            if (xSemaphoreTakeRecursive(hMutex, timeout) != pdPASS) {
                if (timeout != 0U) {
                    stat = XF_ERR_TIMEOUT;
                } else {
                    stat = XF_ERR_RESOURCE;
                }
            }
#endif
        } else {
            if (xSemaphoreTake(hMutex, timeout) != pdPASS) {
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

xf_err_t xf_osal_mutex_release(xf_osal_mutex_t mutex)
{
    SemaphoreHandle_t hMutex;
    xf_err_t stat;
    uint32_t rmtx;

    hMutex = (SemaphoreHandle_t)((uint32_t)mutex & ~1U);

    /* Extract recursive mutex flag */
    rmtx = (uint32_t)mutex & 1U;

    stat = XF_OK;

    if (IRQ_Context() != 0U) {
        stat = XF_ERR_ISR;
    } else if (hMutex == NULL) {
        stat = XF_ERR_INVALID_ARG;
    } else {
        if (rmtx != 0U) {
#if (configUSE_RECURSIVE_MUTEXES == 1)
            if (xSemaphoreGiveRecursive(hMutex) != pdPASS) {
                stat = XF_ERR_RESOURCE;
            }
#endif
        } else {
            if (xSemaphoreGive(hMutex) != pdPASS) {
                stat = XF_ERR_RESOURCE;
            }
        }
    }

    /* Return execution status */
    return (stat);
}

xf_osal_thread_t xf_osal_mutex_get_owner(xf_osal_mutex_t mutex)
{
    SemaphoreHandle_t hMutex;
    xf_osal_thread_t owner;

    hMutex = (SemaphoreHandle_t)((uint32_t)mutex & ~1U);

    if ((IRQ_Context() != 0U) || (hMutex == NULL)) {
        owner = NULL;
    } else {
        owner = (xf_osal_thread_t)xSemaphoreGetMutexHolder(hMutex);
    }

    /* Return owner thread ID */
    return (owner);
}

xf_err_t xf_osal_mutex_delete(xf_osal_mutex_t mutex)
{
    xf_err_t stat;
#ifndef USE_FreeRTOS_HEAP_1
    SemaphoreHandle_t hMutex;

    hMutex = (SemaphoreHandle_t)((uint32_t)mutex & ~1U);

    if (IRQ_Context() != 0U) {
        stat = XF_ERR_ISR;
    } else if (hMutex == NULL) {
        stat = XF_ERR_INVALID_ARG;
    } else {
#if (configQUEUE_REGISTRY_SIZE > 0)
        vQueueUnregisterQueue(hMutex);
#endif
        stat = XF_OK;
        vSemaphoreDelete(hMutex);
    }
#else
    stat = XF_FAIL;
#endif

    /* Return execution status */
    return (stat);
}
/* ==================== [Static Functions] ================================== */

#endif

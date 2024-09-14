/**
 * @file xf_osal_event.c
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

#if XF_OSAL_EVENT_IS_ENABLE

/* ==================== [Typedefs] ========================================== */

/* ==================== [Static Prototypes] ================================= */

/* ==================== [Static Variables] ================================== */

/* ==================== [Macros] ============================================ */

/* ==================== [Global Functions] ================================== */

xf_osal_event_t xf_osal_event_create(const xf_osal_event_attr_t *attr)
{
    EventGroupHandle_t hEventGroup;
    int32_t mem;

    hEventGroup = NULL;

    if (IRQ_Context() == 0U) {
        mem = -1;

        if (attr != NULL) {
            if ((attr->cb_mem != NULL) && (attr->cb_size >= sizeof(StaticEventGroup_t))) {
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
            hEventGroup = xEventGroupCreateStatic(attr->cb_mem);
#endif
        } else {
            if (mem == 0) {
#if (configSUPPORT_DYNAMIC_ALLOCATION == 1)
                hEventGroup = xEventGroupCreate();
#endif
            }
        }
    }

    /* Return event flags ID */
    return ((xf_osal_event_t)hEventGroup);
}

xf_err_t xf_osal_event_set(xf_osal_event_t event, uint32_t flags)
{
    EventGroupHandle_t hEventGroup = (EventGroupHandle_t)event;
    xf_err_t err = XF_OK;
    BaseType_t yield;

    if ((hEventGroup == NULL) || ((flags & XF_OSAL_EVENT_FLAGS_INVALID_BITS) != 0U)) {
        err = XF_ERR_INVALID_ARG;
    } else if (IRQ_Context() != 0U) {
#if (configUSE_OS2_EVENTFLAGS_FROM_ISR == 0)
        (void)yield;
        /* Enable timers and xTimerPendFunctionCall function to support osEventFlagsSet from ISR */
        err = XF_ERR_RESOURCE;
#else
        yield = pdFALSE;

        if (xEventGroupSetBitsFromISR(hEventGroup, (EventBits_t)flags, &yield) == pdFAIL) {
            err = XF_ERR_RESOURCE;
        } else {
            portYIELD_FROM_ISR(yield);
        }
#endif
    } else {
        xEventGroupSetBits(hEventGroup, (EventBits_t)flags);
    }

    /* Return event flags after setting */
    return (err);
}

xf_err_t xf_osal_event_clear(xf_osal_event_t event, uint32_t flags)
{
    EventGroupHandle_t hEventGroup = (EventGroupHandle_t)event;
    xf_err_t err = XF_OK;

    if ((hEventGroup == NULL) || ((flags & XF_OSAL_EVENT_FLAGS_INVALID_BITS) != 0U)) {
        err = XF_ERR_INVALID_ARG;
    } else if (IRQ_Context() != 0U) {
#if (configUSE_OS2_EVENTFLAGS_FROM_ISR == 0)
        /* Enable timers and xTimerPendFunctionCall function to support osEventFlagsSet from ISR */
        err = XF_ERR_RESOURCE;
#else

        if (xEventGroupClearBitsFromISR(hEventGroup, (EventBits_t)flags) == pdFAIL) {
            err = XF_ERR_RESOURCE;
        } else {
            /* xEventGroupClearBitsFromISR only registers clear operation in the timer command queue. */
            /* Yield is required here otherwise clear operation might not execute in the right order. */
            /* See https://github.com/FreeRTOS/FreeRTOS-Kernel/issues/93 for more info.               */
            portYIELD_FROM_ISR(pdTRUE);
        }
#endif
    } else {
        xEventGroupClearBits(hEventGroup, (EventBits_t)flags);
    }

    return (err);
}

uint32_t xf_osal_event_get(xf_osal_event_t event)
{
    EventGroupHandle_t hEventGroup = (EventGroupHandle_t)event;
    uint32_t rflags;

    if (event == NULL) {
        rflags = 0U;
    } else if (IRQ_Context() != 0U) {
        rflags = xEventGroupGetBitsFromISR(hEventGroup);
    } else {
        rflags = xEventGroupGetBits(hEventGroup);
    }

    /* Return current event flags */
    return (rflags);
}

xf_err_t xf_osal_event_wait(xf_osal_event_t event, uint32_t flags, uint32_t options, uint32_t timeout)
{
    EventGroupHandle_t hEventGroup = (EventGroupHandle_t)event;
    BaseType_t wait_all;
    BaseType_t exit_clr;
    xf_err_t err = XF_OK;

    if ((hEventGroup == NULL) || ((flags & XF_OSAL_EVENT_FLAGS_INVALID_BITS) != 0U)) {
        err = XF_ERR_INVALID_ARG;
    } else if (IRQ_Context() != 0U) {
        if (timeout == 0U) {
            /* Try semantic is not supported */
            err = XF_ERR_ISR;
        } else {
            /* Calling osEventFlagsWait from ISR with non-zero timeout is invalid */
            err = XF_ERR_INVALID_ARG;
        }
    } else {
        if (options & XF_OSAL_WAIT_ALL) {
            wait_all = pdTRUE;
        } else {
            wait_all = pdFAIL;
        }

        if (options & XF_OSAL_NO_CLEAR) {
            exit_clr = pdFAIL;
        } else {
            exit_clr = pdTRUE;
        }

        uint32_t rflags = xEventGroupWaitBits(hEventGroup, (EventBits_t)flags, exit_clr, wait_all, (TickType_t)timeout);

        if (options & XF_OSAL_WAIT_ALL) {
            if ((flags & rflags) != flags) {
                if (timeout > 0U) {
                    err = XF_ERR_TIMEOUT;
                } else {
                    err = XF_ERR_RESOURCE;
                }
            }
        } else {
            if ((flags & rflags) == 0U) {
                if (timeout > 0U) {
                    err = XF_ERR_TIMEOUT;
                } else {
                    err = XF_ERR_RESOURCE;
                }
            }
        }
    }

    /* Return event flags before clearing */
    return (err);
}

xf_err_t xf_osal_event_delete(xf_osal_event_t event)
{
    EventGroupHandle_t hEventGroup = (EventGroupHandle_t)event;
    xf_err_t stat = XF_OK;

#ifndef USE_FreeRTOS_HEAP_1
    if (IRQ_Context() != 0U) {
        stat = XF_ERR_ISR;
    } else if (hEventGroup == NULL) {
        stat = XF_ERR_INVALID_ARG;
    } else {
        stat = XF_OK;
        vEventGroupDelete(hEventGroup);
    }
#else
    stat = XF_FAIL;
#endif

    /* Return execution status */
    return (stat);
}

/* ==================== [Static Functions] ================================== */

#endif

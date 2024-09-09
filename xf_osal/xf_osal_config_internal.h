/**
 * @file xf_osal_config.h
 * @author cangyu (sky.kirto@qq.com)
 * @brief
 * @version 0.1
 * @date 2023-12-14
 *
 * @copyright Copyright (c) 2023, CorAL. All rights reserved.
 *
 */

#ifndef __XF_OSAL_CONFIG_H__
#define __XF_OSAL_CONFIG_H__

/* ==================== [Includes] ========================================== */

#include "xf_osal_config.h"

#ifdef __cplusplus
extern "C" {
#endif

/* ==================== [Defines] =========================================== */

#if (!defined(XF_OSAL_KERNEL_ENABLE) || (XF_OSAL_KERNEL_ENABLE))
#define XF_OSAL_KERNEL_IS_ENABLE (1)
#else
#define XF_OSAL_KERNEL_IS_ENABLE (0)
#endif

#if (!defined(XF_OSAL_THREAD_ENABLE) || (XF_OSAL_THREAD_ENABLE))
#define XF_OSAL_THREAD_IS_ENABLE (1)
#else
#define XF_OSAL_THREAD_IS_ENABLE (0)
#endif

#if (!defined(XF_OSAL_TIMER_ENABLE) || (XF_OSAL_TIMER_ENABLE))
#define XF_OSAL_TIMER_IS_ENABLE (1)
#else
#define XF_OSAL_TIMER_IS_ENABLE (0)
#endif

#if (!defined(XF_OSAL_EVENT_ENABLE) || (XF_OSAL_EVENT_ENABLE))
#define XF_OSAL_EVENT_IS_ENABLE (1)
#else
#define XF_OSAL_EVENT_IS_ENABLE (0)
#endif

#if (!defined(XF_OSAL_MUTEX_ENABLE) || (XF_OSAL_MUTEX_ENABLE))
#define XF_OSAL_MUTEX_IS_ENABLE (1)
#else
#define XF_OSAL_MUTEX_IS_ENABLE (0)
#endif

#if (!defined(XF_OSAL_SEMAPHORE_ENABLE) || (XF_OSAL_SEMAPHORE_ENABLE))
#define XF_OSAL_SEMAPHORE_IS_ENABLE (1)
#else
#define XF_OSAL_SEMAPHORE_IS_ENABLE (0)
#endif

#if (!defined(XF_OSAL_QUEUE_ENABLE) || (XF_OSAL_QUEUE_ENABLE))
#define XF_OSAL_QUEUE_IS_ENABLE (1)
#else
#define XF_OSAL_QUEUE_IS_ENABLE (0)
#endif

/* ==================== [Typedefs] ========================================== */

/* ==================== [Global Prototypes] ================================= */

/* ==================== [Macros] ============================================ */

#ifdef __cplusplus
} /* extern "C" */
#endif

#endif // __XF_OSAL_CONFIG_H__


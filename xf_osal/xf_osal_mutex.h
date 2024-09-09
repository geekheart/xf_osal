/**
 * @file xf_osal_mutex.h
 * @author cangyu(sky.kirto@qq.com)
 * @brief
 * @version 0.1
 * @date 2023-12-06
 *
 * @copyright Copyright(c) 2023, CorAL. All rights reserved.
 *
 */

#if XF_OSAL_MUTEX_IS_ENABLE

#ifndef __XF_OSAL_MUTEX_H__
#define __XF_OSAL_MUTEX_H__

/* ==================== [Includes] ========================================== */

#include "xf_osal_thread.h"

#ifdef __cplusplus
extern "C" {
#endif

/* ==================== [Defines] =========================================== */

#define XF_OSAL_MUTEX_RECURSIVE        0x00000001U ///< Recursive mutex.
#define XF_OSAL_MUTEX_PRIO_INHERIT     0x00000002U ///< Priority inherit protocol.
#define XF_OSAL_MUTEX_ROBUST           0x00000008U ///< Robust mutex.

/* ==================== [Typedefs] ========================================== */

typedef struct _xf_osal_mutex_attr_t {
    const char                   *name;   ///< name of the mutex
    uint32_t                 attr_bits;   ///< attribute bits
    void                      *cb_mem;    ///< memory for control block
    uint32_t                   cb_size;   ///< size of provided memory for control block
} xf_osal_mutex_attr_t;

typedef void *xf_osal_mutex_t;

/* ==================== [Global Prototypes] ================================= */

xf_osal_mutex_t xf_osal_mutex_create(const xf_osal_mutex_attr_t *attr);
xf_err_t xf_osal_mutex_acquire(xf_osal_mutex_t mutex, uint32_t timeout);
xf_err_t xf_osal_mutex_release(xf_osal_mutex_t mutex);
xf_osal_thread_t xf_osal_mutex_get_owner(xf_osal_mutex_t mutex);
xf_err_t xf_osal_mutex_delete(xf_osal_mutex_t mutex);

/* ==================== [Macros] ============================================ */

#ifdef __cplusplus
} /* extern "C" */
#endif

#endif // __XF_OSAL_MUTEX_H__

#endif // XF_OSAL_MUTEX_ENABLE

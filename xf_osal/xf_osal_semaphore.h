/**
 * @file xf_osal_semaphore.h
 * @author cangyu(sky.kirto@qq.com)
 * @brief
 * @version 0.1
 * @date 2023-12-06
 *
 * @copyright Copyright(c) 2023, CorAL. All rights reserved.
 *
 */

#if XF_OSAL_SEMAPHORE_IS_ENABLE

#ifndef __XF_OSAL_SEMAPHORE_H__
#define __XF_OSAL_SEMAPHORE_H__

/* ==================== [Includes] ========================================== */

#ifdef __cplusplus
extern "C" {
#endif

/* ==================== [Defines] =========================================== */

/* ==================== [Typedefs] ========================================== */

typedef void *xf_osal_semaphore_t;

typedef struct _xf_osal_semaphore_attr_t {
    const char                   *name;   ///< name of the semaphore
    uint32_t                 attr_bits;   ///< attribute bits
    void                      *cb_mem;    ///< memory for control block
    uint32_t                   cb_size;   ///< size of provided memory for control block
} xf_osal_semaphore_attr_t;

/* ==================== [Global Prototypes] ================================= */

xf_osal_semaphore_t xf_osal_semaphore_create(uint32_t max_count, uint32_t initial_count,
        const xf_osal_semaphore_attr_t *attr);
xf_err_t xf_osal_semaphore_acquire(xf_osal_semaphore_t semaphore, uint32_t timeout);
xf_err_t xf_osal_semaphore_release(xf_osal_semaphore_t semaphore);
uint32_t xf_osal_semaphore_get_count(xf_osal_semaphore_t semaphore);
xf_err_t xf_osal_semaphore_delete(xf_osal_semaphore_t semaphore);

/* ==================== [Macros] ============================================ */

#ifdef __cplusplus
} /* extern "C" */
#endif

#endif // __XF_OSAL_SEMAPHORE_H__

#endif // XF_OSAL_MUTEX_ENABLE

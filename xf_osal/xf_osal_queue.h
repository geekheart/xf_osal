/**
 * @file xf_osal_queue.h
 * @author cangyu(sky.kirto@qq.com)
 * @brief
 * @version 0.1
 * @date 2023-12-06
 *
 * @copyright Copyright(c) 2023, CorAL. All rights reserved.
 *
 */

#if XF_OSAL_QUEUE_IS_ENABLE

#ifndef __XF_OSAL_QUEUE_H__
#define __XF_OSAL_QUEUE_H__

/* ==================== [Includes] ========================================== */

#ifdef __cplusplus
extern "C" {
#endif

/* ==================== [Defines] =========================================== */

/* ==================== [Typedefs] ========================================== */

typedef void *xf_osal_queue_t;

typedef struct _xf_osal_queue_attr_t {
    const char                   *name;   ///< name of the message queue
    uint32_t                 attr_bits;   ///< attribute bits
    void                      *cb_mem;    ///< memory for control block
    uint32_t                   cb_size;   ///< size of provided memory for control block
    void                      *mq_mem;    ///< memory for data storage
    uint32_t                   mq_size;   ///< size of provided memory for data storage
} xf_osal_queue_attr_t;

/* ==================== [Global Prototypes] ================================= */

xf_osal_queue_t xf_osal_queue_create(uint32_t msg_count, uint32_t msg_size, const xf_osal_queue_attr_t *attr);
xf_err_t xf_osal_queue_put(xf_osal_queue_t queue, const void *msg_ptr, uint8_t msg_prio, uint32_t timeout);
xf_err_t xf_osal_queue_get(xf_osal_queue_t queue, void *msg_ptr, uint8_t *msg_prio, uint32_t timeout);
uint32_t xf_osal_queue_get_count(xf_osal_queue_t queue);
xf_err_t xf_osal_queue_reset(xf_osal_queue_t queue);
xf_err_t xf_osal_queue_delete(xf_osal_queue_t queue);

/* ==================== [Macros] ============================================ */

#ifdef __cplusplus
} /* extern "C" */
#endif

#endif // __XF_OSAL_QUEUE_H__

#endif // XF_OSAL_QUEUE_ENABLE

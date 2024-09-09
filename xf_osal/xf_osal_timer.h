/**
 * @file xf_osal_timer.h
 * @author cangyu (sky.kirto@qq.com)
 * @brief
 * @version 0.1
 * @date 2023-12-13
 *
 * @copyright Copyright (c) 2023, CorAL. All rights reserved.
 *
 */

#if XF_OSAL_TIMER_IS_ENABLE

#ifndef __XF_OSAL_TIMER_H__
#define __XF_OSAL_TIMER_H__

/* ==================== [Includes] ========================================== */

#ifdef __cplusplus
extern "C" {
#endif

/* ==================== [Defines] =========================================== */

/* ==================== [Typedefs] ========================================== */

typedef enum _xf_osal_timer_type_t {
    XF_OSAL_TIMER_ONCE             = 0,          ///< One-shot timer.
    XF_OSAL_TIMER_PERIODIC         = 1           ///< Repeating timer.
} xf_osal_timer_type_t;

typedef struct _xf_osal_timer_attr_t {
    const char                   *name;   ///< name of the timer
    uint32_t                 attr_bits;   ///< attribute bits
    void                      *cb_mem;    ///< memory for control block
    uint32_t                   cb_size;   ///< size of provided memory for control block
} xf_osal_timer_attr_t;

typedef void *xf_osal_timer_t;
typedef void (*xf_osal_timer_func_t)(void *argument);

/* ==================== [Global Prototypes] ================================= */

xf_osal_timer_t xf_osal_timer_create(xf_osal_timer_func_t func, xf_osal_timer_type_t type, void *argument,
                                     xf_osal_timer_attr_t *attr);
const char *xf_osal_timer_get_name(xf_osal_timer_t timer);
xf_err_t xf_osal_timer_start(xf_osal_timer_t timer, uint32_t ticks);
xf_err_t xf_osal_timer_stop(xf_osal_timer_t timer);
uint32_t xf_osal_timer_is_running(xf_osal_timer_t timer);
xf_err_t xf_osal_timer_delete(xf_osal_timer_t timer);

/* ==================== [Macros] ============================================ */

#ifdef __cplusplus
} /* extern "C" */
#endif

#endif // __XF_OSAL_TIMER_H__

#endif // XF_OSAL_TIMER_ENABLE

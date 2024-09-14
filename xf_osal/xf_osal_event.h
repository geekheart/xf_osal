/**
 * @file xf_osal_event.h
 * @author cangyu(sky.kirto@qq.com)
 * @brief
 * @version 0.1
 * @date 2023-12-06
 *
 * @copyright Copyright(c) 2023, CorAL. All rights reserved.
 *
 */

#if XF_OSAL_EVENT_IS_ENABLE

#ifndef __XF_OSAL_EVENT_H__
#define __XF_OSAL_EVENT_H__

/* ==================== [Includes] ========================================== */

#ifdef __cplusplus
extern "C" {
#endif

/* ==================== [Defines] =========================================== */

// Timeout value.
#define XF_OSAL_WAIT_FOREVER           0xFFFFFFFFU ///< Wait forever timeout value.

// Flags options (\ref osThreadFlagsWait and \ref osEventFlagsWait).
#define XF_OSAL_WAIT_ANY           0x00000000U ///< Wait for any flag (default).
#define XF_OSAL_WAIT_ALL           0x00000001U ///< Wait for all flags.
#define XF_OSAL_NO_CLEAR           0x00000002U ///< Do not clear flags which have been specified to wait for.

#define MAX_BITS_EVENT_GROUPS     24U
#define XF_OSAL_EVENT_FLAGS_INVALID_BITS  (~((1UL << MAX_BITS_EVENT_GROUPS) - 1U))

/* ==================== [Typedefs] ========================================== */

typedef void *xf_osal_event_t;

typedef struct _xf_osal_event_attr_t {
    const char                   *name;   ///< name of the event flags
    uint32_t                 attr_bits;   ///< attribute bits
    void                      *cb_mem;    ///< memory for control block
    uint32_t                   cb_size;   ///< size of provided memory for control block
} xf_osal_event_attr_t;

/* ==================== [Global Prototypes] ================================= */

xf_osal_event_t xf_osal_event_create(const xf_osal_event_attr_t *attr);
xf_err_t xf_osal_event_set(xf_osal_event_t event, uint32_t flags);
xf_err_t xf_osal_event_clear(xf_osal_event_t event, uint32_t flags);
uint32_t xf_osal_event_get(xf_osal_event_t event);
xf_err_t xf_osal_event_wait(xf_osal_event_t event, uint32_t flags, uint32_t options, uint32_t timeout);
xf_err_t xf_osal_event_delete(xf_osal_event_t event);

/* ==================== [Macros] ============================================ */

#ifdef __cplusplus
} /* extern "C" */
#endif

#endif // __XF_OSAL_EVENT_H__

#endif // XF_OSAL_EVENT_ENABLE

/**
 * @file xf_osal_kernel.h
 * @author cangyu(sky.kirto@qq.com)
 * @brief
 * @version 0.1
 * @date 2023-12-06
 *
 * @copyright Copyright(c) 2023, CorAL. All rights reserved.
 *
 */

#if XF_OSAL_KERNEL_IS_ENABLE

#ifndef __XF_OSAL_KERNEL_H__
#define __XF_OSAL_KERNEL_H__

/* ==================== [Includes] ========================================== */

#ifdef __cplusplus
extern "C" {
#endif

/* ==================== [Defines] =========================================== */


/* ==================== [Typedefs] ========================================== */

typedef struct _xf_osal_version_t {
    uint32_t                       api;   ///< API version(major.minor.rev: mmnnnrrrr dec).
    uint32_t                    kernel;   ///< Kernel version(major.minor.rev: mmnnnrrrr dec).
} xf_osal_version_t;

typedef enum _xf_osal_state_t {
    XF_OSAL_INACTIVE       =  0,         ///< Inactive.
    XF_OSAL_READY          =  1,         ///< Ready.
    XF_OSAL_RUNNING        =  2,         ///< Running.
    XF_OSAL_BLOCKED        =  3,         ///< Blocked.
    XF_OSAL_TERMINATED     =  4,         ///< Terminated.
    XF_OSAL_ERROR          = -1,         ///< Error.
    XF_OSAL_RESERVED       = 0x7FFFFFFF  ///< Prevents enum down-size compiler optimization.
} xf_osal_state_t;

/* ==================== [Global Prototypes] ================================= */

xf_err_t xf_osal_kernel_get_info(xf_osal_version_t *version, char *id_buf, uint32_t id_size);
xf_osal_state_t xf_osal_kernel_get_state(void);
xf_err_t xf_osal_kernel_lock(void);
xf_err_t xf_osal_kernel_unlock(void);
uint32_t xf_osal_kernel_get_tick_count(void);
uint32_t xf_osal_kernel_get_tick_freq(void);

uint32_t xf_osal_kernel_ticks_to_ms(uint32_t ticks);
uint32_t xf_osal_kernel_ms_to_ticks(uint32_t ms);

/* ==================== [Macros] ============================================ */

#ifdef __cplusplus
} /* extern "C" */
#endif

#endif // __XF_OSAL_KERNEL_H__

#endif // XF_OSAL_KERNEL_ENABLE

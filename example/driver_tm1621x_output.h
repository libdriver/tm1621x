/**
 * Copyright (c) 2015 - present LibDriver All rights reserved
 * 
 * The MIT License (MIT)
 *
 * Permission is hereby granted, free of charge, to any person obtaining a copy
 * of this software and associated documentation files (the "Software"), to deal
 * in the Software without restriction, including without limitation the rights
 * to use, copy, modify, merge, publish, distribute, sublicense, and/or sell
 * copies of the Software, and to permit persons to whom the Software is
 * furnished to do so, subject to the following conditions:
 *
 * The above copyright notice and this permission notice shall be included in all
 * copies or substantial portions of the Software.
 *
 * THE SOFTWARE IS PROVIDED "AS IS", WITHOUT WARRANTY OF ANY KIND, EXPRESS OR
 * IMPLIED, INCLUDING BUT NOT LIMITED TO THE WARRANTIES OF MERCHANTABILITY,
 * FITNESS FOR A PARTICULAR PURPOSE AND NONINFRINGEMENT. IN NO EVENT SHALL THE
 * AUTHORS OR COPYRIGHT HOLDERS BE LIABLE FOR ANY CLAIM, DAMAGES OR OTHER
 * LIABILITY, WHETHER IN AN ACTION OF CONTRACT, TORT OR OTHERWISE, ARISING FROM,
 * OUT OF OR IN CONNECTION WITH THE SOFTWARE OR THE USE OR OTHER DEALINGS IN THE
 * SOFTWARE. 
 *
 * @file      driver_tm1621x_output.h
 * @brief     driver tm1621x output header file
 * @version   1.0.0
 * @author    Shifeng Li
 * @date      2026-05-31
 *
 * <h3>history</h3>
 * <table>
 * <tr><th>Date        <th>Version  <th>Author      <th>Description
 * <tr><td>2026/05/31  <td>1.0      <td>Shifeng Li  <td>first upload
 * </table>
 */

#ifndef DRIVER_TM1621X_OUTPUT_H
#define DRIVER_TM1621X_OUTPUT_H

#include "driver_tm1621x_interface.h"

#ifdef __cplusplus
extern "C"{
#endif

/**
 * @addtogroup tm1621x_example_driver
 * @{
 */

/**
 * @brief bias 1/2 definition
 */
#define TM1621X_OUTPUT_BIAS_1DIV2        1

/**
 * @brief bias 1/3 definition
 */
#define TM1621X_OUTPUT_BIAS_1DIV3        2

/**
 * @brief tm1621x output example default definition
 */
#define TM1621X_OUTPUT_DEFAULT_CLOCK        TM1621X_CLOCK_RC_256K               /**< rc 256k */
#define TM1621X_OUTPUT_DEFAULT_USE_BIAS     TM1621X_OUTPUT_BIAS_1DIV3           /**< 1div3 */
#define TM1621X_OUTPUT_DEFAULT_BIAS         TM1621X_BIAS_4                      /**< 4 */

/**
 * @brief     output example init
 * @param[in] type chip type
 * @return    status code
 *            - 0 success
 *            - 1 init failed
 * @note      none
 */
uint8_t tm1621x_output_init(tm1621x_type_t type);

/**
 * @brief  output example deinit
 * @return status code
 *         - 0 success
 *         - 1 deinit failed
 * @note   none
 */
uint8_t tm1621x_output_deinit(void);

/**
 * @brief     output example write
 * @param[in] addr start address
 * @param[in] *data pointer to a data buffer
 * @param[in] len data length
 * @return    status code
 *            - 0 success
 *            - 1 write failed
 * @note      none
 */
uint8_t tm1621x_output_write(uint8_t addr, uint8_t *data, uint8_t len);

/**
 * @brief  output example clear
 * @return status code
 *         - 0 success
 *         - 1 clear failed
 * @note   none
 */
uint8_t tm1621x_output_clear(void);

/**
 * @brief  output example display on
 * @return status code
 *         - 0 success
 *         - 1 display on failed
 * @note   none
 */
uint8_t tm1621x_output_display_on(void);

/**
 * @brief  output example display off
 * @return status code
 *         - 0 success
 *         - 1 display off failed
 * @note   none
 */
uint8_t tm1621x_output_display_off(void);

/**
 * @brief     output example set freq
 * @param[in] freq output freq
 * @return    status code
 *            - 0 success
 *            - 1 set freq failed
 * @note      none
 */
uint8_t tm1621x_output_set_freq(tm1621x_freq_t freq);

/**
 * @brief     output example set timer
 * @param[in] enable bool value
 * @return    status code
 *            - 0 success
 *            - 1 set timer failed
 * @note      none
 */
uint8_t tm1621x_output_set_timer(tm1621x_bool_t enable);

/**
 * @brief     output example set watchdog
 * @param[in] enable bool value
 * @return    status code
 *            - 0 success
 *            - 1 set watchdog failed
 * @note      none
 */
uint8_t tm1621x_output_set_watchdog(tm1621x_bool_t enable);

/**
 * @brief  output example feed watchdog
 * @return status code
 *         - 0 success
 *         - 1 feed watchdog failed
 * @note   none
 */
uint8_t tm1621x_output_feed_watchdog(void);

/**
 * @}
 */

#ifdef __cplusplus
}
#endif

#endif

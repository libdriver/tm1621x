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
 * @file      driver_tm1621x.h
 * @brief     driver tm1621x header file
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

#ifndef DRIVER_TM1621X_H
#define DRIVER_TM1621X_H

#include <stdio.h>
#include <stdint.h>
#include <string.h>

#ifdef __cplusplus
extern "C"{
#endif

/**
 * @defgroup tm1621x_driver tm1621x driver function
 * @brief    tm1621x driver modules
 * @{
 */

/**
 * @addtogroup tm1621x_basic_driver
 * @{
 */

/**
 * @brief tm1621x command data delay definition
 */
#ifndef TM1621X_COMMAND_DATA_DELAY
    #define TM1621X_COMMAND_DATA_DELAY        3        /**< 3us */
#endif

/**
 * @brief tm1621x type enumeration definition
 */
typedef enum
{
    TM1621X_TYPE_B = 0x00,        /**< type b */
    TM1621X_TYPE_C = 0x01,        /**< type c */
    TM1621X_TYPE_D = 0x02,        /**< type d */
    TM1621X_TYPE_E = 0x03,        /**< type e */
} tm1621x_type_t;

/**
 * @brief tm1621x bool enumeration definition
 */
typedef enum
{
    TM1621X_BOOL_FALSE = 0x00,        /**< false */
    TM1621X_BOOL_TRUE  = 0x01,        /**< true */
} tm1621x_bool_t;

/**
 * @brief tm1621x mode enumeration definition
 */
typedef enum
{
    TM1621X_MODE_NORMAL = 0x00,        /**< normal mode */
    TM1621X_MODE_TEST   = 0x01,        /**< test mode */
} tm1621x_mode_t;

/**
 * @brief tm1621x clock enumeration definition
 */
typedef enum
{
    TM1621X_CLOCK_XTAL_32K = 0x00,        /**< xtal 32k */
    TM1621X_CLOCK_RC_256K  = 0x01,        /**< rc 256k */
    TM1621X_CLOCK_EXT_256K = 0x02,        /**< ext 256k */
} tm1621x_clock_t;

/**
 * @brief tm1621x tone freq enumeration definition
 */
typedef enum
{
    TM1621X_TONE_FREQ_2K = 0x00,        /**< tone 2k */
    TM1621X_TONE_FREQ_4K = 0x01,        /**< tone 4k */
} tm1621x_tone_freq_t;

/**
 * @brief tm1621x freq enumeration definition
 */
typedef enum
{
    TM1621X_FREQ_F1   = 0x00,        /**< clock 1hz, wdt 4s */
    TM1621X_FREQ_F2   = 0x01,        /**< clock 2hz, wdt 2s */
    TM1621X_FREQ_F4   = 0x02,        /**< clock 4hz, wdt 1s */
    TM1621X_FREQ_F8   = 0x03,        /**< clock 8hz, wdt 1/2s */
    TM1621X_FREQ_F16  = 0x04,        /**< clock 16hz, wdt 1/4s */
    TM1621X_FREQ_F32  = 0x05,        /**< clock 32hz, wdt 1/8s */
    TM1621X_FREQ_F64  = 0x06,        /**< clock 64hz, wdt 1/16s */
    TM1621X_FREQ_F128 = 0x07,        /**< clock 128hz, wdt 1/32s */
} tm1621x_freq_t;

/**
 * @brief tm1621x bias enumeration definition
 */
typedef enum
{
    TM1621X_BIAS_2 = 0x00,        /**< 2 */
    TM1621X_BIAS_3 = 0x01,        /**< 3 */
    TM1621X_BIAS_4 = 0x02,        /**< 4 */
} tm1621x_bias_t;

/**
 * @brief tm1621x handle structure definition
 */
typedef struct tm1621x_handle_s
{
    uint8_t (*data_gpio_init)(void);                        /**< point to a data_gpio_init function address */
    uint8_t (*data_gpio_deinit)(void);                      /**< point to a data_gpio_deinit function address */
    uint8_t (*data_gpio_write)(uint8_t level);              /**< point to a data_gpio_write function address */
    uint8_t (*data_gpio_read)(uint8_t *level);              /**< point to a data_gpio_read function address */
    uint8_t (*wr_gpio_init)(void);                          /**< point to a wr_gpio_init function address */
    uint8_t (*wr_gpio_deinit)(void);                        /**< point to a wr_gpio_deinit function address */
    uint8_t (*wr_gpio_write)(uint8_t level);                /**< point to a wr_gpio_write function address */
    uint8_t (*rd_gpio_init)(void);                          /**< point to a rd_gpio_init function address */
    uint8_t (*rd_gpio_deinit)(void);                        /**< point to a rd_gpio_deinit function address */
    uint8_t (*rd_gpio_write)(uint8_t level);                /**< point to a rd_gpio_write function address */
    uint8_t (*cs_gpio_init)(void);                          /**< point to a cs_gpio_init function address */
    uint8_t (*cs_gpio_deinit)(void);                        /**< point to a cs_gpio_deinit function address */
    uint8_t (*cs_gpio_write)(uint8_t level);                /**< point to a cs_gpio_write function address */
    void (*delay_us)(uint32_t us);                          /**< point to a delay_us function address */
    void (*delay_ms)(uint32_t ms);                          /**< point to a delay_ms function address */
    void (*debug_print)(const char *const fmt, ...);        /**< point to a debug_print function address */
    uint8_t type;                                           /**< type */
    uint8_t inited;                                         /**< inited flag */
} tm1621x_handle_t;

/**
 * @brief tm1621x information structure definition
 */
typedef struct tm1621x_info_s
{
    char chip_name[32];                /**< chip name */
    char manufacturer_name[32];        /**< manufacturer name */
    char interface[8];                 /**< chip interface name */
    float supply_voltage_min_v;        /**< chip min supply voltage */
    float supply_voltage_max_v;        /**< chip max supply voltage */
    float max_current_ma;              /**< chip max current */
    float temperature_min;             /**< chip min operating temperature */
    float temperature_max;             /**< chip max operating temperature */
    uint32_t driver_version;           /**< driver version */
} tm1621x_info_t;

/**
 * @}
 */

/**
 * @defgroup tm1621x_link_driver tm1621x link driver function
 * @brief    tm1621x link driver modules
 * @ingroup  tm1621x_driver
 * @{
 */

/**
 * @brief     initialize tm1621x_handle_t structure
 * @param[in] HANDLE pointer to a tm1621x handle structure
 * @param[in] STRUCTURE tm1621x_handle_t
 * @note      none
 */
#define DRIVER_TM1621X_LINK_INIT(HANDLE, STRUCTURE)                 memset(HANDLE, 0, sizeof(STRUCTURE))

/**
 * @brief     link data_gpio_init function
 * @param[in] HANDLE pointer to a tm1621x handle structure
 * @param[in] FUC pointer to a data_gpio_init function address
 * @note      none
 */
#define DRIVER_TM1621X_LINK_DATA_GPIO_INIT(HANDLE, FUC)             (HANDLE)->data_gpio_init = FUC

/**
 * @brief     link data_gpio_deinit function
 * @param[in] HANDLE pointer to a tm1621x handle structure
 * @param[in] FUC pointer to a data_gpio_deinit function address
 * @note      none
 */
#define DRIVER_TM1621X_LINK_DATA_GPIO_DEINIT(HANDLE, FUC)           (HANDLE)->data_gpio_deinit = FUC

/**
 * @brief     link data_gpio_write function
 * @param[in] HANDLE pointer to a tm1621x handle structure
 * @param[in] FUC pointer to a data_gpio_write function address
 * @note      none
 */
#define DRIVER_TM1621X_LINK_DATA_GPIO_WRITE(HANDLE, FUC)            (HANDLE)->data_gpio_write = FUC

/**
 * @brief     link data_gpio_read function
 * @param[in] HANDLE pointer to a tm1621x handle structure
 * @param[in] FUC pointer to a data_gpio_read function address
 * @note      none
 */
#define DRIVER_TM1621X_LINK_DATA_GPIO_READ(HANDLE, FUC)             (HANDLE)->data_gpio_read = FUC

/**
 * @brief     link wr_gpio_init function
 * @param[in] HANDLE pointer to a tm1621x handle structure
 * @param[in] FUC pointer to a wr_gpio_init function address
 * @note      none
 */
#define DRIVER_TM1621X_LINK_WR_GPIO_INIT(HANDLE, FUC)               (HANDLE)->wr_gpio_init = FUC

/**
 * @brief     link wr_gpio_deinit function
 * @param[in] HANDLE pointer to a tm1621x handle structure
 * @param[in] FUC pointer to a wr_gpio_deinit function address
 * @note      none
 */
#define DRIVER_TM1621X_LINK_WR_GPIO_DEINIT(HANDLE, FUC)             (HANDLE)->wr_gpio_deinit = FUC

/**
 * @brief     link wr_gpio_write function
 * @param[in] HANDLE pointer to a tm1621x handle structure
 * @param[in] FUC pointer to a wr_gpio_write function address
 * @note      none
 */
#define DRIVER_TM1621X_LINK_WR_GPIO_WRITE(HANDLE, FUC)              (HANDLE)->wr_gpio_write = FUC

/**
 * @brief     link rd_gpio_init function
 * @param[in] HANDLE pointer to a tm1621x handle structure
 * @param[in] FUC pointer to a rd_gpio_init function address
 * @note      none
 */
#define DRIVER_TM1621X_LINK_RD_GPIO_INIT(HANDLE, FUC)               (HANDLE)->rd_gpio_init = FUC

/**
 * @brief     link rd_gpio_deinit function
 * @param[in] HANDLE pointer to a tm1621x handle structure
 * @param[in] FUC pointer to a rd_gpio_deinit function address
 * @note      none
 */
#define DRIVER_TM1621X_LINK_RD_GPIO_DEINIT(HANDLE, FUC)             (HANDLE)->rd_gpio_deinit = FUC

/**
 * @brief     link rd_gpio_write function
 * @param[in] HANDLE pointer to a tm1621x handle structure
 * @param[in] FUC pointer to a rd_gpio_write function address
 * @note      none
 */
#define DRIVER_TM1621X_LINK_RD_GPIO_WRITE(HANDLE, FUC)              (HANDLE)->rd_gpio_write = FUC

/**
 * @brief     link cs_gpio_init function
 * @param[in] HANDLE pointer to a tm1621x handle structure
 * @param[in] FUC pointer to a cs_gpio_init function address
 * @note      none
 */
#define DRIVER_TM1621X_LINK_CS_GPIO_INIT(HANDLE, FUC)               (HANDLE)->cs_gpio_init = FUC

/**
 * @brief     link cs_gpio_deinit function
 * @param[in] HANDLE pointer to a tm1621x handle structure
 * @param[in] FUC pointer to a cs_gpio_deinit function address
 * @note      none
 */
#define DRIVER_TM1621X_LINK_CS_GPIO_DEINIT(HANDLE, FUC)             (HANDLE)->cs_gpio_deinit = FUC

/**
 * @brief     link cs_gpio_write function
 * @param[in] HANDLE pointer to a tm1621x handle structure
 * @param[in] FUC pointer to a cs_gpio_write function address
 * @note      none
 */
#define DRIVER_TM1621X_LINK_CS_GPIO_WRITE(HANDLE, FUC)              (HANDLE)->cs_gpio_write = FUC

/**
 * @brief     link delay_us function
 * @param[in] HANDLE pointer to a tm1621x handle structure
 * @param[in] FUC pointer to a delay_us function address
 * @note      none
 */
#define DRIVER_TM1621X_LINK_DELAY_US(HANDLE, FUC)                   (HANDLE)->delay_us = FUC

/**
 * @brief     link delay_ms function
 * @param[in] HANDLE pointer to a tm1621x handle structure
 * @param[in] FUC pointer to a delay_ms function address
 * @note      none
 */
#define DRIVER_TM1621X_LINK_DELAY_MS(HANDLE, FUC)                   (HANDLE)->delay_ms = FUC

/**
 * @brief     link debug_print function
 * @param[in] HANDLE pointer to a tm1621x handle structure
 * @param[in] FUC pointer to a debug_print function address
 * @note      none
 */
#define DRIVER_TM1621X_LINK_DEBUG_PRINT(HANDLE, FUC)                (HANDLE)->debug_print = FUC

/**
 * @}
 */

/**
 * @defgroup tm1621x_basic_driver tm1621x basic driver function
 * @brief    tm1621x basic driver modules
 * @ingroup  tm1621x_driver
 * @{
 */

/**
 * @brief      get chip's information
 * @param[out] *info pointer to a tm1621x info structure
 * @return     status code
 *             - 0 success
 *             - 2 handle is NULL
 * @note       none
 */
uint8_t tm1621x_info(tm1621x_info_t *info);

/**
 * @brief     set type
 * @param[in] *handle pointer to a tm1621x handle structure
 * @param[in] type chip type
 * @return    status code
 *            - 0 success
 *            - 2 handle is NULL
 * @note      none
 */
uint8_t tm1621x_set_type(tm1621x_handle_t *handle, tm1621x_type_t type);

/**
 * @brief      get type
 * @param[in]  *handle pointer to a tm1621x handle structure
 * @param[out] *type pointer to a chip type buffer
 * @return     status code
 *             - 0 success
 *             - 2 handle is NULL
 * @note       none
 */
uint8_t tm1621x_get_type(tm1621x_handle_t *handle, tm1621x_type_t *type);

/**
 * @brief     initialize the chip
 * @param[in] *handle pointer to a tm1621x handle structure
 * @return    status code
 *            - 0 success
 *            - 1 gpio initialization failed
 *            - 2 handle is NULL
 *            - 3 linked functions is NULL
 * @note      none
 */
uint8_t tm1621x_init(tm1621x_handle_t *handle);

/**
 * @brief     close the chip
 * @param[in] *handle pointer to a tm1621x handle structure
 * @return    status code
 *            - 0 success
 *            - 1 gpio deinit failed
 *            - 2 handle is NULL
 *            - 3 handle is not initialized
 *            - 4 power down failed
 * @note      none
 */
uint8_t tm1621x_deinit(tm1621x_handle_t *handle);

/**
 * @brief     write segment
 * @param[in] *handle pointer to a tm1621x handle structure
 * @param[in] addr address
 * @param[in] *data pointer to an input data buffer
 * @param[in] len input data length
 * @return    status code
 *            - 0 success
 *            - 1 write segment failed
 *            - 2 handle is NULL
 *            - 3 handle is not initialized
 *            - 4 addr + len > 32
 * @note      data width is 4 bits and data <= 0x0F
 */
uint8_t tm1621x_write_segment(tm1621x_handle_t *handle, uint8_t addr, uint8_t *data, uint8_t len);

/**
 * @brief     clear segment
 * @param[in] *handle pointer to a tm1621x handle structure
 * @return    status code
 *            - 0 success
 *            - 1 clear segment failed
 *            - 2 handle is NULL
 *            - 3 handle is not initialized
 * @note      none
 */
uint8_t tm1621x_clear_segment(tm1621x_handle_t *handle);

/**
 * @brief     enable or disable oscillator
 * @param[in] *handle pointer to a tm1621x handle structure
 * @param[in] enable bool value
 * @return    status code
 *            - 0 success
 *            - 1 set oscillator failed
 *            - 2 handle is NULL
 *            - 3 handle is not initialized
 * @note      none
 */
uint8_t tm1621x_set_oscillator(tm1621x_handle_t *handle, tm1621x_bool_t enable);

/**
 * @brief     enable or disable lcd bias
 * @param[in] *handle pointer to a tm1621x handle structure
 * @param[in] enable bool value
 * @return    status code
 *            - 0 success
 *            - 1 set lcd bias failed
 *            - 2 handle is NULL
 *            - 3 handle is not initialized
 * @note      none
 */
uint8_t tm1621x_set_lcd_bias(tm1621x_handle_t *handle, tm1621x_bool_t enable);

/**
 * @brief     set bias 1div2
 * @param[in] *handle pointer to a tm1621x handle structure
 * @param[in] bias input bias
 * @return    status code
 *            - 0 success
 *            - 1 set bias 1div2 failed
 *            - 2 handle is NULL
 *            - 3 handle is not initialized
 * @note      none
 */
uint8_t tm1621x_set_bias_1div2(tm1621x_handle_t *handle, tm1621x_bias_t bias);

/**
 * @brief     set bias 1div3
 * @param[in] *handle pointer to a tm1621x handle structure
 * @param[in] bias input bias
 * @return    status code
 *            - 0 success
 *            - 1 set bias 1div3 failed
 *            - 2 handle is NULL
 *            - 3 handle is not initialized
 * @note      none
 */
uint8_t tm1621x_set_bias_1div3(tm1621x_handle_t *handle, tm1621x_bias_t bias);

/**
 * @brief     set mode
 * @param[in] *handle pointer to a tm1621x handle structure
 * @param[in] mode input mode
 * @return    status code
 *            - 0 success
 *            - 1 set mode failed
 *            - 2 handle is NULL
 *            - 3 handle is not initialized
 * @note      none
 */
uint8_t tm1621x_set_mode(tm1621x_handle_t *handle, tm1621x_mode_t mode);

/**
 * @brief     set clock 
 * @param[in] *handle pointer to a tm1621x handle structure
 * @param[in] clk chip clock
 * @return    status code
 *            - 0 success
 *            - 1 set clock failed
 *            - 2 handle is NULL
 *            - 3 handle is not initialized
 * @note      none
 */
uint8_t tm1621x_set_clock(tm1621x_handle_t *handle, tm1621x_clock_t clk);

/**
 * @brief     set freq 
 * @param[in] *handle pointer to a tm1621x handle structure
 * @param[in] freq output freq
 * @return    status code
 *            - 0 success
 *            - 1 set freq failed
 *            - 2 handle is NULL
 *            - 3 handle is not initialized
 *            - 4 only typeb support this function
 * @note      none
 */
uint8_t tm1621x_set_freq(tm1621x_handle_t *handle, tm1621x_freq_t freq);

/**
 * @brief     set tone freq
 * @param[in] *handle pointer to a tm1621x handle structure
 * @param[in] freq tone freq
 * @return    status code
 *            - 0 success
 *            - 1 set tone freq failed
 *            - 2 handle is NULL
 *            - 3 handle is not initialized
 *            - 4 only typeb support this function
 * @note      none
 */
uint8_t tm1621x_set_tone_freq(tm1621x_handle_t *handle, tm1621x_tone_freq_t freq);

/**
 * @brief     enable or disable timer
 * @param[in] *handle pointer to a tm1621x handle structure
 * @param[in] enable bool value
 * @return    status code
 *            - 0 success
 *            - 1 set timer failed
 *            - 2 handle is NULL
 *            - 3 handle is not initialized
 *            - 4 only typeb support this function
 * @note      none
 */
uint8_t tm1621x_set_timer(tm1621x_handle_t *handle, tm1621x_bool_t enable);

/**
 * @brief     enable or disable watchdog
 * @param[in] *handle pointer to a tm1621x handle structure
 * @param[in] enable bool value
 * @return    status code
 *            - 0 success
 *            - 1 set watchdog failed
 *            - 2 handle is NULL
 *            - 3 handle is not initialized
 *            - 4 only typeb support this function
 * @note      none
 */
uint8_t tm1621x_set_watchdog(tm1621x_handle_t *handle, tm1621x_bool_t enable);

/**
 * @brief     enable or disable tone
 * @param[in] *handle pointer to a tm1621x handle structure
 * @param[in] enable bool value
 * @return    status code
 *            - 0 success
 *            - 1 set tone failed
 *            - 2 handle is NULL
 *            - 3 handle is not initialized
 *            - 4 only typeb support this function
 * @note      none
 */
uint8_t tm1621x_set_tone(tm1621x_handle_t *handle, tm1621x_bool_t enable);

/**
 * @brief     enable or disable irq
 * @param[in] *handle pointer to a tm1621x handle structure
 * @param[in] enable bool value
 * @return    status code
 *            - 0 success
 *            - 1 set irq failed
 *            - 2 handle is NULL
 *            - 3 handle is not initialized
 *            - 4 only typeb support this function
 * @note      none
 */
uint8_t tm1621x_set_irq(tm1621x_handle_t *handle, tm1621x_bool_t enable);

/**
 * @brief     clear timer
 * @param[in] *handle pointer to a tm1621x handle structure
 * @return    status code
 *            - 0 success
 *            - 1 clear timer failed
 *            - 2 handle is NULL
 *            - 3 handle is not initialized
 *            - 4 only typeb support this function
 * @note      none
 */
uint8_t tm1621x_clear_timer(tm1621x_handle_t *handle);

/**
 * @brief     clear watchdog
 * @param[in] *handle pointer to a tm1621x handle structure
 * @return    status code
 *            - 0 success
 *            - 1 clear watchdog failed
 *            - 2 handle is NULL
 *            - 3 handle is not initialized
 *            - 4 only typeb support this function
 * @note      none
 */
uint8_t tm1621x_clear_watchdog(tm1621x_handle_t *handle);

/**
 * @}
 */

/**
 * @defgroup tm1621x_extern_driver tm1621x extern driver function
 * @brief    tm1621x extern driver modules
 * @ingroup  tm1621x_driver
 * @{
 */

/**
 * @brief     set command
 * @param[in] *handle pointer to a tm1621x handle structure
 * @param[in] cmd sent command
 * @return    status code
 *            - 0 success
 *            - 1 write failed
 *            - 2 handle is NULL
 *            - 3 handle is not initialized
 * @note      none
 */
uint8_t tm1621x_set_command(tm1621x_handle_t *handle, uint16_t cmd);

/**
 * @brief     set data
 * @param[in] *handle pointer to a tm1621x handle structure
 * @param[in] addr address
 * @param[in] *data pointer to an input data buffer
 * @param[in] len input data length
 * @return    status code
 *            - 0 success
 *            - 1 write failed
 *            - 2 handle is NULL
 *            - 3 handle is not initialized
 * @note      data width is 4 bits and data <= 0x0F
 */
uint8_t tm1621x_set_data(tm1621x_handle_t *handle, uint8_t addr, uint8_t *data, uint8_t len);

/**
 * @brief     read modify write
 * @param[in] *handle pointer to a tm1621x handle structure
 * @param[in] addr address
 * @param[in] *and_or pointer to an and_or function address
 * @param[in] len data length
 * @return    status code
 *            - 0 success
 *            - 1 read modify write failed
 *            - 2 handle is NULL
 *            - 3 handle is not initialized
 * @note      none
 */
uint8_t tm1621x_read_modify_write(tm1621x_handle_t *handle, uint8_t addr, void (*and_or)(uint8_t addr, uint8_t input, uint8_t *output), uint8_t len);

/**
 * @}
 */

/**
 * @}
 */

#ifdef __cplusplus
}
#endif

#endif

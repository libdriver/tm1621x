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
 * @file      driver_tm1621x_interface_template.c
 * @brief     driver tm1621x interface template source file
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

#include "driver_tm1621x_interface.h"

/**
 * @brief  interface data gpio init
 * @return status code
 *         - 0 success
 *         - 1 data gpio init failed
 * @note   none
 */
uint8_t tm1621x_interface_data_gpio_init(void)
{
    return 0;
}

/**
 * @brief  interface data gpio deinit
 * @return status code
 *         - 0 success
 *         - 1 data gpio deinit failed
 * @note   none
 */
uint8_t tm1621x_interface_data_gpio_deinit(void)
{
    return 0;
}

/**
 * @brief     interface data gpio write
 * @param[in] level gpio level
 * @return    status code
 *            - 0 success
 *            - 1 data gpio write failed
 * @note      none
 */
uint8_t tm1621x_interface_data_gpio_write(uint8_t level)
{
    return 0;
}

/**
 * @brief      interface data gpio read
 * @param[out] *level pointer to a gpio level buffer
 * @return     status code
 *             - 0 success
 *             - 1 data gpio read failed
 * @note       none
 */
uint8_t tm1621x_interface_data_gpio_read(uint8_t *level)
{
    return 0;
}

/**
 * @brief  interface wr gpio init
 * @return status code
 *         - 0 success
 *         - 1 wr gpio init failed
 * @note   none
 */
uint8_t tm1621x_interface_wr_gpio_init(void)
{
    return 0;
}

/**
 * @brief  interface wr gpio deinit
 * @return status code
 *         - 0 success
 *         - 1 wr gpio deinit failed
 * @note   none
 */
uint8_t tm1621x_interface_wr_gpio_deinit(void)
{
    return 0;
}

/**
 * @brief     interface wr gpio write
 * @param[in] level gpio level
 * @return    status code
 *            - 0 success
 *            - 1 wr gpio write failed
 * @note      none
 */
uint8_t tm1621x_interface_wr_gpio_write(uint8_t level)
{
    return 0;
}

/**
 * @brief  interface rd gpio init
 * @return status code
 *         - 0 success
 *         - 1 rd gpio init failed
 * @note   none
 */
uint8_t tm1621x_interface_rd_gpio_init(void)
{
    return 0;
}

/**
 * @brief  interface rd gpio deinit
 * @return status code
 *         - 0 success
 *         - 1 rd gpio deinit failed
 * @note   none
 */
uint8_t tm1621x_interface_rd_gpio_deinit(void)
{
    return 0;
}

/**
 * @brief     interface rd gpio write
 * @param[in] level gpio level
 * @return    status code
 *            - 0 success
 *            - 1 rd gpio write failed
 * @note      none
 */
uint8_t tm1621x_interface_rd_gpio_write(uint8_t level)
{
    return 0;
}

/**
 * @brief  interface cs gpio init
 * @return status code
 *         - 0 success
 *         - 1 cs gpio init failed
 * @note   none
 */
uint8_t tm1621x_interface_cs_gpio_init(void)
{
    return 0;
}

/**
 * @brief  interface cs gpio deinit
 * @return status code
 *         - 0 success
 *         - 1 cs gpio deinit failed
 * @note   none
 */
uint8_t tm1621x_interface_cs_gpio_deinit(void)
{
    return 0;
}

/**
 * @brief     interface cs gpio write
 * @param[in] level gpio level
 * @return    status code
 *            - 0 success
 *            - 1 cs gpio write failed
 * @note      none
 */
uint8_t tm1621x_interface_cs_gpio_write(uint8_t level)
{
    return 0;
}

/**
 * @brief     interface delay us
 * @param[in] us time
 * @note      none
 */
void tm1621x_interface_delay_us(uint32_t us)
{
    
}

/**
 * @brief     interface delay ms
 * @param[in] ms time
 * @note      none
 */
void tm1621x_interface_delay_ms(uint32_t ms)
{
    
}

/**
 * @brief     interface print format data
 * @param[in] fmt format data
 * @note      none
 */
void tm1621x_interface_debug_print(const char *const fmt, ...)
{
    
}

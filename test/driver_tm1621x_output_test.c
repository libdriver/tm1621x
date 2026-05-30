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
 * @file      driver_tm1621x_output_test.c
 * @brief     driver tm1621x output test source file
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
 
#include "driver_tm1621x_output_test.h"

/**
 * @brief tm1621x var definition
 */
static tm1621x_handle_t gs_handle;        /**< tm1621x handle */

/**
 * @brief     output test
 * @param[in] type chip type
 * @return    status code
 *            - 0 success
 *            - 1 test failed
 * @note      none
 */
uint8_t tm1621x_output_test(tm1621x_type_t type)
{
    uint8_t res;
    tm1621x_info_t info;

    /* link interface function */
    DRIVER_TM1621X_LINK_INIT(&gs_handle, tm1621x_handle_t); 
    DRIVER_TM1621X_LINK_DATA_GPIO_INIT(&gs_handle, tm1621x_interface_data_gpio_init);
    DRIVER_TM1621X_LINK_DATA_GPIO_DEINIT(&gs_handle, tm1621x_interface_data_gpio_deinit);
    DRIVER_TM1621X_LINK_DATA_GPIO_WRITE(&gs_handle, tm1621x_interface_data_gpio_write);
    DRIVER_TM1621X_LINK_DATA_GPIO_READ(&gs_handle, tm1621x_interface_data_gpio_read);
    DRIVER_TM1621X_LINK_WR_GPIO_INIT(&gs_handle, tm1621x_interface_wr_gpio_init);
    DRIVER_TM1621X_LINK_WR_GPIO_DEINIT(&gs_handle, tm1621x_interface_wr_gpio_deinit);
    DRIVER_TM1621X_LINK_WR_GPIO_WRITE(&gs_handle, tm1621x_interface_wr_gpio_write);
    DRIVER_TM1621X_LINK_RD_GPIO_INIT(&gs_handle, tm1621x_interface_rd_gpio_init);
    DRIVER_TM1621X_LINK_RD_GPIO_DEINIT(&gs_handle, tm1621x_interface_rd_gpio_deinit);
    DRIVER_TM1621X_LINK_RD_GPIO_WRITE(&gs_handle, tm1621x_interface_rd_gpio_write);
    DRIVER_TM1621X_LINK_CS_GPIO_INIT(&gs_handle, tm1621x_interface_cs_gpio_init);
    DRIVER_TM1621X_LINK_CS_GPIO_DEINIT(&gs_handle, tm1621x_interface_cs_gpio_deinit);
    DRIVER_TM1621X_LINK_CS_GPIO_WRITE(&gs_handle, tm1621x_interface_cs_gpio_write);
    DRIVER_TM1621X_LINK_DELAY_US(&gs_handle, tm1621x_interface_delay_us);
    DRIVER_TM1621X_LINK_DELAY_MS(&gs_handle, tm1621x_interface_delay_ms);
    DRIVER_TM1621X_LINK_DEBUG_PRINT(&gs_handle, tm1621x_interface_debug_print);
    
    /* get information */
    res = tm1621x_info(&info);
    if (res != 0)
    {
        tm1621x_interface_debug_print("tm1621x: get info failed.\n");
        
        return 1;
    }
    else
    {
        /* print chip info */
        tm1621x_interface_debug_print("tm1621x: chip is %s.\n", info.chip_name);
        tm1621x_interface_debug_print("tm1621x: manufacturer is %s.\n", info.manufacturer_name);
        tm1621x_interface_debug_print("tm1621x: interface is %s.\n", info.interface);
        tm1621x_interface_debug_print("tm1621x: driver version is %d.%d.\n", info.driver_version / 1000, (info.driver_version % 1000) / 100);
        tm1621x_interface_debug_print("tm1621x: min supply voltage is %0.1fV.\n", info.supply_voltage_min_v);
        tm1621x_interface_debug_print("tm1621x: max supply voltage is %0.1fV.\n", info.supply_voltage_max_v);
        tm1621x_interface_debug_print("tm1621x: max current is %0.2fmA.\n", info.max_current_ma);
        tm1621x_interface_debug_print("tm1621x: max temperature is %0.1fC.\n", info.temperature_max);
        tm1621x_interface_debug_print("tm1621x: min temperature is %0.1fC.\n", info.temperature_min);
    }
    
    /* start output test */
    tm1621x_interface_debug_print("tm1621x: start output test.\n");
    
    /* check type */
    if (type != TM1621X_TYPE_B)
    {
        tm1621x_interface_debug_print("tm1621x: only type b supports this function.\n");
        
        return 1;
    }
    
    /* set type */
    res = tm1621x_set_type(&gs_handle, type);
    if (res != 0)
    {
        tm1621x_interface_debug_print("tm1621x: set type failed.\n");
        
        return 1;
    }
    
    /* tm1621x init */
    res = tm1621x_init(&gs_handle);
    if (res != 0)
    {
        tm1621x_interface_debug_print("tm1621x: init failed.\n");
        
        return 1;
    }
    
    /* set clock */
    res = tm1621x_set_clock(&gs_handle, TM1621X_CLOCK_RC_256K);
    if (res != 0)
    {
        tm1621x_interface_debug_print("tm1621x: set clock failed.\n");
        (void)tm1621x_deinit(&gs_handle);
        
        return 1;
    }
    
    /* enable oscillator */
    res = tm1621x_set_oscillator(&gs_handle, TM1621X_BOOL_TRUE);
    if (res != 0)
    {
        tm1621x_interface_debug_print("tm1621x: set oscillator failed.\n");
        (void)tm1621x_deinit(&gs_handle);
        
        return 1;
    }
    
    /* set bias 1div3 4 */
    res = tm1621x_set_bias_1div3(&gs_handle, TM1621X_BIAS_4);
    if (res != 0)
    {
        tm1621x_interface_debug_print("tm1621x: set bias 1div3 failed.\n");
        (void)tm1621x_deinit(&gs_handle);
        
        return 1;
    }
    
    /* enable lcd bias */
    res = tm1621x_set_lcd_bias(&gs_handle, TM1621X_BOOL_TRUE);
    if (res != 0)
    {
        tm1621x_interface_debug_print("tm1621x: set lcd bias failed.\n");
        (void)tm1621x_deinit(&gs_handle);
        
        return 1;
    }
    
    /* set normal mode */
    res = tm1621x_set_mode(&gs_handle, TM1621X_MODE_NORMAL);
    if (res != 0)
    {
        tm1621x_interface_debug_print("tm1621x: set mode failed.\n");
        (void)tm1621x_deinit(&gs_handle);
        
        return 1;
    }
    
    /* disable tone */
    res = tm1621x_set_tone(&gs_handle, TM1621X_BOOL_FALSE);
    if (res != 0)
    {
        tm1621x_interface_debug_print("tm1621x: set tone failed.\n");
        (void)tm1621x_deinit(&gs_handle);
        
        return 1;
    }
    
    /* disable timer */
    res = tm1621x_set_timer(&gs_handle, TM1621X_BOOL_FALSE);
    if (res != 0)
    {
        tm1621x_interface_debug_print("tm1621x: set timer failed.\n");
        (void)tm1621x_deinit(&gs_handle);
        
        return 1;
    }
    
    /* clear timer */
    res = tm1621x_clear_timer(&gs_handle);
    if (res != 0)
    {
        tm1621x_interface_debug_print("tm1621x: clear timer failed.\n");
        (void)tm1621x_deinit(&gs_handle);
        
        return 1;
    }
    
    /* disable watchdog */
    res = tm1621x_set_watchdog(&gs_handle, TM1621X_BOOL_FALSE);
    if (res != 0)
    {
        tm1621x_interface_debug_print("tm1621x: set watchdog failed.\n");
        (void)tm1621x_deinit(&gs_handle);
        
        return 1;
    }
    
    /* clear watchdog */
    res = tm1621x_clear_watchdog(&gs_handle);
    if (res != 0)
    {
        tm1621x_interface_debug_print("tm1621x: clear watchdog failed.\n");
        (void)tm1621x_deinit(&gs_handle);
        
        return 1;
    }
    
    /* enable interrupt */
    res = tm1621x_set_irq(&gs_handle, TM1621X_BOOL_TRUE);
    if (res != 0)
    {
        tm1621x_interface_debug_print("tm1621x: set irq failed.\n");
        (void)tm1621x_deinit(&gs_handle);
        
        return 1;
    }
    
    /* clear segment */
    res = tm1621x_clear_segment(&gs_handle);
    if (res != 0)
    {
        tm1621x_interface_debug_print("tm1621x: clear segment failed.\n");
        (void)tm1621x_deinit(&gs_handle);
        
        return 1;
    }
    
    /* set freq clock 1hz, wdt 4s */
    res = tm1621x_set_freq(&gs_handle, TM1621X_FREQ_F1);
    if (res != 0)
    {
        tm1621x_interface_debug_print("tm1621x: set freq failed.\n");
        (void)tm1621x_deinit(&gs_handle);
        
        return 1;
    }
    
    /* enable timer */
    res = tm1621x_set_timer(&gs_handle, TM1621X_BOOL_TRUE);
    if (res != 0)
    {
        tm1621x_interface_debug_print("tm1621x: set timer failed.\n");
        (void)tm1621x_deinit(&gs_handle);
        
        return 1;
    }
    
    /* clock 1hz test */
    tm1621x_interface_debug_print("tm1621x: clock 1hz test.\n");
    
    /* delay 5000ms */
    tm1621x_interface_delay_ms(5000);
    
    /* set freq clock 2hz, wdt 2s */
    res = tm1621x_set_freq(&gs_handle, TM1621X_FREQ_F2);
    if (res != 0)
    {
        tm1621x_interface_debug_print("tm1621x: set freq failed.\n");
        (void)tm1621x_deinit(&gs_handle);
        
        return 1;
    }
    
    /* clock 2hz test */
    tm1621x_interface_debug_print("tm1621x: clock 2hz test.\n");
    
    /* delay 5000ms */
    tm1621x_interface_delay_ms(5000);
    
    /* set freq clock 4hz, wdt 1s */
    res = tm1621x_set_freq(&gs_handle, TM1621X_FREQ_F4);
    if (res != 0)
    {
        tm1621x_interface_debug_print("tm1621x: set freq failed.\n");
        (void)tm1621x_deinit(&gs_handle);
        
        return 1;
    }
    
    /* clock 4hz test */
    tm1621x_interface_debug_print("tm1621x: clock 4hz test.\n");
    
    /* delay 5000ms */
    tm1621x_interface_delay_ms(5000);
    
    /* set freq clock 8hz, wdt 1/2s */
    res = tm1621x_set_freq(&gs_handle, TM1621X_FREQ_F8);
    if (res != 0)
    {
        tm1621x_interface_debug_print("tm1621x: set freq failed.\n");
        (void)tm1621x_deinit(&gs_handle);
        
        return 1;
    }
    
    /* clock 8hz test */
    tm1621x_interface_debug_print("tm1621x: clock 8hz test.\n");
    
    /* delay 5000ms */
    tm1621x_interface_delay_ms(5000);
    
    /* set freq clock 16hz, wdt 1/4s */
    res = tm1621x_set_freq(&gs_handle, TM1621X_FREQ_F16);
    if (res != 0)
    {
        tm1621x_interface_debug_print("tm1621x: set freq failed.\n");
        (void)tm1621x_deinit(&gs_handle);
        
        return 1;
    }
    
    /* clock 16hz test */
    tm1621x_interface_debug_print("tm1621x: clock 16hz test.\n");
    
    /* delay 5000ms */
    tm1621x_interface_delay_ms(5000);
    
    /* set freq clock 32hz, wdt 1/8s */
    res = tm1621x_set_freq(&gs_handle, TM1621X_FREQ_F32);
    if (res != 0)
    {
        tm1621x_interface_debug_print("tm1621x: set freq failed.\n");
        (void)tm1621x_deinit(&gs_handle);
        
        return 1;
    }
    
    /* clock 32hz test */
    tm1621x_interface_debug_print("tm1621x: clock 32hz test.\n");
    
    /* delay 5000ms */
    tm1621x_interface_delay_ms(5000);
    
    /* set freq clock 64hz, wdt 1/16s */
    res = tm1621x_set_freq(&gs_handle, TM1621X_FREQ_F64);
    if (res != 0)
    {
        tm1621x_interface_debug_print("tm1621x: set freq failed.\n");
        (void)tm1621x_deinit(&gs_handle);
        
        return 1;
    }
    
    /* clock 64hz test */
    tm1621x_interface_debug_print("tm1621x: clock 64hz test.\n");
    
    /* delay 5000ms */
    tm1621x_interface_delay_ms(5000);
    
    /* set freq clock 128hz, wdt 1/32s */
    res = tm1621x_set_freq(&gs_handle, TM1621X_FREQ_F128);
    if (res != 0)
    {
        tm1621x_interface_debug_print("tm1621x: set freq failed.\n");
        (void)tm1621x_deinit(&gs_handle);
        
        return 1;
    }
    
    /* clock 128hz test */
    tm1621x_interface_debug_print("tm1621x: clock 128hz test.\n");
    
    /* delay 5000ms */
    tm1621x_interface_delay_ms(5000);
    
    /* disable timer */
    res = tm1621x_set_timer(&gs_handle, TM1621X_BOOL_FALSE);
    if (res != 0)
    {
        tm1621x_interface_debug_print("tm1621x: set timer failed.\n");
        (void)tm1621x_deinit(&gs_handle);
        
        return 1;
    }
    
    /* clear timer */
    res = tm1621x_clear_timer(&gs_handle);
    if (res != 0)
    {
        tm1621x_interface_debug_print("tm1621x: clear timer failed.\n");
        (void)tm1621x_deinit(&gs_handle);
        
        return 1;
    }
    
    /* enable watchdog */
    res = tm1621x_set_watchdog(&gs_handle, TM1621X_BOOL_TRUE);
    if (res != 0)
    {
        tm1621x_interface_debug_print("tm1621x: set watchdog failed.\n");
        (void)tm1621x_deinit(&gs_handle);
        
        return 1;
    }
    
    /* clear watchdog */
    res = tm1621x_clear_watchdog(&gs_handle);
    if (res != 0)
    {
        tm1621x_interface_debug_print("tm1621x: clear watchdog failed.\n");
        (void)tm1621x_deinit(&gs_handle);
        
        return 1;
    }
    
    /* set freq clock 1hz, wdt 4s */
    res = tm1621x_set_freq(&gs_handle, TM1621X_FREQ_F1);
    if (res != 0)
    {
        tm1621x_interface_debug_print("tm1621x: set freq failed.\n");
        (void)tm1621x_deinit(&gs_handle);
        
        return 1;
    }
    
    /* wdt 4s test */
    tm1621x_interface_debug_print("tm1621x: wdt 4s test.\n");
    
    /* delay 5000ms */
    tm1621x_interface_delay_ms(5000);
    
    /* clear watchdog */
    res = tm1621x_clear_watchdog(&gs_handle);
    if (res != 0)
    {
        tm1621x_interface_debug_print("tm1621x: clear watchdog failed.\n");
        (void)tm1621x_deinit(&gs_handle);
        
        return 1;
    }
    
    /* set freq clock 2hz, wdt 2s */
    res = tm1621x_set_freq(&gs_handle, TM1621X_FREQ_F2);
    if (res != 0)
    {
        tm1621x_interface_debug_print("tm1621x: set freq failed.\n");
        (void)tm1621x_deinit(&gs_handle);
        
        return 1;
    }
    
    /* wdt 2s test */
    tm1621x_interface_debug_print("tm1621x: wdt 2s test.\n");
    
    /* delay 3000ms */
    tm1621x_interface_delay_ms(3000);
    
    /* clear watchdog */
    res = tm1621x_clear_watchdog(&gs_handle);
    if (res != 0)
    {
        tm1621x_interface_debug_print("tm1621x: clear watchdog failed.\n");
        (void)tm1621x_deinit(&gs_handle);
        
        return 1;
    }
    
    /* set freq clock 4hz, wdt 1s */
    res = tm1621x_set_freq(&gs_handle, TM1621X_FREQ_F4);
    if (res != 0)
    {
        tm1621x_interface_debug_print("tm1621x: set freq failed.\n");
        (void)tm1621x_deinit(&gs_handle);
        
        return 1;
    }
    
    /* wdt 1s test */
    tm1621x_interface_debug_print("tm1621x: wdt 1s test.\n");
    
    /* delay 2000ms */
    tm1621x_interface_delay_ms(2000);
    
    /* clear watchdog */
    res = tm1621x_clear_watchdog(&gs_handle);
    if (res != 0)
    {
        tm1621x_interface_debug_print("tm1621x: clear watchdog failed.\n");
        (void)tm1621x_deinit(&gs_handle);
        
        return 1;
    }
    
    /* set freq clock 8hz, wdt 1/2s */
    res = tm1621x_set_freq(&gs_handle, TM1621X_FREQ_F8);
    if (res != 0)
    {
        tm1621x_interface_debug_print("tm1621x: set freq failed.\n");
        (void)tm1621x_deinit(&gs_handle);
        
        return 1;
    }
    
    /* wdt 1/2s test */
    tm1621x_interface_debug_print("tm1621x: wdt 1/2s test.\n");
    
    /* delay 1000ms */
    tm1621x_interface_delay_ms(1000);
    
    /* clear watchdog */
    res = tm1621x_clear_watchdog(&gs_handle);
    if (res != 0)
    {
        tm1621x_interface_debug_print("tm1621x: clear watchdog failed.\n");
        (void)tm1621x_deinit(&gs_handle);
        
        return 1;
    }
    
    /* set freq clock 16hz, wdt 1/4s */
    res = tm1621x_set_freq(&gs_handle, TM1621X_FREQ_F16);
    if (res != 0)
    {
        tm1621x_interface_debug_print("tm1621x: set freq failed.\n");
        (void)tm1621x_deinit(&gs_handle);
        
        return 1;
    }
    
    /* wdt 1/4s test */
    tm1621x_interface_debug_print("tm1621x: wdt 1/4s test.\n");
    
    /* delay 1000ms */
    tm1621x_interface_delay_ms(1000);
    
    /* clear watchdog */
    res = tm1621x_clear_watchdog(&gs_handle);
    if (res != 0)
    {
        tm1621x_interface_debug_print("tm1621x: clear watchdog failed.\n");
        (void)tm1621x_deinit(&gs_handle);
        
        return 1;
    }
    
    /* set freq clock 32hz, wdt 1/8s */
    res = tm1621x_set_freq(&gs_handle, TM1621X_FREQ_F32);
    if (res != 0)
    {
        tm1621x_interface_debug_print("tm1621x: set freq failed.\n");
        (void)tm1621x_deinit(&gs_handle);
        
        return 1;
    }
    
    /* wdt 1/8s test */
    tm1621x_interface_debug_print("tm1621x: wdt 1/8s test.\n");
    
    /* delay 1000ms */
    tm1621x_interface_delay_ms(1000);
    
    /* clear watchdog */
    res = tm1621x_clear_watchdog(&gs_handle);
    if (res != 0)
    {
        tm1621x_interface_debug_print("tm1621x: clear watchdog failed.\n");
        (void)tm1621x_deinit(&gs_handle);
        
        return 1;
    }
    
    /* set freq clock 64hz, wdt 1/16s */
    res = tm1621x_set_freq(&gs_handle, TM1621X_FREQ_F64);
    if (res != 0)
    {
        tm1621x_interface_debug_print("tm1621x: set freq failed.\n");
        (void)tm1621x_deinit(&gs_handle);
        
        return 1;
    }
    
    /* wdt 1/16s test */
    tm1621x_interface_debug_print("tm1621x: wdt 1/16s test.\n");
    
    /* delay 1000ms */
    tm1621x_interface_delay_ms(1000);
    
    /* clear watchdog */
    res = tm1621x_clear_watchdog(&gs_handle);
    if (res != 0)
    {
        tm1621x_interface_debug_print("tm1621x: clear watchdog failed.\n");
        (void)tm1621x_deinit(&gs_handle);
        
        return 1;
    }
    
    /* set freq clock 128hz, wdt 1/32s */
    res = tm1621x_set_freq(&gs_handle, TM1621X_FREQ_F128);
    if (res != 0)
    {
        tm1621x_interface_debug_print("tm1621x: set freq failed.\n");
        (void)tm1621x_deinit(&gs_handle);
        
        return 1;
    }
    
    /* wdt 1/32s test */
    tm1621x_interface_debug_print("tm1621x: wdt 1/32s test.\n");
    
    /* delay 1000ms */
    tm1621x_interface_delay_ms(1000);
    
    /* disable watchdog */
    res = tm1621x_set_watchdog(&gs_handle, TM1621X_BOOL_FALSE);
    if (res != 0)
    {
        tm1621x_interface_debug_print("tm1621x: set watchdog failed.\n");
        (void)tm1621x_deinit(&gs_handle);
        
        return 1;
    }
    
    /* clear watchdog */
    res = tm1621x_clear_watchdog(&gs_handle);
    if (res != 0)
    {
        tm1621x_interface_debug_print("tm1621x: clear watchdog failed.\n");
        (void)tm1621x_deinit(&gs_handle);
        
        return 1;
    }
    
    /* finish output test */
    tm1621x_interface_debug_print("tm1621x: finish output test.\n");
    (void)tm1621x_deinit(&gs_handle);
    
    return 0;
}

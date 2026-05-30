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
 * @file      driver_tm1621x_write_test.c
 * @brief     driver tm1621x write test source file
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
 
#include "driver_tm1621x_write_test.h"
#include <stdlib.h>

/**
 * @brief tm1621x var definition
 */
static tm1621x_handle_t gs_handle;        /**< tm1621x handle */
static uint8_t gs_read_buffer[32];        /**< read buffer */
static uint8_t gs_write_buffer[32];       /**< write buffer */
static uint8_t gs_command = 0;            /**< command */

/**
 * @brief      and or progress
 * @param[in]  addr address
 * @param[in]  input input data
 * @param[out] *output pointer to an output data buffer
 * @note       none
 */
static void a_and_or(uint8_t addr, uint8_t input, uint8_t *output)
{
    if (gs_command == 1)
    {
        gs_read_buffer[(addr > 31) ? 31 : addr] = input;
        *output = input;
    }
    if (gs_command == 2)
    {
        *output = gs_write_buffer[(addr > 31) ? 31 : addr];
    }
}

/**
 * @brief     write test
 * @param[in] type chip type
 * @return    status code
 *            - 0 success
 *            - 1 test failed
 * @note      none
 */
uint8_t tm1621x_write_test(tm1621x_type_t type)
{
    uint8_t res;
    uint32_t i;
    uint32_t j;
    const uint8_t seg_table_even[10] =
    {
        0x05,
        0x0E,
        0x0F,
        0x07,
        0x0B,
        0x0B,
        0x0D,
        0x0F,
        0x0F,
        0x0D,
    };
    const uint8_t seg_table_odd[10] =
    {
        0x00,
        0x03,
        0x01,
        0x04,
        0x05,
        0x0F,
        0x00,
        0x0F,
        0x0D,
        0x0F,
    };
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
    
    /* start write test */
    tm1621x_interface_debug_print("tm1621x: start write test.\n");
    
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
    
    if (type == TM1621X_TYPE_B)
    {
        /* set freq clock 1hz, wdt 4s */
        res = tm1621x_set_freq(&gs_handle, TM1621X_FREQ_F1);
        if (res != 0)
        {
            tm1621x_interface_debug_print("tm1621x: set freq failed.\n");
            (void)tm1621x_deinit(&gs_handle);
            
            return 1;
        }
        
        /* set tone freq 2k */
        res = tm1621x_set_tone_freq(&gs_handle, TM1621X_TONE_FREQ_2K);
        if (res != 0)
        {
            tm1621x_interface_debug_print("tm1621x: set tone freq failed.\n");
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
        
        /* disable interrupt */
        res = tm1621x_set_irq(&gs_handle, TM1621X_BOOL_FALSE);
        if (res != 0)
        {
            tm1621x_interface_debug_print("tm1621x: set irq failed.\n");
            (void)tm1621x_deinit(&gs_handle);
            
            return 1;
        }
    }
    
    /* clear segment */
    res = tm1621x_clear_segment(&gs_handle);
    if (res != 0)
    {
        tm1621x_interface_debug_print("tm1621x: clear segment failed.\n");
        (void)tm1621x_deinit(&gs_handle);
        
        return 1;
    }
    
    /* output */
    tm1621x_interface_debug_print("tm1621x: write segment test.\n");
    
    for (i = 0; i < 10; i++)
    {
        uint8_t buffer[32];
        
        /* copy data */
        for (j = 0; j < 32; j++)
        {
            if ((j % 2) != 0)
            {
                buffer[j] = seg_table_odd[i];
            }
            else
            {
                buffer[j] = seg_table_even[i];
            }
        }
        
        /* write segment */
        res = tm1621x_write_segment(&gs_handle, 0x00, buffer, 32);
        if (res != 0)
        {
            tm1621x_interface_debug_print("tm1621x: write segment failed.\n");
            (void)tm1621x_deinit(&gs_handle);
            
            return 1;
        }
        
        /* delay 1000ms */
        tm1621x_interface_delay_ms(1000);
    }
    
    if (type == TM1621X_TYPE_B)
    {
        /* output */
        tm1621x_interface_debug_print("tm1621x: 2k tone test.\n");
        
        /* set tone freq 2k */
        res = tm1621x_set_tone_freq(&gs_handle, TM1621X_TONE_FREQ_2K);
        if (res != 0)
        {
            tm1621x_interface_debug_print("tm1621x: set tone freq failed.\n");
            (void)tm1621x_deinit(&gs_handle);
            
            return 1;
        }
        
        /* enable tone */
        res = tm1621x_set_tone(&gs_handle, TM1621X_BOOL_TRUE);
        if (res != 0)
        {
            tm1621x_interface_debug_print("tm1621x: set tone failed.\n");
            (void)tm1621x_deinit(&gs_handle);
            
            return 1;
        }
        
        /* delay 3000ms */
        tm1621x_interface_delay_ms(3000);
        
        /* disable tone */
        res = tm1621x_set_tone(&gs_handle, TM1621X_BOOL_FALSE);
        if (res != 0)
        {
            tm1621x_interface_debug_print("tm1621x: set tone failed.\n");
            (void)tm1621x_deinit(&gs_handle);
            
            return 1;
        }
        
        /* delay 1000ms */
        tm1621x_interface_delay_ms(1000);
        
        /* output */
        tm1621x_interface_debug_print("tm1621x: 4k tone test.\n");
        
        /* set tone freq 4k */
        res = tm1621x_set_tone_freq(&gs_handle, TM1621X_TONE_FREQ_4K);
        if (res != 0)
        {
            tm1621x_interface_debug_print("tm1621x: set tone freq failed.\n");
            (void)tm1621x_deinit(&gs_handle);
            
            return 1;
        }
        
        /* enable tone */
        res = tm1621x_set_tone(&gs_handle, TM1621X_BOOL_TRUE);
        if (res != 0)
        {
            tm1621x_interface_debug_print("tm1621x: set tone failed.\n");
            (void)tm1621x_deinit(&gs_handle);
            
            return 1;
        }
        
        /* delay 3000ms */
        tm1621x_interface_delay_ms(3000);
        
        /* disable tone */
        res = tm1621x_set_tone(&gs_handle, TM1621X_BOOL_FALSE);
        if (res != 0)
        {
            tm1621x_interface_debug_print("tm1621x: set tone failed.\n");
            (void)tm1621x_deinit(&gs_handle);
            
            return 1;
        }
        
        /* output */
        tm1621x_interface_debug_print("tm1621x: read modify write test.\n");
        
        /* copy data */
        for (j = 0; j < 32; j++)
        {
            gs_write_buffer[j] = j % 0x10;
        }
        
        /* write data */
        gs_command = 2;
        
        /* read modify write */
        res = tm1621x_read_modify_write(&gs_handle, 0x00, a_and_or, 32);
        if (res != 0)
        {
            tm1621x_interface_debug_print("tm1621x: read modify write failed.\n");
            (void)tm1621x_deinit(&gs_handle);
            
            return 1;
        }
        
        /* clear data */
        memset(gs_read_buffer, 0, sizeof(uint8_t) * 32);
        
        /* read data */
        gs_command = 1;
        
        /* read modify write */
        res = tm1621x_read_modify_write(&gs_handle, 0x00, a_and_or, 32);
        if (res != 0)
        {
            tm1621x_interface_debug_print("tm1621x: read modify write failed.\n");
            (void)tm1621x_deinit(&gs_handle);
            
            return 1;
        }
        
        /* copy data */
        for (j = 0; j < 32; j++)
        {
            if (gs_read_buffer[j] != gs_write_buffer[j])
            {
                tm1621x_interface_debug_print("tm1621x: data check failed.\n");
                (void)tm1621x_deinit(&gs_handle);
                
                return 1;
            }
        }
        
        /* output */
        tm1621x_interface_debug_print("tm1621x: data check passed.\n");
    }
    
    /* finish write test */
    tm1621x_interface_debug_print("tm1621x: finish write test.\n");
    (void)tm1621x_deinit(&gs_handle);
    
    return 0;
}

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
 * @file      driver_tm1621x_basic.c
 * @brief     driver tm1621x basic source file
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

#include "driver_tm1621x_basic.h"

static tm1621x_handle_t gs_handle;        /**< tm1621x handle */

/**
 * @brief     basic example init
 * @param[in] type chip type
 * @return    status code
 *            - 0 success
 *            - 1 init failed
 * @note      none
 */
uint8_t tm1621x_basic_init(tm1621x_type_t type)
{
    uint8_t res;
    
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
    
    /* set default clock */
    res = tm1621x_set_clock(&gs_handle, TM1621X_BASIC_DEFAULT_CLOCK);
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
    
#if (TM1621X_BASIC_DEFAULT_USE_BIAS == TM1621X_BASIC_BIAS_1DIV2)
    /* set default bias */
    res = tm1621x_set_bias_1div2(&gs_handle, TM1621X_BASIC_DEFAULT_BIAS);
    if (res != 0)
    {
        tm1621x_interface_debug_print("tm1621x: set bias 1div2 failed.\n");
        (void)tm1621x_deinit(&gs_handle);
        
        return 1;
    }
#elif (TM1621X_BASIC_DEFAULT_USE_BIAS == TM1621X_BASIC_BIAS_1DIV3)
    /* set default bias */
    res = tm1621x_set_bias_1div3(&gs_handle, TM1621X_BASIC_DEFAULT_BIAS);
    if (res != 0)
    {
        tm1621x_interface_debug_print("tm1621x: set bias 1div3 failed.\n");
        (void)tm1621x_deinit(&gs_handle);
        
        return 1;
    }
#else
    #error "invalid bias type"
#endif
    
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
    
    return 0;
}

/**
 * @brief     basic example write
 * @param[in] addr start address
 * @param[in] *data pointer to a data buffer
 * @param[in] len data length
 * @return    status code
 *            - 0 success
 *            - 1 write failed
 * @note      none
 */
uint8_t tm1621x_basic_write(uint8_t addr, uint8_t *data, uint8_t len)
{
    uint8_t res;
    
    /* write segment */
    res = tm1621x_write_segment(&gs_handle, addr, data, len);
    if (res != 0)
    {
        return 1;
    }
    
    return 0;
}

/**
 * @brief  basic example clear
 * @return status code
 *         - 0 success
 *         - 1 clear failed
 * @note   none
 */
uint8_t tm1621x_basic_clear(void)
{
    uint8_t res;
    
    /* clear segment */
    res = tm1621x_clear_segment(&gs_handle);
    if (res != 0)
    {
        return 1;
    }
    
    return 0;
}

/**
 * @brief  basic example display on
 * @return status code
 *         - 0 success
 *         - 1 display on failed
 * @note   none
 */
uint8_t tm1621x_basic_display_on(void)
{
    uint8_t res;
    
    /* enable lcd bias */
    res = tm1621x_set_lcd_bias(&gs_handle, TM1621X_BOOL_TRUE);
    if (res != 0)
    {
        return 1;
    }
    
    return 0;
}

/**
 * @brief  basic example display off
 * @return status code
 *         - 0 success
 *         - 1 display off failed
 * @note   none
 */
uint8_t tm1621x_basic_display_off(void)
{
    uint8_t res;
    
    /* disable lcd bias */
    res = tm1621x_set_lcd_bias(&gs_handle, TM1621X_BOOL_FALSE);
    if (res != 0)
    {
        return 1;
    }
    
    return 0;
}

/**
 * @brief  basic example deinit
 * @return status code
 *         - 0 success
 *         - 1 deinit failed
 * @note   none
 */
uint8_t tm1621x_basic_deinit(void)
{
    uint8_t res;
    
    /* deinit tm1621x */
    res = tm1621x_deinit(&gs_handle);
    if (res != 0)
    {
        return 1;
    }
    
    return 0;
}

/**
 * @brief  basic example enable tone
 * @return status code
 *         - 0 success
 *         - 1 enable tone failed
 * @note   none
 */
uint8_t tm1621x_basic_enable_tone(void)
{
    uint8_t res;
    
    /* enable tone */
    res = tm1621x_set_tone(&gs_handle, TM1621X_BOOL_TRUE);
    if (res != 0)
    {
        return 1;
    }
    
    return 0;
}

/**
 * @brief  basic example disable tone
 * @return status code
 *         - 0 success
 *         - 1 disable tone failed
 * @note   none
 */
uint8_t tm1621x_basic_disable_tone(void)
{
    uint8_t res;
    
    /* disable tone */
    res = tm1621x_set_tone(&gs_handle, TM1621X_BOOL_FALSE);
    if (res != 0)
    {
        return 1;
    }
    
    return 0;
}

/**
 * @brief     basic example set tone freq
 * @param[in] freq tone freq
 * @return    status code
 *            - 0 success
 *            - 1 set tone freq failed
 * @note      none
 */
uint8_t tm1621x_basic_set_tone_freq(tm1621x_tone_freq_t freq)
{
    uint8_t res;
    
    /* set tone freq */
    res = tm1621x_set_tone_freq(&gs_handle, freq);
    if (res != 0)
    {
        return 1;
    }
    
    return 0;
}

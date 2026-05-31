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
 * @file      driver_tm1621x.c
 * @brief     driver tm1621x source file
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

#include "driver_tm1621x.h"

/**
 * @brief chip information definition
 */
#define CHIP_NAME                 "Titan Micro Electronics TM1621X"        /**< chip name */
#define MANUFACTURER_NAME         "Titan Micro Electronics"                /**< manufacturer name */
#define SUPPLY_VOLTAGE_MIN        2.4f                                     /**< chip min supply voltage */
#define SUPPLY_VOLTAGE_MAX        5.2f                                     /**< chip max supply voltage */
#define MAX_CURRENT               2.6f                                     /**< chip max current */
#define TEMPERATURE_MIN           -40.0f                                   /**< chip min operating temperature */
#define TEMPERATURE_MAX           85.0f                                    /**< chip max operating temperature */
#define DRIVER_VERSION            1000                                     /**< driver version */

/**
 * @brief chip command definition
 */
#define TM1621X_COMMAND_SYS_DIS        0x00        /**< system disable command */
#define TM1621X_COMMAND_SYS_EN         0x01        /**< system enable command */
#define TM1621X_COMMAND_LCD_OFF        0x02        /**< lcd off command */
#define TM1621X_COMMAND_LCD_ON         0x03        /**< lcd on command */
#define TM1621X_COMMAND_TIMER_DIS      0x04        /**< timer disable command */
#define TM1621X_COMMAND_WDT_DIS        0x05        /**< wdt disable command */
#define TM1621X_COMMAND_TIMER_EN       0x06        /**< timer enable command */
#define TM1621X_COMMAND_WDT_EN         0x07        /**< wdt enable command */
#define TM1621X_COMMAND_TONE_OFF       0x08        /**< tone off command */
#define TM1621X_COMMAND_TONE_ON        0x09        /**< tone on command */
#define TM1621X_COMMAND_CLR_TIMER      0x0C        /**< clear timer command */
#define TM1621X_COMMAND_CLR_WDT        0x0E        /**< clear wdt command */
#define TM1621X_COMMAND_XTAL_32K       0x14        /**< xtal 32k command */
#define TM1621X_COMMAND_RC_256K        0x18        /**< rc 256k command */
#define TM1621X_COMMAND_EXT_256K       0x1C        /**< ext 256k command */
#define TM1621X_COMMAND_BIAS_1DIV2     0x20        /**< bias 1/2 command */
#define TM1621X_COMMAND_BIAS_1DIV3     0x21        /**< bias 1/3 command */
#define TM1621X_COMMAND_TONE_4K        0x40        /**< tone 4k command */
#define TM1621X_COMMAND_TONE_2K        0x60        /**< tone 2k command */
#define TM1621X_COMMAND_IRQ_DIS        0x80        /**< irq disable command */
#define TM1621X_COMMAND_IRQ_EN         0x88        /**< irq enable command */
#define TM1621X_COMMAND_F1             0xA0        /**< f1 command */
#define TM1621X_COMMAND_F2             0xA1        /**< f2 command */
#define TM1621X_COMMAND_F4             0xA2        /**< f4 command */
#define TM1621X_COMMAND_F8             0xA3        /**< f8 command */
#define TM1621X_COMMAND_F16            0xA4        /**< f16 command */
#define TM1621X_COMMAND_F32            0xA5        /**< f32 command */
#define TM1621X_COMMAND_F64            0xA6        /**< f64 command */
#define TM1621X_COMMAND_F128           0xA7        /**< f128 command */
#define TM1621X_COMMAND_TOPT           0xE0        /**< test command */
#define TM1621X_COMMAND_TNORMAL        0xE3        /**< normal command */

/**
 * @brief     write bits
 * @param[in] *handle pointer to a tm1621x handle structure
 * @param[in] data input data
 * @param[in] len data length
 * @return    status code
 *            - 0 success
 *            - 1 write failed
 * @note      none
 */
static uint8_t a_tm1621x_write_bits(tm1621x_handle_t *handle, uint32_t data, uint8_t len)
{
    uint8_t res;
    uint8_t i;
    
    for (i = 0; i < len; i++)                                                     /* write bits */
    {
        res = handle->wr_gpio_write(0);                                           /* set low */
        if (res != 0)                                                             /* check the result */
        {
            handle->debug_print("tm1621x: wr gpio write failed.\n");              /* wr gpio write failed */
            
            return 1;                                                             /* return error */
        }
        handle->delay_us(TM1621X_COMMAND_DATA_DELAY);                             /* delay */
        if ((data & (1 << (len - 1 - i))) != 0)                                   /* check bit */
        {
            res = handle->data_gpio_write(1);                                     /* set high */
            if (res != 0)                                                         /* check the result */
            {
                handle->debug_print("tm1621x: data gpio write failed.\n");        /* data gpio write failed */
                
                return 1;                                                         /* return error */
            }
        }
        else
        {
            res = handle->data_gpio_write(0);                                     /* set low */
            if (res != 0)                                                         /* check the result */
            {
                handle->debug_print("tm1621x: data gpio write failed.\n");        /* data gpio write failed */
                
                return 1;                                                         /* return error */
            }
        }
        handle->delay_us(TM1621X_COMMAND_DATA_DELAY);                             /* delay */
        res = handle->wr_gpio_write(1);                                           /* set high */
        if (res != 0)                                                             /* check the result */
        {
            handle->debug_print("tm1621x: wr gpio write failed.\n");              /* wr gpio write failed */
            
            return 1;                                                             /* return error */
        }
        handle->delay_us(TM1621X_COMMAND_DATA_DELAY);                             /* delay */
    }
    
    return 0;                                                                     /* success return 0 */
}

/**
 * @brief      read bits
 * @param[in]  *handle pointer to a tm1621x handle structure
 * @param[out] *data pointer to an output data buffer
 * @param[in]  len data length
 * @return     status code
 *             - 0 success
 *             - 1 read failed
 * @note       none
 */
static uint8_t a_tm1621x_read_bits(tm1621x_handle_t *handle, uint32_t *data, uint8_t len)
{
    uint8_t res;
    uint8_t level;
    uint8_t i;
    
    *data = 0;
    for (i = 0; i < len; i++)                                               /* read bits */
    {
        res = handle->rd_gpio_write(0);                                     /* set low */
        if (res != 0)                                                       /* check the result */
        {
            handle->debug_print("tm1621x: rd gpio write failed.\n");        /* rd gpio write failed */
            
            return 1;                                                       /* return error */
        }
        handle->delay_us(TM1621X_COMMAND_DATA_DELAY);                       /* delay */
        res = handle->data_gpio_read(&level);                               /* read level */
        if (res != 0)                                                       /* check the result */
        {
            handle->debug_print("tm1621x: data gpio read failed.\n");       /* data gpio read failed */
            
            return 1;                                                       /* return error */
        }
        *data <<= 1;                                                        /* left shift */
        *data |= level;                                                     /* set bit */
        handle->delay_us(TM1621X_COMMAND_DATA_DELAY);                       /* delay */
        res = handle->rd_gpio_write(1);                                     /* set high */
        if (res != 0)                                                       /* check the result */
        {
            handle->debug_print("tm1621x: rd gpio write failed.\n");        /* rd gpio write failed */
            
            return 1;                                                       /* return error */
        }
        handle->delay_us(TM1621X_COMMAND_DATA_DELAY);                       /* delay */
    }
    
    return 0;                                                               /* success return 0 */
}

/**
 * @brief     write command
 * @param[in] *handle pointer to a tm1621x handle structure
 * @param[in] cmd command
 * @return    status code
 *            - 0 success
 *            - 1 write failed
 * @note      none
 */
static uint8_t a_tm1621x_write_command(tm1621x_handle_t *handle, uint16_t cmd)
{
    uint8_t res;
    
    res = handle->cs_gpio_write(0);                                     /* set low */
    if (res != 0)                                                       /* check the result */
    {
        handle->debug_print("tm1621x: cs gpio write failed.\n");        /* cs gpio write failed */
        
        return 1;                                                       /* return error */
    }
    handle->delay_us(TM1621X_COMMAND_DATA_DELAY);                       /* delay */
    res = a_tm1621x_write_bits(handle, (uint32_t)(0x04), 3);            /* write bits */
    if (res != 0)                                                       /* check the result */
    {
        return 1;                                                       /* return error */
    }
    res = a_tm1621x_write_bits(handle, (uint32_t)(cmd << 1), 9);        /* write bits */
    if (res != 0)                                                       /* check the result */
    {
        return 1;                                                       /* return error */
    }
    res = handle->cs_gpio_write(1);                                     /* set high */
    if (res != 0)                                                       /* check the result */
    {
        handle->debug_print("tm1621x: cs gpio write failed.\n");        /* cs gpio write failed */
        
        return 1;                                                       /* return error */
    }
    
    return 0;                                                           /* success return 0 */
}

/**
 * @brief     write ram
 * @param[in] *handle pointer to a tm1621x handle structure
 * @param[in] addr address
 * @param[in] *data pointer to an input data buffer
 * @param[in] len input data length
 * @return    status code
 *            - 0 success
 *            - 1 write failed
 * @note      none
 */
static uint8_t a_tm1621x_write_ram(tm1621x_handle_t *handle, uint8_t addr, uint8_t *data, uint8_t len)
{
    uint8_t res;
    uint8_t i;
    
    res = handle->cs_gpio_write(0);                                               /* set low */
    if (res != 0)                                                                 /* check the result */
    {
        handle->debug_print("tm1621x: cs gpio write failed.\n");                  /* cs gpio write failed */
        
        return 1;                                                                 /* return error */
    }
    handle->delay_us(TM1621X_COMMAND_DATA_DELAY);                                 /* delay */
    res = a_tm1621x_write_bits(handle, (uint32_t)(0x05), 3);                      /* write bits */
    if (res != 0)                                                                 /* check the result */
    {
        return 1;                                                                 /* return error */
    }
    res = a_tm1621x_write_bits(handle, (uint32_t)(addr & 0x3F), 6);               /* write bits */
    if (res != 0)                                                                 /* check the result */
    {
        return 1;                                                                 /* return error */
    }
    
    for (i = 0; i < len; i++)                                                     /* loop */
    {
        if (data[i] > 0x0F)                                                       /* check data valid */
        {
            handle->debug_print("tm1621x: data > 0xF.\n");                        /* data > 0xF */
            
            return 1;                                                             /* return error */
        }
        res = a_tm1621x_write_bits(handle, (uint32_t)(data[i] & 0x0F), 4);        /* write bits */
        if (res != 0)                                                             /* check the result */
        {
            return 1;                                                             /* return error */
        }
    }
    res = handle->cs_gpio_write(1);                                               /* set high */
    if (res != 0)                                                                 /* check the result */
    {
        handle->debug_print("tm1621x: cs gpio write failed.\n");                  /* cs gpio write failed */
        
        return 1;                                                                 /* return error */
    }
    
    return 0;                                                                     /* success return 0 */
}

/**
 * @brief      read ram
 * @param[in]  *handle pointer to a tm1621x handle structure
 * @param[in]  addr address
 * @param[out] *data pointer to an output data buffer
 * @param[in]  len output data length
 * @return     status code
 *             - 0 success
 *             - 1 read failed
 * @note       none
 */
static uint8_t a_tm1621x_read_ram(tm1621x_handle_t *handle, uint8_t addr, uint8_t *data, uint8_t len)
{
    uint8_t res;
    uint8_t i;
    
    res = handle->cs_gpio_write(0);                                               /* set low */
    if (res != 0)                                                                 /* check the result */
    {
        handle->debug_print("tm1621x: cs gpio write failed.\n");                  /* cs gpio write failed */
        
        return 1;                                                                 /* return error */
    }
    handle->delay_us(TM1621X_COMMAND_DATA_DELAY);                                 /* delay */
    res = a_tm1621x_write_bits(handle, (uint32_t)(0x06), 3);                      /* write bits */
    if (res != 0)                                                                 /* check the result */
    {
        return 1;                                                                 /* return error */
    }
    res = a_tm1621x_write_bits(handle, (uint32_t)(addr & 0x3F), 6);               /* write bits */
    if (res != 0)                                                                 /* check the result */
    {
        return 1;                                                                 /* return error */
    }
    
    for (i = 0; i < len; i++)                                                     /* loop */
    {
        uint32_t output = 0;
        
        res = a_tm1621x_read_bits(handle, &output, 4);                            /* read bits */
        if (res != 0)                                                             /* check the result */
        {
            return 1;                                                             /* return error */
        }
        data[i] = (uint8_t)(output & 0xF);                                        /* set data */
    }
    res = handle->cs_gpio_write(1);                                               /* set high */
    if (res != 0)                                                                 /* check the result */
    {
        handle->debug_print("tm1621x: cs gpio write failed.\n");                  /* cs gpio write failed */
        
        return 1;                                                                 /* return error */
    }
    
    return 0;                                                                     /* success return 0 */
}

/**
 * @brief     read modify write
 * @param[in] *handle pointer to a tm1621x handle structure
 * @param[in] addr address
 * @param[in] *and_or pointer to an and_or function address
 * @param[in] len data length
 * @return    status code
 *            - 0 success
 *            - 1 read modify write failed
 * @note      none
 */
static uint8_t a_tm1621x_read_modify_write(tm1621x_handle_t *handle, uint8_t addr, 
                                           void (*and_or)(uint8_t addr, uint8_t input, uint8_t *output), uint8_t len)
{
    uint8_t res;
    uint8_t i;
    uint32_t data;
    
    res = handle->cs_gpio_write(0);                                               /* set low */
    if (res != 0)                                                                 /* check the result */
    {
        handle->debug_print("tm1621x: cs gpio write failed.\n");                  /* cs gpio write failed */
        
        return 1;                                                                 /* return error */
    }
    handle->delay_us(TM1621X_COMMAND_DATA_DELAY);                                 /* delay */
    res = a_tm1621x_write_bits(handle, (uint32_t)(0x05), 3);                      /* write bits */
    if (res != 0)                                                                 /* check the result */
    {
        return 1;                                                                 /* return error */
    }
    res = a_tm1621x_write_bits(handle, (uint32_t)(addr & 0x3F), 6);               /* write bits */
    if (res != 0)                                                                 /* check the result */
    {
        return 1;                                                                 /* return error */
    }
    
    for (i = 0; i < len; i++)                                                     /* loop */
    {
        uint8_t input;
        uint8_t output = 0;
        
        res = a_tm1621x_read_bits(handle, &data, 4);                              /* read bits */
        if (res != 0)                                                             /* check the result */
        {
            return 1;                                                             /* return error */
        }
        input = (uint8_t)(data & 0xF);                                            /* set input */
        if (and_or != NULL)                                                       /* not null */
        {
            and_or((addr & 0x3F) + i, input, &output);                            /* run and or function */
        }
        res = a_tm1621x_write_bits(handle, (uint32_t)(output & 0x0F), 4);         /* write bits */
        if (res != 0)                                                             /* check the result */
        {
            return 1;                                                             /* return error */
        }
    }
    res = handle->cs_gpio_write(1);                                               /* set high */
    if (res != 0)                                                                 /* check the result */
    {
        handle->debug_print("tm1621x: cs gpio write failed.\n");                  /* cs gpio write failed */
        
        return 1;                                                                 /* return error */
    }
    
    return 0;                                                                     /* success return 0 */
}

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
uint8_t tm1621x_set_oscillator(tm1621x_handle_t *handle, tm1621x_bool_t enable)
{
    uint8_t res;
    
    if (handle == NULL)                                                       /* check handle */
    {
        return 2;                                                             /* return error */
    }
    if (handle->inited != 1)                                                  /* check handle initialization */
    {
        return 3;                                                             /* return error */
    }
    
    if (enable != TM1621X_BOOL_TRUE)                                          /* disable */
    {
        res = a_tm1621x_write_command(handle, TM1621X_COMMAND_SYS_DIS);       /* write command */
        if (res != 0)                                                         /* check error */
        {
            return 1;                                                         /* return error */
        }
        
        return 0;                                                             /* success return 0 */
    }
    else                                                                      /* enable */
    {
        res = a_tm1621x_write_command(handle, TM1621X_COMMAND_SYS_EN);        /* write command */
        if (res != 0)                                                         /* check error */
        {
            return 1;                                                         /* return error */
        }
        
        return 0;                                                             /* success return 0 */
    }
}

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
uint8_t tm1621x_set_lcd_bias(tm1621x_handle_t *handle, tm1621x_bool_t enable)
{
    uint8_t res;
    
    if (handle == NULL)                                                       /* check handle */
    {
        return 2;                                                             /* return error */
    }
    if (handle->inited != 1)                                                  /* check handle initialization */
    {
        return 3;                                                             /* return error */
    }
    
    if (enable != TM1621X_BOOL_TRUE)                                          /* disable */
    {
        res = a_tm1621x_write_command(handle, TM1621X_COMMAND_LCD_OFF);       /* write command */
        if (res != 0)                                                         /* check error */
        {
            return 1;                                                         /* return error */
        }
        
        return 0;                                                             /* success return 0 */
    }
    else                                                                      /* enable */
    {
        res = a_tm1621x_write_command(handle, TM1621X_COMMAND_LCD_ON);        /* write command */
        if (res != 0)                                                         /* check error */
        {
            return 1;                                                         /* return error */
        }
        
        return 0;                                                             /* success return 0 */
    }
}

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
uint8_t tm1621x_set_timer(tm1621x_handle_t *handle, tm1621x_bool_t enable)
{
    uint8_t res;
    
    if (handle == NULL)                                                          /* check handle */
    {
        return 2;                                                                /* return error */
    }
    if (handle->inited != 1)                                                     /* check handle initialization */
    {
        return 3;                                                                /* return error */
    }
    if (handle->type != (uint8_t)TM1621X_TYPE_B)                                 /* check type */
    {
        handle->debug_print("tm1621x: only typeb support this function.\n");     /* only typeb support this function */
        
        return 4;                                                                /* return error */
    }
    
    if (enable != TM1621X_BOOL_TRUE)                                             /* disable */
    {
        res = a_tm1621x_write_command(handle, TM1621X_COMMAND_TIMER_DIS);        /* write command */
        if (res != 0)                                                            /* check error */
        {
            return 1;                                                            /* return error */
        }
        
        return 0;                                                                /* success return 0 */
    }
    else                                                                         /* enable */
    {
        res = a_tm1621x_write_command(handle, TM1621X_COMMAND_TIMER_EN);         /* write command */
        if (res != 0)                                                            /* check error */
        {
            return 1;                                                            /* return error */
        }
        
        return 0;                                                                /* success return 0 */
    }
}

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
uint8_t tm1621x_set_watchdog(tm1621x_handle_t *handle, tm1621x_bool_t enable)
{
    uint8_t res;
    
    if (handle == NULL)                                                          /* check handle */
    {
        return 2;                                                                /* return error */
    }
    if (handle->inited != 1)                                                     /* check handle initialization */
    {
        return 3;                                                                /* return error */
    }
    if (handle->type != (uint8_t)TM1621X_TYPE_B)                                 /* check type */
    {
        handle->debug_print("tm1621x: only typeb support this function.\n");     /* only typeb support this function */
        
        return 4;                                                                /* return error */
    }
    
    if (enable != TM1621X_BOOL_TRUE)                                             /* disable */
    {
        res = a_tm1621x_write_command(handle, TM1621X_COMMAND_WDT_DIS);          /* write command */
        if (res != 0)                                                            /* check error */
        {
            return 1;                                                            /* return error */
        }
        
        return 0;                                                                /* success return 0 */
    }
    else                                                                         /* enable */
    {
        res = a_tm1621x_write_command(handle, TM1621X_COMMAND_WDT_EN);           /* write command */
        if (res != 0)                                                            /* check error */
        {
            return 1;                                                            /* return error */
        }
        
        return 0;                                                                /* success return 0 */
    }
}

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
uint8_t tm1621x_set_tone(tm1621x_handle_t *handle, tm1621x_bool_t enable)
{
    uint8_t res;
    
    if (handle == NULL)                                                          /* check handle */
    {
        return 2;                                                                /* return error */
    }
    if (handle->inited != 1)                                                     /* check handle initialization */
    {
        return 3;                                                                /* return error */
    }
    if (handle->type != (uint8_t)TM1621X_TYPE_B)                                 /* check type */
    {
        handle->debug_print("tm1621x: only typeb support this function.\n");     /* only typeb support this function */
        
        return 4;                                                                /* return error */
    }
    
    if (enable != TM1621X_BOOL_TRUE)                                             /* disable */
    {
        res = a_tm1621x_write_command(handle, TM1621X_COMMAND_TONE_OFF);         /* write command */
        if (res != 0)                                                            /* check error */
        {
            return 1;                                                            /* return error */
        }
        
        return 0;                                                                /* success return 0 */
    }
    else                                                                         /* enable */
    {
        res = a_tm1621x_write_command(handle, TM1621X_COMMAND_TONE_ON);          /* write command */
        if (res != 0)                                                            /* check error */
        {
            return 1;                                                            /* return error */
        }
        
        return 0;                                                                /* success return 0 */
    }
}

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
uint8_t tm1621x_set_irq(tm1621x_handle_t *handle, tm1621x_bool_t enable)
{
    uint8_t res;
    
    if (handle == NULL)                                                          /* check handle */
    {
        return 2;                                                                /* return error */
    }
    if (handle->inited != 1)                                                     /* check handle initialization */
    {
        return 3;                                                                /* return error */
    }
    if (handle->type != (uint8_t)TM1621X_TYPE_B)                                 /* check type */
    {
        handle->debug_print("tm1621x: only typeb support this function.\n");     /* only typeb support this function */
        
        return 4;                                                                /* return error */
    }
    
    if (enable != TM1621X_BOOL_TRUE)                                             /* disable */
    {
        res = a_tm1621x_write_command(handle, TM1621X_COMMAND_IRQ_DIS);          /* write command */
        if (res != 0)                                                            /* check error */
        {
            return 1;                                                            /* return error */
        }
        
        return 0;                                                                /* success return 0 */
    }
    else                                                                         /* enable */
    {
        res = a_tm1621x_write_command(handle, TM1621X_COMMAND_IRQ_EN);           /* write command */
        if (res != 0)                                                            /* check error */
        {
            return 1;                                                            /* return error */
        }
        
        return 0;                                                                /* success return 0 */
    }
}

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
uint8_t tm1621x_clear_timer(tm1621x_handle_t *handle)
{
    uint8_t res;
    
    if (handle == NULL)                                                          /* check handle */
    {
        return 2;                                                                /* return error */
    }
    if (handle->inited != 1)                                                     /* check handle initialization */
    {
        return 3;                                                                /* return error */
    }
    if (handle->type != (uint8_t)TM1621X_TYPE_B)                                 /* check type */
    {
        handle->debug_print("tm1621x: only typeb support this function.\n");     /* only typeb support this function */
        
        return 4;                                                                /* return error */
    }
    
    res = a_tm1621x_write_command(handle, TM1621X_COMMAND_CLR_TIMER);            /* write command */
    if (res != 0)                                                                /* check error */
    {
        return 1;                                                                /* return error */
    }
    
    return 0;                                                                    /* success return 0 */
}

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
uint8_t tm1621x_clear_watchdog(tm1621x_handle_t *handle)
{
    uint8_t res;
    
    if (handle == NULL)                                                          /* check handle */
    {
        return 2;                                                                /* return error */
    }
    if (handle->inited != 1)                                                     /* check handle initialization */
    {
        return 3;                                                                /* return error */
    }
    if (handle->type != (uint8_t)TM1621X_TYPE_B)                                 /* check type */
    {
        handle->debug_print("tm1621x: only typeb support this function.\n");     /* only typeb support this function */
        
        return 4;                                                                /* return error */
    }
    
    res = a_tm1621x_write_command(handle, TM1621X_COMMAND_CLR_WDT);              /* write command */
    if (res != 0)                                                                /* check error */
    {
        return 1;                                                                /* return error */
    }
    
    return 0;                                                                    /* success return 0 */
}

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
uint8_t tm1621x_set_mode(tm1621x_handle_t *handle, tm1621x_mode_t mode)
{
    uint8_t res;
    
    if (handle == NULL)                                                        /* check handle */
    {
        return 2;                                                              /* return error */
    }
    if (handle->inited != 1)                                                   /* check handle initialization */
    {
        return 3;                                                              /* return error */
    }
    
    if (mode != TM1621X_MODE_NORMAL)                                           /* test mode */
    {
        res = a_tm1621x_write_command(handle, TM1621X_COMMAND_TOPT);           /* write command */
        if (res != 0)                                                          /* check error */
        {
            return 1;                                                          /* return error */
        }
        
        return 0;                                                              /* success return 0 */
    }
    else                                                                       /* normal mode */
    {
        res = a_tm1621x_write_command(handle, TM1621X_COMMAND_TNORMAL);        /* write command */
        if (res != 0)                                                          /* check error */
        {
            return 1;                                                          /* return error */
        }
        
        return 0;                                                              /* success return 0 */
    }
}

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
uint8_t tm1621x_set_clock(tm1621x_handle_t *handle, tm1621x_clock_t clk)
{
    uint8_t res;
    
    if (handle == NULL)                                                         /* check handle */
    {
        return 2;                                                               /* return error */
    }
    if (handle->inited != 1)                                                    /* check handle initialization */
    {
        return 3;                                                               /* return error */
    }
    
    if (clk == TM1621X_CLOCK_XTAL_32K)                                          /* xtal 32k */
    {
        res = a_tm1621x_write_command(handle, TM1621X_COMMAND_XTAL_32K);        /* write command */
        if (res != 0)                                                           /* check error */
        {
            return 1;                                                           /* return error */
        }
        
        return 0;                                                               /* success return 0 */
    }
    else if (clk == TM1621X_CLOCK_RC_256K)                                      /* rc 256k */
    {
        res = a_tm1621x_write_command(handle, TM1621X_COMMAND_RC_256K);         /* write command */
        if (res != 0)                                                           /* check error */
        {
            return 1;                                                           /* return error */
        }
        
        return 0;                                                               /* success return 0 */
    }
    else                                                                        /* ext 256k */
    {
        res = a_tm1621x_write_command(handle, TM1621X_COMMAND_EXT_256K);        /* write command */
        if (res != 0)                                                           /* check error */
        {
            return 1;                                                           /* return error */
        }
        
        return 0;                                                               /* success return 0 */
    }
}

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
uint8_t tm1621x_set_freq(tm1621x_handle_t *handle, tm1621x_freq_t freq)
{
    uint8_t res;
    
    if (handle == NULL)                                                          /* check handle */
    {
        return 2;                                                                /* return error */
    }
    if (handle->inited != 1)                                                     /* check handle initialization */
    {
        return 3;                                                                /* return error */
    }
    if (handle->type != (uint8_t)TM1621X_TYPE_B)                                 /* check type */
    {
        handle->debug_print("tm1621x: only typeb support this function.\n");     /* only typeb support this function */
        
        return 4;                                                                /* return error */
    }
    
    if (freq == TM1621X_FREQ_F1)                                                 /* f1 */
    {
        res = a_tm1621x_write_command(handle, TM1621X_COMMAND_F1);               /* write command */
        if (res != 0)                                                            /* check error */
        {
            return 1;                                                            /* return error */
        }
        
        return 0;                                                                /* success return 0 */
    }
    else if (freq == TM1621X_FREQ_F2)                                            /* f2 */
    {
        res = a_tm1621x_write_command(handle, TM1621X_COMMAND_F2);               /* write command */
        if (res != 0)                                                            /* check error */
        {
            return 1;                                                            /* return error */
        }
        
        return 0;                                                                /* success return 0 */
    }
    else if (freq == TM1621X_FREQ_F4)                                            /* f4 */
    {
        res = a_tm1621x_write_command(handle, TM1621X_COMMAND_F4);               /* write command */
        if (res != 0)                                                            /* check error */
        {
            return 1;                                                            /* return error */
        }
        
        return 0;                                                                /* success return 0 */
    }
    else if (freq == TM1621X_FREQ_F8)                                            /* f8 */
    {
        res = a_tm1621x_write_command(handle, TM1621X_COMMAND_F8);               /* write command */
        if (res != 0)                                                            /* check error */
        {
            return 1;                                                            /* return error */
        }
        
        return 0;                                                                /* success return 0 */
    }
    else if (freq == TM1621X_FREQ_F16)                                           /* f16 */
    {
        res = a_tm1621x_write_command(handle, TM1621X_COMMAND_F16);              /* write command */
        if (res != 0)                                                            /* check error */
        {
            return 1;                                                            /* return error */
        }
        
        return 0;                                                                /* success return 0 */
    }
    else if (freq == TM1621X_FREQ_F32)                                           /* f32 */
    {
        res = a_tm1621x_write_command(handle, TM1621X_COMMAND_F32);              /* write command */
        if (res != 0)                                                            /* check error */
        {
            return 1;                                                            /* return error */
        }
        
        return 0;                                                                /* success return 0 */
    }
    else if (freq == TM1621X_FREQ_F64)                                           /* f64 */
    {
        res = a_tm1621x_write_command(handle, TM1621X_COMMAND_F64);              /* write command */
        if (res != 0)                                                            /* check error */
        {
            return 1;                                                            /* return error */
        }
        
        return 0;                                                                /* success return 0 */
    }
    else                                                                         /* f128 */
    {
        res = a_tm1621x_write_command(handle, TM1621X_COMMAND_F128);             /* write command */
        if (res != 0)                                                            /* check error */
        {
            return 1;                                                            /* return error */
        }
        
        return 0;                                                                /* success return 0 */
    }
}

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
uint8_t tm1621x_set_tone_freq(tm1621x_handle_t *handle, tm1621x_tone_freq_t freq)
{
    uint8_t res;
    
    if (handle == NULL)                                                          /* check handle */
    {
        return 2;                                                                /* return error */
    }
    if (handle->inited != 1)                                                     /* check handle initialization */
    {
        return 3;                                                                /* return error */
    }
    if (handle->type != (uint8_t)TM1621X_TYPE_B)                                 /* check type */
    {
        handle->debug_print("tm1621x: only typeb support this function.\n");     /* only typeb support this function */
        
        return 4;                                                                /* return error */
    }
    
    if (freq != TM1621X_TONE_FREQ_4K)                                            /* 2k */
    {
        res = a_tm1621x_write_command(handle, TM1621X_COMMAND_TONE_2K);          /* write command */
        if (res != 0)                                                            /* check error */
        {
            return 1;                                                            /* return error */
        }
        
        return 0;                                                                /* success return 0 */
    }
    else                                                                         /* 4k */
    {
        res = a_tm1621x_write_command(handle, TM1621X_COMMAND_TONE_4K);          /* write command */
        if (res != 0)                                                            /* check error */
        {
            return 1;                                                            /* return error */
        }
        
        return 0;                                                                /* success return 0 */
    }
}

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
uint8_t tm1621x_set_bias_1div2(tm1621x_handle_t *handle, tm1621x_bias_t bias)
{
    uint8_t res;
    
    if (handle == NULL)                                                                     /* check handle */
    {
        return 2;                                                                           /* return error */
    }
    if (handle->inited != 1)                                                                /* check handle initialization */
    {
        return 3;                                                                           /* return error */
    }
    
    res = a_tm1621x_write_command(handle, TM1621X_COMMAND_BIAS_1DIV2 | (bias << 2));        /* write command */
    if (res != 0)                                                                           /* check error */
    {
        return 1;                                                                           /* return error */
    }
    
    return 0;                                                                               /* success return 0 */
}

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
uint8_t tm1621x_set_bias_1div3(tm1621x_handle_t *handle, tm1621x_bias_t bias)
{
    uint8_t res;
    
    if (handle == NULL)                                                                     /* check handle */
    {
        return 2;                                                                           /* return error */
    }
    if (handle->inited != 1)                                                                /* check handle initialization */
    {
        return 3;                                                                           /* return error */
    }
    
    res = a_tm1621x_write_command(handle, TM1621X_COMMAND_BIAS_1DIV3 | (bias << 2));        /* write command */
    if (res != 0)                                                                           /* check error */
    {
        return 1;                                                                           /* return error */
    }
    
    return 0;                                                                               /* success return 0 */
}

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
uint8_t tm1621x_init(tm1621x_handle_t *handle)
{
    uint8_t res;
    
    if (handle == NULL)                                                    /* check handle */
    {
        return 2;                                                          /* return error */
    }
    if (handle->debug_print == NULL)                                       /* check debug_print */
    {
        return 3;                                                          /* return error */
    }
    if (handle->data_gpio_init == NULL)                                    /* check data_gpio_init */
    {
        handle->debug_print("tm1621x: data_gpio_init is null.\n");         /* data_gpio_init is null */
        
        return 3;                                                          /* return error */
    }
    if (handle->data_gpio_deinit == NULL)                                  /* check data_gpio_deinit */
    {
        handle->debug_print("tm1621x: data_gpio_deinit is null.\n");       /* data_gpio_deinit is null */
        
        return 3;                                                          /* return error */
    }
    if (handle->data_gpio_write == NULL)                                   /* check data_gpio_write */
    {
        handle->debug_print("tm1621x: data_gpio_write is null.\n");        /* data_gpio_write is null */
        
        return 3;                                                          /* return error */
    }
    if (handle->data_gpio_read == NULL)                                    /* check data_gpio_read */
    {
        handle->debug_print("tm1621x: data_gpio_read is null.\n");         /* data_gpio_read is null */
        
        return 3;                                                          /* return error */
    }
    if (handle->wr_gpio_init == NULL)                                      /* check wr_gpio_init */
    {
        handle->debug_print("tm1621x: wr_gpio_init is null.\n");           /* wr_gpio_init is null */
        
        return 3;                                                          /* return error */
    }
    if (handle->wr_gpio_deinit == NULL)                                    /* check wr_gpio_deinit */
    {
        handle->debug_print("tm1621x: wr_gpio_deinit is null.\n");         /* wr_gpio_deinit is null */
        
        return 3;                                                          /* return error */
    }
    if (handle->wr_gpio_write == NULL)                                     /* check wr_gpio_write */
    {
        handle->debug_print("tm1621x: wr_gpio_write is null.\n");          /* wr_gpio_write is null */
        
        return 3;                                                          /* return error */
    }
    if (handle->rd_gpio_init == NULL)                                      /* check rd_gpio_init */
    {
        handle->debug_print("tm1621x: rd_gpio_init is null.\n");           /* rd_gpio_init is null */
        
        return 3;                                                          /* return error */
    }
    if (handle->rd_gpio_deinit == NULL)                                    /* check rd_gpio_deinit */
    {
        handle->debug_print("tm1621x: rd_gpio_deinit is null.\n");         /* rd_gpio_deinit is null */
        
        return 3;                                                          /* return error */
    }
    if (handle->rd_gpio_write == NULL)                                     /* check rd_gpio_write */
    {
        handle->debug_print("tm1621x: rd_gpio_write is null.\n");          /* rd_gpio_write is null */
        
        return 3;                                                          /* return error */
    }
    if (handle->cs_gpio_init == NULL)                                      /* check cs_gpio_init */
    {
        handle->debug_print("tm1621x: cs_gpio_init is null.\n");           /* cs_gpio_init is null */
        
        return 3;                                                          /* return error */
    }
    if (handle->cs_gpio_deinit == NULL)                                    /* check cs_gpio_deinit */
    {
        handle->debug_print("tm1621x: cs_gpio_deinit is null.\n");         /* cs_gpio_deinit is null */
        
        return 3;                                                          /* return error */
    }
    if (handle->cs_gpio_write == NULL)                                     /* check cs_gpio_write */
    {
        handle->debug_print("tm1621x: cs_gpio_write is null.\n");          /* cs_gpio_write is null */
        
        return 3;                                                          /* return error */
    }
    if (handle->delay_us == NULL)                                          /* check delay_us */
    {
        handle->debug_print("tm1621x: delay_us is null.\n");               /* delay_us is null */
        
        return 3;                                                          /* return error */
    }
    if (handle->delay_ms == NULL)                                          /* check delay_ms */
    {
        handle->debug_print("tm1621x: delay_ms is null.\n");               /* delay_ms is null */
        
        return 3;                                                          /* return error */
    }
    
    res = handle->data_gpio_init();                                        /* data gpio init */
    if (res != 0)                                                          /* check result */
    {
        handle->debug_print("tm1621x: data gpio init failed.\n");          /* data gpio init failed */
        
        return 1;                                                          /* return error */
    }
    res = handle->wr_gpio_init();                                          /* wr gpio init */
    if (res != 0)                                                          /* check result */
    {
        handle->debug_print("tm1621x: wr gpio init failed.\n");            /* wr gpio init failed */
        (void)handle->data_gpio_deinit();                                  /* data gpio deinit */
        
        return 1;                                                          /* return error */
    }
    res = handle->rd_gpio_init();                                          /* rd gpio init */
    if (res != 0)                                                          /* check result */
    {
        handle->debug_print("tm1621x: rd gpio init failed.\n");            /* rd gpio init failed */
        (void)handle->data_gpio_deinit();                                  /* data gpio deinit */
        (void)handle->wr_gpio_deinit();                                    /* wr gpio deinit */
        
        return 1;                                                          /* return error */
    }
    res = handle->cs_gpio_init();                                          /* cs gpio init */
    if (res != 0)                                                          /* check result */
    {
        handle->debug_print("tm1621x: cs gpio init failed.\n");            /* cs gpio init failed */
        (void)handle->data_gpio_deinit();                                  /* data gpio deinit */
        (void)handle->wr_gpio_deinit();                                    /* wr gpio deinit */
        (void)handle->rd_gpio_deinit();                                    /* rd gpio deinit */
        
        return 1;                                                          /* return error */
    }
    res = handle->cs_gpio_write(1);                                        /* set high */
    if (res != 0)                                                          /* check result */
    {
        handle->debug_print("tm1621x: cs gpio write failed.\n");           /* cs gpio write failed */
        (void)handle->data_gpio_deinit();                                  /* data gpio deinit */
        (void)handle->wr_gpio_deinit();                                    /* wr gpio deinit */
        (void)handle->rd_gpio_deinit();                                    /* rd gpio deinit */
        (void)handle->cs_gpio_deinit();                                    /* cs gpio deinit */
        
        return 1;                                                          /* return error */
    }
    res = handle->wr_gpio_write(1);                                        /* set high */
    if (res != 0)                                                          /* check result */
    {
        handle->debug_print("tm1621x: wr gpio write failed.\n");           /* wr gpio write failed */
        (void)handle->data_gpio_deinit();                                  /* data gpio deinit */
        (void)handle->wr_gpio_deinit();                                    /* wr gpio deinit */
        (void)handle->rd_gpio_deinit();                                    /* rd gpio deinit */
        (void)handle->cs_gpio_deinit();                                    /* cs gpio deinit */
        
        return 1;                                                          /* return error */
    }
    res = handle->rd_gpio_write(1);                                        /* set high */
    if (res != 0)                                                          /* check result */
    {
        handle->debug_print("tm1621x: rd gpio write failed.\n");           /* rd gpio write failed */
        (void)handle->data_gpio_deinit();                                  /* data gpio deinit */
        (void)handle->wr_gpio_deinit();                                    /* wr gpio deinit */
        (void)handle->rd_gpio_deinit();                                    /* rd gpio deinit */
        (void)handle->cs_gpio_deinit();                                    /* cs gpio deinit */
        
        return 1;                                                          /* return error */
    }
    res = handle->data_gpio_write(1);                                      /* set high */
    if (res != 0)                                                          /* check result */
    {
        handle->debug_print("tm1621x: data gpio write failed.\n");         /* data gpio write failed */
        (void)handle->data_gpio_deinit();                                  /* data gpio deinit */
        (void)handle->wr_gpio_deinit();                                    /* wr gpio deinit */
        (void)handle->rd_gpio_deinit();                                    /* rd gpio deinit */
        (void)handle->cs_gpio_deinit();                                    /* cs gpio deinit */
        
        return 1;                                                          /* return error */
    }
    handle->inited = 1;                                                    /* flag inited */
    
    return 0;                                                              /* success return 0 */
}

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
uint8_t tm1621x_deinit(tm1621x_handle_t *handle)
{
    uint8_t res;
    
    if (handle == NULL)                                                   /* check handle */
    {
        return 2;                                                         /* return error */
    }
    if (handle->inited != 1)                                              /* check handle initialization */
    {
        return 3;                                                         /* return error */
    }
    
    res = a_tm1621x_write_command(handle, TM1621X_COMMAND_SYS_DIS);       /* write command */
    if (res != 0)                                                         /* check error */
    {
        return 4;                                                         /* return error */
    }
    
    res = handle->data_gpio_deinit();                                     /* data gpio deinit */
    if (res != 0)                                                         /* check the result */
    {
        handle->debug_print("tm1621x: data gpio deinit failed.\n");       /* data gpio deinit failed */
        
        return 1;                                                         /* return error */
    }
    res = handle->wr_gpio_deinit();                                       /* wr gpio deinit */
    if (res != 0)                                                         /* check the result */
    {
        handle->debug_print("tm1621x: wr gpio deinit failed.\n");         /* wr gpio deinit failed */
        
        return 1;                                                         /* return error */
    }
    res = handle->rd_gpio_deinit();                                       /* rd gpio deinit */
    if (res != 0)                                                         /* check the result */
    {
        handle->debug_print("tm1621x: rd gpio deinit failed.\n");         /* rd gpio deinit failed */
        
        return 1;                                                         /* return error */
    }
    res = handle->cs_gpio_deinit();                                       /* cs gpio deinit */
    if (res != 0)                                                         /* check the result */
    {
        handle->debug_print("tm1621x: cs gpio deinit failed.\n");         /* cs gpio deinit failed */
        
        return 1;                                                         /* return error */
    }
    handle->inited = 0;                                                   /* flag close */
    
    return 0;                                                             /* success return 0 */
}

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
uint8_t tm1621x_write_segment(tm1621x_handle_t *handle, uint8_t addr, uint8_t *data, uint8_t len)
{
    uint8_t res;
    
    if (handle == NULL)                                            /* check handle */
    {
        return 2;                                                  /* return error */
    }
    if (handle->inited != 1)                                       /* check handle initialization */
    {
        return 3;                                                  /* return error */
    }
    if (addr + len > 32)                                           /* check range */
    {
        handle->debug_print("tm1621x: addr + len > 32.\n");        /* addr + len > 32 */
        
        return 4;                                                  /* return error */
    }
    
    res = a_tm1621x_write_ram(handle, addr, data, len);            /* write ram */
    if (res != 0)                                                  /* check error */
    {
        return 1;                                                  /* return error */
    }
    
    return 0;                                                      /* success return 0 */
}

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
uint8_t tm1621x_clear_segment(tm1621x_handle_t *handle)
{
    uint8_t res;
    uint8_t buf[32];
    
    if (handle == NULL)                                   /* check handle */
    {
        return 2;                                         /* return error */
    }
    if (handle->inited != 1)                              /* check handle initialization */
    {
        return 3;                                         /* return error */
    }
    
    memset(buf, 0, sizeof(uint8_t) * 32);                 /* clear buffer */
    res = a_tm1621x_write_ram(handle, 0, buf, 32);        /* write ram */
    if (res != 0)                                         /* check error */
    {
        return 1;                                         /* return error */
    }
    
    return 0;                                             /* success return 0 */
}

/**
 * @brief     set type
 * @param[in] *handle pointer to a tm1621x handle structure
 * @param[in] type chip type
 * @return    status code
 *            - 0 success
 *            - 2 handle is NULL
 * @note      none
 */
uint8_t tm1621x_set_type(tm1621x_handle_t *handle, tm1621x_type_t type)
{
    if (handle == NULL)                  /* check handle */
    {
        return 2;                        /* return error */
    }
    
    handle->type = (uint8_t)type;        /* set type */
    
    return 0;                            /* success return 0 */
}

/**
 * @brief      get type
 * @param[in]  *handle pointer to a tm1621x handle structure
 * @param[out] *type pointer to a chip type buffer
 * @return     status code
 *             - 0 success
 *             - 2 handle is NULL
 * @note       none
 */
uint8_t tm1621x_get_type(tm1621x_handle_t *handle, tm1621x_type_t *type)
{
    if (handle == NULL)                          /* check handle */
    {
        return 2;                                /* return error */
    }
    
    *type = (tm1621x_type_t)handle->type;        /* set type */
    
    return 0;                                    /* success return 0 */
}

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
uint8_t tm1621x_set_command(tm1621x_handle_t *handle, uint16_t cmd)
{
    uint8_t res;
    
    if (handle == NULL)                                /* check handle */
    {
        return 2;                                      /* return error */
    }
    if (handle->inited != 1)                           /* check handle initialization */
    {
        return 3;                                      /* return error */
    }
    
    res = a_tm1621x_write_command(handle, cmd);        /* write */
    if (res != 0)                                      /* check error */
    {
        return 1;                                      /* return error */
    }
    
    return 0;                                          /* success return 0 */
}

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
uint8_t tm1621x_set_data(tm1621x_handle_t *handle, uint8_t addr, uint8_t *data, uint8_t len)
{
    uint8_t res;
    
    if (handle == NULL)                                        /* check handle */
    {
        return 2;                                              /* return error */
    }
    if (handle->inited != 1)                                   /* check handle initialization */
    {
        return 3;                                              /* return error */
    }
    
    res = a_tm1621x_write_ram(handle, addr, data, len);        /* write */
    if (res != 0)                                              /* check error */
    {
        return 1;                                              /* return error */
    }
    
    return 0;                                                  /* success return 0 */
}

/**
 * @brief      get data
 * @param[in]  *handle pointer to a tm1621x handle structure
 * @param[in]  addr address
 * @param[out] *data pointer to an output data buffer
 * @param[in]  len output data length
 * @return     status code
 *             - 0 success
 *             - 1 read failed
 *             - 2 handle is NULL
 *             - 3 handle is not initialized
 * @note       none
 */
uint8_t tm1621x_get_data(tm1621x_handle_t *handle, uint8_t addr, uint8_t *data, uint8_t len)
{
    uint8_t res;
    
    if (handle == NULL)                                       /* check handle */
    {
        return 2;                                             /* return error */
    }
    if (handle->inited != 1)                                  /* check handle initialization */
    {
        return 3;                                             /* return error */
    }
    
    res = a_tm1621x_read_ram(handle, addr, data, len);        /* read */
    if (res != 0)                                             /* check error */
    {
        return 1;                                             /* return error */
    }
    
    return 0;                                                 /* success return 0 */
}

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
uint8_t tm1621x_read_modify_write(tm1621x_handle_t *handle, uint8_t addr, void (*and_or)(uint8_t addr, uint8_t input, uint8_t *output), uint8_t len)
{
    uint8_t res;
    
    if (handle == NULL)                                                  /* check handle */
    {
        return 2;                                                        /* return error */
    }
    if (handle->inited != 1)                                             /* check handle initialization */
    {
        return 3;                                                        /* return error */
    }
    
    res = a_tm1621x_read_modify_write(handle, addr, and_or, len);        /* read write */
    if (res != 0)                                                        /* check error */
    {
        return 1;                                                        /* return error */
    }
    
    return 0;                                                            /* success return 0 */
}

/**
 * @brief      get chip's information
 * @param[out] *info pointer to a tm1621x info structure
 * @return     status code
 *             - 0 success
 *             - 2 handle is NULL
 * @note       none
 */
uint8_t tm1621x_info(tm1621x_info_t *info)
{
    if (info == NULL)                                               /* check handle */
    {
        return 2;                                                   /* return error */
    }
    
    memset(info, 0, sizeof(tm1621x_info_t));                        /* initialize tm1621x info structure */
    strncpy(info->chip_name, CHIP_NAME, 32);                        /* copy chip name */
    strncpy(info->manufacturer_name, MANUFACTURER_NAME, 32);        /* copy manufacturer name */
    strncpy(info->interface, "GPIO", 8);                            /* copy interface name */
    info->supply_voltage_min_v = SUPPLY_VOLTAGE_MIN;                /* set minimal supply voltage */
    info->supply_voltage_max_v = SUPPLY_VOLTAGE_MAX;                /* set maximum supply voltage */
    info->max_current_ma = MAX_CURRENT;                             /* set maximum current */
    info->temperature_max = TEMPERATURE_MAX;                        /* set minimal temperature */
    info->temperature_min = TEMPERATURE_MIN;                        /* set maximum temperature */
    info->driver_version = DRIVER_VERSION;                          /* set driver version */
    
    return 0;                                                       /* success return 0 */
}

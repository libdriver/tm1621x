[English](/README.md) | [ 简体中文](/README_zh-Hans.md) | [繁體中文](/README_zh-Hant.md) | [日本語](/README_ja.md) | [Deutsch](/README_de.md) | [한국어](/README_ko.md)

<div align=center>
<img src="/doc/image/logo.svg" width="400" height="150"/>
</div>

## LibDriver TM1621X

[![MISRA](https://img.shields.io/badge/misra-compliant-brightgreen.svg)](/misra/README.md) [![API](https://img.shields.io/badge/api-reference-blue.svg)](https://www.libdriver.com/docs/tm1621x/index.html) [![License](https://img.shields.io/badge/license-MIT-brightgreen.svg)](/LICENSE)

TM1621X is a memory-mapped and multifunctional LCD driver. The software configuration features of TM1621X make it suitable for various LCD applications, including LCD modules and display subsystems. There are only 4 or 5 pins used to connect the main controller to TM1621X, and TM1621X also has a power-saving command to reduce system power consumption.

LibDriver TM1621X is a full-featured driver for TM1621X, launched by LibDriver. It provides LCD display and additional features. LibDriver is MISRA compliant.

### Table of Contents

  - [Instruction](#Instruction)
  - [Install](#Install)
  - [Usage](#Usage)
    - [example basic](#example-basic)
    - [example output](#example-output)
  - [Document](#Document)
  - [Contributing](#Contributing)
  - [License](#License)
  - [Contact Us](#Contact-Us)

### Instruction

/src includes LibDriver TM1621X source files.

/interface includes LibDriver TM1621X GPIO platform independent template.

/test includes LibDriver TM1621X driver test code and this code can test the chip necessary function simply.

/example includes LibDriver TM1621X sample code.

/doc includes LibDriver TM1621X offline document.

/datasheet includes TM1621X datasheet.

/project includes the common Linux and MCU development board sample code. All projects use the shell script to debug the driver and the detail instruction can be found in each project's README.md.

/misra includes the LibDriver MISRA code scanning results.

### Install

Reference /interface GPIO platform independent template and finish your platform GPIO driver.

Add the /src directory, the interface driver for your platform, and your own drivers to your project, if you want to use the default example drivers, add the /example directory to your project.

### Usage

You can refer to the examples in the /example directory to complete your own driver. If you want to use the default programming examples, here's how to use them.

#### example basic

```C
#include "driver_tm1621x_basic.h"

uint8_t res;
uint8_t buffer[32];

/* init */
res = tm1621x_basic_init(TM1621X_TYPE_B);
if (res != 0)
{
    return 1;
}

...
    
/* write data */
res = tm1621x_basic_write(0, buffer, 32);
if (res != 0)
{
    return 1;
}

...
    
/* set tone freq */
res = tm1621x_basic_set_tone_freq(TM1621X_TONE_FREQ_2K);
if (res != 0)
{
    return 1;
}

...
    
/* enable tone */
res = tm1621x_basic_enable_tone();
if (res != 0)
{
    return 1;
}

...
    
/* deinit */
(void)tm1621x_basic_deinit();

return 0;
```

#### example output

```C
#include "driver_tm1621x_output.h"

uint8_t res;

/* init */
res = tm1621x_output_init(TM1621X_TYPE_B);
if (res != 0)
{
    return 1;
}

...
    
/* set div */
res = tm1621x_output_set_freq(TM1621X_FREQ_F1);
if (res != 0)
{
    return 1;
}

...
    
/* set timer */
res = tm1621x_output_set_timer(TM1621X_BOOL_TRUE);
if (res != 0)
{
    return 1;
}

...
    
/* set div */
res = tm1621x_output_set_freq(TM1621X_FREQ_F1);
if (res != 0)
{
    return 1;
}

...
    
/* set watchdog */
res = tm1621x_output_set_watchdog(TM1621X_BOOL_TRUE);
if (res != 0)
{
    return 1;
}

/* deinit */
(void)tm1621x_output_deinit();

return 0;
```

### Document

Online documents: [https://www.libdriver.com/docs/tm1621x/index.html](https://www.libdriver.com/docs/tm1621x/index.html).

Offline documents: /doc/html/index.html.

### Contributing

Please refer to CONTRIBUTING.md.

### License

Copyright (c) 2015 - present LibDriver All rights reserved



The MIT License (MIT) 



Permission is hereby granted, free of charge, to any person obtaining a copy

of this software and associated documentation files (the "Software"), to deal

in the Software without restriction, including without limitation the rights

to use, copy, modify, merge, publish, distribute, sublicense, and/or sell

copies of the Software, and to permit persons to whom the Software is

furnished to do so, subject to the following conditions: 



The above copyright notice and this permission notice shall be included in all

copies or substantial portions of the Software. 



THE SOFTWARE IS PROVIDED "AS IS", WITHOUT WARRANTY OF ANY KIND, EXPRESS OR

IMPLIED, INCLUDING BUT NOT LIMITED TO THE WARRANTIES OF MERCHANTABILITY,

FITNESS FOR A PARTICULAR PURPOSE AND NONINFRINGEMENT. IN NO EVENT SHALL THE

AUTHORS OR COPYRIGHT HOLDERS BE LIABLE FOR ANY CLAIM, DAMAGES OR OTHER

LIABILITY, WHETHER IN AN ACTION OF CONTRACT, TORT OR OTHERWISE, ARISING FROM,

OUT OF OR IN CONNECTION WITH THE SOFTWARE OR THE USE OR OTHER DEALINGS IN THE

SOFTWARE. 

### Contact Us

Please send an e-mail to lishifenging@outlook.com.
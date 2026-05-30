[English](/README.md) | [ 简体中文](/README_zh-Hans.md) | [繁體中文](/README_zh-Hant.md) | [日本語](/README_ja.md) | [Deutsch](/README_de.md) | [한국어](/README_ko.md)

<div align=center>
<img src="/doc/image/logo.svg" width="400" height="150"/>
</div>

## LibDriver TM1621X

[![MISRA](https://img.shields.io/badge/misra-compliant-brightgreen.svg)](/misra/README.md) [![API](https://img.shields.io/badge/api-reference-blue.svg)](https://www.libdriver.com/docs/tm1621x/index.html) [![License](https://img.shields.io/badge/license-MIT-brightgreen.svg)](/LICENSE)

TM1621X是內存映象和多功能的LCD驅動器，TM1621X的軟件配置特性使它適用於多種LCD應用場合，包括LCD模組和顯示子系統。用於連接主控制器和TM1621X的管腳只有4或5條，TM1621X還有一個節電命令用於降低系統功耗。

LibDriver TM1621X是LibDriver推出的TM1621X的全功能驅動，該驅動提供液晶屏顯示等功能並且它符合MISRA標準。

### 目錄

  - [說明](#說明)
  - [安裝](#安裝)
  - [使用](#使用)
    - [example basic](#example-basic)
    - [example output](#example-output)
  - [文檔](#文檔)
  - [貢獻](#貢獻)
  - [版權](#版權)
  - [聯繫我們](#聯繫我們)

### 說明

/src目錄包含了LibDriver TM1621X的源文件。

/interface目錄包含了LibDriver TM1621X與平台無關的GPIO總線模板。

/test目錄包含了LibDriver TM1621X驅動測試程序，該程序可以簡單的測試芯片必要功能。

/example目錄包含了LibDriver TM1621X編程範例。

/doc目錄包含了LibDriver TM1621X離線文檔。

/datasheet目錄包含了TM1621X數據手冊。

/project目錄包含了常用Linux與單片機開發板的工程樣例。所有工程均採用shell腳本作為調試方法，詳細內容可參考每個工程裡面的README.md。

/misra目錄包含了LibDriver MISRA程式碼掃描結果。

### 安裝

參考/interface目錄下與平台無關的GPIO總線模板，完成指定平台的GPIO總線驅動。

將/src目錄，您使用平臺的介面驅動和您開發的驅動加入工程，如果您想要使用默認的範例驅動，可以將/example目錄加入您的工程。

### 使用

您可以參考/example目錄下的程式設計範例完成適合您的驅動，如果您想要使用默認的程式設計範例，以下是它們的使用方法。

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

### 文檔

在線文檔: [https://www.libdriver.com/docs/tm1621x/index.html](https://www.libdriver.com/docs/tm1621x/index.html)。

離線文檔: /doc/html/index.html。

### 貢獻

請參攷CONTRIBUTING.md。

### 版權

版權 (c) 2015 - 現在 LibDriver 版權所有

MIT 許可證（MIT）

特此免費授予任何獲得本軟件副本和相關文檔文件（下稱“軟件”）的人不受限制地處置該軟件的權利，包括不受限制地使用、複製、修改、合併、發布、分發、轉授許可和/或出售該軟件副本，以及再授權被配發了本軟件的人如上的權利，須在下列條件下：

上述版權聲明和本許可聲明應包含在該軟件的所有副本或實質成分中。

本軟件是“如此”提供的，沒有任何形式的明示或暗示的保證，包括但不限於對適銷性、特定用途的適用性和不侵權的保證。在任何情況下，作者或版權持有人都不對任何索賠、損害或其他責任負責，無論這些追責來自合同、侵權或其它行為中，還是產生於、源於或有關於本軟件以及本軟件的使用或其它處置。

### 聯繫我們

請聯繫lishifenging@outlook.com。
[English](/README.md) | [ 简体中文](/README_zh-Hans.md) | [繁體中文](/README_zh-Hant.md) | [日本語](/README_ja.md) | [Deutsch](/README_de.md) | [한국어](/README_ko.md)

<div align=center>
<img src="/doc/image/logo.svg" width="400" height="150"/>
</div>

## LibDriver TM1621X

[![MISRA](https://img.shields.io/badge/misra-compliant-brightgreen.svg)](/misra/README.md) [![API](https://img.shields.io/badge/api-reference-blue.svg)](https://www.libdriver.com/docs/tm1621x/index.html) [![License](https://img.shields.io/badge/license-MIT-brightgreen.svg)](/LICENSE)

TM1621Xは、メモリマップ方式を採用した多機能LCDドライバです。TM1621Xのソフトウェア構成機能により、LCDモジュールやディスプレイサブシステムなど、様々なLCDアプリケーションに適しています。メインコントローラとTM1621Xの接続には4ピンまたは5ピンしか使用せず、さらにシステム消費電力を削減するための省電力コマンドも備えています。

LibDriver TM1621Xは、LibDriver社が開発したTM1621X用のフル機能ドライバです。LCDディスプレイ機能やその他の追加機能を提供します。LibDriverはMISRA規格に準拠しています。

### 目次

  - [説明](#説明)
  - [インストール](#インストール)
  - [使用](#使用)
    - [example basic](#example-basic)
    - [example output](#example-output)
  - [ドキュメント](#ドキュメント)
  - [貢献](#貢献)
  - [著作権](#著作権)
  - [連絡して](#連絡して)

### 説明

/ srcディレクトリには、LibDriver TM1621Xのソースファイルが含まれています。

/ interfaceディレクトリには、LibDriver TM1621X用のプラットフォームに依存しないGPIOバステンプレートが含まれています。

/ testディレクトリには、チップの必要な機能を簡単にテストできるLibDriver TM1621Xドライバーテストプログラムが含まれています。

/ exampleディレクトリには、LibDriver TM1621Xプログラミング例が含まれています。

/ docディレクトリには、LibDriver TM1621Xオフラインドキュメントが含まれています。

/ datasheetディレクトリには、TM1621Xデータシートが含まれています。

/ projectディレクトリには、一般的に使用されるLinuxおよびマイクロコントローラー開発ボードのプロジェクトサンプルが含まれています。 すべてのプロジェクトは、デバッグ方法としてシェルスクリプトを使用しています。詳細については、各プロジェクトのREADME.mdを参照してください。

/ misraはLibDriver misraコードスキャン結果を含む。

### インストール

/ interfaceディレクトリにあるプラットフォームに依存しないGPIOバステンプレートを参照して、指定したプラットフォームのGPIOバスドライバを完成させます。

/src ディレクトリ、プラットフォームのインターフェイス ドライバー、および独自のドライバーをプロジェクトに追加します。デフォルトのサンプル ドライバーを使用する場合は、/example ディレクトリをプロジェクトに追加します。

### 使用

/example ディレクトリ内のサンプルを参照して、独自のドライバーを完成させることができます。 デフォルトのプログラミング例を使用したい場合の使用方法は次のとおりです。

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

### ドキュメント

オンラインドキュメント: [https://www.libdriver.com/docs/tm1621x/index.html](https://www.libdriver.com/docs/tm1621x/index.html)。

オフラインドキュメント: /doc/html/index.html。

### 貢献

CONTRIBUTING.mdを参照してください。

### 著作権

著作権（c）2015-今 LibDriver 全著作権所有

MITライセンス（MIT）

このソフトウェアおよび関連するドキュメントファイル（「ソフトウェア」）のコピーを取得した人は、無制限の使用、複製、変更、組み込み、公開、配布、サブライセンスを含む、ソフトウェアを処分する権利を制限なく付与されます。ソフトウェアのライセンスおよび/またはコピーの販売、および上記のようにソフトウェアが配布された人の権利のサブライセンスは、次の条件に従うものとします。

上記の著作権表示およびこの許可通知は、このソフトウェアのすべてのコピーまたは実体に含まれるものとします。

このソフトウェアは「現状有姿」で提供され、商品性、特定目的への適合性、および非侵害の保証を含むがこれらに限定されない、明示または黙示を問わず、いかなる種類の保証もありません。 いかなる場合も、作者または著作権所有者は、契約、不法行為、またはその他の方法で、本ソフトウェアおよび本ソフトウェアの使用またはその他の廃棄に起因または関連して、請求、損害、またはその他の責任を負わないものとします。

### 連絡して

お問い合わせくださいlishifenging@outlook.com。
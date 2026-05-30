[English](/README.md) | [ 简体中文](/README_zh-Hans.md) | [繁體中文](/README_zh-Hant.md) | [日本語](/README_ja.md) | [Deutsch](/README_de.md) | [한국어](/README_ko.md)

<div align=center>
<img src="/doc/image/logo.svg" width="400" height="150"/>
</div>

## LibDriver TM1621X

[![MISRA](https://img.shields.io/badge/misra-compliant-brightgreen.svg)](/misra/README.md) [![API](https://img.shields.io/badge/api-reference-blue.svg)](https://www.libdriver.com/docs/tm1621x/index.html) [![License](https://img.shields.io/badge/license-MIT-brightgreen.svg)](/LICENSE) 

Der TM1621X ist ein speicheradressierter und multifunktionaler LCD-Treiber. Dank seiner Softwarekonfiguration eignet er sich für diverse LCD-Anwendungen, darunter LCD-Module und Display-Subsysteme. Für den Anschluss des Hauptcontrollers an den TM1621X werden lediglich vier oder fünf Pins benötigt. Zudem verfügt der TM1621X über einen Energiesparmodus zur Reduzierung des Systemstromverbrauchs.

LibDriver TM1621X ist ein umfassender Treiber für den TM1621X, entwickelt von LibDriver. Er bietet LCD-Display-Unterstützung und weitere Funktionen. LibDriver ist MISRA-konform.

### Inhaltsverzeichnis

  - [Anweisung](#Anweisung)
  - [Installieren](#Installieren)
  - [Nutzung](#Nutzung)
    - [example basic](#example-basic)
    - [example output](#example-output)
  - [Dokument](#Dokument)
  - [Beitrag](#Beitrag)
  - [Lizenz](#Lizenz)
  - [Kontaktieren Sie uns](#Kontaktieren-Sie-uns)

### Anweisung

/src enthält LibDriver TM1621X-Quelldateien.

/interface enthält die plattformunabhängige Vorlage LibDriver TM1621X GPIO.

/test enthält den Testcode des LibDriver TM1621X-Treibers und dieser Code kann die erforderliche Funktion des Chips einfach testen.

/example enthält LibDriver TM1621X-Beispielcode.

/doc enthält das LibDriver TM1621X-Offlinedokument.

/Datenblatt enthält TM1621X-Datenblatt.

/project enthält den allgemeinen Beispielcode für Linux- und MCU-Entwicklungsboards. Alle Projekte verwenden das Shell-Skript, um den Treiber zu debuggen, und die detaillierten Anweisungen finden Sie in der README.md jedes Projekts.

/misra enthält die Ergebnisse des LibDriver MISRA Code Scans.

### Installieren

Verweisen Sie auf eine plattformunabhängige GPIO-Schnittstellenvorlage und stellen Sie Ihren Plattform-GPIO-Treiber fertig.

Fügen Sie das Verzeichnis /src, den Schnittstellentreiber für Ihre Plattform und Ihre eigenen Treiber zu Ihrem Projekt hinzu. Wenn Sie die Standardbeispieltreiber verwenden möchten, fügen Sie das Verzeichnis /example zu Ihrem Projekt hinzu.

### Nutzung

Sie können auf die Beispiele im Verzeichnis /example zurückgreifen, um Ihren eigenen Treiber zu vervollständigen. Wenn Sie die Standardprogrammierbeispiele verwenden möchten, erfahren Sie hier, wie Sie diese verwenden.

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

### Dokument

Online-Dokumente: [https://www.libdriver.com/docs/tm1621x/index.html](https://www.libdriver.com/docs/tm1621x/index.html).

Offline-Dokumente: /doc/html/index.html.

### Beitrag

Bitte beachten Sie CONTRIBUTING.md.

### Lizenz

Urheberrechte © (c) 2015 - Gegenwart LibDriver Alle Rechte vorbehalten



Die MIT-Lizenz (MIT)



Hiermit wird jeder Person kostenlos die Erlaubnis erteilt, eine Kopie zu erhalten

dieser Software und zugehörigen Dokumentationsdateien (die „Software“) zu behandeln

in der Software ohne Einschränkung, einschließlich, aber nicht beschränkt auf die Rechte

zu verwenden, zu kopieren, zu modifizieren, zusammenzuführen, zu veröffentlichen, zu verteilen, unterzulizenzieren und/oder zu verkaufen

Kopien der Software und Personen, denen die Software gehört, zu gestatten

dazu eingerichtet werden, unter folgenden Bedingungen:



Der obige Urheberrechtshinweis und dieser Genehmigungshinweis müssen in allen enthalten sein

Kopien oder wesentliche Teile der Software.



DIE SOFTWARE WIRD "WIE BESEHEN" BEREITGESTELLT, OHNE JEGLICHE GEWÄHRLEISTUNG, AUSDRÜCKLICH ODER

STILLSCHWEIGEND, EINSCHLIESSLICH, ABER NICHT BESCHRÄNKT AUF DIE GEWÄHRLEISTUNG DER MARKTGÄNGIGKEIT,

EIGNUNG FÜR EINEN BESTIMMTEN ZWECK UND NICHTVERLETZUNG VON RECHTEN DRITTER. IN KEINEM FALL DARF DAS

AUTOREN ODER URHEBERRECHTSINHABER HAFTEN FÜR JEGLICHE ANSPRÜCHE, SCHÄDEN ODER ANDERE

HAFTUNG, OB AUS VERTRAG, DELIKT ODER ANDERWEITIG, ENTSTEHEND AUS,

AUS ODER IM ZUSAMMENHANG MIT DER SOFTWARE ODER DER VERWENDUNG ODER ANDEREN HANDLUNGEN MIT DER

SOFTWARE.

### Kontaktieren Sie uns

Bitte senden Sie eine E-Mail an lishifenging@outlook.com.
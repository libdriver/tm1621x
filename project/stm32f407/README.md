### 1. Chip

#### 1.1 Chip Info

Chip Name: STM32F407ZGT6.

Extern Oscillator: 8MHz.

UART Pin: TX/RX PA9/PA10.

GPIO Pin: DATA/WR/RD/CS PA8/PA0/PB1/PB2.

### 2. Development and Debugging

#### 2.1 Integrated Development Environment

LibDriver provides both Keil and IAR integrated development environment projects.

MDK is the Keil ARM project and your Keil version must be 5 or higher.Keil ARM project needs STMicroelectronics STM32F4 Series Device Family Pack and you can download from https://www.keil.com/dd2/stmicroelectronics/stm32f407zgtx.

EW is the IAR ARM project and your IAR version must be 9 or higher.

#### 2.2 Serial Port Parameter

Baud Rate: 115200.

Data Bits : 8.

Stop Bits: 1.

Parity: None.

Flow Control: None.

#### 2.3 Serial Port Assistant

We use '\n' to wrap lines.If your serial port assistant displays exceptions (e.g. the displayed content does not divide lines), please modify the configuration of your serial port assistant or replace one that supports '\n' parsing.

### 3. TM1621X

#### 3.1 Command Instruction

1. Show tm1621x chip and driver information.

    ```shell
    tm1621x (-i | --information)  
    ```

2. Show tm1621x help.

    ```shell
    tm1621x (-h | --help)        
    ```

3. Show tm1621x pin connections of the current board.

    ```shell
    tm1621x (-p | --port)        
    ```

4. Run tm1621x write test.

    ```shell
    tm1621x (-t write | --test=write) [--type=<B | C | D | E>] 
    ```

5. Run tm1621x output test.

    ```shell
    tm1621x (-t output | --test=output) [--type=<B | C | D | E>]
    ```
    
6. Run tm1621x write function,  address is the start address and the range is 0 - 31, hex is the set data.

    ```shell
    tm1621x (-e write | --example=write) [--type=<B | C | D | E>] [--addr=<address>] [--num=<hex>]
    ```
    
7. Run tm1621x tone function.

    ```shell
    tm1621x (-e tone | --example=tone) [--type=<B | C | D | E>] [--freq=<2k | 4k>] [--operator=<on | off>]
    ```

8. Run tm1621x clock function.

    ```shell
    tm1621x (-e clock | --example=clock) [--type=<B | C | D | E>] [--div=<1 | 2 | 4 | 8 | 16 | 32 | 64 | 128>] [--operator=<on | off>]
    ```
9. Run tm1621x watchdog function.

    ```shell
    tm1621x (-e watchdog | --example=watchdog) [--type=<B | C | D | E>] [--div=<1 | 2 | 4 | 8 | 16 | 32 | 64 | 128>] [--operator=<on | off>]
    ```

#### 3.2 Command Example

```shell
tm1621x -i

tm1621x: chip is Titan Micro Electronics TM1621X.
tm1621x: manufacturer is Titan Micro Electronics.
tm1621x: interface is GPIO.
tm1621x: driver version is 1.0.
tm1621x: min supply voltage is 2.4V.
tm1621x: max supply voltage is 5.2V.
tm1621x: max current is 2.60mA.
tm1621x: max temperature is 85.0C.
tm1621x: min temperature is -40.0C.
```

```shell
tm1621x -p

tm1621x: GPIO interface DATA connected to GPIOA PIN8.
tm1621x: GPIO interface WR connected to GPIOA PIN0.
tm1621x: GPIO interface RD connected to GPIOB PIN1.
tm1621x: GPIO interface CS connected to GPIOB PIN2.
```

```shell
tm1621x -t write --type=B

tm1621x: chip is Titan Micro Electronics TM1621X.
tm1621x: manufacturer is Titan Micro Electronics.
tm1621x: interface is GPIO.
tm1621x: driver version is 1.0.
tm1621x: min supply voltage is 2.4V.
tm1621x: max supply voltage is 5.2V.
tm1621x: max current is 2.60mA.
tm1621x: max temperature is 85.0C.
tm1621x: min temperature is -40.0C.
tm1621x: start write test.
tm1621x: write segment test.
tm1621x: 2k tone test.
tm1621x: 4k tone test.
tm1621x: read modify write test.
tm1621x: data check passed.
tm1621x: finish write test.
```

```shell
tm1621x -t output --type=B

tm1621x: chip is Titan Micro Electronics TM1621X.
tm1621x: manufacturer is Titan Micro Electronics.
tm1621x: interface is GPIO.
tm1621x: driver version is 1.0.
tm1621x: min supply voltage is 2.4V.
tm1621x: max supply voltage is 5.2V.
tm1621x: max current is 2.60mA.
tm1621x: max temperature is 85.0C.
tm1621x: min temperature is -40.0C.
tm1621x: start output test.
tm1621x: clock 1hz test.
tm1621x: clock 2hz test.
tm1621x: clock 4hz test.
tm1621x: clock 8hz test.
tm1621x: clock 16hz test.
tm1621x: clock 32hz test.
tm1621x: clock 64hz test.
tm1621x: clock 128hz test.
tm1621x: wdt 4s test.
tm1621x: wdt 2s test.
tm1621x: wdt 1s test.
tm1621x: wdt 1/2s test.
tm1621x: wdt 1/4s test.
tm1621x: wdt 1/8s test.
tm1621x: wdt 1/16s test.
tm1621x: wdt 1/32s test.
tm1621x: finish output test.
```

```shell
tm1621x -e write --type=B --addr=0 --num=0x0F

tm1621x: write address 0x00 0x0F.
```
```shell
tm1621x -e tone --type=B --freq=2k --operator=on

tm1621x: enable 2k tone.
```
```
tm1621x -e clock --type=B --div=128 --operator=on

tm1621x: div 128 and start.
```
```shell
tm1621x -e watchdog --type=B --div=1 --operator=on

tm1621x: div 1 and start.
```
```shell
tm1621x -h

Usage:
  tm1621x (-i | --information)
  tm1621x (-h | --help)
  tm1621x (-p | --port)
  tm1621x (-t write | --test=write) [--type=<B | C | D | E>]
  tm1621x (-t output | --test=output) [--type=<B | C | D | E>]
  tm1621x (-e write | --example=write) [--type=<B | C | D | E>] [--addr=<address>]
          [--num=<hex>]
  tm1621x (-e tone | --example=tone) [--type=<B | C | D | E>]
          [--freq=<2k | 4k>] [--operator=<on | off>]
  tm1621x (-e clock | --example=clock) [--type=<B | C | D | E>]
          [--div=<1 | 2 | 4 | 8 | 16 | 32 | 64 | 128>] [--operator=<on | off>]
  tm1621x (-e watchdog | --example=watchdog) [--type=<B | C | D | E>]
          [--div=<1 | 2 | 4 | 8 | 16 | 32 | 64 | 128>] [--operator=<on | off>]

Options:
      --addr=<address>                   Set the start address and the range is 0-31.([default: 0])
      --div=<1 | 2 | 4 | 8 | 16 | 32 | 64 | 128>
                                         Set the clock division.([default: 1])
  -e <write | tone | clock | watchdog>, --example=<write | tone | clock | watchdog>
                                         Run the driver example.
      --freq=<2k | 4k>                   Set the tone frequency.([default: 2k])
  -h, --help                             Show the help.
  -i, --information                      Show the chip information.
      --operator=<on | off>              Enable or disable the operator.([default: on])
  -p, --port                             Display the pin connections of the current board.
      --num=<hex>                        Set display number.([default: 0x00])
  -t <write | output>, --test=<write | output>
                                         Run the driver test.
      --type=<B | C | D | E>             Set the display type.([default: B])
```

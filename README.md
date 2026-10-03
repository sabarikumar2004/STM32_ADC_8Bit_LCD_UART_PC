# STM32F103 Bare-Metal ADC, 16x2 LCD & UART

## Project Overview

This project demonstrates bare-metal Embedded C programming on the STM32F103C8T6 (Blue Pill).

The project reads an analog voltage from a potentiometer using the ADC1 peripheral, converts the ADC value into voltage, and displays the result on:

- 16x2 LCD
- UART serial terminal on a PC

The STM32 peripherals are configured directly using memory-mapped registers, without using HAL or CubeMX-generated peripheral code.

## Project Images

### Hardware Setup

![STM32F103 ADC LCD UART Hardware Setup](Image/hardware_setup.jpg)

### LCD Output

![16x2 LCD ADC Voltage Display](Image/lcd_output.jpg)

### UART Output

![UART Serial Monitor Output](Image/uart_output.jpg)

## Features

- STM32F103C8T6 Blue Pill
- Bare-metal register-level programming
- 12-bit ADC
- ADC1 Channel 8
- 16x2 LCD in 8-bit mode
- USART1 communication
- 9600 baud UART
- Voltage calculation from ADC reading
- LCD voltage display
- PC serial-terminal voltage display
- ST-LINK programming/debugging

## Hardware Used

| Component | Purpose |
|---|---|
| STM32F103C8T6 Blue Pill | Main microcontroller |
| Potentiometer | Analog voltage input |
| 16x2 LCD | Voltage display |
| ST-LINK V2 | Programming/debugging |
| USB-to-TTL converter | UART communication with PC |
| Jumper wires | Connections |

## Pin Configuration

| Function | STM32 Pin |
|---|---|
| ADC Input | PB0 / ADC1 Channel 8 |
| LCD D0 | PA0 |
| LCD D1 | PA1 |
| LCD D2 | PA2 |
| LCD D3 | PA3 |
| LCD D4 | PA4 |
| LCD D5 | PA5 |
| LCD D6 | PA6 |
| LCD D7 | PA7 |
| LCD RS | PB3 |
| LCD EN | PB1 |
| LCD RW | GND |
| UART1 TX | PA9 |
| SWDIO | PA13 |
| SWCLK | PA14 |

## Working Principle

```text
Potentiometer
      |
      v
PB0 / ADC1 Channel 8
      |
      v
12-bit ADC
      |
      v
ADC Value (0 - 4095)
      |
      v
Voltage Calculation
      |
      +---------------------+
      |                     |
      v                     v
  16x2 LCD             UART1 / PA9
      |                     |
      v                     v
Voltage Display       PC Serial Terminal

The ADC value is converted to voltage using:

Voltage = ADC_Value × 3.3 / 4095

For example:

ADC Value = 2048

Voltage ≈ 2048 × 3.3 / 4095
        ≈ 1.65 V
Bare-Metal Peripherals

The project directly configures the following STM32 peripherals through registers:

RCC
GPIOA
GPIOB
ADC1
USART1
AFIO

No STM32 HAL peripheral functions are used.

ADC Configuration
ADC peripheral: ADC1
ADC channel: Channel 8
Input pin: PB0
Resolution: 12-bit
ADC range: 0–4095
Reference/supply used for calculation: 3.3 V
Sampling time: 239.5 ADC cycles
Single-channel conversion
LCD Configuration

The 16x2 LCD operates in 8-bit mode.

PA0 → D0
PA1 → D1
PA2 → D2
PA3 → D3
PA4 → D4
PA5 → D5
PA6 → D6
PA7 → D7

PB3 → RS
PB1 → EN
RW  → GND

The LCD displays:

ADC VOLTAGE:
1.65 V
UART Configuration

USART1 is used to send the measured voltage to a PC.

TX        → PA9
Baud Rate → 9600

Example serial output:

ADC Voltage: 1.65 V
ADC Voltage: 2.10 V
ADC Voltage: 2.85 V
Programming and Debugging

The STM32F103C8T6 is programmed using an ST-LINK through the SWD interface.

ST-LINK       STM32 Blue Pill
--------------------------------
SWDIO    →    PA13
SWCLK    →    PA14
GND      →    GND
3.3V     →    3.3V
NRST     →    NRST
Project Structure
STM32_ADC_8Bit_LCD_UART_PC
│
├── .settings
├── Debug
├── Image
│   ├── hardware_setup.jpg
│   ├── lcd_output.jpg
│   └── uart_output.jpg
│
├── Inc
├── Src
│   └── main.c
│
├── Startup
├── .gitignore
├── .project
├── .cproject
├── ADC_UART_PC Debug.launch
├── STM32F103C8TX_FLASH.ld
└── README.md
Software Tools
STM32CubeIDE
STM32CubeProgrammer
ST-LINK V2
Serial Terminal / PuTTY
Git
GitHub
Important Note

The analog input on PB0 must remain within the STM32's 3.3 V supply range.

The potentiometer should therefore be powered from 3.3 V, not 5 V.

Learning Outcomes

This project provides practical experience with:

STM32F103C8T6 architecture
Memory-mapped peripheral registers
GPIO configuration
ADC configuration and conversion
ADC voltage calculation
16x2 LCD interfacing
UART communication
USART register configuration
STM32 SWD programming
Bare-metal Embedded C
Git and GitHub project management
Author

K Sabari

GitHub: https://github.com/sabarikumar2004

LinkedIn: https://www.linkedin.com/in/sabarikumar48
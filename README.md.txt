# STM32F103 Bare-Metal ADC, 16x2 LCD & UART Telemetry

Bare-metal Embedded C firmware targeting the **ARM Cortex-M3 (STM32F103C8T6)**. The system performs analog-to-digital conversions on PA0 via ADC1, formats and prints the live readings on a 16x2 character LCD via an 8-bit parallel bus, and transmits telemetry packets concurrently over USART1 to a PC terminal at 9600 baud.

---

## Hardware Output & Setup

| Hardware Setup | UART Serial Console (PuTTY) |
|---|---|
| ![Hardware Setup](docs/hardware_setup.jpeg) | ![UART Console](docs/uart_terminal.jpeg) |

---

## Technical Specifications

- **Target MCU:** STM32F103C8T6 (ARM Cortex-M3, 64 KB Flash, 20 KB SRAM)
- **ADC Configuration:** 12-bit ADC1 on Channel 0 (PA0), continuous single conversion mode.
- **Display Driver:** 16x2 alphanumeric LCD driven in 8-bit parallel mode via GPIO Port B.
- **Serial Telemetry:** USART1 configured for 9600 baud (8-N-1 format) with TXE flag polling.
- **Debug Interface:** ST-LINK V2 SWD debugger and USB-to-TTL UART adapter.

---

## Building and Flashing

1. Open **STM32CubeIDE**.
2. Select `File -> Open Projects from File System...` and select this folder.
3. Build the firmware (`Ctrl + B`).
4. Flash using ST-LINK V2.
5. Connect USB-to-TTL to PA9 (TX) and open PuTTY at 9600 baud.
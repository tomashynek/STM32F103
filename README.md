# STM32F103
Hard way - no IDE, no HAL (or similar) - cross-compiled on RPi 3B using arm-none-eabi-, vim, makefile and openocd

Language - bare metal C - not yet asm, C++ nor RTOS - but I hope they will come too.

I would really like to learn STM32 programming. Hard way seems the most appealing to me, there are no hidden secrets, you have to understand device and toolchain.

This repository will hopefully contain my hobbyist's trials to play with STM32F103 - bluepill from eBay. I will start with simple peripherals like timers, USART, I2C etc.

However time is limited.

## Projects list:
* blink - simple on-board led blinking using while loop to countdown
* TIM1 - blinking using TIM1 for countdown
* TIM1_interrupt - blinking using interrupt service routine of TIM1 for countdown
* serial_helloworld - continuous transmission of "Hello world!" text over USART1
* serial_toggle_led - toggle led state by sending 't' character over USART1 
* adc_internal - read internal (temperature or reference voltage) value by ADC1 and send results over USART1
* ...

## HW and connection [WIP]
* STM32F103 - bluepill from eBay
* ST-LINKv2
* PL2303 - USB-to-Serial convertor
* RPi for compiling

## Toolchain and SW
* arm-none-eabi
* gdb-multiarch
* openocd
* vim
* putty

## Loading executable and debugging [WIP]
Start openocd (reads openocd.cfg file) in one terminal.

In another terminal start gdb (there was arm-none-eabi-gdb previously but seems that current one is gdb-multiarch) gdb-multiarch xxx.elf

In gdb do:
* target remote localhost:3333 - connects to openocd server
* monitor reset halt - reset and halt the target
* load - upload corresponding .elf file
* use common gdb commands - b, l, n, s, ...


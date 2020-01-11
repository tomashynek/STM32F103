# STM32F103
Hard way - no IDE, no HAL (or similar) - cross-compiled on RPi 3B using arm-none-eabi-, vim, makefile and openocd

Language - bare metal C - not yet asm, C++ nor RTOS - but I hope they will come too.

I would really like to learn STM32 programming. Hard way seems the most appealing to me, there are no hidden secrets, you have to understand device and toolchain.

This repository will hopefully contain my hobbyist's trials to play with STM32F103 - bluepill from eBay. I will start with simple peripherials like timers, USART, I2C etc.

However time is limited.

## HW and connection [WIP]

## Loading executable and debugging [WIP]
Start openocd (reads openocd.cfg file) in one terminal
In another terminal start gdb (there was arm-none-eabi-gdb previously but seems that current one is gdb-multiarch) gdb-multiarch xxx.elf
In gdb do:
* target remote localhost:3333 - connects to openocd server
* monitor reset halt - reset and halt the target
* load - upload corresponding .elf file
* use common gdb commands - b, l, n, s, ... 

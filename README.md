# 2byte-command-2byte-response-C-program
Control a microcontroller using  2 byte commands  and 2 byte message responses
The initial setup is based on PC execution, but can be changed for microcontroller platforms 
# STM32F407VET6 board configuration
STM32 CUBE IDE is the programming interface<br>
STM32 CUBE PROGRAMMER is the flashing software<br>
Device Firmware Update (DFU) mode / flash to USB :<br> 
BT0 to HIGH(3V3), BT1 to GND
<br>
Configure STM32 pins through the IOC file in the STM32 ide for output/input/etc<br>
Flash Elf file using the STM32 programmer, while the board is in DFU mode<br>
Remove the jumper connections to BT0 and BT1 pins

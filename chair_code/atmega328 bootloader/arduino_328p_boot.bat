@echo off
@echo "Uploading Bootloader..."
@echo off
avrdude -c dragon_isp -p m328p -D -U flash:w:ATmegaBOOT_168_atmega328_pro_8MHz.hex -vv
echo TIMEOUT 4
echo avrdude -c dragon_isp -p m328p -U lfuse:w:0xff:m
echo TIMEOUT 2
echo avrdude -c dragon_isp -p m328p -U hfuse:w:0xd8:m
Pause


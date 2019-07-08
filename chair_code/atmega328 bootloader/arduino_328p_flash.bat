@echo off
@echo "Uploading Bootloader..."
@echo off
avrdude -c dragon_isp -p m328p -U flash:w:Pot_code.ino.with_bootloader.hex -vv
Pause

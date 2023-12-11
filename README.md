# PCB Christmas Ornament
These are the design files for PrincipIoT's Christmas Tree PCB Ornament.

This repository includes the KiCAD design files, schematic, and bill of materials in the `OrnamentSCH` folder, and software in the `OrnamentCode` file. The hex file for the compiled firmware is available on the releases page.

# Flashing
To flash the firmware to a board, use `avrdude` (it's included in the Arduino IDE). Make sure to have the [ATTinyCore](https://github.com/SpenceKonde/ATTinyCore) installed as well.

`avrdude -Cavrdude.conf -v -pattiny25 -cusbasp -e -Uefuse:w:0xFF:m -Uhfuse:w:0b11010111:m -Ulfuse:w:0xE2:m -Uflash:w:fwv1.0.hex:i`

For the `avrdude.conf` file, use the default provided by the Arduino IDE, except set the `default_bitclock` setting to 5: `default_bitclock = 5;`

# Licensing
All work is copyright PrincipIoT LLC 2023. Design files are released under the respective licenses in each folder.
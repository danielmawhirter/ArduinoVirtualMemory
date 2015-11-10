# ArduinoVirtualMemory
Implementation of virtual memory on the Arduino Fio micorcontroller with GeoMote 3 board. We are storing data on *23k256 SPI SRAM* chip by using SpiSRAM Arduino libbrary which provides read and write operations for the chips.
#Name
-Daniel Mawhirter

-Amos Gwa

-Fnu Aruna

-Johanna Smith

#Files
/libraries

/project3

->VM.cpp (Functions for VM class)

->VM.h (VM class)

->morse.h (Convert characters A-Z 0-9 to Morse symbols.)

->project3.ino (Testing VM implementation, Summing Vectors, and Thrashing for analysis)

->README.md
#Features
Morse Code Converter
Using SD card for storage

#Analysis(Extra Credit)
The page fault rate for the vector summation is 0.03 while the thrashing reports at a rate of 0.5.

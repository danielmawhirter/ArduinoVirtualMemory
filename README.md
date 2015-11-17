# ArduinoVirtualMemory
Implementation of virtual memory on Arduino. A #define guard in VM.h switches this project between using the SpiRAM chip on the Fio and using an SD card on an Arduino Micro. Both should work, but we were unable to get our SpiRAM to respond. It works fully with the SD card.

#Name
- Daniel Mawhirter
- Amos Gwa
- Fnu Aruna
- Johanna Smith

#Files
* /libraries
* /project3
* --/VM.cpp (Functions for VM class)
* --/VM.h (VM class)
* --/morse.h (Convert characters A-Z 0-9 to Morse symbols.)
* --/project3.ino (Testing VM implementation, Summing Vectors, and Thrashing for analysis)
* --/README.md

#Features
* Morse Code Converter (flashing LED)
* Using SD card for storage

The page fault rate for the vector summation is 0.03 while the thrashing reports at a rate of 1.0.

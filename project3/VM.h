#pragma once

#define USESD
#ifdef USESD
 #include <SDspiRAM.h>
#else
 #include <SpiRAM.h>
#endif

#define VERBOSE 1
#define TABLE_SIZE 32
#define PAGE_SIZE 32
#define SRAM_PIN 0
#define HOLD_PIN 9

class VM {
  private:
    unsigned refCount;
    unsigned faultCount;
    char** physical;
   #ifdef USESD
    SDspiRAM SpiRam = SDspiRAM::getInstance();
   #else
    SpiRAM SpiRam; 
   #endif
    int* pages;
    int pageIndex;
  public:
    VM();
    double getFaultRate();
    void resetFaultRate();
    char& operator[](const unsigned);
};


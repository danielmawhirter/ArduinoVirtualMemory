#pragma once

//#define USESD
#ifdef USESD
 #include <SDspiRAM.h>
#else
 #include <SpiRAM.h>
#endif

#define VERBOSE 0
#define TABLE_SIZE 16
#define PAGE_SIZE 32
#define CHIPSELECT_PIN 9

class VM {
  private:
    unsigned refCount;
    unsigned faultCount;
    char** physical;
   #ifdef USESD
    SDspiRAM SpiRam;
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


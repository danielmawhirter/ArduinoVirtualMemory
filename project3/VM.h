#pragma once
#include <SpiRAM.h>
#define VERBOSE 0
#define TABLE_SIZE 16
#define PAGE_SIZE 32
#define SRAM_PIN 0
#define HOLD_PIN 9

//typedef struct Page { char* data = new char[PAGE_SIZE]; } Page;
// these may both be useless, ^ avoids typing "struct" reoeatedly
/*class Page
  private:
    char* data;
  public:
    Page() { data = new char[PAGE_SIZE]; }
    char & operator [](unsigned index) { return data[index]; }
    char* asBuffer() { return data; }
};*/

class VM {
  private:
    unsigned refCount;
    unsigned faultCount;
    //Page pages[TABLE_SIZE];
    
  public:
    //SpiRAM SpiRam;
    VM();// : SpiRam(SRAM_PIN, HOLD_PIN) {};
    double getFaultRate() { return static_cast<double>(faultCount) / static_cast<double>(refCount); }
    void resetFaultRate() { refCount = faultCount = 0; }
    char & operator [](unsigned index);
};


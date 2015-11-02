#pragma once
#include <SpiRAM.h>
#define VERBOSE 1
#define TABLE_SIZE 16
#define PAGE_SIZE 32
#define SRAM_PIN 0
#define HOLD_PIN 10

class VM {
  private:
    unsigned refCount;
    unsigned faultCount;
    char** physical;
    SpiRAM SpiRam;
    int* pages;
    int pageIndex;
  public:
    VM();
    double getFaultRate();
    void resetFaultRate();
    char& operator[](const int);
};

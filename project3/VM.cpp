#include "VM.h"
#include "Streaming.h"

char& VM::operator[](const unsigned address) {
  refCount++;
  unsigned pageNum = address >> 5;
  unsigned offset = address & 0x1F;
  
  if(VERBOSE) {
	Serial << "============================\n";
	Serial << "requesting virtual address: " << address << "\n";
	Serial << "\tpage = " << pageNum << ", offset = " << offset << "\n";
  }
  
  for(int i = 0; i < TABLE_SIZE; i++) {
    if(pages[i] == pageNum) {
	  if(VERBOSE) {
		Serial << "PAGE FOUND!\n";
		Serial << "\tpage table entry: " << i << "\n";
		Serial << "\tphysical address: " << offset << "\n";
	  }
      return physical[i][offset];
    }
  }
  //page fault!
  faultCount++;
  if(VERBOSE) {
	Serial << "PAGE FAULT!\n";
  }
  if(pages[pageIndex] > 0) {
	if(VERBOSE) {
		Serial << "\tNO SPACE in page table\n";
		Serial << "\tpage OUT: " << pages[pageIndex] << "\n";
		Serial << "\tpage IN: " << pageNum << "\n";
		Serial << "\tphysical address: " << offset << "\n";
	}
    SpiRam.write_page(pages[pageIndex], physical[pageIndex]);
  } else {
	if(VERBOSE) {
		Serial << "\tempty slot in page table: " << pageIndex << "\n";
		Serial << "\treading SRAM memory page: " << pageNum << "\n";
		Serial << "\tphysical addresss: " << offset << "\n";
	}
  }
  //kicking out pages[pageIndex]
  //page in
  pages[pageIndex] = pageNum;
  SpiRam.read_page(pageNum, physical[pageIndex]);
  pageIndex = (pageIndex + 1) % TABLE_SIZE;
  return physical[pageIndex][offset];
  
}

void VM::resetFaultRate() {
  refCount = faultCount = 0;
}

double VM::getFaultRate() {
  return static_cast<double>(faultCount) / static_cast<double>(refCount);
}

VM::VM() : refCount(0), faultCount(0), pageIndex(0)
#ifndef USESD //if using sram, initialize it
  , SpiRam(SRAM_PIN, HOLD_PIN)
#endif
{
  physical = new char*[TABLE_SIZE];
  pages = new int[TABLE_SIZE];
  for(int i = 0; i < TABLE_SIZE; i++) {
    physical[i] = new char[PAGE_SIZE];
	pages[i] = -1;
  }
}

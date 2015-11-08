#pragma once
#include <SdFat.h>

class SDspiRAM {
  private:
    SdFat sd;
    SdFile myFile;
  public:
    SDspiRAM(int nop, int pin) {
      if (!sd.begin(pin, SPI_FULL_SPEED)) sd.initErrorHalt();
      if (!myFile.open("pages.dat", O_RDWR) || myFile.fileSize() != 32768) {
		if(!myFile.open("pages.dat", O_RDWR | O_CREAT | O_TRUNC)) {
          sd.errorHalt("opening pages.dat failed");
		} else {
		  Serial.println("Creating page file, please wait");
		  for(int i = 0; i < 1024; i++) {
		    for(int j = 0; j < 32; j++) {
		      myFile.write((uint8_t)(0));
		    }
		    Serial.println(i);
            myFile.flush();
          }
		}
      }
      myFile.seekSet(0);
    }
    void write_page(unsigned index, char* data) {
      index <<= 5; // *32
      myFile.seekSet(index);
      for(int i = 0; i < 32; i++) {
        myFile.write(*(data + i));
      }
	  myFile.flush();
    }
    void read_page(unsigned index, char* data) {
      index <<= 5; // *32
      myFile.seekSet(index);
      for(int i = 0; i < 32; i++) {
        data[i] = (char)(myFile.read());
      }
	  myFile.flush();
    }
};

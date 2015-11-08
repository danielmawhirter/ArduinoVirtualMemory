#include <SdFat.h>
#include <SDspiRAM.h>

#include <Streaming.h>
#include <SPI.h>
#include <SpiRAM.h>
#include "VM.h"

VM vm = VM();

//blink
void setup() {
  Serial.begin(9600);
  while (!Serial) {}  // wait for Leonardo
  Serial.println("test");
  test4();
}

void test1() {
  //VERBOSE = 0; TABLE SIZE = 24;
  vm[7978] = 100;
  vm[127937] = 100;
  vm[39847] = vm[7978] + vm[127937];
  // print using Streaming library:
  Serial << (int)vm[7978] << '+' << (int)vm[127937] << '=' << (int)vm[39847] << '\n';
}

void test2() {
  //VERBOSE = 0; TABLE SIZE = 24; 
    char *msg = "Hello from Virtual Memory!!!";
  for (int i = 0; i < strlen(msg); i++) {
    vm[i*32] = msg[i];
  }
  for (int i = 0; i < strlen(msg); i++) {
    Serial << (char) vm[i*32];
  }
  Serial << '\n';
}

void test3() {
  //VERBOSE = 1; TABLE SIZE = 1;
  vm[32000] = 0xAB; //page 1000, offset 0
  vm[32031] = 0xCD; //page 1000, offset 31
  vm[32032] = 0xEF; //page 1001, offset 0
}

void test4() {
  //VERBOSE = 1; TABLE SIZE = 2;
  vm[2749] = 0xAB;
  vm[963] = 0xCD;
  vm[129775] = 0xEF;
  vm[71066] = 0x01;
}

void loop() {}


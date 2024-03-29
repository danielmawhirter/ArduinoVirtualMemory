#ifdef USESD
 #include <SdFat.h>
 #include <SDspiRAM.h>
#else
 #include <SpiRAM.h>
#endif
#include "morse.h"
#include <Streaming.h>
#include <SPI.h>
#include "VM.h"

//blink
void setup() {
  Serial.begin(57600);
  while (!Serial) {}  // wait for Leonardo
  pinMode(13, OUTPUT);
  VM vm = VM();
  //test1(vm);
  //test2(vm);
  //test3(vm);
  //test4(vm);
  //vecSum(vm);
  //thrashing(vm);
  testMorse(vm);
}

void test1(VM &vm) {
  //VERBOSE = 0; TABLE SIZE = 24;
  vm[7978] = 100;
  vm[27937] = 100;
  vm[9847] = vm[7978] + vm[27937];
  // print using Streaming library:
  Serial << (int)vm[7978] << '+' << (int)vm[27937] << '=' << (uint8_t)vm[9847] << '\n';
}

void test2(VM &vm) {
  //VERBOSE = 0; TABLE SIZE = 24; 
  char *msg = "Hello from Virtual Memory!!!";
  Serial << "string length:" << strlen(msg) << "\n";
  for (int i = 0; i < strlen(msg); i++) {
    vm[i<<5] = msg[i];
  }
  for (int i = 0; i < strlen(msg); i++) {
    Serial << (char) vm[i<<5];
  }
  Serial << '\n';
}

void test3(VM &vm) {
  //VERBOSE = 1; TABLE SIZE = 1;
  vm[32000] = 0xAB; //page 1000, offset 0
  vm[32031] = 0xCD; //page 1000, offset 31
  vm[32032] = 0xEF; //page 1001, offset 0
}

void test4(VM &vm) {
  //VERBOSE = 1; TABLE SIZE = 2;
  vm[2749] = 0xAB;
  vm[963] = 0xCD;
  vm[29775] = 0xEF;
  vm[1066] = 0x01;
}

void vecSum(VM &vm) {
  //Serial << "writing\n";
  for(int i=0; i<10000; i++) {
    char x = i & 0X7F;
    vm[i] = 1 + x;
    vm[10000 + i] = 1 - x;
  }
  vm.resetFaultRate();
  for(int i=0; i<10000; i++) {
    Serial << (uint8_t)(vm[i] + vm[10000 + i]) << '\n';
  }
  Serial << vm.getFaultRate() << '\n';
}

void thrashing(VM &vm) {
  for(int i=0; i<1024; i++){
    vm[i]= i & 0XFF;
  }
  vm.resetFaultRate();
  for(int j=0;j<32;j++){
    for(int k = 0; k < 32; k++) {
      Serial << (int8_t)vm[j+(k<<5)] << '\n';
    }
  }
  Serial << vm.getFaultRate() << '\n';
}

//capital lettern, numbers, and spaces only
void testMorse(VM &vm) {
  char* str = "HELLO FROM VIRTUAL MEMORY";
  for(int i = 0; i < strlen(str); i++) {
    vm[i << 4] = str[i];
  }
  for(int i = 0; i < strlen(str); i++) {
    displayMorse(charToMorse(vm[i << 4]));
  }
}

void loop() {}


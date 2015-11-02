#include <Streaming.h>
#include <SPI.h>
#include <SpiRAM.h>
#include "VM.h"

VM vm = VM();
//blink
void setup() {
  Serial.println("test");
  pinMode(13, OUTPUT);
}

void loop() {
  digitalWrite(13, HIGH);
  vm[7978] = 100;
  vm[127937] = 100;
  vm[39847] = vm[7978] + vm[127937];
  // print using Streaming library:
  Serial << vm[7978] << '+' << vm[127937] << '=' << vm[39847] << endl;

  char *msg = "Hello from Virtual Memory!!!";
  for (int i = 0; i < strlen(msg); i++) {
    vm[i*32] = msg[i];
  }
  delay(100);
  for (int i = 0; i < strlen(msg); i++) {
    Serial << (char) vm[i*32];
  }
  Serial << endl;
  digitalWrite(13, LOW);
  delay(1000);                  // wait for a second
}

#include <SPI.h>
#include <SpiRAM.h>
#include "VM.h"

//blink
void setup() {
  pinMode(13, OUTPUT);
  /*Page one;
  char* arr = one.data;
  char val = arr[12];*/
}

void loop() {
  digitalWrite(13, HIGH);
  delay(125);
  digitalWrite(13, LOW);
  delay(125);
}

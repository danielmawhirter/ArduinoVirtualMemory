#include <SPI.h>
#include <SpiRAM.h>
#include "VM.h"

//SpiRAM SpiRam(SRAM_PIN, HOLD_PIN);
//blink
void setup() {
  Serial.begin(9600);
  Serial.println("test");
  
  pinMode(13, OUTPUT);
}

void loop() {
  digitalWrite(13, HIGH);
  delay(125);
  digitalWrite(13, LOW);
  delay(125);
}

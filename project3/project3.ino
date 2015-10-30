#include <SPI.h>
#include <SpiRAM.h>
#include "VM.h"

SpiRAM SpiRam(SRAM_PIN, HOLD_PIN);
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
  SpiRam.write_byte(53, 'Q');
  Serial.println(SpiRam.read_byte(53));
  /*for(char x = (char)1; x != (char)0; x++) {
    SpiRam.write_byte(1, 0x51);
    Serial.print((int)x);
    Serial.print('\t');
    Serial.println((int)SpiRam.read_byte(1));
  }*/
}

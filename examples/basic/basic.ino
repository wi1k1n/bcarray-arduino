/*
 * Basic usage of BCArray lib for saving memory on storing numbers, which fit less than 8 bits.
 */
#include <BCArray.h>

#define CAP 4     // number of bits that each number takes (can take values {2, 3, 4, 5, 6, 7, 8})
#define LENGTH 20 // the length of an array (quantity of numbers you are going to add)

BCArray data(CAP, LENGTH);  // contains 20 numbers, but only takes 10 bytes of memory

void setup() {
  Serial.begin(9600);

  // put all the data into array
  for (byte i = 0; i < data.length(); i++) {
    data.put(i, random(16));
  }

  Serial.print(F("BCArray only takes "));
  Serial.print(data.bytesLength());
  Serial.print(F(" bytes for storing "));
  Serial.print(data.length());
  Serial.print(F(" numbers ("));
  Serial.print(data.capacity());
  Serial.println(F(" bits each)"));
  
  Serial.println(F("The numbers are:"));
  for (byte i = 0; i < data.length(); i++) {
    Serial.print((uint16_t)data.get(i));
    Serial.print(F(" "));
  }
  Serial.println();
  Serial.println(F("The values of bytes are:"));
  for (byte i = 0; i < data.bytesLength(); i++) {
    Serial.print((uint16_t)data.byteArray()[i]);
    Serial.print(F(" "));
  }
}

void loop() {
  
}

/*
 * Check if your changes work
 */
#include <BCArray.h>

#define LENGTH 256 // the length of an array (quantity of numbers you are going to add)

BCArray* data;  // contains 20 numbers, but only takes 10 bytes of memory
uint8_t arrCheck[LENGTH];

void setup() {
  Serial.begin(9600);

  // iterate over different capacity values
  bool broke = false;
  for (uint8_t c = 2; c <= 8; c++) {
    data = new BCArray(c, LENGTH);
    // create random values
    for (uint16_t i = 0; i < LENGTH; i++) {
      uint8_t r = random(1 << c);
      data->put(i, r);
      arrCheck[i] = r;
    }
    // check differences
    for (uint16_t i = 0; i < LENGTH; i++) {
      if (data->get(i) != arrCheck[i]) {
        Serial.print("Error for value ");
        Serial.print(arrCheck[i]);
        Serial.print("; c=");
        Serial.print(c);
        Serial.print("; i=");
        Serial.println(i);
        broke = true;
        break;
      }
    }
    if (broke) break;
  }
  if (!broke) Serial.println("Test passed! All numbers are the same.");
}

void loop() {
  
}

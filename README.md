
## BCArray for Arduino

This is a small class for Arduino, that can be used instead of `uint8_t arr[]` to use less SRAM.

#### Application

Effective when using numbers that are lower than `uint8_t` (e.g. menu or state variables, which can only take a few values and do not need the whole capacity of `uint8_t`).

Another case is compressing values to lower precision. For example, temperature measurements in range of [0; 30] with precision up to integers. Each measurement needs only 5 bits which is 37% more memory effective than storing each measurement in `uint8_t`.

### Getting started
Please check examples.
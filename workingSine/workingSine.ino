#include <Arduino.h>
#include <math.h>

const int DAC_PIN = 25; // DAC pin (GPIO 25) for ESP32
const int amplitude = 127; // Amplitude of the sine wave (0-127 for 8-bit DAC resolution)
const int offset = 128; // Offset to shift sine wave to positive values (0-255 for 8-bit DAC resolution)
const int frequency = 512; // Desired frequency of the sine wave in Hz
const int numSamples = 256; // Number of samples in the sine wave table

// Create a lookup table for the sine wave
uint8_t sineTable[numSamples];

void setup() {
  // Set the DAC pin as an output
  pinMode(DAC_PIN, OUTPUT);

  // Generate the sine wave lookup table for 8-bit DAC
  for (int i = 0; i < numSamples; i++) {
    float angle = 2 * PI * i / numSamples;
    sineTable[i] = amplitude * (sin(angle) + 1) / 2 + offset;
  }
}

void loop() {
  static int index = 0;

  // Write the current sine wave value to the DAC pin
  dacWrite(DAC_PIN, sineTable[index]);

  // Increment the index and wrap around if necessary
  index++;
  if (index >= numSamples) {
    index = 0;
  }

  // Delay to achieve the desired frequency
  delayMicroseconds((1000000 / frequency) / numSamples); // Delay in microseconds
}

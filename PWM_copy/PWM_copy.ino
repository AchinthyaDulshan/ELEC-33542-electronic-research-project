#include <Arduino.h>

const int PWM_PIN = 25; // Set PWM output pin
const int pwmFrequency = 1000000; // 1 MHz PWM frequency
const int resolution = 8; // 8-bit resolution for duty cycle
const int sineFrequency = 60000; // Desired sine wave frequency (60 kHz)
const int numSamples = 256; // Number of samples in one sine wave cycle

uint8_t sineTable[numSamples]; // Lookup table for sine wave duty cycle values

void setup() {
  // Configure PWM on the specified pin
  ledcSetup(0, pwmFrequency, resolution);
  ledcAttachPin(PWM_PIN, 0);

  // Generate sine wave lookup table for duty cycle values
  for (int i = 0; i < numSamples; i++) {
    float angle = 2 * PI * i / numSamples;
    sineTable[i] = (sin(angle) + 1) * 127; // Scale to 8-bit (0-255) range
  }
}

void loop() {
  for (int i = 0; i < numSamples; i++) {
    ledcWrite(0, sineTable[i]); // Set duty cycle based on sine table
    delayMicroseconds(1000000 / (sineFrequency * numSamples)); // Wait for next sample
  }
}

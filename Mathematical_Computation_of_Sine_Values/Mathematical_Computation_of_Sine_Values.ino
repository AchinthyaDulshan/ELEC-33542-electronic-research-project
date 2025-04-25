#include <Arduino.h>
#include <math.h>

const int DAC_PIN = 25;         // DAC output pin (GPIO 25) for ESP32
const float frequency = 60000;   // Desired sine wave frequency (60 kHz)
const float sampleRate = 960000; // Sample rate (1 MHz is ideal for 16 samples per cycle)
const int amplitude = 127;       // Sine wave amplitude
const int offset = 128;          // Offset to make values positive (0-255 range for 8-bit DAC)
volatile int sampleIndex = 0;    // Keeps track of sample position in the sine wave

hw_timer_t *timer = NULL;        // Hardware timer pointer

void IRAM_ATTR onTimer() {
  // Calculate the current sample angle
  float angle = 2 * PI * frequency * sampleIndex / sampleRate;
  
  // Calculate the sine value, scale to DAC range, and add offset
  uint8_t dacValue = amplitude * sin(angle) + offset;
  
  // Output to DAC
  dacWrite(DAC_PIN, dacValue);
  
  // Increment sample index and wrap it around to stay within one cycle
  sampleIndex++;
  if (sampleIndex >= sampleRate / frequency) {
    sampleIndex = 0;
  }
}

void setup() {
  // Set the DAC pin as output
  pinMode(DAC_PIN, OUTPUT);
  
  // Initialize the hardware timer for generating samples at the desired rate
  timer = timerBegin(0, 80, true); // Timer 0, prescaler 80 (1 tick = 1 microsecond)
  timerAttachInterrupt(timer, &onTimer, true);
  timerAlarmWrite(timer, 1000000 / sampleRate, true); // Set timer to sample rate interval
  timerAlarmEnable(timer); // Enable the alarm
}

void loop() {
  // Nothing to do here, waveform generation is handled by the timer interrupt
}

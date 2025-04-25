#include <Arduino.h>
#include <driver/dac.h>

const int DAC_PIN = DAC1;            // Use DAC1 (GPIO 25) on ESP32
const int sampleRate = 1000000;      // 1 MHz sample rate for smooth output
const int frequency = 60000;         // Desired sine wave frequency (60 kHz)
const int tableSize = 256;           // Number of samples in sine lookup table

// Phase increment calculation
const float phaseIncrement = (float)frequency * tableSize / sampleRate;

// Lookup table for one cycle of a sine wave (8-bit resolution, values 0-255)
uint8_t sineTable[tableSize];

// Phase accumulator
volatile float phase = 0.0;

hw_timer_t *timer = NULL;
portMUX_TYPE timerMux = portMUX_INITIALIZER_UNLOCKED;

void IRAM_ATTR onTimer() {
  portENTER_CRITICAL_ISR(&timerMux);
  // Calculate index from phase accumulator and output to DAC
  int index = (int)phase % tableSize;
  dac_output_voltage(DAC_PIN, sineTable[index]);

  // Update phase accumulator
  phase += phaseIncrement;
  if (phase >= tableSize) phase -= tableSize; // Wrap around if exceeds table
  portEXIT_CRITICAL_ISR(&timerMux);
}

void setup() {
  // Initialize DAC
  dac_output_enable(DAC_PIN);

  // Fill the sine table with values for one cycle of the sine wave
  for (int i = 0; i < tableSize; i++) {
    float angle = 2 * PI * i / tableSize;
    sineTable[i] = (sin(angle) + 1) * 127; // Scale to fit 8-bit range (0-255)
  }

  // Initialize timer to trigger at sample rate
  timer = timerBegin(0, 80, true); // Use timer 0, prescaler 80, count up
  timerAttachInterrupt(timer, &onTimer, true);
  timerAlarmWrite(timer, 1000000 / sampleRate, true); // Set alarm for 1 MHz
  timerAlarmEnable(timer); // Enable timer
}

void loop() {
  // Main loop does nothing, everything is handled by the timer interrupt
}

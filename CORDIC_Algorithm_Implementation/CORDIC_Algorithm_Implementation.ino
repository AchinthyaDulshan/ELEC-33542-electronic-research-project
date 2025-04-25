#include <Arduino.h>
#include <driver/dac.h>

// Constants
const int DAC_PIN = DAC1; // GPIO25 for DAC output on ESP32
const int frequency = 60000; // Desired sine wave frequency in Hz
const int sampleRate = 1000000; // Sampling rate for DAC updates in Hz
const int numIterations = 16; // Number of CORDIC iterations (precision)
const float K = 0.607252935; // CORDIC gain factor for scaling

// Look-up table of arctangent values for CORDIC rotations (in radians)
float atanTable[numIterations] = {
  0.7853981633974483, 0.4636476090008061, 0.24497866312686414,
  0.12435499454676144, 0.06241880999595735, 0.031239833430268277,
  0.015623728620476831, 0.007812341060101111, 0.0039062301319669718,
  0.0019531225164788188, 0.0009765621895593195, 0.0004882812111948983,
  0.00024414062014936177, 0.00012207031189367021, 0.00006103515617420877,
  0.000030517578115526096
};

// Timer and phase accumulator
hw_timer_t *timer = NULL;
volatile float targetAngle = 0.0; // Target angle in radians
const float phaseIncrement = 2 * PI * frequency / sampleRate; // Phase increment per sample

void IRAM_ATTR onTimer() {
  // Compute sine value using CORDIC
  float x = K, y = 0.0; // Initialize vector (1, 0) scaled by CORDIC gain
  float angle = 0.0; // Current angle

  for (int i = 0; i < numIterations; i++) {
    float shift = (1.0 / (1 << i)); // 2^(-i) scaling factor
    if (targetAngle >= angle) {
      // Rotate right
      float tempX = x - y * shift;
      y = y + x * shift;
      x = tempX;
      angle += atanTable[i];
    } else {
      // Rotate left
      float tempX = x + y * shift;
      y = y - x * shift;
      x = tempX;
      angle -= atanTable[i];
    }
  }

  // Scale y to 8-bit DAC range and add offset for positive values
  int dacValue = (int)((y * 127) + 128);
  dacWrite(DAC_PIN, dacValue);

  // Update the target angle for the next sample
  targetAngle += phaseIncrement;
  if (targetAngle >= 2 * PI) targetAngle -= 2 * PI;
}

void setup() {
  // Initialize DAC and timer
  dac_output_enable(DAC_PIN);

  // Set up timer for interrupt-based DAC updates
  timer = timerBegin(0, 80, true); // Timer 0, prescaler 80 for 1 MHz base clock
  timerAttachInterrupt(timer, &onTimer, true);
  timerAlarmWrite(timer, 1000000 / sampleRate, true); // Trigger interrupt at sample rate
  timerAlarmEnable(timer); // Start the timer
}

void loop() {
  // Nothing to do in the main loop; everything is handled by the timer ISR
}

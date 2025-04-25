#include <Arduino.h>
#include <driver/dac.h>

const int DAC_PIN = DAC1;            // DAC1 (GPIO 25) for ESP32
const float frequency = 60000.0;     // Target frequency of the sine wave (60 kHz)
const int sampleRate = 1000000;      // Desired sample rate in Hz (1 MHz for smoother wave)

hw_timer_t *timer = NULL;            // Hardware timer
volatile unsigned long sampleIndex = 0;

void IRAM_ATTR onTimer() {
  // Calculate the phase angle for the current sample
  float angle = 2 * PI * frequency * sampleIndex / sampleRate;
  
  // Compute sine value, scale it to 8-bit DAC range (0-255), and offset to positive
  uint8_t dacValue = (sin(angle) + 1) * 127.5;
  
  // Output the sine value to DAC
  dac_output_voltage(DAC_PIN, dacValue);
  
  // Increment the sample index
  sampleIndex++;
}

void setup() {
  // Initialize DAC on the specified pin
  dac_output_enable(DAC_PIN);

  // Initialize the hardware timer with a frequency that matches the sample rate
  timer = timerBegin(0, 80, true);                      // Use timer 0, prescaler 80 (80 MHz / 80 = 1 MHz base frequency)
  timerAttachInterrupt(timer, &onTimer, true);          // Attach onTimer function to timer interrupt
  timerAlarmWrite(timer, (1000000 / sampleRate), true); // Set alarm interval to achieve the desired sample rate
  timerAlarmEnable(timer);                              // Enable the timer alarm to trigger interrupts
}

void loop() {
  // Nothing required in loop; the timer interrupt handles waveform generation
}

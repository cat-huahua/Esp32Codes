#include <Wire.h>
#include <Adafruit_GFX.h>
#include <Adafruit_SSD1306.h>
#include <math.h>

// OLED config
#define SCREEN_WIDTH 128
#define SCREEN_HEIGHT 64
#define OLED_RESET    -1
Adafruit_SSD1306 display(SCREEN_WIDTH, SCREEN_HEIGHT, &Wire, OLED_RESET);

// Pins
const int sensorPin = 34; // ADC pin from HW-502

// Sampling
const unsigned long sampleIntervalMicros = 5000; // 5 ms -> 200 Hz
unsigned long lastSampleMicros = 0;

// Filtering & detection
int raw = 0;
float smooth = 0;
int prevRaw = 0;
const float alpha = 0.08; // smoothing factor for low-pass
int threshold = 35;       // detection threshold (will be adjusted)
int minBeatInterval = 250; // ms (max 240 BPM limit)
unsigned long lastBeatTime = 0;

// BPM averaging
const int Nbeats = 6;
int beatIdx = 0;
unsigned long intervals[Nbeats] = {0};
bool firstBeat = true;

// waveform buffer for OLED (width = 128)
int waveform[128];
int wfIndex = 0;

// Global variables
int bpm = 0;

void drawDisplay() {
  display.clearDisplay();

  // BPM text
  display.setTextSize(2);
  display.setCursor(0, 0);
  if (bpm > 0) {
    display.print(bpm);
    display.print(" ");
    display.setTextSize(1);
    display.print("BPM");
  } else {
    display.print("--");
    display.setTextSize(1);
    display.print(" BPM");
  }

  // Draw waveform (bottom area)
  int baseY = 20;
  for (int i = 0; i < 127; i++) {
    int idxA = (wfIndex + i) % 128;
    int idxB = (wfIndex + i + 1) % 128;
    int xA = i;
    int xB = i + 1;
    int yA = waveform[idxA];
    int yB = waveform[idxB];
    // shift waveform down a bit so it doesn't overlap text
    display.drawLine(xA, baseY + yA / 2, xB, baseY + yB / 2, SSD1306_WHITE);
  }

  // small helper text
  display.setTextSize(1);
  display.setCursor(0, 54);
  display.print("Place finger. Tweak threshold if needed.");

  display.display();
}

void setup() {
  Serial.begin(115200);
  analogReadResolution(12); // 0-4095

  Wire.begin(21, 22); // SDA, SCL. Adjust if using other pins.
  if (!display.begin(SSD1306_SWITCHCAPVCC, 0x3C)) {
    Serial.println("SSD1306 allocation failed");
    while (true);
  }
  display.clearDisplay();
  display.setTextSize(1);
  display.setTextColor(SSD1306_WHITE);

  // initialize waveform buffer
  for (int i = 0; i < 128; i++) waveform[i] = SCREEN_HEIGHT / 2;
  lastSampleMicros = micros();

  // initialize smooth/prevRaw using the scaled ADC reading (0..1023)
  int initRaw = analogRead(sensorPin); // 0..4095
  int initVal = map(initRaw, 0, 4095, 0, 1023);
  smooth = initVal;
  prevRaw = initVal;

  Serial.println("Ready. Place finger on sensor.");
}

void loop() {
  unsigned long nowMicros = micros();
  if (nowMicros - lastSampleMicros >= sampleIntervalMicros) {
    lastSampleMicros += sampleIntervalMicros;

    // read raw
    raw = analogRead(sensorPin); // 0..4095
    // scale to 0..1023 for easier mapping
    int val = map(raw, 0, 4095, 0, 1023);

    // simple low-pass smoothing
    smooth = smooth * (1.0 - alpha) + val * alpha;

    // populate waveform (scale to display height)
    int y = map((int)smooth, 0, 1023, SCREEN_HEIGHT - 1, 0);
    waveform[wfIndex++] = constrain(y, 0, SCREEN_HEIGHT - 1);
    if (wfIndex >= 128) wfIndex = 0;

    // detection: look for upward edge + magnitude threshold + minimum time since last beat
    int derivative = val - prevRaw;
    prevRaw = val;

    // adaptive baseline
    static int baseline = 512;
    baseline = (baseline * 31 + val) / 32; // slow moving baseline

    int dynamicThreshold = baseline + threshold;

    unsigned long nowMs = millis();
    if (derivative > 10 && smooth > dynamicThreshold && (nowMs - lastBeatTime) > minBeatInterval) {
      // beat detected
      if (!firstBeat) {
        unsigned long interval = nowMs - lastBeatTime;
        intervals[beatIdx] = interval;
        beatIdx = (beatIdx + 1) % Nbeats;
        unsigned long sum = 0;
        int count = 0;
        for (int i = 0; i < Nbeats; i++) if (intervals[i] > 0) { sum += intervals[i]; count++; }
        if (count > 0) bpm = round(60000.0 * count / (float)sum);
      } else {
        firstBeat = false;
      }
      lastBeatTime = nowMs;
      Serial.print("Beat: ");
      Serial.print(nowMs);
      Serial.print(" ms  BPM: ");
      Serial.println(bpm);
    }

    // update display at ~20-30Hz
    static unsigned long lastDisp = 0;
    if (millis() - lastDisp > 50) {
      lastDisp = millis();
      drawDisplay();
    }
  }
}
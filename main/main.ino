#include "arduinoFFT.h"

#define PIN_INPUT A1
#define SAMPLES 256                // meilleure résolution
#define SAMPLING_FREQUENCY 9878.0  // fréquence réelle mesurée

double vReal[SAMPLES];
double vImag[SAMPLES];

ArduinoFFT<double> FFT = ArduinoFFT<double>(vReal, vImag, SAMPLES, SAMPLING_FREQUENCY);

void setup() {
  Serial.begin(115200);
  while (!Serial && millis() < 5000)
    ;

  pinMode(PIN_INPUT, INPUT);
  Serial.println("Initialisation terminée - Mode Hertz corrigé");
}

void loop() {

  // ==============================
  // 1. Acquisition
  // ==============================

  unsigned long sampling_period_us = round(1000000.0 / SAMPLING_FREQUENCY);

  for (int i = 0; i < SAMPLES; i++) {
    unsigned long microseconds = micros();

    vReal[i] = analogRead(PIN_INPUT);
    vImag[i] = 0;

    while (micros() - microseconds < sampling_period_us)
      ;
  }

  // ==============================
  // 2. Suppression composante DC
  // ==============================

  double mean = 0;
  for (int i = 0; i < SAMPLES; i++) {
    mean += vReal[i];
  }
  mean /= SAMPLES;

  for (int i = 0; i < SAMPLES; i++) {
    vReal[i] -= mean;
  }

  // ==============================
  // 3. FFT
  // ==============================

  FFT.windowing(FFT_WIN_TYP_HAMMING, FFT_FORWARD);
  FFT.compute(FFT_FORWARD);
  FFT.complexToMagnitude();

  // ==============================
  // 4. Recherche du vrai pic
  // ==============================

  double maxMagnitude = 0;
  int maxIndex = 0;

  // Ignorer les 3 premiers bins (~ < 100 Hz)
  for (int i = 3; i < SAMPLES / 2; i++) {
    if (vReal[i] > maxMagnitude) {
      maxMagnitude = vReal[i];
      maxIndex = i;
    }
  }

  double frequency = (maxIndex * SAMPLING_FREQUENCY) / SAMPLES;

  // ==============================
  // 5. Affichage
  // ==============================

  Serial.print("Frequence_Hz:");
  Serial.println(frequency);

  Serial.print("Min:20 ");
  Serial.print("Max:5000 ");
  Serial.println();

  delay(50);
}


// 50 -> 300
// 500 -> 350
// 1000 -> 355
// 5000 -> 360
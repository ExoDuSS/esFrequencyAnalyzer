#include <Arduino.h>
#include <arduinoFFT.h>
#include <MD_MAX72xx.h>
#include <SPI.h>

#include "defines.h"
#include "display.h"
#include "FFT.h"

arduinoFFT *FFT;
MD_MAX72XX *MX_Display;

int currentDisplayMode;

double *vecReal;
double *vecImag;
char *vecLastPeaks;

void setup()
{
  Serial.begin(9600);

  ADCSRA = 0b11100101; // set ADC to free running mode and set pre-scalar to 32 (0xe5)
  ADMUX = 0b00000000;  // use pin A0 and external voltage reference

  FFT = new arduinoFFT();
  MX_Display = new MD_MAX72XX(HARDWARE_TYPE, CS_PIN, DOTMATRIX_MAX_DEVICES);
  currentDisplayMode = 1; // 1 -5

  vecReal = new double[SAMPLES]{0.f};
  vecImag = new double[SAMPLES]{0.f};

  vecLastPeaks = new char[DOTMATRIX_WIDTH]{0};

  MX_Display->begin();
  delay(50); // wait for reference voltage to stabilize

  Serial.println("Ready!");
}

void loop()
{
#ifdef DEBUG
  sampleMockSignal(vecReal, vecImag);
#else
  sampleAudioSignal(vecReal, vecImag);
#endif

  PerformFFT(FFT, vecReal, vecImag);
  DisplayFFT(MX_Display, currentDisplayMode, vecLastPeaks, MapToDisplaySize(vecReal));
}
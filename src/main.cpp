#include <Arduino.h>
#include <arduinoFFT.h>
#include <MD_MAX72xx.h>
#include <SPI.h>

#include "defines.h"
#include "display.h"
#include "FFT.h"

arduinoFFT* FFT;
MD_MAX72XX* MX_Display;

int currentDisplayMode;

#ifdef DEBUG
unsigned long timeout;
unsigned long timer;
bool printValues;
#endif

double* vecReal;
double* vecImag;
char* frequencyBucket;
char* vecLastPeaks;

#ifdef DEBUG
void PrintArray(char* aName, double* aArray, int aArraySize)
{
  Serial.print(aName);
  Serial.println(":");
  Serial.print("[");
  for (int i = 0; i < aArraySize; i++)
  {
    Serial.print(aArray[i]);
    if (i + 1 != aArraySize)
      Serial.print(", ");
  }
  Serial.print("]");
  Serial.println();
}

void PrintArray(char* aName, char* aArray, int aArraySize)
{
  Serial.print(aName);
  Serial.println(":");
  Serial.print("[");
  for (int i = 0; i < aArraySize; i++)
  {
    Serial.print((int)aArray[i]);
    if (i + 1 != aArraySize)
      Serial.print(", ");
  }
  Serial.print("]");
  Serial.println();
}
#endif

void setup()
{
  Serial.begin(115200);

  ADCSRA = 0b11100101; // set ADC to free running mode and set pre-scalar to 32 (0xe5)
  ADMUX = 0b00000000;  // use pin A0 and external voltage reference

  FFT = new arduinoFFT();
  MX_Display = new MD_MAX72XX(HARDWARE_TYPE, DATA_PIN, CLK_PIN, CS_PIN, DOTMATRIX_MAX_DEVICES);
  MX_Display->begin();
  currentDisplayMode = DISPLAY_MODE::STANDARD_BOTTOM_POINT;

  frequencyBucket = new char[DOTMATRIX_WIDTH] {0};
  vecLastPeaks = new char[DOTMATRIX_WIDTH] {0};

  vecReal = new double[SAMPLES] {0.f};
  vecImag = new double[SAMPLES] {0.f};

#ifdef DEBUG
  timer = 0;
  timeout = 10000;
  printValues = true;
#endif

  delay(10); // wait for reference voltage to stabilize

  Serial.println("Ready!");
}

void loop()
{
#ifdef DEBUG
  if (millis() > timeout + timer) {
    timer = millis();
    //Serial.println("Alive!");
    printValues = true;
  }
  else {
    printValues = false;
  }
#endif

#ifdef AUDIO_MOCK
  sampleMockSignal(vecReal, vecImag);
#else
  sampleAudioSignal(vecReal, vecImag);
#endif

#ifdef DEBUG
  if (printValues)
    PrintArray("Samples", vecReal, SAMPLES);
#endif

  PerformFFT(FFT, vecReal, vecImag);

#ifdef DEBUG
  if (printValues) {
    PrintArray("vecRealFFT", vecReal, SAMPLES);
    PrintArray("vecImagFFT", vecImag, SAMPLES);
  }
#endif

  MapToDisplaySize(frequencyBucket, vecReal);

#ifdef DEBUG
  if (printValues) 
    PrintArray("FrequencyBucket", frequencyBucket, DOTMATRIX_WIDTH);
#endif

  DisplayFFT(MX_Display, currentDisplayMode, vecLastPeaks, frequencyBucket);

#ifdef DEBUG
  if (printValues) {
    PrintArray("LastPeaks", vecLastPeaks, DOTMATRIX_WIDTH);
    PrintArray("Display", frequencyBucket, DOTMATRIX_WIDTH);
    Serial.println("===========================================================");
  }
#endif
}
#include "FFT.h"

void sampleAudioSignal(double* aVecReal, double* aVecIamg)
{
  for (size_t i = 0; i < SAMPLES; i++)
  {
    while (!(ADCSRA & 0x10))
    {
      // wait for ADC to complete current conversion ie ADIF bit set
    };

    ADCSRA = 0b11110101; // clear ADIF bit so that ADC can do next operation (0xf5)

    aVecReal[i] = (ADC - 512) / 8; // Read from ADC and subtract DC offset
    aVecIamg[i] = 0;               // no imaginary values needed
  }
}

void sampleMockSignal(double* aVecReal, double* aVecImag)
{
  /*
  int randomStart = random(500);
  int randomStep = random(45) + 1;
  int step = randomStart;
  for (size_t i = 0; i < SAMPLES; i++)
  {
    aVecReal[i] = constrain(256 * sin((1 / 500 * step) - randomStart) + 256 + random(256), 0, 1023);
    aVecImag[i] = 0.f;

    step += randomStep;
  }
  */
 
  double signalFrequency = 1000;
  double samplingFrequency = 9600;
  uint8_t amplitude = 255;

  //Number of signal cycles that the sampling will read
  double cycles = (((SAMPLES - 1) * signalFrequency) / samplingFrequency);
  for (uint16_t i = 0; i < SAMPLES; i++)
  {
    // Build data with positive and negative values
    aVecReal[i] = int8_t((amplitude * (sin((i * (twoPi * cycles)) / SAMPLES))) / 2.0);
    //Imaginary part must be zeroed in case of looping to avoid wrong calculations and overflows
    aVecImag[i] = 0.0;
  }
}

void PerformFFT(arduinoFFT* aFFT, double* aVecReal, double* aVecImag)
{
  aFFT->Windowing(aVecReal, SAMPLES, FFT_WIN_TYP_HAMMING, FFT_FORWARD);
  aFFT->Compute(aVecReal, aVecImag, SAMPLES, FFT_FORWARD);
  aFFT->ComplexToMagnitude(aVecReal, aVecImag, SAMPLES);
}
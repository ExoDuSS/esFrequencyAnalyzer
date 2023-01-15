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
  int randomStart = rand();
  for (size_t i = 0; i < SAMPLES; i++)
  {
    aVecReal[i] = constrain(256 * sin(1 / 500 * (randomStart + i)) + 256 + rand(), 0, 1023);
    aVecImag[i] = 0.f;
  }
}

void PerformFFT(arduinoFFT* aFFT, double* aVecReal, double* aVecImag)
{
  aFFT->Windowing(aVecReal, SAMPLES, FFT_WIN_TYP_HAMMING, FFT_FORWARD);
  aFFT->Compute(aVecReal, aVecImag, SAMPLES, FFT_FORWARD);
  aFFT->ComplexToMagnitude(aVecReal, aVecImag, SAMPLES);
}
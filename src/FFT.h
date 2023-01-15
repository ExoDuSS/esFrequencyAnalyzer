#ifndef FFT_H
#define FFT_H

#include <Arduino.h>
#include <arduinoFFT.h>
#include "defines.h"

void sampleAudioSignal(double* aVecReal, double* aVecIamg);
void sampleMockSignal(double* aVecReal, double* aVecImag);
void PerformFFT(arduinoFFT* aFFT, double* aVecReal, double* aVecImag);

#endif
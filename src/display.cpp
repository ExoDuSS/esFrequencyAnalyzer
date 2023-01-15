#include "display.h"

uint8_t GetDisplayValue(int aDisplayMode, int aIndex)
{
    return DISPLAY_MODES[aDisplayMode][aIndex];
}

void MapToDisplaySize(char* aFrequencyBucket, double* aVecReal)
{
    /*
    size_t step = 0;
    size_t stepSize = SAMPLES_HALF / DOTMATRIX_WIDTH;
    size_t sample_offset = 0;

    for (size_t i = 0; i < DOTMATRIX_WIDTH; i++)
    {
        char value = 0;
        for (step = 0; step < stepSize; step++)
        {
            value += aVecReal[sample_offset + step];
        }
        sample_offset += step + 1;
        //aFrequencyBucket[i] = constrain(value / step, 0, 8); // save as average over added values
        aFrequencyBucket[i] = value / step; // save as average over added values
    }
    */
    size_t step = SAMPLES_HALF / DOTMATRIX_WIDTH;
    size_t c = 0;
    for (size_t i = 0; i < SAMPLES_HALF; i += step)
    {
        aFrequencyBucket[c] = 0;
        for (size_t k = 0; k < step; k++) {
            aFrequencyBucket[c] += aVecReal[i + k];
        }
        aFrequencyBucket[c] /= step;
        c++;
    }
    
}

void DisplayFFT(MD_MAX72XX* aDisplay, int aDisplayMode, char* aPeaks, char* aFrequencyBucket)
{
    int valueY = 0;
    for (size_t i = 0; i <= DOTMATRIX_WIDTH; i++)
    {
        aFrequencyBucket[i] = constrain(aFrequencyBucket[i], 0, 80);                // calmap between 0 - 80
        aFrequencyBucket[i] = map(aFrequencyBucket[i], 0, 80, 0, DOTMATRIX_HEIGHT); // map to display height

        valueY = aFrequencyBucket[i];
        aPeaks[i] -= 1; // decay by one light

        if (valueY > aPeaks[i])
            aPeaks[i] = valueY;

        valueY = aPeaks[i];

        aDisplay->setColumn(DOTMATRIX_WIDTH - i, GetDisplayValue(aDisplayMode, valueY));
    }
}
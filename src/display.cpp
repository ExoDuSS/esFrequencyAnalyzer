#include "display.h"

uint8_t GetDisplayValue(int aDisplayMode, int aIndex)
{
    uint8_t bitMask = 0;
    switch (aDisplayMode)
    {
    case 1:
        bitMask = DISPLAY_MODE_1[aIndex];
        break;
    case 2:
        bitMask = DISPLAY_MODE_2[aIndex];
        break;
    case 3:
        bitMask = DISPLAY_MODE_3[aIndex];
        break;
    case 4:
        bitMask = DISPLAY_MODE_4[aIndex];
        break;
    case 5:
        bitMask = DISPLAY_MODE_5[aIndex];
        break;

    default:
        bitMask = DISPLAY_MODE_1[aIndex];
        break;
    }

    return bitMask;
}

char* MapToDisplaySize(double* aVecReal)
{
    size_t stepSize = SAMPLES_HALF / DOTMATRIX_WIDTH;
    size_t step = 0;
    size_t sample_offset = 0;

    char* frequencyBucket = new char[DOTMATRIX_WIDTH] {0};

    for (size_t i = 0; i < DOTMATRIX_WIDTH; i++)
    {
        char value = 0;
        for (step = 0; step < stepSize; step++)
        {
            value += aVecReal[sample_offset + step];
        }
        sample_offset += step + 1;

        frequencyBucket[i] = value / step; // save as average over added values
    }
    return frequencyBucket;
}

void DisplayFFT(MD_MAX72XX* aDisplay, int aDisplayMode, char* aPeaks, char* aData)
{
    int valueY = 0;
    for (size_t i = 0; i <= DOTMATRIX_WIDTH; i++)
    {
        aData[i] = constrain(aData[i], 0, 80);                // calmap between 0 - 80
        aData[i] = map(aData[i], 0, 80, 0, DOTMATRIX_HEIGHT); // map to display height

        valueY = aData[i];
        aPeaks[i] -= 1; // decay by one light

        if (valueY > aPeaks[i])
            aPeaks[i] = valueY;

        valueY = aPeaks[i];

        aDisplay->setColumn(DOTMATRIX_WIDTH - i, GetDisplayValue(aDisplayMode, valueY));
    }
}
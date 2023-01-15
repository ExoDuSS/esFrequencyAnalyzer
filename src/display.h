#ifndef DISPLAY_H
#define DISPLAY_H

#include <MD_MAX72xx.h>
#include "defines.h"

enum DISPLAY_MODE {
    STANDARD = 0,
    STANDARD_BOTTOM_POINT,
    ONLY_PEEKS,
    ONLY_PEEKS_BOTTOM_POINT,
    TOP_GAP,
    STANDARD_MIRRORED
};

const int DISPLAY_MODES[6][9] = {
    { 0b00000000, 0b10000000, 0b11000000, 0b11100000, 0b11110000, 0b11111000, 0b11111100, 0b11111110, 0b11111111 }, // standard pattern
    { 0b10000000, 0b10000000, 0b11000000, 0b11100000, 0b11110000, 0b11111000, 0b11111100, 0b11111110, 0b11111111 }, // standard pattern + bottom point
    { 0b00000000, 0b10000000, 0b01000000, 0b00100000, 0b00010000, 0b00001000, 0b00000100, 0b00000010, 0b00000001 }, // only peaks
    { 0b00000000, 0b10000000, 0b11000000, 0b10100000, 0b10010000, 0b10001000, 0b10000100, 0b10000010, 0b10000001 }, // only peaks + bottom point
    { 0b00000000, 0b10000000, 0b11000000, 0b10100000, 0b11010000, 0b11101000, 0b11110100, 0b11111010, 0b11111101 }, // one gap in the top , 3rd light onwards
    { 0b00000000, 0b00000001, 0b00000011, 0b00000111, 0b00001111, 0b00011111, 0b00111111, 0b01111111, 0b11111111 }  // standard pattern, mirrored vertically
};

uint8_t GetDisplayValue(int aDisplayMode, int aIndex);
void MapToDisplaySize(char* aFrequencyBucket, double* aVecReal);
void DisplayFFT(MD_MAX72XX* aDisplay, int aDisplayMode, char* aPeaks, char* aFrequencyBucket);


#endif
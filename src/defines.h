#ifndef DEFINES_H
#define DEFINES_H

// display related
#define HARDWARE_TYPE MD_MAX72XX::GENERIC_HW
#define CLK_PIN 13
#define DATA_PIN 11
#define CS_PIN 10

#define DOTMATRIX_MAX_DEVICES 2
#define DOTMATRIX_WIDTH 32
#define DOTMATRIX_HEIGHT 8

// audio related
#define SAMPLES 128 // needs to be power of 2
#define SAMPLES_HALF SAMPLES / 2

#ifdef DEBUG
#define RAND_MAX 1023
#endif

#endif
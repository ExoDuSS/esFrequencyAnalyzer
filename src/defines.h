#ifndef DEFINES_H
#define DEFINES_H

// display related
#define HARDWARE_TYPE MD_MAX72XX::FC16_HW
#define CLK_PIN 12
#define DATA_PIN 11
#define CS_PIN 10

#define DOTMATRIX_MAX_DEVICES 2
#define DOTMATRIX_WIDTH (DOTMATRIX_MAX_DEVICES * 8)
#define DOTMATRIX_HEIGHT 8

// audio related
#define SAMPLES 64 // needs to be power of 2
#define SAMPLES_HALF (SAMPLES / 2)

#endif
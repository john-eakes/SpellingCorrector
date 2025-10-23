/**This file declares some of the constant variables or functions used in 
 * the correction.c file
 *
 * @file correction.h
 * @author John Eakes
 */



#ifndef CORRECTION_H
#define CORRECTION_H

#include <stdbool.h>

#define WORD_LIMIT 20

// Function prototypes
void readCorrections();
bool findCorrection(char const target[WORD_LIMIT + 1], char replacement[WORD_LIMIT + 1]);

#endif

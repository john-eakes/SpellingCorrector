/**@file util.h
  *@author John Eakes
 *
 * This program defines the two methods to be used in util.c
 */

#ifndef UTIL_H
#define UTIL_H

// Function prototypes
void removeSubstr(char str[], int pos, int len);
void insertSubstr(char str[], int pos, char const substr[]);

#endif

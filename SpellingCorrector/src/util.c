/** @file util.c
 * @author John Eakes
 *
 * This program provides a baseline of two functions that either remove a
 * substring, or inserts into a substring
 */


#include "util.h"
#include <string.h>

/**Removes a bit of a string from the specified position, to the specified length of removal
 * 
 * @param str the string being removed from
 * @param pos the position that removal starts at
 * @param len the length of the substring that's being removed
 */
void removeSubstr(char str[], int pos, int len)
{
  //If removing from end, just terminate early
  int strLen = strlen(str);
  if(pos + len > strLen){
    len = strLen - pos;
  }

  if(len < 0){
    return;
  }

  //Regular case of removing the substring out of string
  for(int i = pos; i <= strLen - len; i++){
    str[i] = str[i + len];
  }
  str[strLen - len] = '\0';
}



/**Inserts a substring into a string from a specific position
 *
 * @param str the full string that's getting concatenated by the substring
 * @param pos the position that the substring is getting entered into
 * @param substr the substring being added into the string
 */
void insertSubstr(char str[], int pos, char const substr[])
{
  //Get lengths
  int strLen = strlen(str);
  int substrLen = strlen(substr);

  //Shift string chars right to make space for substring
  for(int i = strLen; i >= pos; i--){
    str[i + substrLen] = str[i];
  }

  //Inserting substring into the string
  for(int i = 0; i < substrLen; i++){
    str[pos + i] = substr[i];
  }
}

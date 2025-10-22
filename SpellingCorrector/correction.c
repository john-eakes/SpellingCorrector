/**This file is used to read the correction input and find the corrections
 * needed in the output file
 *
 * @file correction.c
 * @author John Eakes
 */

#include "correction.h"
#include <stdlib.h>
#include <stdio.h>
#include <string.h>
#include <ctype.h>

/** Maximum number of words on the correction list. */
#define CORRECTION_LIMIT 50000

/** Exit status for a bad correction list. */
#define INVALID_CLIST_STATUS 100


//Static vars for list
/** The list of targets(words that're commonly mispelled) */
static char targets[CORRECTION_LIMIT][WORD_LIMIT + 1];
/** The list of replacements(correct spelling of the target words) */
static char replacements[CORRECTION_LIMIT][WORD_LIMIT + 1];
/** The number of corrections in the target word input */
static int numCorrections = 0;


//Helper methods!!!
  
/**This function checks if the target word is a valid target word
 *
 * @param str the string being checked
 *
 */
static bool isValidTarget(const char *str)
{
  for(int i = 0; str[i]; i++){
    if(!(islower(str[i]) || str[i] == '\'')){
      return false;
    }
  }
  return true;
}
  
/**This function checks if the replacement word is a valid replacement word
 *
 * @param str the string being checked
 *
 */
static bool isValidReplacement(const char *str)
{
  for (int i = 0; str[i]; i++) {
        if (!(isalpha(str[i]) || str[i] == '\'')) {
            return false;
        }
    }
    return true;
}


/**This function reads in the correction input, which is a number (representing the number of target and replacement words),
 * then the actual target and replacement words!
 */
void readCorrections()
{
  //Read the NUMBER of corrections
  if(scanf("%d", &numCorrections) != 1){
    exit(INVALID_CLIST_STATUS);
  }
  if(numCorrections < 0 || numCorrections > CORRECTION_LIMIT){
    exit(INVALID_CLIST_STATUS);
  }

  // Read and discard the rest of the line after the number
  int c;
  while ((c = getchar()) != '\n' && c != EOF) {
    // Discard characters until newline
  }

  //Read the actual correction pair
  for(int i = 0; i < numCorrections; i++){
    // Use temporary buffers with extra space to detect overflow
    char tempTarget[WORD_LIMIT + 2];  // +2 to detect overflow
    char tempReplacement[WORD_LIMIT + 2];
    
    // Read words
    if(scanf("%21s %21s", tempTarget, tempReplacement) != 2){
      exit(INVALID_CLIST_STATUS);
    }
    
    // Check length constraints
    if(strlen(tempTarget) == 0 || strlen(tempTarget) > WORD_LIMIT){
      exit(INVALID_CLIST_STATUS);
    }
    if(strlen(tempReplacement) == 0 || strlen(tempReplacement) > WORD_LIMIT){
      exit(INVALID_CLIST_STATUS);
    }
    
    // Now, copy to the actual arrays
    strcpy(targets[i], tempTarget);
    strcpy(replacements[i], tempReplacement);
    
    // Read and discard the rest of the line after each pair
    while ((c = getchar()) != '\n' && c != EOF) {
      // Discard characters until newline
    }
    
    if(!isValidTarget(targets[i])){
      exit(INVALID_CLIST_STATUS);
    }
    if(!isValidReplacement(replacements[i])){
      exit(INVALID_CLIST_STATUS);
    }

    //Check if replacement matches any target
    for(int j = 0; j < i; j++){
      if(strcmp(replacements[i], targets[j]) == 0){
        exit(INVALID_CLIST_STATUS);
      }
    }
  }

  //Make sure that list is sorted
  for(int i = 1; i < numCorrections; i++){
    if(strcmp(targets[i - 1], targets[i]) >= 0){
      exit(INVALID_CLIST_STATUS);
    }
  }
}


/**This function finds the target words in the input paragraph
 * @param target the list of targets being checked
 * @param replacement the list of correctly spelled targets to replace with
 * @return true if found and false if not
 *
 */
bool findCorrection(char const target[WORD_LIMIT + 1], char replacement[WORD_LIMIT + 1])
{
  // Use binary search for the target
  int left = 0;
  int right = numCorrections - 1;
    
    while (left <= right) {
      int mid = left + (right - left) / 2;
      int cmp = strcmp(target, targets[mid]);
        
      if (cmp == 0) {
        strcpy(replacement, replacements[mid]);
	return true;
      } else if (cmp < 0) {
        right = mid - 1;
      } else {
        left = mid + 1;
      }
  }
    
  return false;
}


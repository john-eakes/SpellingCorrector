/**This file is the main file that puts all the other files and methods together to replace lal target words in the input paragraph
 * @file spellcheck.c
 * @author John Eakes
 */




#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <ctype.h>
#include <stdbool.h>
#include "util.h"
#include "correction.h"
/** The maximum character limit allowed in a line */
#define MAX_LINE_LENGTH 80
/** The function that checks if a character is part of a word */
static bool isWordChar(char c);
/** The function that capitalizes an entire word param */
static void capitalizeWord(char *word);
/** The function that processes a word to be used by the main function */
static void processWord(char *line, int start, int end, char *outputLine);

//Helper methods!
/**This function checks if a character is a letter or \.
 * @param c the character being checked
 * @return true if it is a letter and false if not
 */
static bool isWordChar(char c)
{
  return isalpha(c) || c == '\'';
}

/**This function capitalizes a  word that's passed in through the parameter
 * @param word the word being capitalized
 */
static void capitalizeWord(char *word)
{
  if(isalpha(word[0])){
      word[0] = toupper(word[0]);
  }
}

/**This function is used to process a word and see if it needs to be replaced for the output
 * @param line the line of test being passed in to check
 * @param start the starting index being checked
 * @param end the ending index being checked
 * @outputLine the line that's succesfully output with corrected words
 */
static void processWord(char *line, int start, int end, char *outputLine)
{
  // Extract the word
  int wordLen = end - start;
  
  // If word is too long to match any target, just copy it directly
  if (wordLen > WORD_LIMIT) {
    // Copy the long word directly to output
    for (int i = start; i < end; i++) {
      char ch[2] = {line[i], '\0'};
      strcat(outputLine, ch);
    }
    return;
  }
  
  char word[WORD_LIMIT + 1];
  char lowercaseWord[WORD_LIMIT + 1];
    
  strncpy(word, line + start, wordLen);
  word[wordLen] = '\0';
    
  // Create lowercase version for comparison
  strcpy(lowercaseWord, word);
  for (int i = 0; lowercaseWord[i]; i++) {
    lowercaseWord[i] = tolower(lowercaseWord[i]);
  }
    
  // Check if we need to correct this word
  char replacement[WORD_LIMIT + 1];
  if (findCorrection(lowercaseWord, replacement)) {
    // Check if original word was capitalized
    bool wasCapitalized = isupper(word[0]);
        
    if (wasCapitalized) {
      capitalizeWord(replacement);
    }
        
    strcat(outputLine, replacement);
  } else {
    // No correction needed, use original word
    strcat(outputLine, word);
  }
}

/**This is the main function that puts everything together to output a correctly spelled
 * output file based on the words that were passed in as targets
 * @return an exit status (int)
 */
int main()
{
  readCorrections();

  char line[MAX_LINE_LENGTH + 2];

  while(fgets(line, sizeof(line), stdin)){
    // Check if line is too long (including newline)
    int lineLen = strlen(line);
    if(lineLen > MAX_LINE_LENGTH + 1 || 
       (lineLen == MAX_LINE_LENGTH + 1 && line[MAX_LINE_LENGTH] != '\n')){
      exit(101);
    }

    // Remove newline character for processing
    if(lineLen > 0 && line[lineLen - 1] == '\n'){
      line[lineLen - 1] = '\0';
      lineLen--;
    }

    char outputLine[MAX_LINE_LENGTH * 2] = ""; // Initialize empty
    int wordStart = -1;

    for(int i = 0; i <= lineLen; i++){
      if(i < lineLen && isWordChar(line[i])){
        if(wordStart == -1){
          wordStart = i;
        }
      } else{
        if(wordStart != -1){
          processWord(line, wordStart, i, outputLine);
          wordStart = -1;
        }
        if(i < lineLen){
          // Add non-word character
          char nonWord[2] = {line[i], '\0'};
          strcat(outputLine, nonWord);
        }
      }
    }

    // Check output line length before printing
    int outputLen = strlen(outputLine);
    if(outputLen > MAX_LINE_LENGTH){
      exit(102);
    }

    // Print the line with newline
    printf("%s\n", outputLine);
  }
  return 0;
}

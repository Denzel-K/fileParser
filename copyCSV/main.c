#include <stdio.h>
#include <stdlib.h>
#include <string.h>

#define MAX_LINE_LENGTH 1024

int main(){
  FILE  *inputFile;
  FILE *outputFile;

  inputFile = fopen("input.csv", "r");
  outputFile = fopen("output.csv", "w");

  if(inputFile == NULL || outputFile == NULL){
    printf("Error opening file(s) !! \n");
    exit(0);
  }

  //Read from input file
  char line[MAX_LINE_LENGTH];

  while(fgets(line, MAX_LINE_LENGTH, inputFile)){
    char *token = strtok(line, ",");

    while (token != NULL){
      // Write the transformed number to the output file.
      fprintf(outputFile, "%s", token);

      /* Get next :

      After the first call to 'strtok', subsequent calls use NULL as the first argument, which tells the function to continue tokenizing the same string where it left off. It finds the next token after the first comma.
      */
      token = strtok(NULL, ",");

      if (token != NULL) {
        fprintf(outputFile, ",");
      }
    }

    // Newline after each line
    fprintf(outputFile, "\n");
  }

  fclose(inputFile);
  fclose(outputFile);

  return 0;
}
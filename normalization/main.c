#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <float.h>

#define MAX_LINE_LENGTH 1024

double normalize(double value, double min, double max){
  return (value - min) / (max - min);
}

int main(){
  FILE  *inputFile;
  FILE *outputFile;

  inputFile = fopen("population.csv", "r");
  outputFile = fopen("normalized_population.csv", "w");

   if (inputFile == NULL || outputFile == NULL) {
    printf("Error opening file.\n");
    return 1;
  }

  //Read from input file
  char line[MAX_LINE_LENGTH];

  double population, min_population = DBL_MAX, max_population = DBL_MIN;
  char city[100], country[100], header[MAX_LINE_LENGTH];

  // Read the header line and write it to the output file
  fgets(header, MAX_LINE_LENGTH, inputFile);
  fprintf(outputFile, "%s", header);

  // First pass: find the min and max population
  while(fgets(line, MAX_LINE_LENGTH, inputFile)){
    sscanf(line, "%[^,],%[^,],%lf", city, country, &population);

    if (population < min_population){
      min_population = population;
    }
    if (population > max_population){
      max_population = population;
    }
  }

  // Reset file pointer to beginning of file
  rewind(inputFile);
  fgets(header, MAX_LINE_LENGTH, inputFile);  // Skip header

  // Second pass: normalize population and write to the output file
  while (fgets(line, MAX_LINE_LENGTH, inputFile)) {
    sscanf(line, "%[^,],%[^,],%lf", city, country, &population);

    double normalized_population = normalize(population, min_population, max_population);

    // Write the normalized data to the output file
    fprintf(outputFile, "%s,%s,%.6lf\n", city, country, normalized_population);
  }

  fclose(inputFile);
  fclose(outputFile);

  printf("Data normalization complete. Output saved to 'normalized_population.csv'.\n");

  return 0;
}

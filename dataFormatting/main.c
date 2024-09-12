#include <stdio.h>
#include <stdlib.h>
#include <string.h>

#define MAX_LINE_LEN 1024
#define DATE_LEN 11  // YYYY-MM-DD\0

void format_date(const char *input_date, char *output_date) {
  // Extract year, month, day from YYYY-MM-DD
  int year, month, day;
  sscanf(input_date, "%4d-%2d-%2d", &year, &month, &day);

  // Format as MM/DD/YYYY
  sprintf(output_date, "%02d/%02d/%d", month, day, year);
}

int main() {
  FILE *inputFile = fopen("dates.csv", "r");
  FILE *outputFile = fopen("formatted_dates.csv", "w");

  if (inputFile == NULL || outputFile == NULL) {
      printf("Error opening file.\n");
      return 1;
  }

  char line[MAX_LINE_LEN];
  char name[100], date[DATE_LEN], formatted_date[11];
  char header[MAX_LINE_LEN];

  // Read the header line and write it to the output file
  fgets(header, MAX_LINE_LEN, inputFile);
  fprintf(outputFile, "%s", header);

  // Process each line
  while (fgets(line, MAX_LINE_LEN, inputFile)) {
      // Parse the name and date
      sscanf(line, "%[^,],%s", name, date);

      // Format the date
      format_date(date, formatted_date);
      
      // Write the name and formatted date to the output file
      fprintf(outputFile, "%s,%s\n", name, formatted_date);
  }

  fclose(inputFile);
  fclose(outputFile);

  printf("Date formatting complete. Output saved to 'formatted_dates.csv'.\n");

  return 0;
}

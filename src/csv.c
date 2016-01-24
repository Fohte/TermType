#include "csv.h"
#include <stdio.h>
#include <stdlib.h>
#include <string.h>

int linecount = 0;
char* csvfile;

result_t* csv2results()
{
  static result_t* results;

  FILE* fp;
  if ((fp = fopen(csvfile, "r")) == NULL) {
    return NULL;
  }

  results = (result_t*)malloc(sizeof(result_t) * linecount);

  for (int i = 0; i < linecount; i++) {
    fscanf(fp, "%d,%d,%f,%f,%f\n", &results[i].type_count, &results[i].typo_count, &results[i].time, &results[i].tps, &results[i].accuracy);
  }

  return results;
}

void init_csvrec_file(char* filename)
{
  csvfile = (char*)malloc(strlen(filename) + 1);
  strcpy(csvfile, filename);

  FILE* fp;
  if ((fp = fopen(csvfile, "r")) == NULL) {
    return;
  }

  linecount = 0;
  char text[256];
  while (fgets(text, sizeof(text), fp) != NULL) {
    linecount++;
  }
}

void csvrec_append(result_t result)
{
  FILE *fp;

  if ((fp = fopen(csvfile, "a")) == NULL) {
    return;
  }

  fprintf(fp, "%d,%d,%f,%.2f,%.3f\n", result.type_count, result.typo_count, result.time, result.tps, result.accuracy);
  linecount++;

  fclose(fp);
}

int get_csvrec_size()
{
  return linecount;
}

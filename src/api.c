#include <stdio.h>
#include <stdlib.h>
#include "api.h"

char* cachepath = "/tmp/termtype_cache";

irrec_t* api_record_get()
{
  static irrec_t records[100];
  /* records = (irrec_t *)malloc(sizeof(irrec_t) * 100); */

  char* curl;
  curl = (char *)malloc(256);
  sprintf(curl, "curl %s/api/data 1> %s 2> /dev/null", server_address, cachepath);
  system(curl);

  FILE* fp;
  fp = fopen(cachepath, "r");

  int i = 0;
  for (int i = 0; i < 100; i++) {
    if (fscanf(fp, "%[^,],%f\n", records[i].name, &records[i].tps) == EOF) {
      break;
    }
  }
  
  remove(cachepath);

  fclose(fp);

  return records;
}


void api_record_post(char* name, result_t result)
{
  char* curl;
  curl = (char *)malloc(256);
  sprintf(curl, "curl \"%s/api/data/new?name=%s&tps=%f\" 1> /dev/null 2> /dev/null", server_address, name, result.tps);
  system(curl);
}

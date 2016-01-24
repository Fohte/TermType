#ifndef API_H
#define API_H

#include "scene.h"

typedef struct {
  char name[11];
  float tps;
} irrec_t;

char* server_address;

irrec_t* api_record_get();
void api_record_post(char* name, result_t result);

#endif

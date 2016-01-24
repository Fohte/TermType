#ifndef CSV_H
#define CSV_H

#include "scene.h"

result_t* csv2results();
void init_csvrec_file(char* filename);
void csvrec_append(result_t result);
int get_csvrec_size();

#endif

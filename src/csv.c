#include <stdio.h>
#include <stdlib.h>
#include <string.h>

  typedef struct {
    int type_count;
    int typo_count;
    float tps;
    float accuracy;
  }score_t;
  int linecount;
  char* csvfile;

  score_t* csv2score(char* csv_score)
  {
    static score_t* scores;
    char* str;
    char* tmp;
    char* chr = "";
    char* position;
    int i;

    linecount = 1;
    for (i = 0; *(csv_score + i) != '\0'; i++) {
      if (*(csv_score + i) == '\n') linecount++;
    }
    scores = (score_t*)malloc(sizeof(score_t) * linecount);
    if ((position = strchr(csv_score, '\n')) == NULL) {
      sscanf(csv_score, "%d,%d,%f,%f", &scores->type_count, &scores->typo_count, &scores->tps, &scores->accuracy);
      return scores;
    }
    str = (char*)malloc(256);
    i = 0;
    strncpy(str, csv_score, position - csv_score);
    sscanf(str, "%d,%d,%f,%f", &(scores + i)->type_count, &(scores + i)->typo_count, &(scores + i)->tps, &(scores + i)->accuracy);
    i++;
    while (1) {
      chr = ++position;
      if ((position = strchr(chr, '\n')) == NULL) break;
      strncpy(str, chr, position - chr);
      sscanf(str, "%d,%d,%f,%f", &(scores + i)->type_count, &(scores + i)->typo_count, &(scores + i)->tps, &(scores + i)->accuracy);
      i++;
    }
    sscanf(chr, "%d,%d,%f,%f", &(scores + i)->type_count, &(scores + i)->typo_count, &(scores + i)->tps, &(scores + i)->accuracy);

    return scores;
  }

  void init_csvrec_file(char* filename) {
    csvfile = (char*)malloc(strlen(filename) + 1);
    strcpy(csvfile,filename);
  }

  void csvrec_append(score_t* score) {
    FILE *fp;
    char* s;
    s = (char*)malloc(256);
    sprintf(s, "%d,%d,%.2f,%.2f", score->type_count, score->typo_count, score->tps, score->accuracy);
    fp = fopen(csvfile, "a");
    fprintf(fp, "%s", s);
    fclose(fp);
  }

  int get_csvrec_size() {
    return linecount;
  }

  int main()
  {
    return 0;
  }
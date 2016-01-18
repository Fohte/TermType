#include "word.h"
#include <stdio.h>
#include <string.h>
#include <stdbool.h>
#include <stdlib.h>
#include <unistd.h>
#include <sys/time.h>

int random_range(int min, int max)
{
  static bool is_created_seed = false;

  if (!is_created_seed) {
    srand((unsigned int)time(NULL));
    is_created_seed = true;
  }

  return min + (int)(rand() * (max - min + 1.0) / (1.0 + RAND_MAX));
}

char** all_typing_words;
int typing_words_count = 0;

void init_typing_words(char* filename)
{
  FILE *fp;
  char word[256];
  int i = 0;

  if ((fp = fopen(filename, "r")) == NULL) {
    return;
  }

  while (fgets(word, sizeof(word), fp) != NULL) {
    typing_words_count++;
  }

  rewind(fp);

  all_typing_words = (char **)malloc(typing_words_count * 256);
  for (int i = 0; i < typing_words_count; i++) {
    all_typing_words[i] = (char *)malloc(256);
    fscanf(fp, "%s", all_typing_words[i]);
  }

  fclose(fp);
}

char** get_typing_words(int num)
{
  static char** typing_words;

  typing_words = (char **)malloc(num * 256);
  for (int i = 0; i < num; i++) {
    typing_words[i] = (char *)malloc(256);
  }

  for (int i = 0; i < num; i++) {
    strcpy(typing_words[i], all_typing_words[random_range(0, typing_words_count)]);
  }

  return typing_words;
}

#include "scene.h"
#include "word.h"
#include <stdlib.h>
#include <unistd.h>
#include <sys/time.h>
#include <stdbool.h>

const char* START_MSG = "Press the Space Key";
char* type_string;
int VIEW_TYPE_STRING_NUM = 30;

int TYPING_TEXTS_NUM = 20;
char** typing_texts;

result_t result;


void concat_typing_texts()
{
  int size = TYPING_TEXTS_NUM - 1; // 空白文字数
  for (int i = 0; i < TYPING_TEXTS_NUM; i++) {
    size += strlen(typing_texts[i]);
  }

  type_string = (char *)malloc(size + 1);

  for (int i = 0; i < TYPING_TEXTS_NUM; i++) {
    strcat(type_string, typing_texts[i]);

    if (i + 1 != TYPING_TEXTS_NUM) {
      strcat(type_string, " ");
    }
  }

  *(type_string + size) = '\0';
}

char* strlshift(char* str, int n)
{
  int len = strlen(str);

  char* new_str = (char *)malloc(len + 1);
  for (int i = 0; i <= len; i++) {
    if (i - n < 0)
      continue;

    if (*(str + i) == '\0') {
      *(new_str + i - n) = '\0';
      break;
    }
    *(new_str + i - n) = *(str + i);
  }

  return new_str;
}

void countdown(int count)
{
  char count_str[10];

  while (count > 0) {
    sprintf(count_str, "%d", count);

    wclear(current_window);
    mvwprintw(current_window, LINES / 2, (COLS - strlen(count_str)) / 2, count_str);
    wrefresh(current_window);
    sleep(1);

    count--;
  }
}

void game()
{
  struct timeval start_timeval;
  struct timeval end_timeval;
  float time_seconds;
  int c;
  char view_type_string[VIEW_TYPE_STRING_NUM + 1];
  int typecursor_x = (COLS - VIEW_TYPE_STRING_NUM) / 2;
  int length;

  concat_typing_texts();
  length = strlen(type_string);

  wclear(current_window);
  // いろいろUI表示する
  wrefresh(current_window);

  gettimeofday(&start_timeval, NULL);

  int i = 0;
  int type_correct_count = 0;

  strncpy(view_type_string, type_string, VIEW_TYPE_STRING_NUM);
  view_type_string[VIEW_TYPE_STRING_NUM] = '\0';

  mvwprintw(current_window, LINES / 2, typecursor_x, view_type_string);
  mvwprintw(current_window, LINES / 2 + 1, typecursor_x, "*");
  wrefresh(current_window);

  result.type_count = 0;
  result.typo_count = 0;

  while (type_correct_count != length && (c = getch()) != 27) {
    result.type_count++;

    if (c == (int)type_string[0]) {
      type_string = strlshift(type_string, 1);
      strcpy(view_type_string, "");
      strncpy(view_type_string, type_string, VIEW_TYPE_STRING_NUM);
      view_type_string[VIEW_TYPE_STRING_NUM] = '\0';

      wmove(current_window, LINES / 2, 0);
      wclrtoeol(current_window);
      mvwprintw(current_window, LINES / 2, typecursor_x, view_type_string);
      type_correct_count++;
      mvwprintw(current_window, 1, 1, "o");
    } else {
      result.typo_count++;
      mvwprintw(current_window, 1, 1, "x");
    }

    wrefresh(current_window);
  }

  gettimeofday(&end_timeval, NULL);

  result.time = (end_timeval.tv_sec - start_timeval.tv_sec)
    + (end_timeval.tv_usec - start_timeval.tv_usec) / 1000000.0;

  free(type_string);

  result.tps = (result.type_count - result.typo_count) / result.time;
  result.accuracy = (result.type_count - result.typo_count) / (float)result.type_count;
}

void scene_typing()
{
  current_window = newwin(LINES, COLS, 0, 0);

  typing_texts = get_typing_words(TYPING_TEXTS_NUM);

  /* mvwprintw(current_window, 0, 0, typing_texts[0]); */

  mvwprintw(current_window, LINES / 2, (COLS - strlen(START_MSG)) / 2, START_MSG);
  wrefresh(current_window);

  while (getch() != ' ') { }

  countdown(3);

  game();

  delwin(current_window);
  scene_result(result);
}

#include "scene.h"
#include "csv.h"
#include "api.h"
#include <string.h>

const char question_text[] = "Enter your name.";

void scene_result(result_t result)
{
  current_window = newwin(LINES, COLS, 0, 0);

  mvwprintw(current_window, 0, 0, "Type: %d Correct, %d Miss", result.type_count - result.typo_count, result.typo_count);
  mvwprintw(current_window, 1, 0, "TPS: %.2f", result.tps);
  mvwprintw(current_window, 2, 0, "Time: %.2fsec", result.time);
  mvwprintw(current_window, 3, 0, "Accuracy: %.1f%%", result.accuracy * 100);

  int begin_x = (2 + strlen(question_text) + 4 + 10 + 1) / 2;
  mvwprintw(current_window, LINES / 4 * 3, begin_x, "* %s > [          ]", question_text);

  wrefresh(current_window);

  echo();
  curs_set(1);

  char name[11];
  mvwgetnstr(current_window, LINES / 4 * 3, begin_x + 2 + strlen(question_text) + 4, name, 10);

  noecho();
  curs_set(0);

  csvrec_append(result);
  api_record_post(name, result);

  delwin(current_window);
}

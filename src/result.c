#include "scene.h"

void scene_result(result_t result)
{
  current_window = newwin(LINES, COLS, 0, 0);

  mvwprintw(current_window, 0, 0, "tps: %3.2f, %3.1f\%", result.tps, result.accuracy*100);
  wrefresh(current_window);

  while (getch() != '\n') { }

  delwin(current_window);
}

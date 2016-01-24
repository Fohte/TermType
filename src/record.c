#include "scene.h"
#include "csv.h"

record_t record_get(result_t* results, int results_size)
{
  record_t record = {0};

  for (int i = 0; i < results_size; i++) {
    record.total_types += results[i].type_count;
    record.total_practice++;

    if (i == 0)
      record.best_tps = results[0].tps;

    if (i != 0 && record.best_tps < results[i].tps)
      record.best_tps = results[i].tps;

    record.accuracy += results[i].accuracy;
  }

  record.accuracy /= (float)record.total_practice;

  return record;
}

void scene_record()
{
  current_window = newwin(LINES, COLS, 0, 0);

  result_t* results = csv2results();
  record_t record = record_get(results, get_csvrec_size());

  mvwprintw(current_window, 0, 0, "Practice Count: %d", record.total_practice);
  mvwprintw(current_window, 1, 0, "Type Count: %d", record.total_types);
  mvwprintw(current_window, 2, 0, "Best TPS: %.2f", record.best_tps);
  mvwprintw(current_window, 3, 0, "Average Accuracy: %.1f%%", record.accuracy * 100);
  wrefresh(current_window);

  while (getch() != '\n') { }

  delwin(current_window);

}

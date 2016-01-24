#include "scene.h"
#include "api.h"

int scroll_count = 0;
irrec_t* records;

void echo_records()
{
  if (scroll_count < 0) {
    scroll_count = 0;
    return;
  }

  if (scroll_count > 100 - LINES) {
    scroll_count = 100 - LINES;
    return;
  }

  wmove(current_window, 0, 0);
  wclrtobot(current_window);

  for (int i = scroll_count; i < scroll_count + LINES && i < 100; i++) {
    wmove(current_window, i - scroll_count, 0);
    wprintw(current_window, "%3d: %-10s %.2ftps", i+1, records[i].name, records[i].tps);
  }
  wrefresh(current_window);
}

void scene_ir()
{
  current_window = newwin(LINES, COLS, 0, 0);

  int ch;

  records = api_record_get();
  echo_records();

  while ((ch = getch()) != 'q') {
    switch (ch) {
    case KEY_DOWN:
    case 'j':
    case 's':
      scroll_count++;
      echo_records();
      break;

    case KEY_UP:
    case 'k':
    case 'w':
      scroll_count--;
      echo_records();
      break;
    }
  }

  delwin(current_window);
}

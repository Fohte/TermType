#include <stdlib.h>
#include <ncurses.h>
#include "csv.h"
#include "word.h"
#include "scene.h"
#include "api.h"

void setting()
{
  curs_set(0); // カーソル非表示
  cbreak();
  noecho();
  keypad(stdscr, TRUE);
}

int main(int argc, char** argv)
{
  server_address = argv[1];
  current_window = initscr();

  setting();

  init_typing_words("resources/en/words");
  init_csvrec_file("data/record.csv");

  scene_menu();

  endwin();
  return EXIT_SUCCESS;
}

#include <stdlib.h>
#include <ncurses.h>
#include "word.h"
#include "scene.h"

void setting()
{
  curs_set(0); // カーソル非表示
  cbreak();
  noecho();
  keypad(stdscr, TRUE);
}

int main()
{
  current_window = initscr();

  setting();
  
  init_typing_words("resources/en/words");

  scene_menu();

  endwin();
  return EXIT_SUCCESS;
}

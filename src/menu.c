#include "scene.h"

WINDOW* menu_window;
int begin_x;
int begin_y;

struct menu_t {
  char* text;
  bool is_select;
};

struct menu_t menu_items[] = {
  {"Typing", true},
  {"My Records", false},
  {"Internet Ranking", false},
  {"Exit", false}
};
int menu_items_size = sizeof(menu_items) / sizeof(struct menu_t);

int getmaxlen()
{
  int max_length = 0;
  int length;

  for (int i = 0; i < menu_items_size; i++) {
    length = strlen(menu_items[i].text);

    if (max_length < length) {
      max_length = length;
    }
  }

  return max_length;
}

void echo_menu()
{
  for (int i = 0; i < menu_items_size; i++) {
    move(
        begin_y + i * 2,
        begin_x + 2
    );
    printw(menu_items[i].text);
  }
}

int get_selected_menu_index()
{
  for (int i = 0; i < menu_items_size; i++) {
    if (menu_items[i].is_select == true)
      return i;
  }
 
  return -1;
}

void change_selected_menu(int diff)
{
  int index = get_selected_menu_index();

  move(begin_y + index * 2, begin_x);
  printw(" ");
  menu_items[index].is_select = false;

  move(begin_y + (index + diff) * 2, begin_x);
  printw("*");
  menu_items[index + diff].is_select = true;
}

void scene_menu()
{
  int ch;
  bool do_exit = false;

  int line_count = menu_items_size + (menu_items_size - 1);

  menu_window = current_window;

  begin_x = (COLS - getmaxlen()) /2;
  begin_y = (LINES - line_count) / 2;

  echo_menu();

  change_selected_menu(0);

  while (!do_exit && (ch = getch()) != 'q') {
    switch (ch) {
    case KEY_DOWN:
    case 'j':
    case 's':
      if (get_selected_menu_index() < menu_items_size - 1) {
        change_selected_menu(1);
      }
      break;

    case KEY_UP:
    case 'k':
    case 'w':
      if (get_selected_menu_index() > 0) {
        change_selected_menu(-1);
      }
      break;

    case KEY_RIGHT:
    case 'd':
    case 'l':
    case '\n':
    case '\r':
      switch (get_selected_menu_index()) {
      case 0:
        scene_typing();
        break;

      case 1:
        break;

      case 2:
        scene_ir();
        break;

      case 3:
        do_exit = true;
        break;
      }
      current_window = menu_window;
      mvwin(current_window, 0, 0);

      break;
    }
  }
}

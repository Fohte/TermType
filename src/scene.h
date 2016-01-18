#ifndef SCENE_H
#define SCENE_H

#include <stdio.h>
#include <ncurses.h>
#include <string.h>

WINDOW* current_window;

typedef struct {
  int type_count;
  int typo_count;
  float time;
  float tps;
  float accuracy;
} result_t;

typedef struct {
  int total_practice;
  int total_types;
  float best_tps;
  float accuracy;
} record_t;

void scene_login();
void scene_menu();
void scene_typing();
void scene_result(result_t);
void scene_record();
void scene_ir();
void scene_help();

#endif

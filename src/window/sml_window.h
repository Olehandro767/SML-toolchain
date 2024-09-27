#ifndef SML_WINDOW_H
#define SML_WINDOW_H
#include "stdbool.h"

typedef struct {
  const char *title;
  const char *iconPath;
  int width;
  int height;
  int min_width;
  int min_height;
  int window_pos_x;
  int window_pos_y;
  bool borderless;
} sml_window_properties;

sml_window_properties sml_init_window_properties(unsigned int width,
                                                 unsigned int height,
                                                 char *title);

void *sml_create_simple_window(unsigned int width, unsigned int height,
                               char *title);

void *sml_open_window(sml_window_properties properties);

void *sml_just_open_window(char *title);

void sml_close_window(void *sml_context);

#endif /* SML_WINDOW_H */

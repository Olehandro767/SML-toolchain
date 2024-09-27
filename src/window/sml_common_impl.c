#include "../media/screen/sml_screen.h"
#include "sml_window.h"
#include "stdlib.h"

sml_window_properties sml_init_window_properties(unsigned int width,
                                                 unsigned int height,
                                                 const_string title) {
  sml_window_properties properties;
  properties.title = title;
  properties.width = width;
  properties.height = height;
  properties.icon_path = NULL;
  properties.min_width = width / 2;
  properties.min_height = height / 2;
  properties.window_pos_x = -1;
  properties.window_pos_y = -1;
  properties.borderless = false;
  return properties;
}

void *sml_create_simple_window(unsigned int width, unsigned int height,
                               const_string title) {
  sml_window_properties properties =
      sml_init_window_properties(width, height, title);
  return sml_open_window(properties);
}

void *sml_just_open_window(const_string title) {
  sml_screen_resolution resolution = sml_get_screen_resilution();
  return sml_create_simple_window(resolution.width, resolution.height, title);
}

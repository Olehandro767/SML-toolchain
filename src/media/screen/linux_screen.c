#include "sml_screen.h"
#include "stdio.h"
#include "stdlib.h"
#include "string.h"

sml_screen_resolution sml_get_screen_resilution() {
  char *array[8];
  char screen_size[64];
  FILE *cmd = popen("xdpyinfo | awk '/dimensions/ {print $2}'", "r");

  if (!cmd) {
    exit(1);
  }

  while (fgets(screen_size, sizeof(screen_size), cmd) != NULL)
    ;
  pclose(cmd);

  char *token = strtok(screen_size, "x\n");

  if (!token) {
    exit(1);
  }

  for (unsigned short i = 0; token != NULL; ++i) {
    array[i] = token;
    token = strtok(NULL, "x\n");
  }

  sml_screen_resolution screen_resolution;
  screen_resolution.width = atoi(array[0]);
  screen_resolution.height = atoi(array[1]);
  return screen_resolution;
}

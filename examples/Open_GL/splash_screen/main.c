#include "window/sml_window.h"
#include <unistd.h>

int main() {
  // TODO
  void* ctx_ptr = sml_just_open_window("Test Window");
  sleep(3);
  return sml_close_window(ctx_ptr);
}

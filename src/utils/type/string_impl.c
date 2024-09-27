#include "smp_string.h"
#include <string.h>

unsigned int smp_string_length(string str) { return strlen(str); }

bool smp_strings_are_equal(string str1, string str2) {
  return strcmp(str1, str2) == 0;
}

bool smp_string_is_empty(string str) {
  return str != NULL && smp_string_length(str) == 0;
}

bool smp_string_is_not_empty(string str) {
  return str != NULL && smp_string_length(str) > 0;
}

#ifndef SML_H
#define SML_H
#include <stdbool.h>

typedef char *string;
typedef const char *const_string;

unsigned int smp_string_length(string str);

bool smp_strings_are_equal(string str1, string str2);

bool smp_string_is_empty(string str);

bool smp_string_is_not_empty(string str);

#endif /* SML_H */

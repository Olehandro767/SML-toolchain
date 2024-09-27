#ifndef SML_UTILS_ASYNC_H
#define SML_UTILS_ASYNC_H

typedef struct {
  void *args;
  void (*rootine)(void *);
} sml_async_void_context;

typedef struct {
  void *args;
  void *yield;
  void *(*rootine)(void *);
} sml_async_context;

void sml_just_run_async(void (*rootine)(void *), void *args);

void *sml_run_async(void *(*rootine)(void *), void *args);

#endif /* SML_UTILS_ASYNC_H */

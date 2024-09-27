#include "pthread.h"
#include "sml_async.h"

void sml_just_run_async(void *(*rootine)(void *), void *args) {
  pthread_t thread_id;
  pthread_create(&thread_id, NULL, rootine, args);
  pthread_join(thread_id, NULL);
}

void *sml_run_async(void *(*rootine)(void *), void *args) {
  pthread_t thread_id;
  sml_async_context async_context;
  async_context.args = args;
  pthread_create(&thread_id, NULL, rootine, &async_context);
  pthread_join(thread_id, NULL);

  return async_context.yield;
}

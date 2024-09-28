#include "sml_async.h"
#include <pthread.h>

void *_just_run_async(void *args) {
  sml_async_void_context async_context = (*(sml_async_void_context *)args);
  async_context.rootine(async_context.args);
  return NULL;
}

void *_run_async(void *args) {
  sml_async_context async_context = (*(sml_async_context *)args);
  async_context.yield = async_context.rootine(async_context.args);
  return NULL;
}

void sml_await_operation(sml_operation_ptr ptr) {
  pthread_t thread_id = (*(pthread_t *)ptr.native_data_ptr);
  pthread_join(thread_id, NULL);
}

sml_operation_ptr sml_just_run_async(void (*rootine)(void *), void *args) {
  pthread_t thread_id;
  sml_operation_ptr pthread_ptr;
  pthread_ptr.native_data_ptr = &thread_id;
  sml_async_void_context async_context;
  async_context.args = args;
  async_context.rootine = rootine;
  pthread_create(&thread_id, NULL, _just_run_async, args);

  return pthread_ptr;
}

void sml_run_async_and_await(void (*rootine)(void *), void *args) {
  pthread_t thread_id;
  sml_async_void_context async_context;
  async_context.args = args;
  async_context.rootine = rootine;
  pthread_create(&thread_id, NULL, _just_run_async, args);
  pthread_join(thread_id, NULL);
}

void *sml_run_async_and_await_data(void *(*rootine)(void *), void *args) {
  pthread_t thread_id;
  sml_async_context async_context;
  async_context.args = args;
  async_context.rootine = rootine;
  pthread_create(&thread_id, NULL, _run_async, &async_context);
  pthread_join(thread_id, NULL);

  return async_context.yield;
}

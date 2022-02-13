#include <pthread.h>
#include "zend_API.h"

#if defined(DEBUG)
// https://stackoverflow.com/questions/77005/how-to-automatically-generate-a-stacktrace-when-my-program-crashes

#include <stdio.h>
#include <execinfo.h>
#include <signal.h>
#include <stdlib.h>
#include <unistd.h>

void handler(int sig) {
  void *array[10];
  size_t size;

  size = backtrace(array, 10);

  fprintf(stderr, "Error: signal %d:\n", sig);
  backtrace_symbols_fd(array, size, STDERR_FILENO);
  exit(1);
}
#endif

typedef void (*_phpthread_function)();

typedef struct _phpthread {
    int index;
    pthread_t thread;
    ZEND_API _phpthread_function function;
} phpthread;

phpthread *phpthreads = (phpthread *)malloc(10 * sizeof(phpthread));
int phpthread_index = 0;

void *pthread_function( void *ptr ) {
    int index = *(int*)ptr;
    phpthreads[index].function();

    return ptr;
}

extern "C" void phpthread_create(_phpthread_function function) {

#if defined(DEBUG)
  signal(SIGSEGV, handler);
#endif

  phpthreads[phpthread_index].index = phpthread_index;
  phpthreads[phpthread_index].function = function;

  pthread_create( &phpthreads[phpthread_index].thread, NULL, pthread_function, (void*)&phpthreads[phpthread_index].index);

  phpthread_index++;
}

extern "C" void phpthread_join() {
     for(int index = 0; index < phpthread_index; index ++) {
        pthread_join(phpthreads[index].thread, NULL);
     }
}

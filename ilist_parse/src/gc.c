#include "gc.h"
#include <stdlib.h>

void* gc_alloc_vo(unsigned int size)
{
  return malloc(size);
}

void gc_free(void *p)
{
  free(p);
}

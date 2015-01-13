#include <ctype.h>
#include <assert.h>
#include <string.h>
#include "gc.h"
#include "ilist_parse.h"

static void enlarge_int_vec(int **int_vec_ptr, uint32 cur_vec_size)
{
    const uint32 INT_VEC_ENLARGE_SIZE = 8;

    if (cur_vec_size%INT_VEC_ENLARGE_SIZE == 0) {
      /* Need enlarge to accomodate more integers */

      const uint32 new_vec_size = cur_vec_size + INT_VEC_ENLARGE_SIZE;
      int *int_new_vec = gc_alloc_vo(new_vec_size * sizeof(int));
      if (int_new_vec == NULL) {
        if (*int_vec_ptr != NULL) {
	  gc_free(*int_vec_ptr);
          *int_vec_ptr = NULL;
	}
	return;
      }

      memset(int_new_vec, 0, new_vec_size * sizeof(int));
      if (*int_vec_ptr != NULL) {
        assert(cur_vec_size > 0);
        memcpy(int_new_vec, *int_vec_ptr, cur_vec_size * sizeof(int));
        gc_free(*int_vec_ptr);
      }

      *int_vec_ptr = int_new_vec;
    }
}

int parse_ilist_str(int **int_vec_ptr, uint32 *vec_size_ptr, const char *str)
{
    int state = 0;  /* state machine start state is 0  */
    int *p = NULL;
    uint32 i = 0;

    if (int_vec_ptr == NULL || vec_size_ptr == NULL || str == NULL) {
      return -1;
    }

    /* match the int_vec state machine until '\0' */
    while (*str) {
      switch (state) {
      case 0:
	if (*str == ' ') {
	  break;
	}
	else if (*str=='+' || *str=='-' || isdigit(*str)) {
	  state = (isdigit(*str)) ? 2 : 1;
	  enlarge_int_vec(&p, i);
	  if (p == NULL) {
	    return -2;
	  }

	  p[i++] = atoi((char *)str);
	  break;
	}
	else goto mismatch;

      case 1:
	if (isdigit(*str)) {
	  state = 2;
	  break;
	}
	else goto mismatch;

      case 2:
	if (isdigit(*str)) {
	  break;
	}
	else if (',' == *str) {
	  state = 0;
	  break;
	}
	else if (' ' == *str) {
	  state = 3;
	  break;
	}
	else goto mismatch;

      case 3:
	if (' ' == *str) {
	  break;
	}
	else if (',' == *str) {
	  state = 0;
	  break;
	}
	else goto mismatch;


      /* default impossible */
      }

      str++;
    }
    
    if (state==2 || state==3) {
      *int_vec_ptr = p;
      *vec_size_ptr = i;

      return 0;
    }

 mismatch:
    if (p != NULL) {
      gc_free(p);
      p = NULL;
      i = 0;
    }
    return -1;
}

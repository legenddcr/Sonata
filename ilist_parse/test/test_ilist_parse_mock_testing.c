#include "ilist_parse.h"
#include "unity.h"
#include "Mockgc.h"

static int *p;
static uint32 i;

void setUp(void)
{
  p = NULL;
  i = 0;
}

void tearDown(void)
{
  if (p != NULL) {
    free(p);
    p = NULL;
    i = 0;
  }
}

void test_call_gc_alloc_vo_ShouldReturnNULL1(void)
{
  gc_alloc_vo_ExpectAndReturn(32, NULL); /*first 8 int slots for vec*/
  TEST_ASSERT_EQUAL(-2, parse_ilist_str(&p, &i, "123"));
}

void test_call_gc_alloc_vo_ShouldReturnNull2(void)
{
  int temp[32] = {0};
  gc_alloc_vo_ExpectAndReturn(32, temp);
  gc_alloc_vo_ExpectAndReturn(64, NULL);
  gc_free_Expect(temp);
  TEST_ASSERT_EQUAL(-2, parse_ilist_str(&p, &i, "1,2,3,4,5,6,7,8,9,10,11,12"));
}


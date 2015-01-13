#include "ilist_parse.h"
#include "unity.h"

static int *p;
uint32 i;

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

void test_validate_ilist_str_ShouldRetrunInvalidParameterIfNullArg(void)
{
  const char *s = "1,2,3";
  TEST_ASSERT_EQUAL(-1, parse_ilist_str(&p, &i, NULL));
  TEST_ASSERT_EQUAL(-1, parse_ilist_str(NULL, &i, s));
  TEST_ASSERT_EQUAL(-1, parse_ilist_str(&p, NULL, s));
}

void test_parse_ilist_str_ShouldReturnInvalidParameterIfSignStr(void)
{
  TEST_ASSERT_EQUAL(-1, parse_ilist_str(&p, &i, "+"));
  TEST_ASSERT_EQUAL(-1, parse_ilist_str(&p, &i, "-"));
  TEST_ASSERT_EQUAL(-1, parse_ilist_str(&p, &i, "+ 7"));
}

void test_parse_ilist_str_ShouldReturnZeroIfInvalidDigit(void)
{
  TEST_ASSERT_EQUAL(-1, parse_ilist_str(&p, &i, " -100  , -5467 , 987 a"));
  TEST_ASSERT_EQUAL(-1, parse_ilist_str(&p, &i, "a"));
  TEST_ASSERT_EQUAL(-1, parse_ilist_str(&p, &i, "7a"));
  TEST_ASSERT_EQUAL(-1, parse_ilist_str(&p, &i, " "));
}

void test_parse_ilist_ShouldReturnZeroForSpaceStrNum1(void)
{
  TEST_ASSERT_EQUAL(0, parse_ilist_str(&p, &i, " 0"));
  TEST_ASSERT_EQUAL(1, i);
  TEST_ASSERT_EQUAL(0, p[0]);
}

void test_parse_ilist_ShouldReturnZeroForSpaceStrNum2(void)
{
  TEST_ASSERT_EQUAL(0, parse_ilist_str(&p, &i, "0 "));
  TEST_ASSERT_EQUAL(1, i);
  TEST_ASSERT_EQUAL(0, p[0]);
}

void test_parse_ilist_ShouldReturnZeroForSpaceStrNum3(void)
{
  TEST_ASSERT_EQUAL(0, parse_ilist_str(&p, &i, " 0 "));
  TEST_ASSERT_EQUAL(1, i);
  TEST_ASSERT_EQUAL(0, p[0]);
}

void test_parse_ilist_ShouldReturnZeroForSpaceStrNum4(void)
{
  TEST_ASSERT_EQUAL(0, parse_ilist_str(&p, &i, "0, 1"));
  TEST_ASSERT_EQUAL(2, i);
  TEST_ASSERT_EQUAL(0, p[0]);
  TEST_ASSERT_EQUAL(1, p[1]);
}

void test_parse_ilist_ShouldReturnZeroForSpaceStrNum5(void)
{
  TEST_ASSERT_EQUAL(0, parse_ilist_str(&p, &i, "0,1 "));
  TEST_ASSERT_EQUAL(2, i);
  TEST_ASSERT_EQUAL(0, p[0]);
}

void test_parse_ilist_str_ShouldReturnOneForOneInt1(void)
{
  TEST_ASSERT_EQUAL(0, parse_ilist_str(&p, &i, "0"));
  TEST_ASSERT_EQUAL(1, i);
  TEST_ASSERT_EQUAL(0, p[0]);
}

void test_parse_ilist_str_ShouldReturnOneForOneInt2(void)
{
  TEST_ASSERT_EQUAL(0, parse_ilist_str(&p, &i, "10"));
  TEST_ASSERT_EQUAL(1, i);
  TEST_ASSERT_EQUAL(10, p[0]);
}

void test_parse_ilist_str_ShouldReturnOneForOneMaxInt32(void)
{
  TEST_ASSERT_EQUAL(0, parse_ilist_str(&p, &i, "2147483647"));
  TEST_ASSERT_EQUAL(1, i);
  TEST_ASSERT_EQUAL(2147483647, p[0]);
}

void test_parse_ilist_str_ShouldReturnOneForOneMinInt32(void)
{
  TEST_ASSERT_EQUAL(0, parse_ilist_str(&p, &i, "-2147483648"));
  TEST_ASSERT_EQUAL(1, i);
  TEST_ASSERT_EQUAL(-2147483647-1, p[0]);
}

void test_parse_ilist_str_ShouldReturnOneForTwoInt1(void)
{
  TEST_ASSERT_EQUAL(0, parse_ilist_str(&p, &i, "0,1"));
  TEST_ASSERT_EQUAL(2, i);
  TEST_ASSERT_EQUAL(0, p[0]);
  TEST_ASSERT_EQUAL(1, p[1]);
}

void test_parse_ilist_str_ShouldReturnOneForTwoInt2(void)
{
  TEST_ASSERT_EQUAL(0, parse_ilist_str(&p, &i, "10,1"));
  TEST_ASSERT_EQUAL(2, i);
  TEST_ASSERT_EQUAL(10, p[0]);
  TEST_ASSERT_EQUAL(1, p[1]);
}

void test_parse_ilist_str_ShouldReturnOneForTwoInt3(void)
{
  TEST_ASSERT_EQUAL(0, parse_ilist_str(&p, &i, "1,10"));
  TEST_ASSERT_EQUAL(2, i);
  TEST_ASSERT_EQUAL(1, p[0]);
  TEST_ASSERT_EQUAL(10, p[1]);
}

void test_parse_ilist_str_ShouldReturnOneForTwoInt4(void)
{
  TEST_ASSERT_EQUAL(0, parse_ilist_str(&p, &i, "1,-10"));
  TEST_ASSERT_EQUAL(2, i);
  TEST_ASSERT_EQUAL(1, p[0]);
  TEST_ASSERT_EQUAL(-10, p[1]);
}

void test_parse_ilist_str_ShouldReturnOneForTwoInt5(void)
{
  TEST_ASSERT_EQUAL(0, parse_ilist_str(&p, &i, "10,-1"));
  TEST_ASSERT_EQUAL(2, i);
  TEST_ASSERT_EQUAL(10, p[0]);
  TEST_ASSERT_EQUAL(-1, p[1]);
}

void test_parse_ilist_str_ShouldReturnOneForTwoInt6(void)
{
  TEST_ASSERT_EQUAL(0, parse_ilist_str(&p, &i, "-10,1"));
  TEST_ASSERT_EQUAL(2, i);
  TEST_ASSERT_EQUAL(-10, p[0]);
  TEST_ASSERT_EQUAL(1, p[1]);
}

void test_parse_ilist_ShouldReturnThree1(void)
{
  TEST_ASSERT_EQUAL(0, parse_ilist_str(&p, &i, "1,2147483647,-2147483648"));
  TEST_ASSERT_EQUAL(3, i);
  TEST_ASSERT_EQUAL(1, p[0]);
  TEST_ASSERT_EQUAL(2147483647, p[1]);
  TEST_ASSERT_EQUAL(-2147483647-1, p[2]);
}

void test_parse_ilist_ShouldReturnThree2(void)
{
  TEST_ASSERT_EQUAL(0, parse_ilist_str(&p, &i, "2147483647,1,-2147483648"));
  TEST_ASSERT_EQUAL(3, i);
  TEST_ASSERT_EQUAL(1, p[1]);
  TEST_ASSERT_EQUAL(2147483647, p[0]);
  TEST_ASSERT_EQUAL(-2147483647-1, p[2]);
}

void test_parse_ilist_ShouldReturnThree3(void)
{
  TEST_ASSERT_EQUAL(0, parse_ilist_str(&p, &i, "2147483647,-2147483648,1"));
  TEST_ASSERT_EQUAL(3, i);
  TEST_ASSERT_EQUAL(1, p[2]);
  TEST_ASSERT_EQUAL(2147483647, p[0]);
  TEST_ASSERT_EQUAL(-2147483647-1, p[1]);
}

void test_parse_ilist_ShouldReturnThree4(void)
{
  TEST_ASSERT_EQUAL(0, parse_ilist_str(&p, &i, "-2147483648,2147483647,1"));
  TEST_ASSERT_EQUAL(3, i);
  TEST_ASSERT_EQUAL(1, p[2]);
  TEST_ASSERT_EQUAL(2147483647, p[1]);
  TEST_ASSERT_EQUAL(-2147483647-1, p[0]);
}

void test_parse_ilist_ShouldReturn33ForLonglist(void)
{
  TEST_ASSERT_EQUAL(0, parse_ilist_str(&p, &i, "1,2,3,4,5,6,7,8,9,10,-1,-2,-3,-4,-5,-6,-7,-8,-9,-10,-11,-12,-13,-14,-15,11,12,13,14,15,31,32,33"));
  TEST_ASSERT_EQUAL(33, i);
  TEST_ASSERT_EQUAL(1, p[0]);
  TEST_ASSERT_EQUAL(-1, p[10]);
  TEST_ASSERT_EQUAL(33, p[32]);
}

void test_parse_ilist_ShouldReturn1ForSignInt(void)
{
  TEST_ASSERT_EQUAL(0, parse_ilist_str(&p, &i, "+987"));
  TEST_ASSERT_EQUAL(1, i);
  TEST_ASSERT_EQUAL(987, p[0]);
}

void test_parse_ilist_ShouldReturn1ForNegSignInt(void)
{
  TEST_ASSERT_EQUAL(0, parse_ilist_str(&p, &i, "-987"));
  TEST_ASSERT_EQUAL(1, i);
  TEST_ASSERT_EQUAL(-987, p[0]);
}


void test_parse_ilist_ShouldReturn3ForSignInt(void)
{
  TEST_ASSERT_EQUAL(0, parse_ilist_str(&p, &i, "-100, -5467, 987"));
  TEST_ASSERT_EQUAL(3, i);
  TEST_ASSERT_EQUAL(-100, p[0]);
  TEST_ASSERT_EQUAL(-5467, p[1]);
  TEST_ASSERT_EQUAL(987, p[2]);
}

void test_parse_ilist_ShouldReturn2ForTwoIntsWithCommaSpace(void)
{
  TEST_ASSERT_EQUAL(0, parse_ilist_str(&p, &i, " -100  , -5467 , 987 "));
  TEST_ASSERT_EQUAL(3, i);
  TEST_ASSERT_EQUAL(-100, p[0]);
  TEST_ASSERT_EQUAL(-5467, p[1]);
  TEST_ASSERT_EQUAL(987, p[2]);
}

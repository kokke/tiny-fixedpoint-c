#include "fixedpoint.h"
#include <assert.h>
#include <stdio.h>


static void test_fixedpoint(void)
{
  const fp_t one = fp(1,0);
  const fp_t ten = fp(10,0);

  fp_t n   = fp(0,0001);
  fp_t s   = fp(0,0);

  int i,j,k;
  int total = 0;
  for (k = 0; k < 1000; ++k)
  {
    assert(s == (fp_mul(ten, one) * k));
    for (j = 0; j < 10; ++j)
    {
      for (i = 0; i < 10000; ++i)
      {
        s = fp_add(s, n);
        total += 1;
      }
    }
    assert(s == (fp_mul(ten, one) * (1+k)));
  }
  printf("fixed point: %d x %s", total, fp_to_string(n)); printf(" = %s\n", fp_to_string(s));
}


static void test_float(void)
{
  float n = (float)0.0001;
  float s = 0.0;

  int i,j;
  int total = 0;
  for (j = 0; j < 10000; ++j)
  {
    for (i = 0; i < 10000; ++i)
    {
      s = (s + n);
      total += 1;
    }
  }
  printf("float:       %d x %.04f = %f\n", total, n, s);
}

static void test_double(void)
{
  double n = 0.0001;
  double s = 0.0;

  int i,j;
  int total = 0;
  for (j = 0; j < 10000; ++j)
  {
    for (i = 0; i < 10000; ++i)
    {
      s = (s + n);
      total += 1;
    }
  }
  printf("double:      %d x %.04f = %f\n", total, n, s);
}


int main()
{
  test_fixedpoint();
  test_float();
  test_double();

  return 0;
}



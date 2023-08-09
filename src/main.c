#include "fixedpoint.h"
#include <assert.h>
#include <stdio.h>


int main()
{
  char* s;

  {
    int i;
    fp_t a = fp(1,005);
    for (i = 0; i < 10; ++i)
    {
      s = fp_to_string(a);
      printf("%d : %s\n", i, s);
      a /= 10;
    }
    s = fp_to_string(a);
    printf("%d: %s\n", i, s);
  }
  printf("\n");

  {
    //fp_t a = fp(3,141592653589793);
    fp_t a = fp(3,141592654);
    s = fp_to_string(a);
    printf("pi  = %s, (raw = " FP_FORMAT ")\n", s, a);
    s = fp_to_string(2*a);
    printf("2pi = %s, (raw = " FP_FORMAT ")\n", s, 2*a);
    //fp_t b = fp_new(3, 14159);
    //s = fp_to_string(b);
    //printf("manual pi = %s (raw = %ld)\n", s, b);
  }
  printf("\n");

  {
    fp_t a = fp(-1,000001);
    s = fp_to_string(a);
    printf("n  = %s, (raw = " FP_FORMAT ")\n", s, a);
    s = fp_to_string(2*a);
    printf("2n = %s, (raw = " FP_FORMAT ")\n", s, 2*a);
  }
  printf("\n");

  {
    int i;
    fp_t a = fp(1,0);
    for (i = 0; i < 33; ++i)
    {
      s = fp_to_string(a);
      printf("2^%-2d = %12s\n", i, s);
      a *= 2;
    }
    s = fp_to_string(a);
    printf("2^%-2d = %12s\n", i, s);
  }
  printf("\n");

  {
    fp_t a = fp(5,000);

    int i;
    for (i = 0; i < 10; ++i)
    {
      s = fp_to_string(a);
      printf("%d: n  = %s, (raw = " FP_FORMAT ")\n", i, s, a);
      a = fp_dec(a);
    }

    s = fp_to_string(a);
    printf("%d: n  = %s, (raw = " FP_FORMAT ")\n", i, s, a);

    for (i = 0; i < 10; ++i)
    {
      a = fp_inc(a);
      s = fp_to_string(a);
      printf("%d: n  = %s, (raw = " FP_FORMAT ")\n", i, s, a);
    }
  }
  printf("\n");

  {
    printf("a = %s\n", fp_to_string(fp(1,0)));
    printf("a = %s\n", fp_to_string(fp(+1,0)));
    printf("a = %s\n", fp_to_string(fp(-1,0)));
    printf("a = %s\n", fp_to_string(-(fp(1,0))));
    printf("a = %s\n", fp_to_string(+(-(fp(1,0)))));
  }
  printf("\n");

  {
    printf("a = %s\n", fp_to_string(fp(-10,0)));
  }
  printf("\n");

  {
    fp_t a = fp(3,14);
    fp_t b = fp(1,1);
    printf("a = %s\n", fp_to_string(fp_mod(a,b)));
  }
  printf("\n");

  {
    fp_t a = fp(0,0001);
    fp_t b = fp(10000,0);
    fp_t c = fp_mul(a, b);
    fp_t d = 0;
    printf("c = %s\n", fp_to_string(c));

    int i;
    for (i = 0; i < 10000; ++i)
    {
      d = fp_add(d, a);
    }
    printf("d = %s (10000 x a)\n", fp_to_string(d));
  }
  printf("\n");

  {
    fp_t a = (fp_t)(3*FP_SCALE);
    printf("a = %s\n", fp_to_string(a));
  }
  printf("\n");

  {
    fp_t a = fp_new(3,1);
    printf("a = %s\n", fp_to_string(a));
  }
  printf("\n");

  printf("%s\n", fp_to_string(fp_from_string("1.2345678901234567890")));
  printf("%s\n", fp_to_string(fp_from_string("-1.2345678901234567890")));
  printf("%s\n", fp_to_string(fp_from_string("1234.5678901234567890")));
  printf("%s\n", fp_to_string(fp_from_string("1.0")));
  printf("%s\n", fp_to_string(fp_from_string("-2.34")));
  printf("%s\n", fp_to_string(fp_from_string("-0.001")));
  printf("%s\n", fp_to_string(fp_from_string("5.0")));
  printf("\n");

  {
    fp_t a = fp(-0,0123);
    printf("a = %s\n", fp_to_string(a));
  }
  printf("\n");

  return 0;
}





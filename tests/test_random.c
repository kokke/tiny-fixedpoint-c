#include <assert.h>
#include <math.h>
#include <string.h>
#include <stdio.h>
#include <stdlib.h>
#include <time.h>
#include "fixedpoint.h"


static void random_test(void)
{
  enum
  {
    OP_ADD,
    OP_SUB,
    OP_MUL,
    OP_DIV,
    OP_MOD,
    OP_INC,
    OP_DEC,
    NUM_OPS,
  };

  const char* op_syms[] = { "+", "-", "*", "/", "%", "++", "--" };

  static char bufa[64];
  static char bufb[64];
  static char bufc[64];
  static double da;
  static double db;
  static double dc;
start:

  da = (((unsigned)rand()) % 100) * (((double)(rand() % 100)) / 10000.0);
  db = (((unsigned)rand()) % 100) * (((double)(rand() % 100)) / 10000.0);

  int op = rand() % (NUM_OPS-2);

  if ((op == OP_DIV || op == OP_MOD) && (db == 0)) // avoid zero division
    goto start;
  else if (op == OP_MOD) goto start;

  switch (op)
  {
    case OP_ADD: dc = da + db; break;
    case OP_SUB: dc = da - db; break;
    case OP_MUL: dc = da * db; break;
    case OP_DIV: dc = da / db; break;
    case OP_MOD: dc = fmod(da, db); break;
    case OP_INC: dc = ++da; break;
    case OP_DEC: dc = --da; break;
    default: assert(0);
  }

  // limit to four significant digits
  sprintf(bufa, "%.4f", da);
  sprintf(bufb, "%.4f", db);
  sprintf(bufc, "%.4f", dc);
  
  fp_t fa = fp_from_string(bufa);
  fp_t fb = fp_from_string(bufb);
  fp_t fc = fp_from_string(bufc);

  switch (op)
  {
    case OP_ADD: fc = fp_add(fa, fb); break;
    case OP_SUB: fc = fp_sub(fa, fb); break;
    case OP_MUL: fc = fp_mul(fa, fb); break;
    case OP_DIV: fc = fp_div(fa, fb); break;
    case OP_MOD: fc = fp_mod(fa, fb); break;
    case OP_INC: fc = fp_inc(fa);   break;
    case OP_DEC: fc = fp_dec(fa);   break;
    default: assert(0);
  }

  //printf("%s %s %s = %s\n", bufa, op_syms[op], bufb, bufc);

  // convert to string and back again to truncate noise in decimal-part
  double c_from_fixpnt_str = atof(fp_to_string(fc));
  double c_from_float_str  = atof(bufc);

  if (c_from_float_str != c_from_fixpnt_str)
  {
    static char abs_err_str[64];
    static char max_err_str[64];
    double abs_error = fabs(c_from_fixpnt_str - c_from_float_str);
    sprintf(abs_err_str, "%.4f", abs_error);

    // precision for each consequtive operation is max 1/SCALE   
    const double max_error = (1.0/(float)FP_SCALE);
    if (max_err_str[0] == 0)
    {
      sprintf(max_err_str, "%.4f", max_error);
    }
    
    if (strcmp(abs_err_str, max_err_str) != 0)
    {
      printf("abs error = '%f'\n", abs_error);
      printf("max error = '%f'\n", max_error);
      printf("delta err = '%f'\n", max_error - abs_error);
      printf("bufc      = '%s'\n", bufc);
      printf("fc        = '%s'\n", fp_to_string(fc));
      printf(" a raw    = %d\n", fa);
      printf(" b raw    = %d\n", fb);
      printf(" c raw    = %d\n", fc);
      assert(0);
    }
  }
}

int main(void)
{
  srand((unsigned int)time((int)0));
  int i;
  for (i = 0; i < 1000000; ++i)
    random_test();

  return 0;
}

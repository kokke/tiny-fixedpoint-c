#ifndef __FIXED_POINT_H__
#define __FIXED_POINT_H__

/*

Fixed point arithmetic
======================

Uses the standard method of scaling each number by a static amount - here called FP_SCALE.

For 64-bit backing numbers (fp_t), an FP_SCALE of 10^9 leaves 34 bits for the whole-part.

For 32-bit numbers, an FP_SCALE of e.g. 10^6 leaves only 12 bits left for the whole-part (-2048 -> +2048).

The default chooses FP_SCALE = 10^4 which means 18 bits integer resolution and 4 significant digits.

Depending on your application, this may suffice.

------------------------------------------------

Example definitions:

  For 64-bit numbers
    #define fp_t       int64_t
    #define FP_SCALE   (fp_t)1000000000
    #define FP_FORMAT  "%ld"

  For 32-bit numbers
    #define fp_t       int32_t
    #define FP_SCALE   1000000
    #define FP_FORMAT  "%d"

*/

#include <stdint.h>

#if 0
/* This is the type used for fixed-point arithmetic -- know the type's limits! */
#define fp_t              int64_t
/* This is how much you scale each number. 1 == FP_SCALE */
#define FP_SCALE          (fp_t)1000000000 /* 2^30 - 2^26 - 2^22 - 2^21 - 2^18 - 2^16 - 2^13 - 2^12 - 2^10 - 2^9 */
/* This is the printf-format string for output */
#define FP_FORMAT         "%ld"

#else
  #define fp_t       int32_t
  #define FP_SCALE   10000
  #define FP_FORMAT  "%d"
#endif


/* Convenience macros */
#define int2fp(n)         ((fp_t)(n) * FP_SCALE)
#define fp2int(n)         ((fp_t)(n) / FP_SCALE)
//#define fp(_int, _dec)    (((double)_int==(double)-0) ?  -(_fp(_int, _dec)) : _fp(_int, _dec))
#define fp(_int, _dec)   fp_macro( ((fp_t)_int), ((fp_t)1 ## _dec) )



fp_t  fp_macro(fp_t _int, fp_t _dec); /* constructor with macro-magic */
fp_t  fp_new(fp_t _int, fp_t _dec);   /* constructor                  */

fp_t  fp_inc(fp_t n);                 /* unary, increment             */
fp_t  fp_dec(fp_t n);                 /* unary, decrement             */

fp_t  fp_add(fp_t l, fp_t r);         /* binary, add                  */
fp_t  fp_sub(fp_t l, fp_t r);         /* binary, subtract             */
fp_t  fp_mul(fp_t l, fp_t r);         /* binary, multiply             */
fp_t  fp_div(fp_t l, fp_t r);         /* binary, division             */
fp_t  fp_mod(fp_t l, fp_t r);         /* binary, modulo/remainder     */

char* fp_to_string(fp_t n);           /* to string representation     */
fp_t  fp_from_string(char* s);        /* from string representation   */

#endif /* __FIXED_POINT_H__ */


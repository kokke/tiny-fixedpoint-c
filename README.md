# fixedpoint-c

## Fixed-point arithmetic in C99

### Description

Small portable library for [Fixed-point arithmetic](https://en.wikipedia.org/wiki/Fixed-point_arithmetic) in C, for calculating with decimal numbers.

This library uses a static scaling of the numbers (a power of ten).

No dynamic memory management is utilized, and stdio is only used for testing.

### Current status

Basic arithmetic is implemented (+ - * / %) and increment + decrement. Comparison works like on normal integers, because the fixed-points are scaled equivalently (by a static amount). 

**The paint is still a bit wet.**


### Design goals

The main design goal is to be small, correct, self contained and use only few resources while retaining acceptable performance and feature completeness. Clarity of the code is also highly valued.

### Notable features and omissions

- Small code and binary size: 2-300SLOC, ~1kb binary for x86 (0.6kb for ARM/Thumb).
- No dynamic memory allocation (no `malloc` / `free`)
- Randomized testing

### API

You can create new fixed-point variables using `fp_new` or the (more convenient) macro `fp`.

`fp_new` takes an integer-part and a decimal-part. For the mathematical constant 'Pi', you would call `fp_new(3 * SCALE, 14159264)` and need to be very careful with scaling of the numbers.

You can also use the macro `fp`. E.g. `fp(3,141592653589793)` creates a fixed-point version of PI that is scaled automatically.

There is some macro magic to allow this, and the `fp`-macro only works with numerals, not variables. You can also just scale the numbers manually.

---

This is the API

```c
#define fp_t int64_t


fp_t  fp_new(fp_t _int, fp_t _dec); /* constructor              */

fp_t  fp_inc(fp_t n);               /* unary, increment         */
fp_t  fp_dec(fp_t n);               /* unary, decrement         */

fp_t  fp_add(fp_t l, fp_t r);       /* binary, add              */
fp_t  fp_sub(fp_t l, fp_t r);       /* binary, subtract         */
fp_t  fp_mul(fp_t l, fp_t r);       /* binary, multiply         */
fp_t  fp_div(fp_t l, fp_t r);       /* binary, division         */
fp_t  fp_mod(fp_t l, fp_t r);       /* binary, modulo/remainder */

char* fp_to_string(fp_t n);         /* string representation    */
```

### Usage

See main.c for usage examples

### Examples

### FAQ

### License

All material in this repository is in the public domain.


#ifndef type
#define type int
#endif

#ifndef B01557EB_9610_4434_811C_45AE5EADCCD8
#define B01557EB_9610_4434_811C_45AE5EADCCD8
#include <memory.h>
#include <stdint.h>
#include <stdio.h>
#include <stdlib.h>

typedef uint64_t u64;
typedef uint32_t u32;
typedef uint16_t u16;
typedef uint8_t u8;

typedef int64_t i64;
typedef int32_t i32;
typedef int16_t i16;
typedef int8_t i8;

typedef float f32;
typedef double f64;
#define concat(a, b) a##_##b
#define vec(t) concat(vec, t)
#define vec_push(t) concat(vec_push, t)
#define vec_new(t) concat(vec_new, t)

#define vec_clone(t) concat(vec_clone, t)
#define vec_drop(t) concat(vec_drop, t)
#endif /* B01557EB_9610_4434_811C_45AE5EADCCD8 */

typedef struct vec(type) {
  type* p;
  u64 len, cap;
}
vec(type);

static vec(type) vec_new(type)(u64 cap) {
  vec(type) re = {.p = (type*)calloc(1,cap*sizeof(type)), .cap = cap};
  return re;
}

static void vec_push(type)(vec(type) * v, type item) {
  if (!v->cap) {
    v->p = (type*)malloc((v->cap = 4) * sizeof(type));
  } else if (v->len == v->cap) {
    v->p = (type*)realloc(v->p, (v->cap *= 2) * sizeof(type));
  }
  v->p[v->len++] = item;
}

static void vec_drop(type)(vec(type) * v) {
#ifdef type_drop
  for (u64 i = 0; i < v->len; ++i)
    type_drop(v->p + i);
#endif
  free(v->p);
}

static vec(type) vec_clone(type)(vec(type) * v) {
  vec(type) re = {
      .p = (type*)malloc(v->len * sizeof(type)),
      .len = v->len,
      .cap = v->len,
  };
#ifdef type_clone
  for (u64 i = 0; i < v->len; ++i)
    re.p[i] = type_clone(v->p + i);
#else
  memcpy(re.p, v->p, v->len * sizeof(type));
#endif
  return re;
}

#ifdef type_clone
#undef type_clone
#endif
#undef type

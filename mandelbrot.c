#define type f64
#include "vec.h"
#define type u8
#include "vec.h"
#define type_clone vec_clone(f64)
#define type_drop vec_drop(f64)
#define type vec(f64)
#include "vec.h"

const u64 MAX_ITER = 50;
const u64 VLEN = 8;

void add8(f64 dst[8], f64 src0[8], f64 src1[8]) {
  u64 i = 8;
  while (i--)
    *dst++ = *src0++ + *src1++;
}

void mbrot8(u8* out, f64 cr[8], f64 ci[8]) {
  f64 zr[8] = {};
  f64 zi[8] = {};
  f64 tr[8] = {};
  f64 ti[8] = {};
  f64 absz[8] = {};

  for (u64 i = 0; i < MAX_ITER / 5; ++i) {
    for (u64 j = 0; j < 5; ++j) {
      for (u64 k = 0; k < 8; ++k) {
        zi[k] = (zr[k] + zr[k]) * zi[k] + ci[k];
        zr[k] = tr[k] - ti[k] + cr[k];
        tr[k] = zr[k] * zr[k];
        ti[k] = zi[k] * zi[k];
      }
    }

    add8(absz, tr, ti);
    for (u64 i = 0; i < 8; ++i) {
      if (absz[i] > 4.0)
        return;
    }
  }
  u8 acc = 0;
  for (u64 i = 0; i < 8; ++i) {
    if (absz[i] <= 4.0) {
      acc |= 0x80 >> i;
    }
  }
  *out = acc;
}

int main() {
  const u64 size = 1024 / VLEN * VLEN;
  const u64 chunk_size = size / VLEN;
  const f64 inv = 2.0 / (f64)size;

  vec(vec(f64)) xloc = vec_new(vec(f64))(chunk_size);
  vec(u8) rows = vec_new(u8)(size * chunk_size);

  xloc.len = xloc.cap;
  rows.len = rows.cap;


  for (u64 i = 0; i < xloc.len; ++i) {
    xloc.p[i] = vec_new(f64)(VLEN);
    xloc.p[i].len = VLEN;
  }

  for (u64 i = 0; i < size; ++i) {
    xloc.p[i / VLEN].p[i % VLEN] = (f64)i * inv - 1.5;
  }


  for (u64 j = 0; j < size; ++j) {
    f64 ci[8] = {};
    u64 i = 8;
    while (i--)
      ci[i] = j * inv - 1.0;
    for (u64 i = 0; i < chunk_size; ++i) {
      mbrot8(rows.p + i + j * chunk_size, xloc.p[i].p, ci);
    }
  }

  printf("P4\n%zu %zu ", size, size);
  fwrite(rows.p, 1, rows.len, stdout);

  vec_drop(vec(f64))(&xloc);
  vec_drop(u8)(&rows);
}
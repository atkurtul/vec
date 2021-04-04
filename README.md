Generic vector impl

```C

//import vec(f64)
#define type f64
#include "vec.h"

//import vec(u8)
#define type u8
#include "vec.h"

//import vec(vec(f64)) and define clone & drop for it
#define type_clone vec_clone(f64)
#define type_drop vec_drop(f64)
#define type vec(f64)
#include "vec.h"

int main() {
  ...
  //Create vectors
  vec(vec(f64)) xloc = vec_new(vec(f64))(chunk_size);
  vec(u8) rows = vec_new(u8)(size * chunk_size);
  ...

  //Free vectors
  vec_drop(vec(f64))(&xloc);
  vec_drop(u8)(&rows);
}
```

# No leaks!

![Valgrind](https://raw.githubusercontent.com/atkurtul/vec/master/valgrind.png)

![Mandelbrot](https://raw.githubusercontent.com/atkurtul/vec/master/mandelbrot.png)
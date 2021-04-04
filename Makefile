
all:
	clang mandelbrot.c -o mandelbrot
	valgrind ./mandelbrot > mandelbrot.bmap
	rm ./mandelbrot
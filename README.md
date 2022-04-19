# Mandelbrot set
This program proceeds the Mandelbrot set image using AVX2 instructions. The main goal is to measure how avx instructions affect computing speed

## How to build
```
$ git clone https://github.com/andreyStrachuk/MandelbrotSet
$ cd MandelbrotSet
$ make
$ ./man
```

## Optimizations

I used AVX2 instructions for storing 64 bit double values and computing the color. Thus, for one loop interation program manages to handle 4 values.

|        | AVX2 without asserts | AVX2 without asserts  | No optimizations |
| :----- | :------------------- | :------------------- | :------------------- |
|FPS| ~85| ~40|~2.3|

Surprisingly, program operates 36 times faster after optimizations. Noticeably, standart assert from assert.h may significantly slow down the program. 
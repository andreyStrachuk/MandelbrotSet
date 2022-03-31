
CC=g++

CFLAGS=-Werror -Wpedantic -Wextra -O3 -c

SRC=Mandelbrot.cpp MandelbrotFunctions.cpp
SRC_O=Mandelbrot.o MandelbrotFunctions.o
SRC_SFML=-lsfml-graphics -lsfml-window -lsfml-system

Mbrot_o=man
Mandelbrot=m

all: $(Mandelbrot) $(SRC) $(Mbrot_o) $(SRC_O)

$(Mandelbrot): $(SRC)
	$(CC) $(CFLAGS) $(SRC)


$(Mbrot_o): $(SRC_O)
	$(CC) $(SRC_O) -o $(Mbrot_o) $(SRC_SFML)

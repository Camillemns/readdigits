CC = gcc
CFLAGS = -Wall -Wextra -Werror -std=c99 -pedantic -fsanitize=address -g
LDFLAGS = -fsanitize=address
LDLIBS = `pkg-config gtk+-3.0 --libs sdl` -lSDL_image -lm

SRC = main.c gradient.c segmentation.c nn_tools.c dataprep.c nn.c print_weights_biases.c
OBJ = ${SRC:.c=.o}
DEP = ${SRC:.c=.d}

all : main
main : ${OBJ}
.PHONY: clean

clean:
	${RM} ${OBJ}
	${RM} ${DEP}
	${RM} main

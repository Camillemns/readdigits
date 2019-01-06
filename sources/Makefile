CC = gcc
CFLAGS = -Wall -Wextra -Werror -std=c99 -pedantic -fsanitize=address -g
LDFLAGS = -fsanitize=address
LDLIBS = `pkg-config gtk+-3.0 --libs sdl` -lSDL_image -lSDL_ttf -lm

SRC = main.c code/segmentation.c code/nn_tools.c code/dataprep.c code/nn.c code/print_weights_biases.c code/read_weights_biases.c code/mysdl.c code/interface.c
OBJ = ${SRC:.c=.o}
DEP = ${SRC:.c=.d}

all : main
main : ${OBJ}
.PHONY: clean

clean:
	${RM} ${OBJ}
	${RM} ${DEP}
	${RM} main

#ifndef SEGMENTATION_H
# define SEGMENTATION_H
#include <stdio.h>
#include <stdlib.h>
#include <SDL/SDL.h>
#include <SDL/SDL_image.h>
#include <err.h>
#include <math.h>
#include "mysdl.h"
#include "nn.h"

void grayscale(SDL_Surface *img);
void blacknwhite(SDL_Surface *img);
void resize (SDL_Surface *scr ,int **src_bin, int (*dest)[28]);
void binarised(SDL_Surface *img, float *tab);

#endif /* !SEGMENTATION_H */

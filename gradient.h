#ifndef GRADIENT_H
# define GRADIENT_H

SDL_Surface* load_image(char *path);
SDL_Surface* open_image(SDL_Surface *img);
Uint32 getpixel(SDL_Surface *surface, int x, int y);
void putpixel(SDL_Surface *surface, int x, int y, Uint32 pixel);
void grayscale(SDL_Surface *img);
void blacknwhite(SDL_Surface *img);
void wait_for_keypressed(void);
SDL_Surface resize(SDL_Surface *img);

#endif /* !GRADIENT_H */

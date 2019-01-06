# ifndef MYSDL_H
# define MYSDL_H


SDL_Surface* load_image(char *path);
SDL_Surface* open_image(SDL_Surface *img);
void wait_for_keypressed(void);
void putpixel(SDL_Surface *surface, int x, int y, Uint32 pixel);
Uint32 getpixel(SDL_Surface *surface, int x, int y);


#endif

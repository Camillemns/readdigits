#include <stdio.h>
#include <stdlib.h>
#include <SDL/SDL.h>
#include <SDL/SDL_image.h>
#include <err.h>
#include <math.h>

SDL_Surface* load_image(char *path)
{
    SDL_Surface *img;
    img = IMG_Load(path);
    return img;
}

SDL_Surface* open_image(SDL_Surface *img)
{

    SDL_Surface *screen;
    screen = SDL_SetVideoMode(img->w, img->h, 0, SDL_SWSURFACE | SDL_ANYFORMAT);

    if (screen == NULL)
        errx(1, "On n'a pas pu  mettre %dx,%d mode video : %s\n", img->w, img->h, SDL_GetError());

    if(SDL_BlitSurface(img, NULL, screen, NULL))
        warnx("BlitSurface error: %s\n", SDL_GetError());

    SDL_UpdateRect(screen, 0, 0, img->w, img->h);

    return screen;
}


Uint32 getpixel(SDL_Surface *surface, int x, int y)
{
    int bpp = surface->format->BytesPerPixel;
    //Here p is the address to the pixel we want to retrieve 
    Uint8 *p = (Uint8 *)surface->pixels + y * surface->pitch + x * bpp;

    switch(bpp) {
        case 1:
            return *p;

        case 2:
            return *(Uint16 *)p;

        case 3:
            if(SDL_BYTEORDER == SDL_BIG_ENDIAN)
                return p[0] << 16 | p[1] << 8 | p[2];
            else
                return p[0] | p[1] << 8 | p[2] << 16;

        case 4:
            return *(Uint32 *)p;

        default:
            return 0;       //shouldn't happen, but avoids warnings 
    }
}

void putpixel(SDL_Surface *surface, int x, int y, Uint32 pixel)
{
    int bpp = surface->format->BytesPerPixel;
    // Here p is the address to the pixel we want to set 
    Uint8 *p = (Uint8 *)surface->pixels + y * surface->pitch + x * bpp;

    switch(bpp) {
        case 1:
            *p = pixel;
            break;

        case 2:
            *(Uint16 *)p = pixel;
            break;

        case 3:
            if(SDL_BYTEORDER == SDL_BIG_ENDIAN) {
                p[0] = (pixel >> 16) & 0xff;
                p[1] = (pixel >> 8) & 0xff;
                p[2] = pixel & 0xff;
            } else {
                p[0] = pixel & 0xff;
                p[1] = (pixel >> 8) & 0xff;
                p[2] = (pixel >> 16) & 0xff;
            }
            break;

        case 4:
            *(Uint32 *)p = pixel;
            break;
    }
}

void grayscale(SDL_Surface *img)
{ 
    Uint32 pixel;
    Uint8 r;
    Uint8 g;
    Uint8 b;
    for (int i=0; i < img->w; i++)
    {
        for(int j=0; j < img->h; j++)
        { 
            pixel = getpixel(img, i, j);
            SDL_GetRGB(pixel, img->format, &r, &g, &b);
            Uint8 coef_r = r * 0.3;
            Uint8 coef_g = g * 0.59;
            Uint8 coef_b = b * 0.11;
            Uint8 luminance = coef_r + coef_g + coef_b;
            pixel = SDL_MapRGB(img->format, luminance, luminance, luminance);
            putpixel(img, i, j, pixel);
        }
    }
}

void blacknwhite(SDL_Surface *img)
{
  Uint32 pixel;
  Uint8 r;
  Uint8 g;
  Uint8 b;
  for(int i = 0; i < img->w; i++)
    {
      for(int j = 0; j < img->h; j++)
	{
	  pixel = getpixel(img, i, j);
	  SDL_GetRGB(pixel, img->format, &r, &g, &b);
	  if( r > 127 && b > 127 && g > 127)
	    {
	      r = 255;
	      b = 255;
	      g = 255;
	    }
	  else
	    {
	      r = 0;
	      g = 0;
	      b = 0;
	    }
	  pixel = SDL_MapRGB(img->format, r, g, b);
	  putpixel(img, i, j, pixel);
	}
    }
}

void wait_for_keypressed(void)
{
    SDL_Event             event;
    // Infinite loop, waiting for event
    for (;;) {
        // Take an event
        SDL_PollEvent( &event );
        // Switch on event type
        switch (event.type) {
            // Someone pressed a key -> leave the function
            case SDL_KEYDOWN: return;
            default: break;
        }
        // Loop until we got the expected event
    }
}

/*SDL_Surface * resize ( SDL_Surface *img)
{
  SDL_Surface *res = SDL_CreateRGBSurface(SDL_SWSURFACE, 28, 28, img->format->BitsPerPixel, 0, 0, 0, 0);
  SDL_BlitSurface(img, NULL, res, NULL);
  return res;
}*/

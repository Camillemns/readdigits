#include <stdio.h>
#include <stdlib.h>
#include <SDL/SDL.h>
#include <SDL/SDL_image.h>
#include <err.h>
#include <math.h>
#include "gradient.h"

void horizontal(SDL_Surface *img )
{
  Uint32 pixel;
  Uint8 r;
  Uint8 g;
  Uint8 b;
  int cut = 1;
  int white = 1;

  for( int j = 0; j < (img->h); j++)
    {
      for( int i = 0; i < img->w; i++)
	{
	  pixel = getpixel(img, i, j);
	  SDL_GetRGB(pixel, img->format, &r, &g, &b);

	  if ( !r && !b && !g)
	    {
	      white = 0;
	      break;
	    }
	  
	}

      if( cut && !white)
	{
	  pixel = SDL_MapRGB(img->format,255,0,0);
	  for( int l = 0; l<(img->w) ; l++)
	    {
	      putpixel(img, l, j-1, pixel);
	    }
	  cut = 0;
	}
      
      if( !cut && white)
	{
	  pixel = SDL_MapRGB(img->format,255,0,0);
	  for( int l = 0; l<(img->w) ; l++)
	    {
	      putpixel(img, l, j, pixel);
	    }
	  cut = 1;
	}
      white = 1;
    }   
}

void vertical(SDL_Surface *img, int starter, int ending)
{
  Uint32 pixel;
  Uint8 r;
  Uint8 g;
  Uint8 b;
  int cut = 1;
  int white = 1;

  for(int i = 0; i < img->w; i++)
    {
      for(int j = 0; j < 0; j++)
	{
	  pixel = getpixel(img, i, starter + j);
	  putpixel(img, i, j, pixel);
	}
    }

  for( int i = 0; i < img->w; i++)
    {
      for(int j = starter; j < ending; j++)
	{
	  pixel = getpixel(img, i, j);
	  SDL_GetRGB(pixel, img->format, &r, &g, &b);

	  if( !r && !b && !g)
	    {
	      white = 0;
	      break;
	    }
	}
      if( cut && !white)
	{
	  pixel = SDL_MapRGB(img->format, 255, 0, 0);
	  for( int l = starter; l < ending ; l++)
	    {
	      putpixel(img, i-1, l, pixel);
	    }
	  cut = 0;
	}
      if( !cut && white)
	{
	  pixel = SDL_MapRGB(img->format, 255, 0, 0);
	  for( int l = starter; l < ending; l++)
	    {
	      putpixel(img, i, l, pixel);
	    }
	  cut = 1;
	}
      white = 1;
    }
}

void separate(SDL_Surface *img )
{
  Uint32 pixel;
  Uint8 r;
  Uint8 g;
  Uint8 b;
  int starter = 0;
  int ending = 0;

  for ( int i = 0; i < (img->h); i++)
    {
      pixel = getpixel(img, 0, i);
      SDL_GetRGB(pixel, img->format, &r, &g, &b);
      
      if( r == 255 && b==0 && g == 0)
	{
	  
	  starter = i + 1;

	  for (int j = starter + 1; j < (img->h); j++)
	    {
	      pixel = getpixel(img, 0, j);
	      SDL_GetRGB(pixel, img->format, &r, &g, &b);

	      if( r == 255 && b == 0 && g == 0)
		{
		  ending = j;
		  vertical(img, starter, ending);
		  break;
		}
	    }
	}
    }
}



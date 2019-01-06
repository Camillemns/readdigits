#define _GNU_SOURCE
#include "segmentation.h"
extern net* a;

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

void resize (SDL_Surface *scr ,int **src_bin, int (*dest)[28])
{
    int a, b, adlarg, adhaut;
    adlarg=28 - ((scr->w)%28);
    a= ((scr->w)+adlarg)/28 ;
    adhaut=28 - ((scr->h)%28);
    b= ((scr->h)+adhaut)/28 ;

    for (int i=0; i<28; i++)
    {
        for(int j=0; j<28; j++)
        {
            float  S=0;
            for (int I=0; I<a; I++)
            {
                for(int J=0; J<b; J++)
                {
                    int s=0;
                    int x=(i*a)+I;
                    int y=((j*b)+J);
                    if(  (x < scr->w )&& (y < scr->h ) )
                    {
                        s=src_bin[x][y];
                    }
                    S=S+s;
                }
            }
            if ( ( S/(a*b)  ) < 0.5 )
            {
                dest[i][j]=0;
            }

            else
            {
                dest[i][j]=1;
            }
        }
    }
}


void binarised(SDL_Surface *img, float *tab)
{
    blacknwhite(img);
    Uint8 r,g,b;
    Uint32 pixel;
    int **img_bin = calloc(img->w,sizeof(int *));
    for (int i=0;i<img->w;i++)
        img_bin[i]=calloc(img->h,sizeof(int));

    for(int i=0; i<img->w; i++)
    {
        for (int j=0;j<img->h;j++)
        {
            pixel = getpixel(img, i, j);
            SDL_GetRGB(pixel, img->format, &r, &g, &b);
            if( r==0 && b==0 && g ==0)
            {
                img_bin[i][j]=1;
            }
            else
            {
                img_bin[i][j]=0;

            }
        }
    }
    int r_img[28][28];

    for (int i=0; i<28;i++)
    {
        for (int j=0; j<28; j++)
        {
            r_img[i][j]=0;
        }
    }

    resize(img,img_bin,r_img);
    int comp = 0;
    for (int j=0; j<28; j++)
    {
        for (int i=0; i<28; i++)
        {
            tab[comp] = (float) r_img[i][j];
            comp ++;
        }
    }
    for (int i = 0; i < img -> w; i++)
    {
        free(img_bin[i]);
    }
    free(img_bin);
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


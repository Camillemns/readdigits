#include "main.h"
int in = 28 *28;
int hid = 16;
int out = 10;
net *a;

int main(void)
{
    srand(time(NULL));

    //initialisation net
    SDL_Init(SDL_INIT_EVERYTHING);
    TTF_Init();
    a = init_neural_network(in, hid, out);

    //INTERFACE
    SDL_Surface *ecran = NULL;
    ecran = SDL_SetVideoMode(500, 500, 32, SDL_HWSURFACE | SDL_DOUBLEBUF | SDL_NOFRAME);
    SDL_FillRect(ecran, NULL, SDL_MapRGB(ecran -> format, 0, 0, 0));
    SDL_Flip(ecran);
    wait_for_keypressed();
    fenetre_1(ecran);
    wait_for_keypressed();

    //END
    TTF_Quit();
    SDL_FreeSurface(ecran);
    SDL_Quit();
    free_nn(a);

    return 0;
}

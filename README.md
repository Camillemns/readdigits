# Protocole d’utilisation

Ce projet est un programme de reconnaissance de chiffres écrits à la main en utilisant la méthode de l’apprentissage approfondi aussi connue sous le nom de deeplearnig.

Pour commencer:
 
Le langage utilisé est le C et le programme utilise la librairies SDL ainsi que les librairies complémentaires SDL_image et SDL_TTF. Ce sont des librairies extérieures ils est donc nécessaire de les installer sur la machine pour pouvoir exécuter le programme. Nous avons aussi utilisé d’autres librairies standard : stdlib, stdio, math, et time. 
INSTALATION DES LIBRAIRIES
 
- Vous pourrez trouver les codes sources de ses librairies aux liens suivants :
https://www.libsdl.org/download-2.0.php
https://www.libsdl.org/projects/SDL_image/
https://www.libsdl.org/projects/SDL_ttf/

- Si vous avez linux, il suffit de rentrer des commandes dans le terminal pour les installer :
	Pour la librairie SDL : sudo apt-get install libsdl2-dev
	Pour la librairie SDL_image : sudo apt-get install libsdl-image1.2 libsdl-image1.2-dev
	Pour la libraire SDL_ttf : sudo apt-get install libsdl-ttf2.0-dev
Pour plus d’information sur comment installer ces librairies, nous vous invitons à vous rendre sur le site suivant :
https://openclassrooms.com/fr/courses/19980-apprenez-a-programmer-en-c/17117-installation-de-la-sdl

Exécution du programme:
 
Accéder dans le dossier sources depuis le terminal.
Entrer la ligne de commande :  make 
Puis :  ./main 
 
Une fois le programme lancé:
 
Sur la fenêtre d'accueil : 
Appuyer sur Entrée
Sélectionner à l’aide de la souris un des choix proposés

Dans la fenêtre test : 
utiliser la souris pour effectuer le second choix

Dans la fenêtre Image :
Entrer le nom d’une image présente dans le dossier
 Appuyer sur Entrer pour lancer la reconnaissance et pour poursuivre le processus de reconnaissance
Entrer à nouveau le nom d’une image pour recommencer le processus
Cliquer sur Retour pour retourner sur la page précédente
Attention: une fois le processus de reconnaissance lancé il faut attendre qu’il se termine pour pouvoir quitter la page

Dans la fenêtre Draw: 
dessiner avec la souris sur la zone blanche un chiffre
clic gauche pour effacer le dessin
Appuyer sur Entrée pour lancer la reconnaissance
cliquer sur Retour pour retourner sur la page précédente	

Dans la fenêtre Training: 
cliquer sur go pour lancer le l’entrainement du réseau neuronal
cliquer sur Retour pour retourner sur la page précédente
Attention: une fois le processus d'entraînement lancé il faut attendre qu’il se termine pour pouvoir quitter ma page

Pour quitter le programme: 
appuyer sur Entrée à plusieurs reprises dans la fenêtre d'accueil ou fenêtre Test
une fois la fenêtre fermée entrer dans le terminal entrer :   make clean 

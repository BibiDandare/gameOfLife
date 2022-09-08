#include <stdio.h>
#include <stdlib.h>
#include <time.h>
#include <unistd.h>


/*  Ces constantes sont la taille de notre grille pour le jeu. Elles sont    */
/*  initialisées de sorte à avoir le plus grand affichage net pour mon écran.*/
/*  Ces constantes peuvent être changées par tout celui qui désire de tester */
/*  le code, mais elles ne sont qu'a augmenter que si taille de votre écran  */
/*                      est supérieur à 13,3 pouces                          */

#define nbLignes 45
#define nbColonnes 75

// Nous initialisons des constantes pour faciliter la suite de l'implémentation
enum {mort = 0, vivant = 1};



//  ----------------------------------------------------------------------   //
//  affichage_grille                                                         //
//                                                                           //
//  Cette fonction nous permet d'afficher notre grille sur la console.       //
//  L'affichage se fait avec des 'X' et des points '.' . Une cellule vivante //
//  est représentée par un 'X' et une cellule morte avec un point '.'.       //
//                                                                           //
//  Entrée: Elle prend en entrée le tableau à double dimensions contenant    //
//  nos cellules, un entier 'ligne' représentant le nombre de ligne du       //
//  tableau, et 'colonne' étant le nombre de colonnes.                       //
//                                                                           //
//  Sortie: Cette fonction ne renvoie rien, elle a comme effet de bord       //
//  l'affichage de notre grille                                              //
//  ----------------------------------------------------------------------   //

void affichage_grille(int grille[][nbColonnes], int ligne, int colonne)
{
    int i;
    int j;

    for(i = 0 ; i < ligne ; i++)
    {
        for(j = 0 ; j < colonne ; j++)
        {
            if(grille[i][j] == vivant)
            {
                //  Représentation d'une cellule vivante par 'X'
                printf("X "); 
            }
            else
            {
                //  Cellule morte par '.'
                printf(". ");
            }
        }
        printf("\n");
    }
    printf("\n");

}


//  ----------------------------------------------------------------------   //
//  voisinage                                                                //
//                                                                           //
//  La fonction voisinage nous permet de calculer le nombre de voisins de    //
//  la cellule sélectionnée. La fonciton parcourt les cases de notre         //
//  grille en faisant attention au débordement. La fonction gère également   //
//  le cas ou elle retomberait sur elle même (je ne peux pas être mon propre //
//  voisins).                                                                //
//                                                                           //
//  Entrée: La fonction prend comme paramètre notre grille, la ligne de la   //
//  cellule dont on doit calculer le nombre de voisins, la colonne dont on   //
//  doir calculer le nombre de voisins, le nombre de lignes de notre grille  //
//  et son nombre de colonnes.                                               //
//                                                                           //
//  Sortie: La fonction calcule et renvoie le nombre de voisins de la        //
//  cellule                                                                  //
//  ----------------------------------------------------------------------   //

int voisinage(int grille[][nbColonnes], int  indice_i, int indice_j, 
                                        int  ligne   , int colonne  )
{
    int nbVoisins = 0;
    int i;
    int j;

    //  Boucle nous permettant de parcourir les lignes alentours de la cellule actuelle
    for(i = indice_i - 1 ; i <= indice_i + 1 ; i++)
    {
        //  On vérifie que l'on ne dépasse pas les lignes voisines de la celulle actuelle
        if( i >= 0 && i < ligne)
        {
            //  Boucle nous permettant de parcourir les colonnes alentours de la cellule actuelle
            for( j = indice_j - 1 ; j <= indice_j + 1 ; j++)
            {
                //  On vérifie que nous ne dépassons pas les colonnes voisines de la cellule actuelle
                if(j >= 0 && j < colonne)
                {
                    /*  Ce test nous permet de vérifier que l'on passe exactement sur toutes les  cellules */
                    /*     voisines mais que l'on ne passe pas la cellule actuelle dans la vérification    */
                    if(i != indice_i || j != indice_j)
                    {
                        if(grille[i][j] == vivant)
                        {
                            nbVoisins++;
                        }
                    }
                }
            }
        }
    }
    return nbVoisins;
}

//  ----------------------------------------------------------------------   //
//  voisinageTorique                                                         //
//                                                                           //
//  Notre fonction voisinageTorique se base sur des tests offrant une        // 
//  meilleure complexité que si on parcourait toute la grille en entier.     //
//  Nous vérifions la ligne sur laquelle on se trouve et nous calculons ses  //
//  voisins, si nous sommes sur les bords nous revenons sur la ligne inverse //
//  ou la colonne inverse grâce au modulo (%). Nous avons toute une série de //
//  test parce que si nous sommes sur une ligne ou une colonne égale à 0     //
//  lorsqu'on fait (ligne - 1) % 10 par exemple on pourrait avoir une        //
//  segmation fault. Par contre si on était en python on aurai juste besoin  //
//  du "else" car avec Python3 (-1 % 10 = 9), mais en C (-1 % 10 = -1) donc  //
//  on doit gérer tous les cas possibles pour le fonctionnement de notre     //
//  fonciton.                                                                //
//                                                                           //
//  Entrée : Elle prend en entrée notre grille, la ligne de la cellule sur   //
//  laquelle on se trouve et sa colonne                                      //
//                                                                           //
//  Sortie : Elle nous renvoie le nombre de voisins de la cellule sur un     //
//  environnement torique                                                    //

int voisinageTorique(int grille[][nbColonnes], int indice_i, int indice_j)
{

    int     ligne = indice_i;
    int   colonne = indice_j; 
    int nbVoisins =        0;

    //  Les test qui s'effectueront si nous sommes sur la ligne 0 ou la colonne 0
    if(ligne == 0 && colonne == 0)
    {
        if(grille[ligne][9] == vivant) {nbVoisins++;}
        if(grille[ligne][(colonne + 1) % 10] == vivant) {nbVoisins++;}
        if(grille[9][colonne] == vivant) {nbVoisins++;}
        if(grille[(ligne + 1) % 10][colonne] == vivant) {nbVoisins++;}
        if(grille[9][9] == vivant) {nbVoisins++;}
        if(grille[9][(colonne + 1) % 10] == vivant) {nbVoisins++;}
        if(grille[(ligne + 1) % 10][9] == vivant) {nbVoisins++;}
        if(grille[(ligne + 1) % 10][(colonne + 1) % 10] == vivant) {nbVoisins++;}
        return nbVoisins;
    }
    //  Si la ligne est égale à 0
    else if(ligne == 0)
    {
        if(grille[ligne][(colonne - 1) % 10] == vivant) {nbVoisins++;}
        if(grille[ligne][(colonne + 1) % 10] == vivant) {nbVoisins++;}
        if(grille[9][colonne] == vivant) {nbVoisins++;}
        if(grille[(ligne + 1) % 10][colonne] == vivant) {nbVoisins++;}
        if(grille[9][(colonne - 1) % 10] == vivant) {nbVoisins++;}
        if(grille[9][(colonne + 1) % 10] == vivant) {nbVoisins++;}
        if(grille[(ligne + 1) % 10][(colonne - 1) % 10] == vivant) {nbVoisins++;}
        if(grille[(ligne + 1) % 10][(colonne + 1) % 10] == vivant) {nbVoisins++;}

        return nbVoisins;
    }
    //  Si la colonne est égale à 0
    else if(colonne == 0)
    {
        if(grille[ligne][9] == vivant) {nbVoisins++;}
        if(grille[ligne][(colonne + 1) % 10] == vivant) {nbVoisins++;}
        if(grille[(ligne - 1) % 10][colonne] == vivant) {nbVoisins++;}
        if(grille[(ligne + 1) % 10][colonne] == vivant) {nbVoisins++;}
        if(grille[(ligne - 1) % 10][9] == vivant) {nbVoisins++;}
        if(grille[(ligne - 1) % 10][(colonne + 1) % 10] == vivant) {nbVoisins++;}
        if(grille[(ligne + 1) % 10][9] == vivant) {nbVoisins++;}
        if(grille[(ligne + 1) % 10][(colonne + 1) % 10] == vivant) {nbVoisins++;}
        return nbVoisins;
    }
    //  Lorsque la ligne et la colonne sont différentes de 0
    else
    {
        if(grille[ligne][(colonne - 1) % 10] == vivant) {nbVoisins++;}
        if(grille[ligne][(colonne + 1) % 10] == vivant) {nbVoisins++;}
        if(grille[(ligne - 1) % 10][colonne] == vivant) {nbVoisins++;}
        if(grille[(ligne + 1) % 10][colonne] == vivant) {nbVoisins++;}
        if(grille[(ligne - 1) % 10][(colonne - 1) % 10] == vivant) {nbVoisins++;}
        if(grille[(ligne - 1) % 10][(colonne + 1) % 10] == vivant) {nbVoisins++;}
        if(grille[(ligne + 1) % 10][(colonne - 1) % 10] == vivant) {nbVoisins++;}
        if(grille[(ligne + 1) % 10][(colonne + 1) % 10] == vivant) {nbVoisins++;}
        return nbVoisins;
    }    
}


//  ----------------------------------------------------------------------   //
//  animer_ou_tuer                                                           //
//                                                                           //
//  Après avoir calculé le nombre de voisins d'une cellule, l'on renseigne   //
//  ce dernier à notre fonction animer_ou_tuer, c'est cette fonciton qui va  //
//  s'occuper de donner la vie ou la retirer à une cellule selon ses nombres //
//  de voisins en suivant les règles du jeu.                                 //
//                                                                           //
//  Entrée : Elle prend en entrée une grille, ses nombres de voisins, la     //
//  ligne de la cellule sur laquelle on est, et sa colonne.                  //
//                                                                           //
//  Sortie : Elle renvoie (mort ou vivant) soit les entiers (0 ou 1) pour    //
//  chaque cellule, ce qui déterminera si la cellule doit mourir ou être    //
//  animée.                                                                  //
//  ----------------------------------------------------------------------   //

int animer_ou_tuer(int grille[][nbColonnes], int nbVoisins, int indice_i, int indice_j)
{

    /*  Vérifie si la cellule vivante à 2 ou 3 voisines et la maintient en vie  */
    /*              Sinon elle meurt dans le cas contraire                      */
    if(grille[indice_i][indice_j] == vivant)
    {
        if(nbVoisins == 2 || nbVoisins == 3)
        {
            return vivant;
        }
        else
        {
            return mort;
        }
    }
    //  Vérifie si la cellule morte à exactement 3 voisines pour la rendre vivante, sinon elle reste morte
    else
    {
        if(nbVoisins == 3)
        {
            return vivant;
        }
        else
        {
            return mort;
        }
    }
}


//  ----------------------------------------------------------------------   //
//  deplacement                                                              //
//                                                                           //
//  La fonction déplacement sert à déplacer les cellules par l'intermédiaire //
//  d'une autre grille appelée 'transition'. L'on renseigne à la fonction    //
//  notre grille, nous somme donc à un instant t, à l'instant t + 1 il       //
//  y'aura de nouvelles cellules qui vont naître ou mourir, ces dernières    //
//  sont placées dans la grille transition. Et à la fin l'on affecte toutes  //
//  les cellules de la grille transition à notre grille principale "grille"  //
//  L'on ce sert d'une autre grille car pour avoir nos cellules de l'instant //
//  t + 1 on a besoin de toutes les cellules de l'ancienne grille, ce n'est  //
//  qu'après le calcule que l'on renseigne à notre grille principale les     //
//  nouvelles cellules de l'instant t + 1.                                   //
//                                                                           //
//  Entrée : Elle prend en paramètre notre grille principale, la grille de   //
//  transition, le nombre de lignes de nos grilles et le nombre de colonnes  //
//  (les deux grilles ayant la même dimension)                               //
//                                                                           //
//  Sortie : Cette fonction ne renvoie rien, elle a pour effet de bord le    //
//  calcul de l'état des nouvelles cellules
//  ----------------------------------------------------------------------   //

void deplacement(int grille[][nbColonnes], int transition[][nbColonnes], int ligne, int colonne)
{
    int i;
    int j;

    for(i = 0 ; i < ligne ; i++)
    {
        for(j = 0 ; j < colonne ; j++)
        {
            //  Compte le nombre de voisins de transition[i][j] et détermine l'état suivant de la cellule
            transition[i][j] = animer_ou_tuer(grille, voisinage(grille, i, j, ligne, colonne), i, j);
        }
    }

    for(i = 0 ; i < ligne ; i++)
    {
        for (j = 0 ; j < colonne ; j++)
        {
            // Affectation de l'état t + 1 de nos cellules dans la grille
            grille[i][j] = transition[i][j];
        }
        
    }
}

//  -----------------------------------------------------------------------  //
//  deplacemetTorique                                                        //
//                                                                           //
//  Cette fonction est pareille que notre fonction déplacement, sauf qu'au   //
//  niveau du calcul de l'état t + 1 nous avons un appel de la fonciton      //
//  voisinageTorique contrairement à la fonciton de déplacement simple ou    //
//  c'est l'appel de la fonction voisingae qui est fait. En dehors de ça     //
//  tous les autres paramètre de voisinage et voisinageTorique reste les     //
//  même.                                                                    //
//                                                                           //
//  Entrée : L'on renseigne à la fonction notre grille, la matrice           //
//  transition, ainsi que le nombre de lignes et de colonnes de nos matrices //
//                                                                           //
//  Sortie : Cette fonction ne renvoie aucune donnée, elle a pour effet de   //
//  bord le calcul de l'état t + 1 sur un environnement torique              //
//  -----------------------------------------------------------------------  //

void deplacementTorique(int grille[][nbColonnes], int transition[][nbColonnes], int ligne, int colonne)
{
    int i;
    int j;

    for(i = 0 ; i < ligne ; i++)
    {
        for(j = 0 ; j < colonne ; j++)
        {
            transition[i][j] = animer_ou_tuer(grille, voisinageTorique(grille, i, j), i, j);
        }
    }

    for(i = 0 ; i < ligne ; i++)
    {
        for (j = 0 ; j < colonne ; j++)
        {
            grille[i][j] = transition[i][j];
        }
        
    }
}

//  ----------------------------------------------------------------------   //
//  miniGrille                                                               //
//                                                                           //
//  La fonction miniGrille nous permet d'insérer une matrice de notre choix  //
//  dans notre grille principale, l'on insert donc une petite grille dans    //
//  la grande grille. Cette fonction est utile si l'on veut donner l'état de //
//  départ de nos cellules et voir sans problème leurs évolutions. Nous      //
//  passons ici par des pointeurs pour pouvoir sélectionner une partie de la //
//  mémoire de la grille principale ou l'on veut insérer notre mini grille.  //
//                                                                           //
//  Entrée : Elle prend en entrée une grille principale que l'on renseigne   //
//  par adresse mémoire, le nombre de lignes de la grille principale, son    //
//  nombre de colonnes, une mini grille renseignée aussi par adresse mémoire //
//  le nombre de lignes de la mimi grille, son nombre de colonnes, un entier //
//  'x' qui détermine la ligne de la grille principale ou on doit insérer la //
//  mini grille, et un entier 'y' la colonne de la grille principale ou on   //
//  doit insérer la mini grille.                                             //
//                                                                           //
//  Sortie : La fonction ne renvoie rien, elle a pour effet de bord          //
//  l'insertion d'une matrice de notre choix qui sera le début des états de  //
//  l'évoution de nos cellules dans la grille principale.                    //
//  ----------------------------------------------------------------------   //
void miniGrille(int *grille, int ligne, int colonne, int *jeu, int ligne_jeu, int colonne_jeu, int x, int y)
{
    int i;
    int j;

    for(i = y ; i < y + ligne_jeu ; i++)
    {
        for(j = x ; j < x + colonne_jeu ; j++)
        {
            /*  *(grille + i * colonne + j est équivalent à grille[i][j], c'est juste */
            /*                  que nous passons par des pointeurs                    */                  
            *(grille + i * colonne + j) = *(jeu + (i -  y) * colonne_jeu + (j - x));
        }
    }
}


//  ----------------------------------------------------------------------   //
//  random_init                                                              //
//                                                                           //
//  C'est à l'aide de cette fonction que nous initialisons nos grilles. Vu   //
//  que l'on a que deux choix possible, vivant/mort, nous n'avons pas besoin //
//  d'utiliser un super générateur pour le choix aléatoire de nos variables, //
//  la fonction rand() nous permet parfaitement de choisir entre vivant ou   //
//  mort avec "rand()%2".                                                    //
//                                                                           //
//  Entrée : La fonction prend en entrée un tableau à double dimension qui   //
//  est notre grille, le nombre de ligne de la grille, et son nombre de      //
//  colonne.                                                                 //
//                                                                           //
//  Sortie : Cette fonction ne renvoie rien, elle a pour effet de bord       //
//  l'affectation de chaque cellules de notre grille avec soit 0 ou 1        //
//                                                         (mort ou vivant)  //
//  ----------------------------------------------------------------------   //

void random_init(int grille[][nbColonnes], int ligne, int colonne)
{
    int i;
    int j;
    for(i = 0 ; i < ligne ; i++)
    {
        for(j = 0 ; j < colonne ; j++)
        {
            //  Affectation aléatoire entre 0 et 1 donc entre (mort et vivant)
            grille[i][j] = rand()%2;
        }
    }
}

//  ----------------------------------------------------------------------   //
//  glider_10                                                                //
//                                                                           //
//  La fonction glider_10 nous permet d'initialiser notre grille de façon    //
//  non aléatoire, en effet elle initialise la grille de telle sorte qu'elle //
//  produise un glider (planeur) uniquement sur une grille 10*10            //
//                                                                           //
//  Entrée : Elle prend en paramètre une grille, son nombre de lignes, et    //
//  son nombre de colonnes.                                                  //
//                                                                           //
//  Sortie : La fonction ne renvoie rien, elle se permet juste d'initialiser //
//  notre grille selon les paramètres que l'on lui a soumise                 //
//  ----------------------------------------------------------------------   //

void glider_10(int grille[][nbColonnes], int ligne, int colonne)
{
    int i;
    int j;

    for(i = 0; i < ligne ; i++)
    {
        for(j = 0 ; j < colonne ; j++)
        {
            if( (i == 1 && j == 1) || (i == 2 && j == 2) || (i == 3 && j == 0) ||
                                      (i == 3 && j == 1) || (i ==3 && j == 2))
            {
                grille[i][j] = vivant;
            }
            else
            {
                grille[i][j] = mort;
            }
        }
    }
}



int main(int argc, char *argv[])
{
    srand(time(NULL));

    //  Initialisation
    int grille[nbLignes][nbColonnes] = {mort};
    int transition[nbLignes][nbColonnes] = {mort};

    /*  Initialisation d'un tableau nous permettant d'avoir un canon à glider (planeurs)   */
    /*                  LA SOURCE DU TABLEAU SERA NOTIFIÉE DANS LE RAPPORT                  */
    int glider[9][36] = {
        {0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 1, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0},
        {0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 1, 0, 1, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0},
        {0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 1, 1, 0, 0, 0, 0, 0, 0, 1, 1, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 1, 1},
        {0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 1, 0, 0, 0, 1, 0, 0, 0, 0, 1, 1, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 1, 1},
        {1, 1, 0, 0, 0, 0, 0, 0, 0, 0, 1, 0, 0, 0, 0, 0, 1, 0, 0, 0, 1, 1, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0},
        {1, 1, 0, 0, 0, 0, 0, 0, 0, 0, 1, 0, 0, 0, 1, 0, 1, 1, 0, 0, 0, 0, 1, 0, 1, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0},
        {0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 1, 0, 0, 0, 0, 0, 1, 0, 0, 0, 0, 0, 0, 0, 1, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0},
        {0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 1, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0},
        {0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 1, 1, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0},
    };


    int choix3;
    int choix2;
    int choix1;
    int  choix;

    /*  Selon les éditeurs de texte, les lignes des printf sont extrèmement  */
    /*  longues car si on veut avoir des retours à la ligne sur notre        */
    /*  console à l'affichage on est obligé d'écrire tout dans une même      */
    /*  ligne de printf et de séparer nos lignes avec des retours à la ligne */
    /*  '\n'. Le retour à la ligne généré par la touche entrée du clavier    */
    /*              n'est pas pris en compte avec le printf                  */                

    printf("\n");
    printf("Bienvenue au jeu de la vie! \n");
    printf("\n");

    printf("Appuyer sur 1 pour lancer une partie alétoire en plein écran\n");
    printf("\n");

    printf("Appuyer sur 2 pour lancer une partie aléatoire à échelle réduite avec des dimensions précises\n");
    printf("\n");

    printf("Appuyer sur 3 pour lancer une partie aléatoire à échelle réduite avec des dimensions précises avec un temps pour la cadence des évolutions de nos cellules\n");
    printf("\n");

    printf("Appuyer sur 4 pour lancer une partie avec le glider (planeur) sur une grille 10*10 comme celle de la question 1 de l'énoncé sur une grille NORMALE\n");
    printf("\n");

    printf("Appuyer sur 5 pour lancer une partie avec le glider (planeur) sur une grille 10*10 comme celle de la question 1 de l'énoncé sur une grille TORIQUE\n");
    printf("\n");

    printf("Appuyer sur 6 pour lancer une partie non aléatoire en plein écran avec un canon de gliders (planeurs)\n");
    printf("\n");

    printf("NB : Plus petites seront les dimensions de la grille moins précises seront les séquences de résultats\n     Plus petites seront les dimensions de la grille plus rapide et plus ennuyant sera le jeu\n     Le programme étant très rapide il faudra parfois appuyer rapidement plusieurs fois crtl-c pour l'arrêter\n     En tapant des nombres pour une grille plus petite avec le choix 2, veiller à ne rentrer aucun autre caractère que des chiffres\n     Avec le choix 2, si vous choisissez des dimensions pour la grille plus grande que les dimensions de votre écran, l'affichage risque d'être corrompu !\n     (conseils : ne pas dépasser 45 lignes ou 75 colonnes pour un écran de 13,3 pouces)\n");

    printf("\n");
    printf("Pour quitter le programme à n'importe quel moment, appuyer sur (contrôle et c simultanément) crtl-c \n");

    scanf("%d", &choix);

    switch(choix)
    {
        case 1 :

            //  Affectation aléatoire : (soit mort soit vivant pour chaque case)
            random_init(grille, nbLignes, nbColonnes);

            //  boucle permettant le déroulement monotone du jeu
            while(-1)
            {
                //  Permet de réniatiliser le terminal à chaque passage pour donner l'effet d'immobilité de la grille
                system("clear");

                /*  Déroulement du jeu avec permutation entre la matrice grille et la nouvelle matrice transition contenant */
                /*                          les nouveaux éléments vivants ou morts au temps t + 1                           */
                deplacement(grille, transition, nbLignes, nbColonnes);

                affichage_grille(grille, nbLignes, nbColonnes);

                //coupure du programme pour la facilité du ctrl-c
                usleep(15000);
            }
        break;

        case 2 :

            printf("Saisissez le nombre de lignes\n");
            printf("\n");

            scanf("%d", &choix1);

            printf("Saisissez maintenant le nombre de colonnes\n");
            printf("\n");

            scanf("%d", &choix2);

            random_init(grille, choix1, choix2);

            while(-1)
            {
                system("clear");

                deplacement(grille, transition, choix1, choix2);

                affichage_grille(grille, choix1, choix2);

                usleep(15000);
            }

        break;

        case 3 :

            printf("Saisissez le nombre de lignes\n");
            printf("\n");

            scanf("%d", &choix1);

            printf("Saisissez maintenant le nombre de colonnes\n");
            printf("\n");

            scanf("%d", &choix2);

            printf("Saisissez un temps en microsecondes la cadence des évolutions  (de préférence supérieur ou égale à 15000 pour faciliter le ctrl-c)\n");
            printf("\n");

            scanf("%d", &choix3);

            random_init(grille, choix1, choix2);

            while(-1)
            {
                system("clear");

                deplacement(grille, transition, choix1, choix2);

                affichage_grille(grille, choix1, choix2);

                usleep(choix3);
            }

        break;
        
        case 4 :

            //  Initialisation d'une grille qui va générer un seul glider, comme dans la question 1 de l'énoncé
            glider_10(grille, 10, 10);

            while(-1)
            {
                system("clear");

                deplacement(grille, transition, 10, 10);

                affichage_grille(grille, 10, 10);

                usleep(50000);
            }

        break;

        case 5 :

            //  Initialisation d'une grille qui va générer un seul glider, comme dans la question 1 de l'énoncé ---TORIQUE---

            glider_10(grille, 10, 10);

            while(-1)
            {
                system("clear");

                //  grille torique
                deplacementTorique(grille, transition, 10, 10);

                affichage_grille(grille, 10, 10);

                usleep(50000);
            }

        break;

        case 6 :

            //  Insertion du tableau "glider" dans notre grille
            miniGrille(&grille[0][0], nbLignes, nbColonnes, &glider[0][0], 9, 36, 20, 10);

            while(-1)
            {
                system("clear");

                deplacement(grille, transition, nbLignes, nbColonnes);

                affichage_grille(grille, nbLignes, nbColonnes);

                usleep(15000);
            }

        break;

        default : 
            printf("Choix incorrect, veuillez relancer le jeu s'il vous plaît\n");
    }

    return 0;
}
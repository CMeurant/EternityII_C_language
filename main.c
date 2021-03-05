#include <stdio.h>
#include <stdlib.h>
#include <time.h>
#include <String.h>


/**
 * INFO 4A - PROJET 2019-2020 - L2
 * Auteurs : MEURANT Christophe & CHIBILE Romuald
 * Enseignant de TP : MORLET Lucas
 **/
 
char*** genPuzzEXP(int);
int isSolved(char***,int);
char*** mixGame(char***,int);
char*** swapPiece(char***,char[]);
char*** turnPiece(char***,char[]);
int IAcorrespondence(char***,int,int,int,int,int);
void IAplaying(char***,int);
void display(char***,int);
void freeTab(char***,int);
void theGame(char***,int);

/**
 * Rappel des positions des coords de chaque pièce dans le tab :
 *   0 : NORD
 *   1 : EST
 *   2 : SUD
 *   3 : OUEST
 **/

/**
 * Fonction main() du programme. Indispensable !
 **/
 
int main()
{
    int tabSize;
    printf("Bienvenue dans ce merveilleux jeu : ETERNITY II\n");
    printf("******************************************************\n");
    do
	{
        printf("Merci d'indiquer la taille de tableau souhaitee, comprise entre 4 et 7 !\n");
        scanf("%d", &tabSize);
    }while(tabSize<4 || tabSize>7);
	printf("Vous jouerez cette partie sur un tableau de taille %d\n",tabSize);
    char*** tabJeu=genPuzzEXP(tabSize);
	mixGame(tabJeu,tabSize);
    display(tabJeu,tabSize);
    theGame(tabJeu,tabSize);
    freeTab(tabJeu,tabSize);

	return 0;
}

/**
 * Méthode permettant l'allocution mémoire nécessaire à la génération d'un puzzle finissable.
 * Prends la taille désirée pour le puzzle en paramètre afin de retourner le char*** adéquat.
 * -> Alloue la mémoire nécessaire dans un premier temps
 * -> Puis génère un puzzle finissable ( détaillé dans le rapport )
 **/

char*** genPuzzEXP(int size)
{
	srand(time(NULL));
    char*** puzzle=(char***)calloc(size,sizeof(char**));
    for(int i=0;i<size;i++)
	{
        puzzle[i]=(char**)calloc(size,sizeof(char*));
        for(int j=0;j<size;j++)
		{
            puzzle[i][j]=(char*)calloc(4,sizeof(char));
        }
    }
	
    /** 
	 * La mémoire pour le puzzle est allouée
     * Génération s'en suit..
	 **/

    for(int lig=0;lig<size;lig++)
	{
        for(int col=0;col<size;col++)
		{
            for(int pos=0;pos<4;pos++)
			{
                puzzle[lig][col][pos]=('A'+rand()%4);
            }
        }

        /** 
		 * Ligne générée, on vérifie que celle-ci n'a pas de problèmes.
         * Si on est pas sur la première ligne, on vérifie par rapport aux pièces du dessus.
		 **/

        if(lig!=0)
		{
            for(int col=0;col<size;col++)
			{
                if(puzzle[lig][col][0] != puzzle[lig-1][col][2])
				{
                    puzzle[lig][col][0]=puzzle[lig-1][col][2];
                }
            }
        }
		
        /**
		 * Si on se trouve sur la dernière ligne du tableau, on vérifie que les positions SUD correspondent aux NORD de la première
		 **/
		 
        if(lig==size-1)
		{
            for(int col=0;col<size;col++)
			{
                if(puzzle[lig][col][2] != puzzle[0][col][0])
				{
                    puzzle[lig][col][2] = puzzle[0][col][0];
                }
            }
        }

        /** 
		 * Dans TOUS les cas on vérifie les positions OUEST/EST de chaque pièce...
		 **/
		 
        for(int col=0;col<size;col++)
		{
            /** 
			 * Avec un cas spécifique pour la première, qu'on compare à la dernière
			 **/

            if(col==0)
			{
                if(puzzle[lig][0][3] != puzzle[lig][size-1][1])
				{
                    puzzle[lig][0][3]=puzzle[lig][size-1][1];
                }
            }
            else
			{
                if(puzzle[lig][col][3] != puzzle[lig][col-1][1])
				{
                    puzzle[lig][col][3]=puzzle[lig][col-1][1];
                }
            }
        }
    }
    return puzzle;
}

/**
 * Algorithme de vérification de l'instance courante du puzzle.
 * Le tableau et sa taille sont donnés en paramètre. Il renverra 1 ou 0, à la manière d'un booléen, afin de savoir si le puzzle est terminé.
 **/
 
int isSolved(char*** tab, int size)
{
    /**
	 * La fonction renvoie 1 si elle arrive à son terme. A la moindre erreur elle renvoie 0.
	 * Le processus est plus ou moins similaire à celui de la fonction genPuzzEXP()
	 **/
	 
    for(int lig=0;lig<size;lig++)
	{
        for(int col=0;col<size;col++)
		{      
            if(lig!=0)
			{
                for(int col=0;col<size;col++)
				{
                    if(tab[lig][col][0] != tab[lig-1][col][2])
					{
                        return 0;
                    }
                }
            }
            if(lig==size-1)
			{
                for(int col=0;col<size;col++)
				{
                    if(tab[lig][col][2] != tab[0][col][0])
					{
                        return 0;
                    }
                }
            }
            for(int col=0;col<size;col++)
			{
                if(col==0)
				{
                    if(tab[lig][0][3] != tab[lig][size-1][1])
					{
                        return 0;
                    }
                }
                else
				{
                    if(tab[lig][col][3] != tab[lig][col-1][1])
					{
                        return 0;
                    }
                }
            }
        }
    }
    return 1;
}

/**
 * Méthode permettant de mélanger le jeu.
 **/
 
char*** mixGame(char*** tabPuzzle, int size)
{
    int nbMix=((rand()%20)+10)*size*size,mix=0;
    char tabAlea[4];

    for(int i=0;i<=nbMix;i++)
    {
        mix=rand()%2;
        if (!mix)
        {
            for(int j=0;j<4;j++)
			{
                tabAlea[j]=rand()%(size-1) + ('0'*(j%2)) + ('a'*((j+1)%2));
			}
            tabPuzzle=swapPiece(tabPuzzle,tabAlea);
        }
        else
        {
            for(int j=0;j<2;j++)
			{
                tabAlea[j]=rand()%(size-1) + ('0'*(j%2)) + ('a'*((j+1)%2));
			}
            tabAlea[2]=(rand()%2)*'L';
            tabPuzzle=turnPiece(tabPuzzle,tabAlea);
        }
    }
    return tabPuzzle;
}

/**
 * Méthode utilisée dans le jeu afin d'échanger deux pièces de place dans le tableau.
 * Les indices du tableau de char choix sont écrits ainsi ; 0 et 2 : lettres(lignes) // 1 et 3 : chiffres des pièces(colonnes)
 **/
 
char*** swapPiece(char*** tab, char choix[])
{
    char tmpPiece[4];
    for(int i=0;i<4;i++)
    {
        tmpPiece[i]=tab[choix[0]-'a'][choix[1]-'0'][i];
        tab[choix[0]-'a'][choix[1]-'0'][i]=tab[choix[2]-'a'][choix[3]-'0'][i];
        tab[choix[2]-'a'][choix[3]-'0'][i]=tmpPiece[i];
    }
    return tab;
}

/**
 * Méthode utilisée dans le jeu afin de tourner une pièce.
 * Les indices du tableau de char choix sont écrits ainsi ; 0 :lettre(lignes) // 1: chiffre(colonnes) // 2: lettre pour la rotation(facultative)
 **/
char*** turnPiece(char***tab, char choix[])
{
    char tmpPiece;
    if (choix[2]==0 || choix[2]-'R' ==0 || choix[2]-'r' ==0)
    {
        tmpPiece=tab[choix[0]-'a'][choix[1]-'0'][0];
        tab[choix[0]-'a'][choix[1]-'0'][0]=tab[choix[0]-'a'][choix[1]-'0'][3];
        tab[choix[0]-'a'][choix[1]-'0'][3]=tab[choix[0]-'a'][choix[1]-'0'][2];
        tab[choix[0]-'a'][choix[1]-'0'][2]=tab[choix[0]-'a'][choix[1]-'0'][1];
        tab[choix[0]-'a'][choix[1]-'0'][1]=tmpPiece;
    }

    else
    {
        tmpPiece=tab[choix[0]-'a'][choix[1]-'0'][0];
        tab[choix[0]-'a'][choix[1]-'0'][0]=tab[choix[0]-'a'][choix[1]-'0'][1];
        tab[choix[0]-'a'][choix[1]-'0'][1]=tab[choix[0]-'a'][choix[1]-'0'][2];
        tab[choix[0]-'a'][choix[1]-'0'][2]=tab[choix[0]-'a'][choix[1]-'0'][3];
        tab[choix[0]-'a'][choix[1]-'0'][3]=tmpPiece;
    }
    return tab;
}


/** 
 * Fonction utilisée exclusivement par l'IA pour reproduire le processus de réflexion humain avant de déplacer une pièce.
 * Son utilisation est détaillée dans le rapport.
 **/
 
int IAcorrespondence(char*** tab,int size, int X, int Y, int X2, int Y2)
{
	/**
	 * X et Y l'emplacement hypothétique de la pièce testée,
	 * X2 et Y2 la pièce testée.
	 **/

	if(X==0)
	{ // Première ligne. Vérification à l'Ouest de la pièce, à l'Est pour la dernière
		if(Y==size-1)
		{
			return ((tab[X2][Y2][3] == tab[X][Y-1][1]) && (tab[X2][Y2][1] == tab[X][Y-size+1][3]));
		}
		else
		{
			return (tab[X2][Y2][3] == tab[X][Y-1][1]);
		}
	}
	else if(X==size-1)
	{ // Dernière ligne. Vérification N S pour la premire pièce. N S O E pour la dernière. N S O pour les autres.
		if(Y==0)
		{
			return ((tab[X2][Y2][0] == tab[X-1][Y][2]) && (tab[X2][Y2][2] == tab[X-size+1][Y][0]));
		}
		else if(Y==size-1)
		{
			return isSolved(tab,size); // Comme il s'agit de la dernière pièce à tenter, il n'y a plus qu'à vérifier si le tableau entier est correct.
		}
		else
		{
			return ((tab[X2][Y2][3] == tab[X][Y-1][1]) && (tab[X2][Y2][0] == tab[X-1][Y][2]) && (tab[X2][Y2][2] == tab[X-size+1][Y][0]));
		}
	}
	else
	{ // Lignes intermédiaires. Vérification N pour la première pièce. N O E pour la dernière. N O pour les autres.
		if(Y==0)
		{
			return tab[X2][Y2][0] == tab[X-1][Y][2];
		}
		else if(Y==size-1)
		{
			return ((tab[X2][Y2][3] == tab[X][Y-1][1]) && (tab[X2][Y2][0] == tab[X-1][Y][2]) && (tab[X2][Y2][1] == tab[X][Y-size+1][3]));
		}
		else
		{
			return ((tab[X2][Y2][0] == tab[X-1][Y][2]) && (tab[X2][Y2][3] == tab[X][Y-1][1]));
		}
	}
}

/**
 * Fonction permettant à l'IA de jouer et de procéder à ses choix dans la résolution du puzzle.
 * Son utilisation est détaillée dans le rapport.
 **/

void IAplaying(char*** tab, int size)
{
	int resolved=0; // si cette variable passe à 1, le jeu est gagné !
	int pieceTrouvee=0; // Pour arrêter de faire tourner la pièce pour rien
	int cptDeplace=0;
	int cptTourne=0;
	while(!isSolved(tab,size))
	{
		for(int lig=0;lig<size;lig++)
		{
			for(int col=0;col<size;col++)
			{
				if(lig==0 && col==0)
				{ 	// Début d'une nouvelle recherche pour l'IA ; celle-ci prend une pièce aléatoire comme "base"
					char choix[4];
					choix[0]='a';
					choix[1]='0';
					choix[2]=rand()%size+'a';
					choix[3]=rand()%size+'0';
					tab=swapPiece(tab,choix);
					cptDeplace++;
				}
				else
				{ // L'IA est en train de résoudre le puzzle. Elle va chercher des correspondances avec la pièce en cours de traitement.
					pieceTrouvee=0;
					for(int ligTest=size-1;ligTest>=lig && !pieceTrouvee ;ligTest--)
					{
						for(int colTest=size-1 ; colTest>=(ligTest==lig?col:0) && !pieceTrouvee ;colTest--)
						{ 	// Tant qu'on a pas tout testé, ou trouvé une solution..
							char currentPiece[4];
							currentPiece[0]=ligTest+'a';
							currentPiece[1]=colTest+'0';
							pieceTrouvee=IAcorrespondence(tab,size,lig,col,ligTest,colTest);
							if(pieceTrouvee)
							{
								currentPiece[2]=lig+'a';
								currentPiece[3]=col+'0';
								swapPiece(tab,currentPiece);
								cptDeplace++;
							}
							else
							{
								for(int i=0; i<4 && pieceTrouvee==0 ;i++)
								{
									tab=turnPiece(tab,currentPiece);
									pieceTrouvee=IAcorrespondence(tab,size,lig,col,ligTest,colTest);
									cptTourne++;
								}
								if(pieceTrouvee)
								{
									currentPiece[2]=lig+'a';
									currentPiece[3]=col+'0';
									tab=swapPiece(tab,currentPiece);
								}
							}
						}
					}
				}
			}
		}
		resolved=isSolved(tab,size);
		if(resolved)
		{
			display(tab,size);
			printf("L'IA a fini ! Deplacements : %d ; Rotations : %d \n",cptDeplace,cptTourne);
		}
	}
}

/**
 * Fonction d'affichage du jeu. Appelée à chaque étape, elle ne renvoie rien mais affiche le tableau dans son état actuel.
 **/
 
void display(char*** tab, int size)
{
    //Affiche le numero de la colonne
    for(int i=0;i<size;i++)
	{
       printf("    %d ",i);
	}
    printf("\n");
	//Affiche le puzzle ligne par ligne
    for(int i=0;i<size;i++)
    {
        int ligAffich=0;
        for(int j=0;j<size;j++)
		{//Affiche le haut des pieces d'une ligne
            printf("    %c ",tab[i][j][0]);
		}
        printf("\n");

        for(int j=0;j<size;j++)//Affiche le centre des pieces d'une ligne
        {
            if(!ligAffich)
			{//Permet un affichage unique par ligne
                printf("%c ",i+'a');
			}
            printf("%c # %c ",tab[i][j][3],tab[i][j][1]);
            ligAffich=1;
        }
        printf("\n");

        for(int j=0;j<size;j++)
		{//Affiche le bas des pieces d'une ligne
            printf("    %c ",tab[i][j][2]);
		}
        printf("\n");
    }
    printf("\n######################################################\n\n");
}

/**
 * Fonction permettant de procéder à la libération de l'espace mémoire occupé par le jeu
 **/
 
void freeTab(char*** tab, int size)
{
    for(int i=0;i<size;i++)
    {
        for(int j=0;j<size;j++)
		{
            free(tab[i][j]);
		}
        free(tab[i]);
    }
    free(tab);
}

/**
 * Très joli menu du jeu, interactif, vous n'avez qu'à compiler, exécuter et jouer pour le tester !
 **/
 
void theGame(char*** puzzle,int size)
{
    int win=0;
    char input[50];
    printf("Pour afficher les commandes disponible entrez: help\n");
    while(!win)
    {
        scanf("%s", &input[0]);

        if(strcmp(input,"help") == 0 || strcmp(input,"Help") == 0)
        {
            printf("Pour afficher les regles du jeu entrez: rules\n");
            printf("Pour que l'IA gagne pour vous entrez: win\n");
            printf("Pour effectuer une rotation entrez les coordoonees de la piece exemple: a0\n");
            printf("Par defaut la rotation s'effectue vers la droite sauf si vous precisez left ou right exemple: a0r\n");
            printf("Pour effectuer un echange entrez les coordoonees des pieces exemple: a0a2\n");
            printf("Pour afficher le puzzle entrez: refresh\n");
        }
        else if(strcmp(input,"rules") == 0 || strcmp(input,"Rules") == 0)
        {
            printf("Dans Eternity II vous controlez les pieces d'un puzzle \nPour resoudre celui-ci vous pouvez effectuer des rotations et echanger la place de deux pieces \n");
            printf("Afin que chaque face d'une piece voit un motif identique au sien sur la piece juxtaposee \n/!\\ La face superieur d'une colonne est contigu avec la face inferieur de cette meme colonne /!\\ \n");
            printf("/!\\ La face droite d'une ligne est contigu avec la face gauche de cette meme ligne /!\\ \n");
        }
        else if(strcmp(input,"refresh") == 0 || strcmp(input,"Refresh") == 0)
		{
            display(puzzle,size);
		}
        else if(strcmp(input,"win") == 0 || strcmp(input,"Win") == 0)
        {
            IAplaying(puzzle,size);
            win=isSolved(puzzle,size);
        }
        else if(strcmp(input,"dev") == 0 || strcmp(input,"Dev") == 0)
        {
            printf("Bravo tu es le meilleur\nTu as realise le meilleur score\nLes medecins te deteste avec ta solution miracle\nTu es genial\nTu obtiens la note de 20/20\nTon score est : S+\nTu es parfait\nVoila ton prix \n ");
            printf(" ___________\n '._==_==_=_.'\n .-\\  you  /-.\n| (|  are  |) |\n '-|  the  |-'\n   \\  best /\n    '.   .'\n      ) (\n    _.' '._\n");
            win++;
        }
        else if(strlen(input) == 2 || strlen(input) == 3)
        {
            if((input[0]-'a')<=size && (input[1]-'0')<=size)
            {
                if (input[2]==0 || input[2]-'R' ==0 || input[2]-'r' ==0 || input[2]-'L' ==0 || input[2]-'l' ==0)
                {
                    puzzle=turnPiece(puzzle,input);
                    display(puzzle,size);
                    win=isSolved(puzzle,size);
                }
                else
                printf("Commande invalide !\nPour effectuer une rotation a droite ou a gauche specifiez R ou L \n");
            }
            else if ((input[0]-'0')<=size && (input[1]-'a')<=size)
			{
                printf("/!\\ Vous avez interverti ligne et colonne /!\\ \n");
			}
            else
			{
                printf("Commande invalide !\nPour afficher les regles du jeu entrez: rules\nPour afficher les commandes disponible entrez: help\n");
			}
		}
        else if(strlen(input) == 4)
        {
            if((input[0]-'a')<=size && (input[1]-'0')<=size && (input[2]-'a')<=size && (input[3]-'0')<=size )
            {
            puzzle=swapPiece(puzzle,input);
            display(puzzle,size);
            win=isSolved(puzzle,size);
            }
            else if((input[0]-'0')<=size && (input[1]-'a')<=size && (input[2]-'0')<=size && (input[3]-'a')<=size )
            {				
				printf("/!\\ Vous avez interverti la ligne et la colonne des deux pieces /!\\ \n");
			}
            else if ((input[0]-'0')<=size && (input[1]-'a')<=size)
			{
                printf("/!\\ Vous avez interverti la ligne et la colonne de la premiere piece /!\\ \n");
			}
            else if ((input[2]-'0')<=size && (input[3]-'a')<=size)
			{
                printf("/!\\ Vous avez interverti la ligne et la colonne de la seconde piece /!\\ \n");
			}
            else
			{
                printf("Commande invalide !\nPour afficher les regles du jeu entrez: rules\nPour afficher les commandes disponible entrez: help\n");
			}
		}
        else
		{
            printf("N'ecrivez pas n'importe quoi !\nPour afficher les regles du jeu entrez: rules\nPour afficher les commandes disponible entrez: help\n");
		}
	}
    printf("Congratulation you beat the Game !\n");
}

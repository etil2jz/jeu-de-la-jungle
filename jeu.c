/*
Le projet consiste plus spécialement à modéliser le jeu en mode texte (dans un premier temps).
Les pions seront des lettres. Le déplacement des pièces se fera d’abord par l’entrée des coordonnées
puis par l'intermédiaire de la souris.
Suivant l’avancement du projet, le programme permettra :
	- de jouer à deux sur le même PC
	- de jouer contre l’ordinateur grâce à l’implantation d’une intelligence artificielle
	- de jouer contre un autre logiciel (une intelligence artificielle contre l’autre)
La réalisation en mode graphique apportera un bonus (maximum 2 points), mais n’est pas obligatoire.



Gérer les commandes de l'utilisateur :
	- Placer les pions
	- Contrôler le déroulement de la partie (règles...)
	- Jouer un coup
	- Reprendre une partie à partir d'un coup donné
	- Sauver la partie sur disque
	- Calculer les points des joueurs

Sortie sur écran des informations

Définir les structures de données permettant la résolution de ce problème

Décrire sous forme modulaire les différentes séquences de fonctionnement

Traduire les structures de données et les actions en C
*/

#include <stdio.h>
#include <stdlib.h>
#include <windows.h>
#include <string.h>

void regles() {
	system("color A");
	printf_s("            \x10 REGLES DU JEU \x11");
	printf_s("\n\n\x16 Chaque joueur deplace, a son tour, une des pieces d'une seule case a la fois, horizontalement ou verticalement.\n\n\x16 A l'occasion d'un deplacement une piece peut prendre une piece adverse egale ou inferieure en se mettant a sa place. La piece prise est enlevee du jeu. Cependant, le rat peut prendre l'elephant.\n\n\x16 Seul le rat peut se deplacer dans les lacs mais il ne peut pas capturer l'elephant adverse en passant du lac sur la rive.\n\n\x16 Les lions et les tigres peuvent sauter directement d'une rive a l'autre verticalement ou horizontalement sauf si un rat (ami ou adverse) se trouve dans la ligne de saut.\n\n\x16 Quand une piece se trouve dans un piege adverse, sa force combative devient momentanement nulle mais elle conserve la possibilite de se deplacer.\n\n\x16 Les pieces ne peuvent pas entrer dans leur propre sanctuaire.\n\n\nPatientez 10 secondes...\n");
	Sleep(1000);
	system("cls");
	system("color b");
}

typedef struct rat {
	int x, y, oldVraiX, oldVraiY, force, etat;
	char nom;
}rat;

typedef struct chat {
	int x, y, oldVraiX, oldVraiY, force, etat;
	char nom;
}chat;

typedef struct loup {
	int x, y, oldVraiX, oldVraiY, force, etat;
	char nom;
}loup;

typedef struct chien {
	int x, y, oldVraiX, oldVraiY, force, etat;
	char nom;
}chien;

typedef struct panthere {
	int x, y, oldVraiX, oldVraiY, force, etat;
	char nom;
}panthere;

typedef struct tigre {
	int x, y, oldVraiX, oldVraiY, force, etat;
	char nom;
}tigre;

typedef struct lion {
	int x, y, oldVraiX, oldVraiY, force, etat;
	char nom;
}lion;

typedef struct elephant {
	int x, y, oldVraiX, oldVraiY, force, etat;
	char nom;
}elephant;

void initPlateau(char plateau[][15], rat ratbleu, rat ratrouge, chat chatbleu, chat chatrouge, loup loupbleu, loup louprouge, chien chienbleu, chien chienrouge, panthere pantherebleu, panthere panthererouge, tigre tigrebleu, tigre tigrerouge, lion lionbleu, lion lionrouge, elephant elephantbleu, elephant elephantrouge) {
	plateau[1][1] = lionbleu.nom;
	plateau[1][3] = ' ';
	plateau[1][5] = ' ';
	plateau[1][7] = ' ';
	plateau[1][9] = ' ';
	plateau[1][11] = ' ';
	plateau[1][13] = tigrebleu.nom;

	plateau[3][1] = ' ';
	plateau[3][3] = chienbleu.nom;
	plateau[3][5] = ' ';
	plateau[3][7] = ' ';
	plateau[3][9] = ' ';
	plateau[3][11] = chatbleu.nom;
	plateau[3][13] = ' ';
	
	plateau[5][1] = ratbleu.nom;
	plateau[5][3] = ' ';
	plateau[5][5] = pantherebleu.nom;
	plateau[5][7] = ' ';
	plateau[5][9] = loupbleu.nom;
	plateau[5][11] = ' ';
	plateau[5][13] = elephantbleu.nom;

	plateau[7][1] = ' ';
	plateau[7][3] = '\xB0';
	plateau[7][5] = '\xB0';
	plateau[7][7] = ' ';
	plateau[7][9] = '\xB0';
	plateau[7][11] = '\xB0';
	plateau[7][13] = ' ';

	plateau[9][1] = ' ';
	plateau[9][3] = '\xB0';
	plateau[9][5] = '\xB0';
	plateau[9][7] = ' ';
	plateau[9][9] = '\xB0';
	plateau[9][11] = '\xB0';
	plateau[9][13] = ' ';

	plateau[11][1] = ' ';
	plateau[11][3] = '\xB0';
	plateau[11][5] = '\xB0';
	plateau[11][7] = ' ';
	plateau[11][9] = '\xB0';
	plateau[11][11] = '\xB0';
	plateau[11][13] = ' ';

	plateau[13][1] = elephantrouge.nom;
	plateau[13][3] = ' ';
	plateau[13][5] = louprouge.nom;
	plateau[13][7] = ' ';
	plateau[13][9] = panthererouge.nom;
	plateau[13][11] = ' ';
	plateau[13][13] = ratrouge.nom;

	plateau[15][1] = ' ';
	plateau[15][3] = chatrouge.nom;
	plateau[15][5] = ' ';
	plateau[15][7] = ' ';
	plateau[15][9] = ' ';
	plateau[15][11] = chienrouge.nom;
	plateau[15][13] = ' ';

	plateau[17][1] = tigrerouge.nom;
	plateau[17][3] = ' ';
	plateau[17][5] = ' ';
	plateau[17][7] = ' ';
	plateau[17][9] = ' ';
	plateau[17][11] = ' ';
	plateau[17][13] = lionrouge.nom;
}

void affichagePlateau(char plateau[][15]) {
	system("cls");
	for (int i = 0; i < 19; i++) {
		if ((i % 2) == 0) {
			for (int j = 0; j < 15; j++) {
				plateau[i][j] = '-';
			}
		}
		else {
			for (int j = 0; j < 15; j += 2) {
				plateau[i][j] = '|';
			}
		}
	}

	for (int i = 0; i < 19; i++) {
		for (int j = 0; j < 15; j++) {
			printf_s("%c", plateau[i][j]);
		}
		printf_s("\n");
	}
}

int initEquipes() {
	int x;
	do {
		printf_s("Joueur 1, choisissez votre equipe.\n\nTapez 1 pour les bleus, 2 pour les rouges :\n");
		scanf_s("%i", &x);
	} while (x < 1 || x > 2);
	return x;
}

void play(char plateau[][15], rat ratbleu, rat ratrouge, chat chatbleu, chat chatrouge, loup loupbleu, loup louprouge, chien chienbleu, chien chienrouge, panthere pantherebleu, panthere panthererouge, tigre tigrebleu, tigre tigrerouge, lion lionbleu, lion lionrouge, elephant elephantbleu, elephant elephantrouge) {
	int alternerTours = 0, etatBleu = 1, etatRouge = 1, tempX = 0, tempY = 0, repPion/*x1 = 1, x2 = 3, x3 = 5, x4 = 7, x5 = 9, x6 = 11, x7 = 13, y1 = 17, y2 = 15, y3 = 13, y4 = 11, y5 = 9, y6 = 7, y7 = 5, y8 = 3, y9 = 1*/;
	do {
		if ((alternerTours % 2) == 0) {
			do {
				printf_s("\n\nAu tour des bleus de deplacer un pion\n(1 rat, 2 chat, 3 loup, 4 chien, 5 panthere, 6 tigre, 7 lion, 8 elephant)\nEntrez le numero du pion : ");
				scanf_s("%i", &repPion);
			} while (repPion < 1 || repPion > 8);
			switch (repPion) {
			case 1: printf_s("\nLes coordonnees de R sont (%i; %i)\nEntrez ses nouvelles coordonnees :\n", ratbleu.x, ratbleu.y);
				scanf_s("%i%i", &tempX, &tempY);
				ratbleu.x = tempX;
				ratbleu.y = tempY;
				switch (tempX) {
				case 1: tempX = 1;
					break;
				case 2: tempX = 3;
					break;
				case 3: tempX = 5;
					break;
				case 4: tempX = 7;
					break;
				case 5: tempX = 9;
					break;
				case 6: tempX = 11;
					break;
				case 7: tempX = 13;
					break;
				default: printf_s("\nErreur de saisie\n");
				}
				switch (tempY) {
				case 1: tempY = 17;
					break;
				case 2: tempY = 15;
					break;
				case 3: tempY = 13;
					break;
				case 4: tempY = 11;
					break;
				case 5: tempY = 9;
					break;
				case 6: tempY = 7;
					break;
				case 7: tempY = 5;
					break;
				case 8: tempY = 3;
					break;
				case 9: tempY = 1;
					break;
				default: printf_s("\nErreur de saisie\n");
				}
				//printf_s("\n%i et %i", tempX, tempY); // test les valeurs
				plateau[tempY][tempX] = ratbleu.nom;
				plateau[ratbleu.oldVraiY][ratbleu.oldVraiX] = ' ';
				ratbleu.oldVraiY = tempY;
				ratbleu.oldVraiX = tempX;
				break;
			case 2: printf_s("\nLes coordonnees de H sont (%i; %i)\nEntrez ses nouvelles coordonnees :\n", chatbleu.x, chatbleu.y);
				scanf_s("%i%i", &tempX, &tempY);
				chatbleu.x = tempX;
				chatbleu.y = tempY;
				switch (tempX) {
				case 1: tempX = 1;
					break;
				case 2: tempX = 3;
					break;
				case 3: tempX = 5;
					break;
				case 4: tempX = 7;
					break;
				case 5: tempX = 9;
					break;
				case 6: tempX = 11;
					break;
				case 7: tempX = 13;
					break;
				default: printf_s("\nErreur de saisie\n");
				}
				switch (tempY) {
				case 1: tempY = 17;
					break;
				case 2: tempY = 15;
					break;
				case 3: tempY = 13;
					break;
				case 4: tempY = 11;
					break;
				case 5: tempY = 9;
					break;
				case 6: tempY = 7;
					break;
				case 7: tempY = 5;
					break;
				case 8: tempY = 3;
					break;
				case 9: tempY = 1;
					break;
				default: printf_s("\nErreur de saisie\n");
				}
				//printf_s("\n%i et %i", tempX, tempY); // test les valeurs
				plateau[tempY][tempX] = chatbleu.nom;
				plateau[chatbleu.oldVraiY][chatbleu.oldVraiX] = ' ';
				chatbleu.oldVraiY = tempY;
				chatbleu.oldVraiX = tempX;
				break;
			case 3: printf_s("\nLes coordonnees de O sont (%i; %i)\nEntrez ses nouvelles coordonnees :\n", loupbleu.x, loupbleu.y);
				scanf_s("%i%i", &tempX, &tempY);
				loupbleu.x = tempX;
				loupbleu.y = tempY;
				switch (tempX) {
				case 1: tempX = 1;
					break;
				case 2: tempX = 3;
					break;
				case 3: tempX = 5;
					break;
				case 4: tempX = 7;
					break;
				case 5: tempX = 9;
					break;
				case 6: tempX = 11;
					break;
				case 7: tempX = 13;
					break;
				default: printf_s("\nErreur de saisie\n");
				}
				switch (tempY) {
				case 1: tempY = 17;
					break;
				case 2: tempY = 15;
					break;
				case 3: tempY = 13;
					break;
				case 4: tempY = 11;
					break;
				case 5: tempY = 9;
					break;
				case 6: tempY = 7;
					break;
				case 7: tempY = 5;
					break;
				case 8: tempY = 3;
					break;
				case 9: tempY = 1;
					break;
				default: printf_s("\nErreur de saisie\n");
				}
				//printf_s("\n%i et %i", tempX, tempY); // test les valeurs
				plateau[tempY][tempX] = loupbleu.nom;
				plateau[loupbleu.oldVraiY][loupbleu.oldVraiX] = ' ';
				loupbleu.oldVraiY = tempY;
				loupbleu.oldVraiX = tempX;
				break;
			case 4: printf_s("\nLes coordonnees de C sont (%i; %i)\nEntrez ses nouvelles coordonnees :\n", chienbleu.x, chienbleu.y);
				scanf_s("%i%i", &tempX, &tempY);
				chienbleu.x = tempX;
				chienbleu.y = tempY;
				switch (tempX) {
				case 1: tempX = 1;
					break;
				case 2: tempX = 3;
					break;
				case 3: tempX = 5;
					break;
				case 4: tempX = 7;
					break;
				case 5: tempX = 9;
					break;
				case 6: tempX = 11;
					break;
				case 7: tempX = 13;
					break;
				default: printf_s("\nErreur de saisie\n");
				}
				switch (tempY) {
				case 1: tempY = 17;
					break;
				case 2: tempY = 15;
					break;
				case 3: tempY = 13;
					break;
				case 4: tempY = 11;
					break;
				case 5: tempY = 9;
					break;
				case 6: tempY = 7;
					break;
				case 7: tempY = 5;
					break;
				case 8: tempY = 3;
					break;
				case 9: tempY = 1;
					break;
				default: printf_s("\nErreur de saisie\n");
				}
				//printf_s("\n%i et %i", tempX, tempY); // test les valeurs
				plateau[tempY][tempX] = chienbleu.nom;
				plateau[chienbleu.oldVraiY][chienbleu.oldVraiX] = ' ';
				chienbleu.oldVraiY = tempY;
				chienbleu.oldVraiX = tempX;
				break;
			case 5: printf_s("\nLes coordonnees de P sont (%i; %i)\nEntrez ses nouvelles coordonnees :\n", pantherebleu.x, pantherebleu.y);
				scanf_s("%i%i", &tempX, &tempY);
				pantherebleu.x = tempX;
				pantherebleu.y = tempY;
				switch (tempX) {
				case 1: tempX = 1;
					break;
				case 2: tempX = 3;
					break;
				case 3: tempX = 5;
					break;
				case 4: tempX = 7;
					break;
				case 5: tempX = 9;
					break;
				case 6: tempX = 11;
					break;
				case 7: tempX = 13;
					break;
				default: printf_s("\nErreur de saisie\n");
				}
				switch (tempY) {
				case 1: tempY = 17;
					break;
				case 2: tempY = 15;
					break;
				case 3: tempY = 13;
					break;
				case 4: tempY = 11;
					break;
				case 5: tempY = 9;
					break;
				case 6: tempY = 7;
					break;
				case 7: tempY = 5;
					break;
				case 8: tempY = 3;
					break;
				case 9: tempY = 1;
					break;
				default: printf_s("\nErreur de saisie\n");
				}
				//printf_s("\n%i et %i", tempX, tempY); // test les valeurs
				plateau[tempY][tempX] = pantherebleu.nom;
				plateau[pantherebleu.oldVraiY][pantherebleu.oldVraiX] = ' ';
				pantherebleu.oldVraiY = tempY;
				pantherebleu.oldVraiX = tempX;
				break;
			case 6: printf_s("\nLes coordonnees de T sont (%i; %i)\nEntrez ses nouvelles coordonnees :\n", tigrebleu.x, tigrebleu.y);
				scanf_s("%i%i", &tempX, &tempY);
				tigrebleu.x = tempX;
				tigrebleu.y = tempY;
				switch (tempX) {
				case 1: tempX = 1;
					break;
				case 2: tempX = 3;
					break;
				case 3: tempX = 5;
					break;
				case 4: tempX = 7;
					break;
				case 5: tempX = 9;
					break;
				case 6: tempX = 11;
					break;
				case 7: tempX = 13;
					break;
				default: printf_s("\nErreur de saisie\n");
				}
				switch (tempY) {
				case 1: tempY = 17;
					break;
				case 2: tempY = 15;
					break;
				case 3: tempY = 13;
					break;
				case 4: tempY = 11;
					break;
				case 5: tempY = 9;
					break;
				case 6: tempY = 7;
					break;
				case 7: tempY = 5;
					break;
				case 8: tempY = 3;
					break;
				case 9: tempY = 1;
					break;
				default: printf_s("\nErreur de saisie\n");
				}
				//printf_s("\n%i et %i", tempX, tempY); // test les valeurs
				plateau[tempY][tempX] = tigrebleu.nom;
				plateau[tigrebleu.oldVraiY][tigrebleu.oldVraiX] = ' ';
				tigrebleu.oldVraiY = tempY;
				tigrebleu.oldVraiX = tempX;
				break;
			case 7: printf_s("\nLes coordonnees de L sont (%i; %i)\nEntrez ses nouvelles coordonnees :\n", lionbleu.x, lionbleu.y);
				scanf_s("%i%i", &tempX, &tempY);
				lionbleu.x = tempX;
				lionbleu.y = tempY;
				switch (tempX) {
				case 1: tempX = 1;
					break;
				case 2: tempX = 3;
					break;
				case 3: tempX = 5;
					break;
				case 4: tempX = 7;
					break;
				case 5: tempX = 9;
					break;
				case 6: tempX = 11;
					break;
				case 7: tempX = 13;
					break;
				default: printf_s("\nErreur de saisie\n");
				}
				switch (tempY) {
				case 1: tempY = 17;
					break;
				case 2: tempY = 15;
					break;
				case 3: tempY = 13;
					break;
				case 4: tempY = 11;
					break;
				case 5: tempY = 9;
					break;
				case 6: tempY = 7;
					break;
				case 7: tempY = 5;
					break;
				case 8: tempY = 3;
					break;
				case 9: tempY = 1;
					break;
				default: printf_s("\nErreur de saisie\n");
				}
				//printf_s("\n%i et %i", tempX, tempY); // test les valeurs
				plateau[tempY][tempX] = lionbleu.nom;
				plateau[lionbleu.oldVraiY][lionbleu.oldVraiX] = ' ';
				lionbleu.oldVraiY = tempY;
				lionbleu.oldVraiX = tempX;
				break;
			case 8: printf_s("\nLes coordonnees de E sont (%i; %i)\nEntrez ses nouvelles coordonnees :\n", elephantbleu.x, elephantbleu.y);
				scanf_s("%i%i", &tempX, &tempY);
				elephantbleu.x = tempX;
				elephantbleu.y = tempY;
				switch (tempX) {
				case 1: tempX = 1;
					break;
				case 2: tempX = 3;
					break;
				case 3: tempX = 5;
					break;
				case 4: tempX = 7;
					break;
				case 5: tempX = 9;
					break;
				case 6: tempX = 11;
					break;
				case 7: tempX = 13;
					break;
				default: printf_s("\nErreur de saisie\n");
				}
				switch (tempY) {
				case 1: tempY = 17;
					break;
				case 2: tempY = 15;
					break;
				case 3: tempY = 13;
					break;
				case 4: tempY = 11;
					break;
				case 5: tempY = 9;
					break;
				case 6: tempY = 7;
					break;
				case 7: tempY = 5;
					break;
				case 8: tempY = 3;
					break;
				case 9: tempY = 1;
					break;
				default: printf_s("\nErreur de saisie\n");
				}
				//printf_s("\n%i et %i", tempX, tempY); // test les valeurs
				plateau[tempY][tempX] = elephantbleu.nom;
				plateau[elephantbleu.oldVraiY][elephantbleu.oldVraiX] = ' ';
				elephantbleu.oldVraiY = tempY;
				elephantbleu.oldVraiX = tempX;
				break;
			default: printf_s("\nErreur de saisie\n");
			}
			alternerTours++;
			affichagePlateau(plateau);
		}
		else {
			do {
				printf_s("\n\nAu tour des rouges de deplacer un pion\n(1 rat, 2 chat, 3 loup, 4 chien, 5 panthere, 6 tigre, 7 lion, 8 elephant)\nEntrez le numero du pion : ");
				scanf_s("%i", &repPion);
			} while (repPion < 1 || repPion > 8);
			switch (repPion) {
			case 1: printf_s("\nLes coordonnees de r sont (%i; %i)\nEntrez ses nouvelles coordonnees :\n", ratrouge.x, ratrouge.y);
				scanf_s("%i%i", &tempX, &tempY);
				ratrouge.x = tempX;
				ratrouge.y = tempY;
				switch (tempX) {
				case 1: tempX = 1;
					break;
				case 2: tempX = 3;
					break;
				case 3: tempX = 5;
					break;
				case 4: tempX = 7;
					break;
				case 5: tempX = 9;
					break;
				case 6: tempX = 11;
					break;
				case 7: tempX = 13;
					break;
				default: printf_s("\nErreur de saisie\n");
				}
				switch (tempY) {
				case 1: tempY = 17;
					break;
				case 2: tempY = 15;
					break;
				case 3: tempY = 13;
					break;
				case 4: tempY = 11;
					break;
				case 5: tempY = 9;
					break;
				case 6: tempY = 7;
					break;
				case 7: tempY = 5;
					break;
				case 8: tempY = 3;
					break;
				case 9: tempY = 1;
					break;
				default: printf_s("\nErreur de saisie\n");
				}
				//printf_s("\n%i et %i", tempX, tempY); // test les valeurs
				plateau[tempY][tempX] = ratrouge.nom;
				plateau[ratrouge.oldVraiY][ratrouge.oldVraiX] = ' ';
				ratrouge.oldVraiY = tempY;
				ratrouge.oldVraiX = tempX;
				break;
			case 2: printf_s("\nLes coordonnees de h sont (%i; %i)\nEntrez ses nouvelles coordonnees :\n", chatrouge.x, chatrouge.y);
				scanf_s("%i%i", &tempX, &tempY);
				chatrouge.x = tempX;
				chatrouge.y = tempY;
				switch (tempX) {
				case 1: tempX = 1;
					break;
				case 2: tempX = 3;
					break;
				case 3: tempX = 5;
					break;
				case 4: tempX = 7;
					break;
				case 5: tempX = 9;
					break;
				case 6: tempX = 11;
					break;
				case 7: tempX = 13;
					break;
				default: printf_s("\nErreur de saisie\n");
				}
				switch (tempY) {
				case 1: tempY = 17;
					break;
				case 2: tempY = 15;
					break;
				case 3: tempY = 13;
					break;
				case 4: tempY = 11;
					break;
				case 5: tempY = 9;
					break;
				case 6: tempY = 7;
					break;
				case 7: tempY = 5;
					break;
				case 8: tempY = 3;
					break;
				case 9: tempY = 1;
					break;
				default: printf_s("\nErreur de saisie\n");
				}
				//printf_s("\n%i et %i", tempX, tempY); // test les valeurs
				plateau[tempY][tempX] = chatrouge.nom;
				plateau[chatrouge.oldVraiY][chatrouge.oldVraiX] = ' ';
				chatrouge.oldVraiY = tempY;
				chatrouge.oldVraiX = tempX;
				break;
			case 3: printf_s("\nLes coordonnees de o sont (%i; %i)\nEntrez ses nouvelles coordonnees :\n", louprouge.x, louprouge.y);
				scanf_s("%i%i", &tempX, &tempY);
				louprouge.x = tempX;
				louprouge.y = tempY;
				switch (tempX) {
				case 1: tempX = 1;
					break;
				case 2: tempX = 3;
					break;
				case 3: tempX = 5;
					break;
				case 4: tempX = 7;
					break;
				case 5: tempX = 9;
					break;
				case 6: tempX = 11;
					break;
				case 7: tempX = 13;
					break;
				default: printf_s("\nErreur de saisie\n");
				}
				switch (tempY) {
				case 1: tempY = 17;
					break;
				case 2: tempY = 15;
					break;
				case 3: tempY = 13;
					break;
				case 4: tempY = 11;
					break;
				case 5: tempY = 9;
					break;
				case 6: tempY = 7;
					break;
				case 7: tempY = 5;
					break;
				case 8: tempY = 3;
					break;
				case 9: tempY = 1;
					break;
				default: printf_s("\nErreur de saisie\n");
				}
				//printf_s("\n%i et %i", tempX, tempY); // test les valeurs
				plateau[tempY][tempX] = louprouge.nom;
				plateau[louprouge.oldVraiY][louprouge.oldVraiX] = ' ';
				louprouge.oldVraiY = tempY;
				louprouge.oldVraiX = tempX;
				break;
			case 4: printf_s("\nLes coordonnees de c sont (%i; %i)\nEntrez ses nouvelles coordonnees :\n", chienrouge.x, chienrouge.y);
				scanf_s("%i%i", &tempX, &tempY);
				chienrouge.x = tempX;
				chienrouge.y = tempY;
				switch (tempX) {
				case 1: tempX = 1;
					break;
				case 2: tempX = 3;
					break;
				case 3: tempX = 5;
					break;
				case 4: tempX = 7;
					break;
				case 5: tempX = 9;
					break;
				case 6: tempX = 11;
					break;
				case 7: tempX = 13;
					break;
				default: printf_s("\nErreur de saisie\n");
				}
				switch (tempY) {
				case 1: tempY = 17;
					break;
				case 2: tempY = 15;
					break;
				case 3: tempY = 13;
					break;
				case 4: tempY = 11;
					break;
				case 5: tempY = 9;
					break;
				case 6: tempY = 7;
					break;
				case 7: tempY = 5;
					break;
				case 8: tempY = 3;
					break;
				case 9: tempY = 1;
					break;
				default: printf_s("\nErreur de saisie\n");
				}
				//printf_s("\n%i et %i", tempX, tempY); // test les valeurs
				plateau[tempY][tempX] = chienrouge.nom;
				plateau[chienrouge.oldVraiY][chienrouge.oldVraiX] = ' ';
				chienrouge.oldVraiY = tempY;
				chienrouge.oldVraiX = tempX;
				break;
			case 5: printf_s("\nLes coordonnees de p sont (%i; %i)\nEntrez ses nouvelles coordonnees :\n", panthererouge.x, panthererouge.y);
				scanf_s("%i%i", &tempX, &tempY);
				panthererouge.x = tempX;
				panthererouge.y = tempY;
				switch (tempX) {
				case 1: tempX = 1;
					break;
				case 2: tempX = 3;
					break;
				case 3: tempX = 5;
					break;
				case 4: tempX = 7;
					break;
				case 5: tempX = 9;
					break;
				case 6: tempX = 11;
					break;
				case 7: tempX = 13;
					break;
				default: printf_s("\nErreur de saisie\n");
				}
				switch (tempY) {
				case 1: tempY = 17;
					break;
				case 2: tempY = 15;
					break;
				case 3: tempY = 13;
					break;
				case 4: tempY = 11;
					break;
				case 5: tempY = 9;
					break;
				case 6: tempY = 7;
					break;
				case 7: tempY = 5;
					break;
				case 8: tempY = 3;
					break;
				case 9: tempY = 1;
					break;
				default: printf_s("\nErreur de saisie\n");
				}
				//printf_s("\n%i et %i", tempX, tempY); // test les valeurs
				plateau[tempY][tempX] = panthererouge.nom;
				plateau[panthererouge.oldVraiY][panthererouge.oldVraiX] = ' ';
				panthererouge.oldVraiY = tempY;
				panthererouge.oldVraiX = tempX;
				break;
			case 6: printf_s("\nLes coordonnees de t sont (%i; %i)\nEntrez ses nouvelles coordonnees :\n", tigrerouge.x, tigrerouge.y);
				scanf_s("%i%i", &tempX, &tempY);
				tigrerouge.x = tempX;
				tigrerouge.y = tempY;
				switch (tempX) {
				case 1: tempX = 1;
					break;
				case 2: tempX = 3;
					break;
				case 3: tempX = 5;
					break;
				case 4: tempX = 7;
					break;
				case 5: tempX = 9;
					break;
				case 6: tempX = 11;
					break;
				case 7: tempX = 13;
					break;
				default: printf_s("\nErreur de saisie\n");
				}
				switch (tempY) {
				case 1: tempY = 17;
					break;
				case 2: tempY = 15;
					break;
				case 3: tempY = 13;
					break;
				case 4: tempY = 11;
					break;
				case 5: tempY = 9;
					break;
				case 6: tempY = 7;
					break;
				case 7: tempY = 5;
					break;
				case 8: tempY = 3;
					break;
				case 9: tempY = 1;
					break;
				default: printf_s("\nErreur de saisie\n");
				}
				//printf_s("\n%i et %i", tempX, tempY); // test les valeurs
				plateau[tempY][tempX] = tigrerouge.nom;
				plateau[tigrerouge.oldVraiY][tigrerouge.oldVraiX] = ' ';
				tigrerouge.oldVraiY = tempY;
				tigrerouge.oldVraiX = tempX;
				break;
			case 7: printf_s("\nLes coordonnees de l sont (%i; %i)\nEntrez ses nouvelles coordonnees :\n", lionrouge.x, lionrouge.y);
				scanf_s("%i%i", &tempX, &tempY);
				lionrouge.x = tempX;
				lionrouge.y = tempY;
				switch (tempX) {
				case 1: tempX = 1;
					break;
				case 2: tempX = 3;
					break;
				case 3: tempX = 5;
					break;
				case 4: tempX = 7;
					break;
				case 5: tempX = 9;
					break;
				case 6: tempX = 11;
					break;
				case 7: tempX = 13;
					break;
				default: printf_s("\nErreur de saisie\n");
				}
				switch (tempY) {
				case 1: tempY = 17;
					break;
				case 2: tempY = 15;
					break;
				case 3: tempY = 13;
					break;
				case 4: tempY = 11;
					break;
				case 5: tempY = 9;
					break;
				case 6: tempY = 7;
					break;
				case 7: tempY = 5;
					break;
				case 8: tempY = 3;
					break;
				case 9: tempY = 1;
					break;
				default: printf_s("\nErreur de saisie\n");
				}
				//printf_s("\n%i et %i", tempX, tempY); // test les valeurs
				plateau[tempY][tempX] = lionrouge.nom;
				plateau[lionrouge.oldVraiY][lionrouge.oldVraiX] = ' ';
				lionrouge.oldVraiY = tempY;
				lionrouge.oldVraiX = tempX;
				break;
			case 8: printf_s("\nLes coordonnees de e sont (%i; %i)\nEntrez ses nouvelles coordonnees :\n", elephantrouge.x, elephantrouge.y);
				scanf_s("%i%i", &tempX, &tempY);
				elephantrouge.x = tempX;
				elephantrouge.y = tempY;
				switch (tempX) {
				case 1: tempX = 1;
					break;
				case 2: tempX = 3;
					break;
				case 3: tempX = 5;
					break;
				case 4: tempX = 7;
					break;
				case 5: tempX = 9;
					break;
				case 6: tempX = 11;
					break;
				case 7: tempX = 13;
					break;
				default: printf_s("\nErreur de saisie\n");
				}
				switch (tempY) {
				case 1: tempY = 17;
					break;
				case 2: tempY = 15;
					break;
				case 3: tempY = 13;
					break;
				case 4: tempY = 11;
					break;
				case 5: tempY = 9;
					break;
				case 6: tempY = 7;
					break;
				case 7: tempY = 5;
					break;
				case 8: tempY = 3;
					break;
				case 9: tempY = 1;
					break;
				default: printf_s("\nErreur de saisie\n");
				}
				//printf_s("\n%i et %i", tempX, tempY); // test les valeurs
				plateau[tempY][tempX] = elephantrouge.nom;
				plateau[elephantrouge.oldVraiY][elephantrouge.oldVraiX] = ' ';
				elephantrouge.oldVraiY = tempY;
				elephantrouge.oldVraiX = tempX;
				break;
			default: printf_s("\nErreur de saisie\n");
			}
			alternerTours++;
			affichagePlateau(plateau);
		}
	} while (etatBleu == 1 && etatRouge == 1);
}

//void sauvegarder(char plateau[][15]) {
//	int n;
//	FILE* ecriture;
//	fopen("save.txt", "w");
//	ecriture = fopen("save.txt", "a");
//	for (int i = 0; i < 19; i++) {
//		for (int j = 0; j < 14; j++) {
//			n = plateau[i][j];
//			fputc(n, ecriture);
//		}
//	}
//	fclose(ecriture);
//}
//
//void charger(char plateau[][15]) {
//	int n;
//	FILE* ouverture;
//	ouverture = fopen("save.txt", "r");
//	for (int i = 0; i < 19; i++) {
//		for (int j = 0; j < 14; j++) {
//			n = fgetc(ouverture);
//			plateau[i][j] = n;
//		}
//	}
//}

int main() {
	int joueur1 = 0, joueur2 = 0, vraiX = 0, vraiY = 0;
	char plateau[19][15];
	rat ratbleu, ratrouge;
	chat chatbleu, chatrouge;
	loup loupbleu, louprouge;
	chien chienbleu, chienrouge;
	panthere pantherebleu, panthererouge;
	tigre tigrebleu, tigrerouge;
	lion lionbleu, lionrouge;
	elephant elephantbleu, elephantrouge;
	ratbleu.y = 7;
	ratbleu.x = 1;
	ratbleu.oldVraiY = 5;
	ratbleu.oldVraiX = 1;
	ratbleu.force = 1;
	ratbleu.etat = 1;
	ratbleu.nom = '\x52';
	ratrouge.y = 3;
	ratrouge.x = 7;
	ratrouge.oldVraiY = 13;
	ratrouge.oldVraiX = 13;
	ratrouge.force = 1;
	ratrouge.etat = 1;
	ratrouge.nom = '\x72';
	chatbleu.y = 8;
	chatbleu.x = 6;
	chatbleu.oldVraiY = 3;
	chatbleu.oldVraiX = 11;
	chatbleu.force = 2;
	chatbleu.etat = 1;
	chatbleu.nom = '\x48';
	chatrouge.y = 2;
	chatrouge.x = 2;
	chatrouge.oldVraiY = 15;
	chatrouge.oldVraiX = 3;
	chatrouge.force = 2;
	chatrouge.etat = 1;
	chatrouge.nom = '\x68';
	loupbleu.y = 7;
	loupbleu.x = 5;
	loupbleu.oldVraiY = 5;
	loupbleu.oldVraiX = 9;
	loupbleu.force = 3;
	loupbleu.etat = 1;
	loupbleu.nom = '\x4F';
	louprouge.y = 3;
	louprouge.x = 3;
	louprouge.oldVraiY = 13;
	louprouge.oldVraiX = 5;
	louprouge.force = 3;
	louprouge.etat = 1;
	louprouge.nom = '\x6F';
	chienbleu.y = 8;
	chienbleu.x = 2;
	chienbleu.oldVraiY = 3;
	chienbleu.oldVraiX = 3;
	chienbleu.force = 4;
	chienbleu.etat = 1;
	chienbleu.nom = '\x43';
	chienrouge.y = 2;
	chienrouge.x = 6;
	chienrouge.oldVraiY = 15;
	chienrouge.oldVraiX = 11;
	chienrouge.force = 4;
	chienrouge.etat = 1;
	chienrouge.nom = '\x63';
	pantherebleu.y = 7;
	pantherebleu.x = 3;
	pantherebleu.oldVraiY = 5;
	pantherebleu.oldVraiX = 5;
	pantherebleu.force = 5;
	pantherebleu.etat = 1;
	pantherebleu.nom = '\x50';
	panthererouge.y = 3;
	panthererouge.x = 5;
	panthererouge.oldVraiY = 13;
	panthererouge.oldVraiX = 9;
	panthererouge.force = 5;
	panthererouge.etat = 1;
	panthererouge.nom = '\x70';
	tigrebleu.y = 9;
	tigrebleu.x = 7;
	tigrebleu.oldVraiY = 1;
	tigrebleu.oldVraiX = 13;
	tigrebleu.force = 6;
	tigrebleu.etat = 1;
	tigrebleu.nom = '\x54';
	tigrerouge.y = 1;
	tigrerouge.x = 1;
	tigrerouge.oldVraiY = 17;
	tigrerouge.oldVraiX = 1;
	tigrerouge.force = 6;
	tigrerouge.etat = 1;
	tigrerouge.nom = '\x74';
	lionbleu.y = 9;
	lionbleu.x = 1;
	lionbleu.oldVraiY = 1;
	lionbleu.oldVraiX = 1;
	lionbleu.force = 7;
	lionbleu.etat = 1;
	lionbleu.nom = '\x4C';
	lionrouge.y = 1;
	lionrouge.x = 7;
	lionrouge.oldVraiY = 17;
	lionrouge.oldVraiX = 13;
	lionrouge.force = 7;
	lionrouge.etat = 1;
	lionrouge.nom = '\x6C';
	elephantbleu.y = 7;
	elephantbleu.x = 7;
	elephantbleu.oldVraiY = 5;
	elephantbleu.oldVraiX = 13;
	elephantbleu.force = 8;
	elephantbleu.etat = 1;
	elephantbleu.nom = '\x45';
	elephantrouge.y = 3;
	elephantrouge.x = 1;
	elephantrouge.oldVraiY = 13;
	elephantrouge.oldVraiX = 1;
	elephantrouge.force = 8;
	elephantrouge.etat = 1;
	elephantrouge.nom = '\x65';
	system("title Jeu de la jungle");
	regles();
	joueur1 = initEquipes();
	if (joueur1 == 1) {
		joueur2 = 2;
		printf_s("\nLe joueur 1 est dans l'equipe bleue\nVos pieces seront en majuscule\n\nLe joueur 2 est dans l'equipe rouge\nVos pieces seront en minuscule\n");
	}
	else {
		joueur2 = 1;
		printf_s("\nLe joueur 1 est dans l'equipe rouge\nVos pieces seront en minuscule\n\nLe joueur 2 est dans l'equipe bleue\nVos pieces seront en majuscule\n");
	}
	Sleep(1000);
	initPlateau(plateau, ratbleu, ratrouge, chatbleu, chatrouge, loupbleu, louprouge, chienbleu, chienrouge, pantherebleu, panthererouge, tigrebleu, tigrerouge, lionbleu, lionrouge, elephantbleu, elephantrouge);
	affichagePlateau(plateau);
	play(plateau, ratbleu, ratrouge, chatbleu, chatrouge, loupbleu, louprouge, chienbleu, chienrouge, pantherebleu, panthererouge, tigrebleu, tigrerouge, lionbleu, lionrouge, elephantbleu, elephantrouge, vraiX, vraiY);
}
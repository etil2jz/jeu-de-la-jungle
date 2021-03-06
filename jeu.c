/*
Le projet consiste plus sp?cialement ? mod?liser le jeu en mode texte (dans un premier temps).
Les pions seront des lettres. Le d?placement des pi?ces se fera d?abord par l?entr?e des coordonn?es
puis par l'interm?diaire de la souris.
Suivant l?avancement du projet, le programme permettra :
	- de jouer ? deux sur le m?me PC
	- de jouer contre l?ordinateur gr?ce ? l?implantation d?une intelligence artificielle
	- de jouer contre un autre logiciel (une intelligence artificielle contre l?autre)
La r?alisation en mode graphique apportera un bonus (maximum 2 points), mais n?est pas obligatoire.



G?rer les commandes de l'utilisateur :
	- Placer les pions
	- Contr?ler le d?roulement de la partie (r?gles...)
	- Jouer un coup
	- Reprendre une partie ? partir d'un coup donn?
	- Sauver la partie sur disque
	- Calculer les points des joueurs

Sortie sur ?cran des informations

D?finir les structures de donn?es permettant la r?solution de ce probl?me

D?crire sous forme modulaire les diff?rentes s?quences de fonctionnement

Traduire les structures de donn?es et les actions en C
*/

#include <stdio.h>
#include <stdlib.h>
#include <windows.h>
#include <string.h>

void regles() {
	system("color A");
	printf_s("            \x10 REGLES DU JEU \x11");
	printf_s("\n\n\x16 Chaque joueur deplace, a son tour, une des pieces d'une seule case a la fois, horizontalement ou verticalement.\n\n\x16 A l'occasion d'un deplacement une piece peut prendre une piece adverse egale ou inferieure en se mettant a sa place. La piece prise est enlevee du jeu. Cependant, le rat peut prendre l'elephant.\n\n\x16 Seul le rat peut se deplacer dans les lacs mais il ne peut pas capturer l'elephant adverse en passant du lac sur la rive.\n\n\x16 Les lions et les tigres peuvent sauter directement d'une rive a l'autre verticalement ou horizontalement sauf si un rat (ami ou adverse) se trouve dans la ligne de saut.\n\n\x16 Quand une piece se trouve dans un piege adverse, sa force combative devient momentanement nulle mais elle conserve la possibilite de se deplacer.\n\n\x16 Les pieces ne peuvent pas entrer dans leur propre sanctuaire.\n\n\nPatientez 10 secondes...\n");
	Sleep(10000);
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

typedef struct piege {
	int x1, y1, x2, y2, x3, y3, oldVraiX1, oldVraiY1, oldVraiX2, oldVraiY2, oldVraiX3, oldVraiY3;
	char nom;
}piege;

typedef struct base {
	int x, y, oldVraiX, oldVraiY;
	char nom;
}base;

void initPlateau(char plateau[][15], base basebleu, base baserouge, piege piegeb, piege pieger, rat ratbleu, rat ratrouge, chat chatbleu, chat chatrouge, loup loupbleu, loup louprouge, chien chienbleu, chien chienrouge, panthere pantherebleu, panthere panthererouge, tigre tigrebleu, tigre tigrerouge, lion lionbleu, lion lionrouge, elephant elephantbleu, elephant elephantrouge) {
	plateau[1][1] = lionbleu.nom;
	plateau[1][3] = ' ';
	plateau[1][5] = piegeb.nom;
	plateau[1][7] = basebleu.nom;
	plateau[1][9] = piegeb.nom;
	plateau[1][11] = ' ';
	plateau[1][13] = tigrebleu.nom;

	plateau[3][1] = ' ';
	plateau[3][3] = chienbleu.nom;
	plateau[3][5] = ' ';
	plateau[3][7] = piegeb.nom;
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
	plateau[15][7] = pieger.nom;
	plateau[15][9] = ' ';
	plateau[15][11] = chienrouge.nom;
	plateau[15][13] = ' ';

	plateau[17][1] = tigrerouge.nom;
	plateau[17][3] = ' ';
	plateau[17][5] = pieger.nom;
	plateau[17][7] = baserouge.nom;
	plateau[17][9] = pieger.nom;
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

int switchCoordX(int tempX) {
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
	return tempX;
}

int switchCoordY(int tempY) {
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
	return tempY;
}

void play(char plateau[][15], base basebleu, base baserouge, piege piegeb, piege pieger, rat ratbleu, rat ratrouge, chat chatbleu, chat chatrouge, loup loupbleu, loup louprouge, chien chienbleu, chien chienrouge, panthere pantherebleu, panthere panthererouge, tigre tigrebleu, tigre tigrerouge, lion lionbleu, lion lionrouge, elephant elephantbleu, elephant elephantrouge) {
	int alternerTours = 0, etatBleu = 1, etatRouge = 1, tempX = 0, tempY = 0, repPion;
	do {
		if ((alternerTours % 2) == 0) {
			do {
				printf_s("\n\nAu tour des bleus de deplacer un pion\n(1 rat, 2 chat, 3 loup, 4 chien, 5 panthere, 6 tigre, 7 lion, 8 elephant)\nEntrez le numero du pion : ");
				scanf_s("%i", &repPion);
			} while (repPion < 1 || repPion > 8);
			switch (repPion) {
			case 1: if (ratbleu.etat == 1) {
				printf_s("\nLes coordonnees de R sont (%i; %i)\nEntrez ses nouvelles coordonnees :\n", ratbleu.x, ratbleu.y);
				do {	
					scanf_s("%i%i", &tempX, &tempY);
				} while ((tempX > ratbleu.x + 1) || (tempX < ratbleu.x - 1) || (tempY > ratbleu.y + 1) || (tempY < ratbleu.y - 1) || (((tempX > ratbleu.x) || (tempX < ratbleu.x)) && ((tempY > ratbleu.y) || (tempY < ratbleu.y))));
				ratbleu.x = tempX;
				ratbleu.y = tempY;
				tempX = switchCoordX(tempX);
				tempY = switchCoordY(tempY);
				//printf_s("\n%i et %i", tempX, tempY); // test les valeurs
				plateau[ratbleu.oldVraiY][ratbleu.oldVraiX] = ' ';
				plateau[tempY][tempX] = ratbleu.nom;
				ratbleu.oldVraiY = tempY;
				ratbleu.oldVraiX = tempX;
			}
				  else {
				printf_s("\nCette piece a ete prise par l'equipe rouge...\n");
			}
				break;
			case 2: if (chatbleu.etat == 1) {
				printf_s("\nLes coordonnees de H sont (%i; %i)\nEntrez ses nouvelles coordonnees :\n", chatbleu.x, chatbleu.y);
				do {
					scanf_s("%i%i", &tempX, &tempY);
				} while ((tempX > chatbleu.x + 1) || (tempX < chatbleu.x - 1) || (tempY > chatbleu.y + 1) || (tempY < chatbleu.y - 1) || (((tempX > chatbleu.x) || (tempX < chatbleu.x)) && ((tempY > chatbleu.y) || (tempY < chatbleu.y))));
				chatbleu.x = tempX;
				chatbleu.y = tempY;
				tempX = switchCoordX(tempX);
				tempY = switchCoordY(tempY);
				//printf_s("\n%i et %i", tempX, tempY); // test les valeurs
				plateau[chatbleu.oldVraiY][chatbleu.oldVraiX] = ' ';
				plateau[tempY][tempX] = chatbleu.nom;
				chatbleu.oldVraiY = tempY;
				chatbleu.oldVraiX = tempX;
			}
				  else {
				printf_s("\nCette piece a ete prise par l'equipe rouge...\n");
			}
				break;
			case 3: if (loupbleu.etat == 1) {
				printf_s("\nLes coordonnees de O sont (%i; %i)\nEntrez ses nouvelles coordonnees :\n", loupbleu.x, loupbleu.y);
				do {
					scanf_s("%i%i", &tempX, &tempY);
				} while ((tempX > loupbleu.x + 1) || (tempX < loupbleu.x - 1) || (tempY > loupbleu.y + 1) || (tempY < loupbleu.y - 1) || (((tempX > loupbleu.x) || (tempX < loupbleu.x)) && ((tempY > loupbleu.y) || (tempY < loupbleu.y))));
				loupbleu.x = tempX;
				loupbleu.y = tempY;
				tempX = switchCoordX(tempX);
				tempY = switchCoordY(tempY);
				//printf_s("\n%i et %i", tempX, tempY); // test les valeurs
				plateau[loupbleu.oldVraiY][loupbleu.oldVraiX] = ' ';
				plateau[tempY][tempX] = loupbleu.nom;
				loupbleu.oldVraiY = tempY;
				loupbleu.oldVraiX = tempX;
			}
				  else {
				printf_s("\nCette piece a ete prise par l'equipe rouge...\n");
			}
				break;
			case 4: if (chienbleu.etat == 1) {
				printf_s("\nLes coordonnees de C sont (%i; %i)\nEntrez ses nouvelles coordonnees :\n", chienbleu.x, chienbleu.y);
				do {
					scanf_s("%i%i", &tempX, &tempY);
				} while ((tempX > chienbleu.x + 1) || (tempX < chienbleu.x - 1) || (tempY > chienbleu.y + 1) || (tempY < chienbleu.y - 1) || (((tempX > chienbleu.x) || (tempX < chienbleu.x)) && ((tempY > chienbleu.y) || (tempY < chienbleu.y))));
				chienbleu.x = tempX;
				chienbleu.y = tempY;
				tempX = switchCoordX(tempX);
				tempY = switchCoordY(tempY);
				//printf_s("\n%i et %i", tempX, tempY); // test les valeurs
				plateau[chienbleu.oldVraiY][chienbleu.oldVraiX] = ' ';
				plateau[tempY][tempX] = chienbleu.nom;
				chienbleu.oldVraiY = tempY;
				chienbleu.oldVraiX = tempX;
			}
				  else {
				printf_s("\nCette piece a ete prise par l'equipe rouge...\n");
			}
				break;
			case 5: if (pantherebleu.etat == 1) {
				printf_s("\nLes coordonnees de P sont (%i; %i)\nEntrez ses nouvelles coordonnees :\n", pantherebleu.x, pantherebleu.y);
				do {
					scanf_s("%i%i", &tempX, &tempY);
				} while ((tempX > pantherebleu.x + 1) || (tempX < pantherebleu.x - 1) || (tempY > pantherebleu.y + 1) || (tempY < pantherebleu.y - 1) || (((tempX > pantherebleu.x) || (tempX < pantherebleu.x)) && ((tempY > pantherebleu.y) || (tempY < pantherebleu.y))));
				pantherebleu.x = tempX;
				pantherebleu.y = tempY;
				tempX = switchCoordX(tempX);
				tempY = switchCoordY(tempY);
				//printf_s("\n%i et %i", tempX, tempY); // test les valeurs
				plateau[pantherebleu.oldVraiY][pantherebleu.oldVraiX] = ' ';
				plateau[tempY][tempX] = pantherebleu.nom;
				pantherebleu.oldVraiY = tempY;
				pantherebleu.oldVraiX = tempX;
			}
				  else {
				printf_s("\nCette piece a ete prise par l'equipe rouge...\n");
			}
				break;
			case 6: if (tigrebleu.etat == 1) {
				printf_s("\nLes coordonnees de T sont (%i; %i)\nEntrez ses nouvelles coordonnees :\n", tigrebleu.x, tigrebleu.y);
				do {
					scanf_s("%i%i", &tempX, &tempY);
				} while ((tempX > tigrebleu.x + 1) || (tempX < tigrebleu.x - 1) || (tempY > tigrebleu.y + 1) || (tempY < tigrebleu.y - 1) || (((tempX > tigrebleu.x) || (tempX < tigrebleu.x)) && ((tempY > tigrebleu.y) || (tempY < tigrebleu.y))));
				tigrebleu.x = tempX;
				tigrebleu.y = tempY;
				tempX = switchCoordX(tempX);
				tempY = switchCoordY(tempY);
				//printf_s("\n%i et %i", tempX, tempY); // test les valeurs
				plateau[tigrebleu.oldVraiY][tigrebleu.oldVraiX] = ' ';
				plateau[tempY][tempX] = tigrebleu.nom;
				tigrebleu.oldVraiY = tempY;
				tigrebleu.oldVraiX = tempX;
			}
				  else {
				printf_s("\nCette piece a ete prise par l'equipe rouge...\n");
			}
				break;
			case 7: if (lionbleu.etat == 1) {
				printf_s("\nLes coordonnees de L sont (%i; %i)\nEntrez ses nouvelles coordonnees :\n", lionbleu.x, lionbleu.y);
				do {
					scanf_s("%i%i", &tempX, &tempY);
				} while ((tempX > lionbleu.x + 1) || (tempX < lionbleu.x - 1) || (tempY > lionbleu.y + 1) || (tempY < lionbleu.y - 1) || (((tempX > lionbleu.x) || (tempX < lionbleu.x)) && ((tempY > lionbleu.y) || (tempY < lionbleu.y))));
				lionbleu.x = tempX;
				lionbleu.y = tempY;
				tempX = switchCoordX(tempX);
				tempY = switchCoordY(tempY);
				//printf_s("\n%i et %i", tempX, tempY); // test les valeurs
				plateau[lionbleu.oldVraiY][lionbleu.oldVraiX] = ' ';
				plateau[tempY][tempX] = lionbleu.nom;
				lionbleu.oldVraiY = tempY;
				lionbleu.oldVraiX = tempX;
			}
				  else {
				printf_s("\nCette piece a ete prise par l'equipe rouge...\n");
			}
				break;
			case 8: if (elephantbleu.etat == 1) {
				printf_s("\nLes coordonnees de E sont (%i; %i)\nEntrez ses nouvelles coordonnees :\n", elephantbleu.x, elephantbleu.y);
				do {
					scanf_s("%i%i", &tempX, &tempY);
				} while ((tempX > elephantbleu.x + 1) || (tempX < elephantbleu.x - 1) || (tempY > elephantbleu.y + 1) || (tempY < elephantbleu.y - 1) || (((tempX > elephantbleu.x) || (tempX < elephantbleu.x)) && ((tempY > elephantbleu.y) || (tempY < elephantbleu.y))));
				elephantbleu.x = tempX;
				elephantbleu.y = tempY;
				tempX = switchCoordX(tempX);
				tempY = switchCoordY(tempY);
				//printf_s("\n%i et %i", tempX, tempY); // test les valeurs
				plateau[elephantbleu.oldVraiY][elephantbleu.oldVraiX] = ' ';
				plateau[tempY][tempX] = elephantbleu.nom;
				elephantbleu.oldVraiY = tempY;
				elephantbleu.oldVraiX = tempX;
			}
				  else {
				printf_s("\nCette piece a ete prise par l'equipe rouge...\n");
			}
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
			case 1: if (ratrouge.etat == 1) {
				printf_s("\nLes coordonnees de r sont (%i; %i)\nEntrez ses nouvelles coordonnees :\n", ratrouge.x, ratrouge.y);
				do {
					scanf_s("%i%i", &tempX, &tempY);
				} while ((tempX > ratrouge.x + 1) || (tempX < ratrouge.x - 1) || (tempY > ratrouge.y + 1) || (tempY < ratrouge.y - 1) || (((tempX > ratrouge.x) || (tempX < ratrouge.x)) && ((tempY > ratrouge.y) || (tempY < ratrouge.y))));
				ratrouge.x = tempX;
				ratrouge.y = tempY;
				tempX = switchCoordX(tempX);
				tempY = switchCoordY(tempY);
				//printf_s("\n%i et %i", tempX, tempY); // test les valeurs
				plateau[ratrouge.oldVraiY][ratrouge.oldVraiX] = ' ';
				plateau[tempY][tempX] = ratrouge.nom;
				ratrouge.oldVraiY = tempY;
				ratrouge.oldVraiX = tempX;
			}
				  else {
				printf_s("\nCette piece a ete prise par l'equipe bleu...\n");
			}
				break;
			case 2: if (chatrouge.etat == 1) {
				printf_s("\nLes coordonnees de h sont (%i; %i)\nEntrez ses nouvelles coordonnees :\n", chatrouge.x, chatrouge.y);
				do {
					scanf_s("%i%i", &tempX, &tempY);
				} while ((tempX > chatrouge.x + 1) || (tempX < chatrouge.x - 1) || (tempY > chatrouge.y + 1) || (tempY < chatrouge.y - 1) || (((tempX > chatrouge.x) || (tempX < chatrouge.x)) && ((tempY > chatrouge.y) || (tempY < chatrouge.y))));
				chatrouge.x = tempX;
				chatrouge.y = tempY;
				tempX = switchCoordX(tempX);
				tempY = switchCoordY(tempY);
				//printf_s("\n%i et %i", tempX, tempY); // test les valeurs
				plateau[chatrouge.oldVraiY][chatrouge.oldVraiX] = ' ';
				plateau[tempY][tempX] = chatrouge.nom;
				chatrouge.oldVraiY = tempY;
				chatrouge.oldVraiX = tempX;
			}
				  else {
				printf_s("\nCette piece a ete prise par l'equipe bleu...\n");
			}
				break;
			case 3: if (louprouge.etat == 1) {
				printf_s("\nLes coordonnees de o sont (%i; %i)\nEntrez ses nouvelles coordonnees :\n", louprouge.x, louprouge.y);
				do {
					scanf_s("%i%i", &tempX, &tempY);
				} while ((tempX > louprouge.x + 1) || (tempX < louprouge.x - 1) || (tempY > louprouge.y + 1) || (tempY < louprouge.y - 1) || (((tempX > louprouge.x) || (tempX < louprouge.x)) && ((tempY > louprouge.y) || (tempY < louprouge.y))));
				louprouge.x = tempX;
				louprouge.y = tempY;
				tempX = switchCoordX(tempX);
				tempY = switchCoordY(tempY);
				//printf_s("\n%i et %i", tempX, tempY); // test les valeurs
				plateau[louprouge.oldVraiY][louprouge.oldVraiX] = ' ';
				plateau[tempY][tempX] = louprouge.nom;
				louprouge.oldVraiY = tempY;
				louprouge.oldVraiX = tempX;
			}
				  else {
				printf_s("\nCette piece a ete prise par l'equipe bleu...\n");
			}
				break;
			case 4: if (chienrouge.etat == 1) {
				printf_s("\nLes coordonnees de c sont (%i; %i)\nEntrez ses nouvelles coordonnees :\n", chienrouge.x, chienrouge.y);
				do {
					scanf_s("%i%i", &tempX, &tempY);
				} while ((tempX > chienrouge.x + 1) || (tempX < chienrouge.x - 1) || (tempY > chienrouge.y + 1) || (tempY < chienrouge.y - 1) || (((tempX > chienrouge.x) || (tempX < chienrouge.x)) && ((tempY > chienrouge.y) || (tempY < chienrouge.y))));
				chienrouge.x = tempX;
				chienrouge.y = tempY;
				tempX = switchCoordX(tempX);
				tempY = switchCoordY(tempY);
				//printf_s("\n%i et %i", tempX, tempY); // test les valeurs
				plateau[chienrouge.oldVraiY][chienrouge.oldVraiX] = ' ';
				plateau[tempY][tempX] = chienrouge.nom;
				chienrouge.oldVraiY = tempY;
				chienrouge.oldVraiX = tempX;
			}
				  else {
				printf_s("\nCette piece a ete prise par l'equipe bleu...\n");
			}
				break;
			case 5: if (panthererouge.etat == 1) {
				printf_s("\nLes coordonnees de p sont (%i; %i)\nEntrez ses nouvelles coordonnees :\n", panthererouge.x, panthererouge.y);
				do {
					scanf_s("%i%i", &tempX, &tempY);
				} while ((tempX > panthererouge.x + 1) || (tempX < panthererouge.x - 1) || (tempY > panthererouge.y + 1) || (tempY < panthererouge.y - 1) || (((tempX > panthererouge.x) || (tempX < panthererouge.x)) && ((tempY > panthererouge.y) || (tempY < panthererouge.y))));
				panthererouge.x = tempX;
				panthererouge.y = tempY;
				tempX = switchCoordX(tempX);
				tempY = switchCoordY(tempY);
				//printf_s("\n%i et %i", tempX, tempY); // test les valeurs
				plateau[panthererouge.oldVraiY][panthererouge.oldVraiX] = ' ';
				plateau[tempY][tempX] = panthererouge.nom;
				panthererouge.oldVraiY = tempY;
				panthererouge.oldVraiX = tempX;
			}
				  else {
				printf_s("\nCette piece a ete prise par l'equipe bleu...\n");
			}
				break;
			case 6: if (tigrerouge.etat == 1) {
				printf_s("\nLes coordonnees de t sont (%i; %i)\nEntrez ses nouvelles coordonnees :\n", tigrerouge.x, tigrerouge.y);
				do {
					scanf_s("%i%i", &tempX, &tempY);
				} while ((tempX > tigrerouge.x + 1) || (tempX < tigrerouge.x - 1) || (tempY > tigrerouge.y + 1) || (tempY < tigrerouge.y - 1) || (((tempX > tigrerouge.x) || (tempX < tigrerouge.x)) && ((tempY > tigrerouge.y) || (tempY < tigrerouge.y))));
				tigrerouge.x = tempX;
				tigrerouge.y = tempY;
				tempX = switchCoordX(tempX);
				tempY = switchCoordY(tempY);
				//printf_s("\n%i et %i", tempX, tempY); // test les valeurs
				plateau[tigrerouge.oldVraiY][tigrerouge.oldVraiX] = ' ';
				plateau[tempY][tempX] = tigrerouge.nom;
				tigrerouge.oldVraiY = tempY;
				tigrerouge.oldVraiX = tempX;
			}
				  else {
				printf_s("\nCette piece a ete prise par l'equipe bleu...\n");
			}
				break;
			case 7: if (lionrouge.etat == 1) {
				printf_s("\nLes coordonnees de l sont (%i; %i)\nEntrez ses nouvelles coordonnees :\n", lionrouge.x, lionrouge.y);
				do {
					scanf_s("%i%i", &tempX, &tempY);
				} while ((tempX > lionrouge.x + 1) || (tempX < lionrouge.x - 1) || (tempY > lionrouge.y + 1) || (tempY < lionrouge.y - 1) || (((tempX > lionrouge.x) || (tempX < lionrouge.x)) && ((tempY > lionrouge.y) || (tempY < lionrouge.y))));
				lionrouge.x = tempX;
				lionrouge.y = tempY;
				tempX = switchCoordX(tempX);
				tempY = switchCoordY(tempY);
				//printf_s("\n%i et %i", tempX, tempY); // test les valeurs
				plateau[lionrouge.oldVraiY][lionrouge.oldVraiX] = ' ';
				plateau[tempY][tempX] = lionrouge.nom;
				lionrouge.oldVraiY = tempY;
				lionrouge.oldVraiX = tempX;
			}
				  else {
				printf_s("\nCette piece a ete prise par l'equipe bleu...\n");
			}
				break;
			case 8: if (elephantrouge.etat == 1) {
				printf_s("\nLes coordonnees de e sont (%i; %i)\nEntrez ses nouvelles coordonnees :\n", elephantrouge.x, elephantrouge.y);
				do {
					scanf_s("%i%i", &tempX, &tempY);
				} while ((tempX > elephantrouge.x + 1) || (tempX < elephantrouge.x - 1) || (tempY > elephantrouge.y + 1) || (tempY < elephantrouge.y - 1) || (((tempX > elephantrouge.x) || (tempX < elephantrouge.x)) && ((tempY > elephantrouge.y) || (tempY < elephantrouge.y))));
				elephantrouge.x = tempX;
				elephantrouge.y = tempY;
				tempX = switchCoordX(tempX);
				tempY = switchCoordY(tempY);
				//printf_s("\n%i et %i", tempX, tempY); // test les valeurs
				plateau[elephantrouge.oldVraiY][elephantrouge.oldVraiX] = ' ';
				plateau[tempY][tempX] = elephantrouge.nom;
				elephantrouge.oldVraiY = tempY;
				elephantrouge.oldVraiX = tempX;
			}
				  else {
				printf_s("\nCette piece a ete prise par l'equipe bleu...\n");
			}
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
	base basebleu, baserouge;
	piege piegeb, pieger;
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
	basebleu.x = 4;
	basebleu.y = 9;
	basebleu.oldVraiX = 7;
	basebleu.oldVraiY = 1;
	basebleu.nom = '\x58';
	baserouge.x = 4;
	baserouge.y = 9;
	baserouge.oldVraiX = 7;
	baserouge.oldVraiY = 17;
	baserouge.nom = '\x78';
	piegeb.x1 = 3;
	piegeb.y1 = 9;
	piegeb.oldVraiX1 = 5;
	piegeb.oldVraiY1 = 1;
	piegeb.x2 = 5;
	piegeb.y2 = 9;
	piegeb.oldVraiX2 = 9;
	piegeb.oldVraiY2 = 1;
	piegeb.x3 = 4;
	piegeb.y3 = 8;
	piegeb.oldVraiX3 = 7;
	piegeb.oldVraiY3 = 2;
	piegeb.nom = '\x2B';
	pieger.x1 = 3;
	pieger.y1 = 1;
	pieger.oldVraiX1 = 5;
	pieger.oldVraiY1 = 17;
	pieger.x1 = 5;
	pieger.y1 = 1;
	pieger.oldVraiX1 = 9;
	pieger.oldVraiY1 = 17;
	pieger.x1 = 4;
	pieger.y1 = 2;
	pieger.oldVraiX1 = 7;
	pieger.oldVraiY1 = 15;
	pieger.nom = '\x2B';
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
	Sleep(5000);
	initPlateau(plateau, basebleu, baserouge, piegeb, pieger, ratbleu, ratrouge, chatbleu, chatrouge, loupbleu, louprouge, chienbleu, chienrouge, pantherebleu, panthererouge, tigrebleu, tigrerouge, lionbleu, lionrouge, elephantbleu, elephantrouge);
	affichagePlateau(plateau);
	play(plateau, basebleu, baserouge, piegeb, pieger, ratbleu, ratrouge, chatbleu, chatrouge, loupbleu, louprouge, chienbleu, chienrouge, pantherebleu, panthererouge, tigrebleu, tigrerouge, lionbleu, lionrouge, elephantbleu, elephantrouge, vraiX, vraiY);
}
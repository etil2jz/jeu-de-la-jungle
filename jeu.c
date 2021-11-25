/*
Le projet consiste plus spécialement à modéliser le jeu en mode texte (dans un premier temps).
Les pions seront des lettres. Le déplacement des pièces se fera d’abord par l’entrée des coordonnées
puis par l'intermédiaire de la souris.
Suivant l’avancement du projet, le programme permettra :
	- de jouer à deux sur le même PC
	- de jouer contre l’ordinateur grâce à l’implantation d’une intelligence artificielle
	- de jouer contre un autre logiciel (une intelligence artificielle contre l’autre)
La réalisation en mode graphique apportera un bonus (maximum 2 points), mais n’est pas obligatoire.
*/

/*
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
	int x, y, force, etat;
}rat;

typedef struct chat {
	int x, y, force, etat;
}chat;

typedef struct loup {
	int x, y, force, etat;
}loup;

typedef struct chien {
	int x, y, force, etat;
}chien;

typedef struct panthere {
	int x, y, force, etat;
}panthere;

typedef struct tigre {
	int x, y, force, etat;
}tigre;

typedef struct lion {
	int x, y, force, etat;
}lion;

typedef struct elephant {
	int x, y, force, etat;
}elephant;

void initPlateau(char plateau[][15]) {
	int i, j;
	plateau[1][1] = 'L';
	plateau[1][3] = ' ';
	plateau[1][5] = ' ';
	plateau[1][7] = ' ';
	plateau[1][9] = ' ';
	plateau[1][11] = ' ';
	plateau[1][13] = 'T';

	plateau[3][1] = ' ';
	plateau[3][3] = 'C';
	plateau[3][5] = ' ';
	plateau[3][7] = ' ';
	plateau[3][9] = ' ';
	plateau[3][11] = 'H';
	plateau[3][13] = ' ';

	plateau[5][1] = 'R';
	plateau[5][3] = ' ';
	plateau[5][5] = 'P';
	plateau[5][7] = ' ';
	plateau[5][9] = 'O';
	plateau[5][11] = ' ';
	plateau[5][13] = 'E';

	plateau[7][1] = ' ';
	plateau[7][3] = 0xb2;
	plateau[7][5] = 0xb2;
	plateau[7][7] = ' ';
	plateau[7][9] = 0xb2;
	plateau[7][11] = 0xb2;
	plateau[7][13] = ' ';

	plateau[9][1] = ' ';
	plateau[9][3] = 0xb2;
	plateau[9][5] = 0xb2;
	plateau[9][7] = ' ';
	plateau[9][9] = 0xb2;
	plateau[9][11] = 0xb2;
	plateau[9][13] = ' ';

	plateau[11][1] = ' ';
	plateau[11][3] = 0xb2;
	plateau[11][5] = 0xb2;
	plateau[11][7] = ' ';
	plateau[11][9] = 0xb2;
	plateau[11][11] = 0xb2;
	plateau[11][13] = ' ';

	plateau[13][1] = 'E';
	plateau[13][3] = ' ';
	plateau[13][5] = 'O';
	plateau[13][7] = ' ';
	plateau[13][9] = 'P';
	plateau[13][11] = ' ';
	plateau[13][13] = 'R';

	plateau[15][1] = ' ';
	plateau[15][3] = 'H';
	plateau[15][5] = ' ';
	plateau[15][7] = ' ';
	plateau[15][9] = ' ';
	plateau[15][11] = 'C';
	plateau[15][13] = ' ';

	plateau[17][1] = 'T';
	plateau[17][3] = ' ';
	plateau[17][5] = ' ';
	plateau[17][7] = ' ';
	plateau[17][9] = ' ';
	plateau[17][11] = ' ';
	plateau[17][13] = 'L';
}

void affichagePlateau(char plateau[][15]) {
	int i, j;
	for (i = 0; i < 19; i++) {
		if ((i % 2) == 0) {
			for (j = 0; j < 15; j++) {
				plateau[i][j] = '-';
			}
		}
		else {
			for (j = 0; j < 15; j += 2) {
				plateau[i][j] = '|';
			}
		}
	}

	for (i = 0; i < 19; i++) {
		for (j = 0; j < 15; j++) {
			printf_s("%c", plateau[i][j]);
		}
		printf_s("\n");
	}
}

void initPions() {
	rat ratbleu, ratrouge;
	chat chatbleu, chatrouge;
	loup loupbleu, louprouge;
	chien chienbleu, chienrouge;
	panthere pantherebleu, panthererouge;
	tigre tigrebleu, tigrerouge;
	lion lionbleu, lionrouge;
	elephant elephantbleu, elephantrouge;
	ratbleu.x = 7;
	ratbleu.y = 3;
	ratbleu.force = 1;
	ratbleu.etat = 1;
	ratrouge.x = 1;
	ratrouge.y = 7;
	ratrouge.force = 1;
	ratrouge.etat = 1;

}

int initEquipes() {
	int x;
	do {
		printf_s("Joueur 1, choisissez votre equipe.\n\nTapez 1 pour les bleus, 2 pour les rouges :\n");
		scanf_s("%i", &x);
	} while (x < 1 || x > 2);
	return x;
}

int main() {
	int joueur1 = 0, joueur2 = 0;
	char plateau[19][15];
	system("title Jeu de la jungle");
	regles();
	joueur1 = initEquipes();
	if (joueur1 == 1) {
		printf_s("\nLe joueur 1 est dans l'equipe bleue\nVos pieces seront en minuscule\n\nLe joueur 2 est dans l'equipe rouge\nVos pieces seront en majuscule\n");
	}
	else {
		printf_s("\nLe joueur 1 est dans l'equipe rouge\nVos pieces seront en majuscule\n\nLe joueur 2 est dans l'equipe bleue\nVos pieces seront en minuscule\n");
	}
	Sleep(1000);
	system("cls");
	//initPions();
	initPlateau(plateau);
	affichagePlateau(plateau);
}
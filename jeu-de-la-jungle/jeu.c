/*
Le projet consiste plus sp�cialement � mod�liser le jeu en mode texte (dans un premier temps).
Les pions seront des lettres. Le d�placement des pi�ces se fera d�abord par l�entr�e des coordonn�es
puis par l'interm�diaire de la souris.
Suivant l�avancement du projet, le programme permettra :
	- de jouer � deux sur le m�me PC
	- de jouer contre l�ordinateur gr�ce � l�implantation d�une intelligence artificielle
	- de jouer contre un autre logiciel (une intelligence artificielle contre l�autre)
La r�alisation en mode graphique apportera un bonus (maximum 2 points), mais n�est pas obligatoire.
*/

/*
G�rer les commandes de l'utilisateur :
	- Placer les pions
	- Contr�ler le d�roulement de la partie (r�gles...)
	- Jouer un coup
	- Reprendre une partie � partir d'un coup donn�
	- Sauver la partie sur disque
	- Calculer les points des joueurs

Sortie sur �cran des informations

D�finir les structures de donn�es permettant la r�solution de ce probl�me

D�crire sous forme modulaire les diff�rentes s�quences de fonctionnement

Traduire les structures de donn�es et les actions en C
*/

#include <stdio.h>
#include <stdlib.h>

void regles() {
	int lu = 0;
	system("color A");
	printf_s("            \x10 REGLES DU JEU \x11");
	printf_s("\n\n\x16 Chaque joueur deplace, a son tour, une des pieces d'une seule case a la fois, horizontalement ou verticalement.\n\n\x16 A l'occasion d'un deplacement une piece peut prendre une piece adverse egale ou inferieure en se mettant a sa place. La piece prise est enlevee du jeu. Cependant, le rat peut prendre l'elephant.\n\n\x16 Seul le rat peut se deplacer dans les lacs mais il ne peut pas capturer l'elephant adverse en passant du lac sur la rive.\n\n\x16 Les lions et les tigres peuvent sauter directement d'une rive a l'autre verticalement ou horizontalement sauf si un rat (ami ou adverse) se trouve dans la ligne de saut.\n\n\x16 Quand une piece se trouve dans un piege adverse, sa force combative devient momentanement nulle mais elle conserve la possibilite de se deplacer.\n\n\x16 Les pieces ne peuvent pas entrer dans leur propre sanctuaire.\n\n\nApres avoir pris connaissance des regles, tapez 1 :\n");
	do {
		scanf_s("%i", &lu);
	} while (lu != 1);
	system("cls");
	system("color 7");
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

// tableau 15 largeur 19 hauteur ?

void initPlateau() {

	for (int i = 0; i < 9; i++) {
		printf_s("---------------------------------\n");
		for (int j = 0; j < 16; j++) {

		}
	}
}

int main() {
	rat ratbleu, ratrouge;
	ratrouge.x = 2;
	ratrouge.y = 6;
	ratbleu.x = ;
	chat chatbleu, chatrouge;
	loup loupbleu, louprouge;
	chien chienbleu, chienrouge;
	panthere pantherebleu, panthererouge;
	tigre tigrebleu, tigrerouge;
	lion lionbleu, lionrouge;
	elephant elephantbleu, elephantrouge;
	system("title Jeu de la jungle");
	regles();
	initPlateau();
}
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

void regles() {
	printf_s("::REGLES DU JEU::\n\n- Chaque joueur deplace, a son tour, une des pieces d'une seule case a la fois, horizontalement ou verticalement.\n\n- A l'occasion d'un deplacement une piece peut prendre une piece adverse egale ou inferieure en se mettant a sa place. La piece prise est enlevee du jeu. Cependant, le rat peut prendre l'elephant.\n\n- Seul le rat peut se deplacer dans les lacs mais il ne peut pas capturer l'elephant adverse en passant du lac sur la rive.\n\n- Les lions et les tigres peuvent sauter directement d'une rive a l'autre verticalement ou horizontalement sauf si un rat (ami ou adverse) se trouve dans la ligne de saut.\n\n- Quand une piece se trouve dans un piege adverse, sa force combative devient momentanement nulle mais elle conserve la possibilite de se deplacer.\n\n- Les pieces ne peuvent pas entrer dans leur propre sanctuaire.\n\n\n");
}

typedef struct rat {
	int x, y;
}rat;

typedef struct chat {
	int x, y;
}chat;

typedef struct loup {
	int x, y;
}loup;

typedef struct chien {
	int x, y;
}chien;

typedef struct panthere {
	int x, y;
}panthere;

typedef struct tigre {
	int x, y;
}tigre;

typedef struct lion {
	int x, y;
}lion;

typedef struct elephant {
	int x, y;
}elephant;

int main() {
	regles();
}
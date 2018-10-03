#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#pragma warning(disable:4996)

#define max_champs 25 // Nombre maximum de champs d'une table
#define max_enregistrement 100 //Nombre maximal d'enregistrements
#define lgMot 30 // Longueur max d'une chaine de caracteres
#define lgMax 80 // Longueur maximale d'une ligne de commande

typedef enum { TRUE, FALSE }bool;
char mot[lgMot + 1];//une chaîne de caractères dans laquelle on stocke la commande saisie
unsigned char crit1[lgMot + 1], crit2[lgMot + 1];
unsigned int cmp_table = 0;

typedef struct {
	unsigned char data[lgMot + 1];
}Data;
typedef struct {
	Data colonne[max_champs];
}Enregistrement;
typedef struct {
	char nom[lgMot + 1];// variable nom de type char et de longueur 30 + 1
	char type[lgMot + 1];// variable type de type char et de longueur 30 + 1
} Champ;
typedef struct {
	char nom[lgMot + 1];      //chaîne de caractères dans laquelle on stocke le nom de la table
	Champ schema[max_champs];   //struct qui contient le nom et le type de chaques champs
	Enregistrement enrg[max_enregistrement];  //struct dans laquelle on stocke le nom des enregistrements et leurs rangs
	unsigned int nbChamps;     //variable indiquant le nombre de champs d'une table
	unsigned int nbEnrg;
}Table;


//Prototypes des fonctions utilisées
void create_table(Table *t);
void afficher_schema(const Table *t);
void inserer_enregistrement(Table* t);
void afficher_enregistrements(const Table* t);
void delete_enregistrement(Table* t);
void afficher_enregistrement(const Table* t);
void delete_table(Table* t);
void select_enregistrement(Table* t);
bool compare_enregistrement(Table *t, unsigned int nbChamps_temp, unsigned int rang_temp);//fonction de vérification de validité des enregistrements par rapport aux critères


int main() {
	Table table = { NULL };
	table.nbEnrg = 0;
	while (1) { // ou do {} while(1);
				// boucle infinie sur les 9 commandes
		scanf("%s", &mot); // le mot lu est une chaine de 30 caract. 
						   //on verifie quelle est la commande saisie
		if (strcmp(mot, "Create_table") == 0) {
			create_table(&table); //créer une table
		}
		else if (strcmp(mot, "Afficher_schema") == 0) {
			afficher_schema(&table); //affiche une table
		}
		else if (strcmp(mot, "Insert_enregistrement") == 0) {
			inserer_enregistrement(&table); //insert un enregistrement
		}
		else if (strcmp(mot, "Afficher_enregistrements") == 0) {
			afficher_enregistrements(&table); //affiche tous les enregistrements d'une table donnée
		}
		else if (strcmp(mot, "Delete_enregistrement") == 0) {
			delete_enregistrement(&table); //supprime un enregistrement
		}
		else if (strcmp(mot, "Afficher_enregistrement") == 0) {
			afficher_enregistrement(&table); //affiche un enregistrement donné
		}
		else if (strcmp(mot, "Delete_table") == 0) {
			delete_table(&table); //supprime touts les éléments d'une table
		}
		else if (strcmp(mot, "Select_enregistrement") == 0) {
			select_enregistrement(&table);  //
		}
		else if (strcmp(mot, "Exit") == 0) {
			exit(0); // sortie du programme principal
		}
	}
	system("pause");
	return 0;
}
void create_table(Table *t) {
	unsigned char temp[lgMot + 1];//variable de stockage temporaire pour le nom de la table
	scanf("%s", &temp);                                //lorsqu'on entre une 2eme fois ou plus dans la fonction
	if (strcmp(temp, t->nom) != 0 && cmp_table != 0) { //on vérifie si la table existe 
		printf("table inconnue\n");
	}
	else if (cmp_table != 0)
		printf("table existante\n");
	else {      //la première fois qu'on entre dans la fonction create_table
		scanf("%u", &(t->nbChamps));       //on demande la saisie du nombre de champs
		strcpy(t->nom, temp);                //on colle la valeur de temp dans t.nom
		for (unsigned int i = 0; i < t->nbChamps; ++i) { // pour i allant de 0 à nombre de champs-1
			scanf("%s %s", t->schema[i].nom, t->schema[i].type); //on demande la saisie du nom et du type de chaque champs 
		++cmp_table;
		}
		
	}
}
void afficher_schema(const Table *t) {
	unsigned char table_nom[lgMot + 1];//variable locale qui vérifie si la table éxiste
	scanf("%s", &table_nom);            //on la lit...
	if (strcmp(table_nom, t->nom) == 0) { //...et si la table existe:
		printf("%s %u\n", &t->nom, t->nbChamps);       //on affiche son nom et son nombre de champs
		for (unsigned int i = 0; i < t->nbChamps; ++i) { // pour i allant de 0 à nombre de champs-1
			printf("%s %s\n", t->schema[i].nom, t->schema[i].type); //on affiche le nom et le type de chaque champs
		}
	}
	else {
		printf("table inconnue\n");    //sinon on affiche "table inconnue"
	}
}
void inserer_enregistrement(Table* t) {
	++t->nbEnrg;
	unsigned char table_nom[lgMot + 1]; //variable locale qui vérifie si la table éxiste
	scanf("%s", &table_nom);             //on la lit...
	if (strcmp(table_nom, t->nom) == 0) { //...et si la table existe:
		for (unsigned int i = 0; i < t->nbChamps; ++i) { // pour i allant de 0 à nombre de champs-1
			scanf("%s", t->enrg[t->nbEnrg].colonne[i].data);      //on demande la saisie de chaque enregistrements
		}
	}
	else {
		printf("table inconnue\n");     //sinon on affiche "table inconnue"
	}

}
void afficher_enregistrements(const Table* t) {
	unsigned char table_nom[lgMot + 1]; //variable locale qui vérifie si la table existe
	scanf("%s", &table_nom);             //on la lit...
	if (strcmp(table_nom, t->nom) == 0) { //...et si la table existe: 
		for (unsigned int i = 1; i <= t->nbEnrg; ++i) { // pour i allant de 1 au nombre d'enregistrement saisi
			printf("%u", i);            // on affiche le rang de chaque enregistrement
			for (unsigned int n = 0; n < t->nbChamps; ++n) { // pour n allant de 0 à nombre de champs-1
				printf(" %s %s", t->schema[n].type, t->enrg[i].colonne[n].data); // on affiche chaques enregistrements précédés de leur type
			}
			printf("\n");                                 //puis on revient à la ligne après la procédure 
		}
	}
	else {
		printf("table inconnue\n");          //sinon on affiche "table inconnue"
	}
}
void delete_enregistrement(Table* t) {
	unsigned char table_nom[lgMot + 1]; //variable locale qui vérifie si la table éxiste
	unsigned int rang_suppr;             //variable locale qui indique le rang de l'enregistrement à supprimer
	scanf("%s", &table_nom);             //on demande la saisie du nom de la table
	if (strcmp(table_nom, t->nom) == 0) { //et si elle éxiste:
		scanf("%u", &rang_suppr);                          //on demande la saisie du rang de l'enregistrement à supprimer
		for (; rang_suppr <= t->nbEnrg; ++rang_suppr) { //on vérifie si l'enregistrement demandé existe
			for (unsigned int i = 0; i < t->nbChamps; ++i) {            //et pour i allant de 0 à nombre de champs-1
				if (rang_suppr == t->nbEnrg) {                           //si on se trouve à la dernière ligne de l'enregistrement
					--t->nbEnrg;        //on diminue le nombre de rangs de 1, on annule la valeur du dernier rang supprimé et on sort du if 
					return;
				}
				else {
					strcpy(t->enrg[rang_suppr].colonne[i].data, t->enrg[rang_suppr + 1].colonne[i].data); //sinon on supprime l'enregistrement demandé et on décale chaque enrgistrements d'un cran en arrière 
				}
			}
		}
		printf("enregistrement inconnu\n");      //si l'enregistrement n'existe pas on affiche "enregistrement inconnu"
		return;
	}
	else
		printf("table inconnue\n");  //sinon on affiche "table inconnue"
}
void afficher_enregistrement(const Table* t) {
	unsigned char table_nom[lgMot + 1];//variable locale qui vérifie si la table éxiste
	unsigned int rang_enrg;          //variable locale qui indique le rang de l'enregistrement à afficher
	scanf("%s", &table_nom);          //on demande la saisie du nom de la table
	if (strcmp(table_nom, t->nom) == 0) {//et si elle éxiste:
		scanf("%u", &rang_enrg);                          //on demande la saisie du rang de l'enregistrement à afficher
		if (rang_enrg <= t->nbEnrg) {                  //si l'enregistrement à afficher existe,
			printf("%u", rang_enrg);  //on affiche son rang
			for (unsigned int i = 0; i < t->nbChamps; ++i) {     // pour i allant de 0 à nombre de champs-1
				printf(" %s %s", t->schema[i].type, t->enrg[rang_enrg].colonne[i].data); //on affiche l'enregistrement demandé précédé de sont type
			}
			printf("\n"); return;                         //on revient à la ligne et on sort de la boucle
		}
		printf("enregistrement inconnu\n");           //si l'enregistrement n'existe pas on affiche "enregistrement inconnu"
		return;
	}
	else
		printf("table inconnue\n");           //sinon on affiche "table inconnue"
}
void delete_table(Table* t) {
	unsigned char table_nom[lgMot + 1]; //variable locale qui vérifie si la table éxiste
	scanf("%s", &table_nom);             //on la lit...
	if (strcmp(table_nom, t->nom) == 0) { //...et si la table existe:
		t->nbChamps = t->nbEnrg = cmp_table = 0;              //on réinitialise le nombre de champs...
		strcpy(t->nom, "\0");
	}
	else {
		printf("table inconnue\n");     //sinon on affiche "table inconnue"
	}
}

void select_enregistrement(Table* t) {
	unsigned char table_nom[lgMot + 1], schema_nom[lgMot + 1];
	unsigned int statut;
	scanf("%s", &table_nom);
	if (strcmp(table_nom, t->nom) == 0) {
		scanf("%s", &schema_nom);
		scanf("%s %s", &crit1, &crit2);
		for (unsigned int i = 0; i < t->nbChamps; ++i) {
			if (strcmp(schema_nom, t->schema[i].nom) == 0) {
				for (unsigned int rang_temp = 1; rang_temp <= t->nbEnrg; ++rang_temp) {
					statut = 0;
					statut = compare_enregistrement(t, i, rang_temp, &statut);
					if (statut) {
						printf("%u", rang_temp);  //on affiche son rang
						for (unsigned int n = 0; n < t->nbChamps; ++n) {     // pour i allant de 0 à nombre de champs-1
							printf(" %s %s", t->schema[n].type, t->enrg[rang_temp].colonne[n].data); //on affiche l'enregistrement demandé précédé de sont type
						}
						printf("\n");
					}
				}
			}
		}
	}
	else {
		printf("table inconnue\n");
	}
}
#define L t->enrg[rang_temp].colonne[nbChamps_temp].data
bool compare_enregistrement(Table *t, unsigned int nbChamps_temp, unsigned int rang_temp) {
	if (strcmp(t->schema[nbChamps_temp].type, "INT") == 0) {
		return ((atoi(crit1) <= atoi(&L)) && (atoi(&L) <= atoi(crit2)) || (atoi(crit2) <= atoi(&L)) && (atoi(&L) <= atoi(crit1)));
	}
	else if (strcmp(t->schema[nbChamps_temp].type, "FLOAT") == 0) {
		return ((atof(crit1) <= atof(&L)) && (atof(&L) <= atof(crit2)) || (atof(crit2) <= atof(&L)) && (atof(&L) <= atof(crit1)));
	}
	else if (strcmp(t->schema[nbChamps_temp].type, "TEXT") == 0) {
		return ((strcmp(crit1, L) <= 0) && (strcmp(crit2, L) >= 0) || (strcmp(crit2, L) <= 0) && (strcmp(crit1, L) >= 0));
	}
	else if (strcmp(t->schema[nbChamps_temp].type, "DATE") == 0) {
		char aux[3][lgMot + 1];
		unsigned int c1 = atoi(strncpy(aux[0], crit1, 2)) + atoi(strncpy(aux[0], crit1 + 3, 2)) * 100 + atoi(strncpy(aux[0], crit1 + 6, 4)) * 10000;
		unsigned int c2 = atoi(strncpy(aux[1], crit2, 2)) + atoi(strncpy(aux[1], crit2 + 3, 2)) * 100 + atoi(strncpy(aux[1], crit2 + 6, 4)) * 10000;
		unsigned int data = atoi(strncpy(aux[2], L, 2)) + atoi(strncpy(aux[2], L + 3, 2)) * 100 + atoi(strncpy(aux[2], L + 6, 4)) * 10000;
		return ((c1 <= data && data <= c2) || (c2 <= data && data <= c1));
	}
}

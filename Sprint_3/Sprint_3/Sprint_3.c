#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#pragma warning(disable:4996)

#define max_champs 25 // Nombre maximum de champs d'une table
#define max_enregistrement 100 //Nombre maximal d'enregistrements
#define lgMot 30 // Longueur max d'une chaine de caracteres
#define lgMax 80 // Longueur maximale d'une ligne de commande

char mot[lgMot + 1];	//une chaîne de caractères dans laquelle on stocke la commande saisie
unsigned int cmp_table = 0;	//un compteur qui passe à 1 lorsque une table est créée et à 0 quand il n'y a soit pas de table soit qu'elle est supprimée

typedef struct {
	unsigned char data[lgMot + 1];	//variable nom de type char et de longueur 30 + 1
}Data;
typedef struct {
	Data colonne[max_champs];	//struct dans lequel on stocke les valeurs de chaque champ dans une ligne d'enregistrement
}Enregistrement;
typedef struct {
	char nom[lgMot + 1];	// variable nom de type char et de longueur 30 + 1
	char type[lgMot + 1];	// variable type de type char et de longueur 30 + 1
} Champ;
typedef struct {
	char nom[lgMot + 1];      //chaîne de caractères dans laquelle on stocke le nom de la table
	Champ schema[max_champs];   //struct qui contient le nom et le type de chaques champs
	Enregistrement enrg[max_enregistrement];  //struct dans lequel on stocke les enregistrements
	unsigned int nbChamps;     //variable indiquant le nombre de champs d'une table
	unsigned int nbEnrg;	//varable indiquant le nombre d'enregistrement d'une table
}Table;


//Prototypes des fonctions utilisées
/*Création d'une table
*[in-out] t la table créée
*/
void create_table(Table *t);
/*Affichage d'une table
*[in] t la table à afficher
*/
void afficher_schema(const Table *t);
/*Insertion d'une ligne d'enregistrement
*[in-out] t la table dans laquelle on insère l'enregistrement
*/
void inserer_enregistrement(Table* t);
/*Affichage de tout les enregistrements
*[in] t la table qui contient les enregistrements à afficher
*/
void afficher_enregistrements(const Table* t);
/*Suppression d'un enregistrement
*[in] t la table dans laquelle on veut supprimer un enregistrement
*/
void delete_enregistrement(Table* t);
/*Affichage d'un enregistrement spécifique à une ligne n <= nbEnrg
*[in-out] t la table qui contient l'enregistrement à afficher
*/
void afficher_enregistrement(const Table* t);

int main() {
	Table table = { NULL }; //mise à vide de la table
	table.nbEnrg = 0; // mise à zéro du nombre d'enregistrement
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
	if (strcmp(temp, t->nom) != 0 && cmp_table != 0) {
		printf("table inconnue\n");	//si la table saisie est différente de celle déjà existante
	}
	else if (cmp_table != 0) //si la table existe déjà
		printf("table existante\n");
	else {      //la première fois qu'on entre dans la fonction create_table
		scanf("%u", &(t->nbChamps));       //on saisie le nombre de champs
		strcpy(t->nom, temp);                //on affecte la valeur de temp dans table.nom
		for (unsigned int i = 0; i < t->nbChamps; ++i) { // pour i allant de 0 à nombre de champs-1
			scanf("%s %s", t->schema[i].nom, t->schema[i].type); //on demande la saisie du nom et du type de chaque champs 
		}
		++cmp_table; // on incrémente le compteur de table pour indiquer son existance
	}
}
void afficher_schema(const Table *t) {
	unsigned char table_nom[lgMot + 1];//variable locale de stockage du nom de la table dont on veut afficher le schema
	scanf("%s", &table_nom);
	if (strcmp(table_nom, t->nom) == 0) { //on compare le nom de la table à celui saisi pour vérifier qu'elle existe 
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
	unsigned char table_nom[lgMot + 1]; //variable locale de stockage du nom de la table dans laquelle on veut insérer un enregistrement
	scanf("%s", &table_nom);
	if (strcmp(table_nom, t->nom) == 0) { //on compare le nom de la table à celui saisi pour vérifier qu'elle existe 
		++t->nbEnrg;			//on incrémente de 1 le nombre d'enregistrement
		for (unsigned int i = 0; i < t->nbChamps; ++i) { // pour i allant de 0 à nombre de champs-1
			scanf("%s", t->enrg[t->nbEnrg].colonne[i].data);      //on demande la saisie de chaque champ pour cet ligne d'enregistrement
		}
	}
	else {
		printf("table inconnue\n");     //sinon on affiche "table inconnue"
	}
}
void afficher_enregistrements(const Table* t) {
	unsigned char table_nom[lgMot + 1]; //variable locale de stockage du nom de la table dont on veut afficher les enregistrement
	scanf("%s", &table_nom);
	if (strcmp(table_nom, t->nom) == 0) { //on compare le nom de la table à celui saisi pour vérifier qu'elle existe 
		for (unsigned int i = 1; i <= t->nbEnrg; ++i) { // pour i allant de 1 au nombre d'enregistrement saisi
			printf("%u", i);            // on affiche le rang de chaque enregistrement
			for (unsigned int n = 0; n < t->nbChamps; ++n) { // pour n allant de 0 à nombre de champs-1
				printf(" %s %s", t->schema[n].type, t->enrg[i].colonne[n].data); // on affiche chaques enregistrements précédés de leur type
			}
			printf("\n");                                 //puis on revient à la ligne l'affichage d'une ligne entière
		}
	}
	else {
		printf("table inconnue\n");          //sinon on affiche "table inconnue"
	}
}
void delete_enregistrement(Table* t) {
	unsigned char table_nom[lgMot + 1]; //variable locale de stockage du nom de la table dont on veut supprimer un enregistrement
	unsigned int rang_suppr;             //variable locale qui indique le rang de l'enregistrement à supprimer
	scanf("%s", &table_nom);             //on demande la saisie du nom de la table
	if (strcmp(table_nom, t->nom) == 0) { //et si elle existe:
		scanf("%u", &rang_suppr);                          //on demande la saisie du rang de l'enregistrement à supprimer
		for (; rang_suppr <= t->nbEnrg; ++rang_suppr) { //on vérifie si l'enregistrement demandé existe et on décale les enregistrements à partir de rang_suppr jusqu'à table.nbEnrg
			for (unsigned int i = 0; i < t->nbChamps; ++i) {            //et pour i allant de 0 à nombre de champs-1
				if (rang_suppr == t->nbEnrg) {                           //lorsque on est à la dernière valeur de rang_suppr == table.nbEnrg
					--t->nbEnrg;        //on diminue le nombre de rangs de 1
					return;
				}
				else {
					strcpy(t->enrg[rang_suppr].colonne[i].data, t->enrg[rang_suppr + 1].colonne[i].data); //sinon on supprime l'enregistrement demandé et on décale chaque enrgistrements d'un cran en arrière 
				}
			}
		}
		printf("enregistrement inconnu\n");   //si l'enregistrement n'existe pas on affiche "enregistrement inconnu"
		return;
	}
	else
		printf("table inconnue\n");  //sinon on affiche "table inconnue"
}
void afficher_enregistrement(const Table* t) {
	unsigned char table_nom[lgMot + 1];//variable locale de stockage du nom de la table dont on veut afficher un enregistrement
	unsigned int rang_enrg;          //variable locale qui indique le rang de l'enregistrement à afficher
	scanf("%s", &table_nom);          //on demande la saisie du nom de la table
	if (strcmp(table_nom, t->nom) == 0) {//et si elle existe
		scanf("%u", &rang_enrg);                          //on demande la saisie du rang de l'enregistrement à afficher
		if (rang_enrg <= t->nbEnrg) {                  //si l'enregistrement à afficher existe,
			printf("%u", rang_enrg);  //on affiche son rang
			for (unsigned int i = 0; i < t->nbChamps; ++i) {     // pour i allant de 0 à nombre de champs-1
				printf(" %s %s", t->schema[i].type, t->enrg[rang_enrg].colonne[i].data); //on affiche les valeurs de chaque champ de l'enregistrement précédé de sont type
			}
			printf("\n"); return;                         //on revient à la ligne et on sort de la boucle
		}
		printf("enregistrement inconnu\n");           //si l'enregistrement n'existe pas on affiche "enregistrement inconnu"
		return;
	}
	else
		printf("table inconnue\n");           //sinon on affiche "table inconnue"
}
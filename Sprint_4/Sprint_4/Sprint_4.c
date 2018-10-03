#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#pragma warning(disable:4996)

#define max_champs 25 
#define max_enregistrement 100 
#define lgMot 30 
#define lgMax 80 

typedef enum { FALSE, TRUE}bool;
char mot[lgMot + 1];	
unsigned char crit1[lgMot + 1], crit2[lgMot + 1];	
unsigned int cmp_table = 0;	

typedef struct {
	unsigned char data[lgMot + 1];	
}Data;
typedef struct {
	Data colonne[max_champs];	
}Enregistrement;
typedef struct {
	char nom[lgMot + 1];	
	char type[lgMot + 1];	
} Champ;
typedef struct {
	char nom[lgMot + 1];      
	Champ schema[max_champs];   
	Enregistrement enrg[max_enregistrement];  
	unsigned int nbChamps;     
	unsigned int nbEnrg;	
}Table; 

void create_table(Table *t);

void afficher_schema(const Table *t);
void inserer_enregistrement(Table* t);
void afficher_enregistrements(const Table* t);
void delete_enregistrement(Table* t);
void afficher_enregistrement(const Table* t);
void delete_table(Table* t);
void select_enregistrement(const Table* t);
bool compare_enregistrement(const char type[lgMot + 1], const char data[lgMot + 1]);


int main() {
	Table table = { NULL }; 
	table.nbEnrg = 0; 
	while (1) { 
				
		scanf("%s", &mot); 
		
		if (strcmp(mot, "Create_table") == 0) {
			create_table(&table); 
		}
		else if (strcmp(mot, "Afficher_schema") == 0) {
			afficher_schema(&table); 
		}
		else if (strcmp(mot, "Insert_enregistrement") == 0) {
			inserer_enregistrement(&table); 
		}
		else if (strcmp(mot, "Afficher_enregistrements") == 0) {
			afficher_enregistrements(&table); 
		}
		else if (strcmp(mot, "Delete_enregistrement") == 0) {
			delete_enregistrement(&table); 
		}
		else if (strcmp(mot, "Afficher_enregistrement") == 0) {
			afficher_enregistrement(&table); 
		}
		else if (strcmp(mot, "Delete_table") == 0) {
			delete_table(&table); 
		}
		else if (strcmp(mot, "Select_enregistrement") == 0) {
			select_enregistrement(&table);  
		}
		else if (strcmp(mot, "Exit") == 0) {
			exit(0); 
		}
	}
	system("pause");
	return 0;
}
void create_table(Table *t) {
	unsigned char temp[lgMot + 1];
	scanf("%s", &temp);                                
	if (strcmp(temp, t->nom) != 0 && cmp_table != 0) { 
		printf("table inconnue\n");	
	}
	else if (cmp_table != 0) 
		printf("table existante\n");
	else {      
		scanf("%u", &(t->nbChamps));       
		strcpy(t->nom, temp);                
		for (unsigned int i = 0; i < t->nbChamps; ++i) { 
			scanf("%s %s", t->schema[i].nom, t->schema[i].type); 
		}
		++cmp_table; 
	}
}
void afficher_schema(const Table *t) {
	unsigned char table_nom[lgMot + 1];
	scanf("%s", &table_nom);            
	if (strcmp(table_nom, t->nom) == 0) { 
		printf("%s %u\n", &t->nom, t->nbChamps);       
		for (unsigned int i = 0; i < t->nbChamps; ++i) { 
			printf("%s %s\n", t->schema[i].nom, t->schema[i].type); 
		}
	}
	else {
		printf("table inconnue\n");    
	}
}
void inserer_enregistrement(Table* t) {
	unsigned char table_nom[lgMot + 1]; 
	scanf("%s", &table_nom);             
	if (strcmp(table_nom, t->nom) == 0) { 
		++t->nbEnrg;			
		for (unsigned int i = 0; i < t->nbChamps; ++i) { 
			scanf("%s", t->enrg[t->nbEnrg].colonne[i].data);      
		}
	}
	else {
		printf("table inconnue\n");     
	}
}
void afficher_enregistrements(const Table* t) {
	unsigned char table_nom[lgMot + 1]; 
	scanf("%s", &table_nom);
	if (strcmp(table_nom, t->nom) == 0) { 
		for (unsigned int i = 1; i <= t->nbEnrg; ++i) { 
			printf("%u", i);            
			for (unsigned int n = 0; n < t->nbChamps; ++n) { 
				printf(" %s %s", t->schema[n].type, t->enrg[i].colonne[n].data); 
			}
			printf("\n");                                 
		}
	}
	else {
		printf("table inconnue\n");          
	}
}
void delete_enregistrement(Table* t) {
	unsigned char table_nom[lgMot + 1]; 
	unsigned int rang_suppr;             
	scanf("%s", &table_nom);             
	if (strcmp(table_nom, t->nom) == 0) { 
		scanf("%u", &rang_suppr);                          
		for (; rang_suppr <= t->nbEnrg; ++rang_suppr) { 
			for (unsigned int i = 0; i < t->nbChamps; ++i) {            
				if (rang_suppr == t->nbEnrg) {                           
					--t->nbEnrg;        
					return;
				}
				else {
					strcpy(t->enrg[rang_suppr].colonne[i].data, t->enrg[rang_suppr + 1].colonne[i].data); 
				}
			}
		}
		printf("enregistrement inconnu\n");   
		return;
	}
	else
		printf("table inconnue\n");  
}
void afficher_enregistrement(const Table* t) {
	unsigned char table_nom[lgMot + 1];
	unsigned int rang_enrg;          
	scanf("%s", &table_nom);          
	if (strcmp(table_nom, t->nom) == 0) {
		scanf("%u", &rang_enrg);                          
		if (rang_enrg <= t->nbEnrg) {                  
			printf("%u", rang_enrg);  
			for (unsigned int i = 0; i < t->nbChamps; ++i) {     
				printf(" %s %s", t->schema[i].type, t->enrg[rang_enrg].colonne[i].data); 
			}
			printf("\n"); return;                         
		}
		printf("enregistrement inconnu\n");           
		return;
	}
	else
		printf("table inconnue\n");           
}
void delete_table(Table* t) {
	unsigned char table_nom[lgMot + 1]; 
	scanf("%s", &table_nom);             
	if (strcmp(table_nom, t->nom) == 0) { 
		cmp_table = t->nbEnrg = t->nbChamps = 0;            
		strcpy(t->nom, "\0");
	}
	else {
		printf("table inconnue\n");     
	}
}

void select_enregistrement(const Table* t) {
	unsigned char table_nom[lgMot + 1], champ_nom[lgMot + 1]; 
	scanf("%s", &table_nom); 
	if (strcmp(table_nom, t->nom) == 0) {
		scanf("%s", &champ_nom); 
		scanf("%s %s", &crit1, &crit2);
		for (unsigned int i = 0; i < t->nbChamps; ++i) { 
			if (strcmp(champ_nom, t->schema[i].nom) == 0) { 
				for (unsigned int rang_temp = 1; rang_temp <= t->nbEnrg; ++rang_temp) { 
					if (compare_enregistrement(t->schema[i].type, t->enrg[rang_temp].colonne[i].data)) {  
						printf("%u", rang_temp);  
						for (unsigned int n = 0; n < t->nbChamps; ++n) { 
							printf(" %s %s", t->schema[n].type, t->enrg[rang_temp].colonne[n].data); 
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

bool compare_enregistrement(const char type[lgMot + 1], const char data[lgMot + 1]) {
	if (strcmp(type, "INT") == 0) {		
		return (atoi(crit1) <= atoi(data) && atoi(data) <= atoi(crit2) || atoi(crit2) <= atoi(data) && atoi(data) <= atoi(crit1)); 
	}
	else if (strcmp(type, "FLOAT") == 0) {		
		return ((atof(crit1) <= atof(data)) && (atof(data) <= atof(crit2)) || (atof(crit2) <= atof(data)) && (atof(data) <= atof(crit1))); 
	}
	else if (strcmp(type, "TEXT") == 0) {		
		return ((crit1[0] <= data[0]) && (crit2[0] >= data[0]) || (crit2[0] >= data[0]) && (crit1[0] <= data[0])); 
	}
	else if (strcmp(type, "DATE") == 0) {		
		char aux[3][lgMot + 1]; 
		unsigned int c1 = atoi(strncpy(aux[0], crit1, 2)) + atoi(strncpy(aux[0], crit1 + 3, 2)) * 100 + atoi(strncpy(aux[0], crit1 + 6, 4)) * 10000; 
		unsigned int c2 = atoi(strncpy(aux[1], crit2, 2)) + atoi(strncpy(aux[1], crit2 + 3, 2)) * 100 + atoi(strncpy(aux[1], crit2 + 6, 4)) * 10000; 
		unsigned int data1 = atoi(strncpy(aux[2], data, 2)) + atoi(strncpy(aux[2], data + 3, 2)) * 100 + atoi(strncpy(aux[2], data + 6, 4)) * 10000;
		return ((c1 <= data1 && data1 <= c2) || (c2 <= data1 && data1 <= c1)); 
	}
	else
		return 0; 
}
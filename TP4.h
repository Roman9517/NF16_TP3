#include <stdio.h>
#include <stdlib.h>
#define NMAX 20

//declaration des structures

typedef struct benevole
{
    char nom[NMAX];
    char prenom[NMAX];
    char sexe;
    int CID;
    int annee;
    struct benevole *suivant;
} Benevole;

typedef struct ListeBenevole
{
    int nb;
    Benevole *premier;
} ListBenevoles;

typedef struct Tranche
{
    ListBenevoles *liste;
    int BorneSup;
    struct Tranche *pere;
    struct Tranche *filsG;
    struct Tranche *filsD;
} Tranche;



//prototypes

Benevole *nouveauBen(char *nom, char *prenom, int CIN, char sexe, int annee);

Tranche *nouvelleTranche(int borneSup);

ListBenevoles *nouvelleListe();

Tranche *ajoutTranche(Tranche *racine, int borneSup);

Benevole *insererBen(Tranche *racine, Benevole *benevole);

Benevole *chercherBen(Tranche *racine,int CIN, int *annee);

int supprimerBen(Tranche *racine, int CIN, int annee);

int supprimerTranche(Tranche *racine, int borneSup);

ListBenevoles *BenDhonneur(Tranche *racine);

int actualiser(Tranche *racine);

int totalBenTranche(Tranche *racine, int borneSup);

int totalBen(Tranche *racine);

float pourcentageTranche(Tranche *racine, int borneSup);

void afficherTranche(Tranche *racine, int borneSup);

void afficherArbre(Tranche *racine);



//prototypes fonctions ajoutées

int attribuerBorne(int annee);

ListBenevoles *insererlist(Tranche *tr, Benevole *bene);

Tranche *chercherTranche(Tranche *racine, int Bornesup );

int anneeActuelle();

int bornemax(Tranche *racine);

void afficherBen(Benevole *ben);

void detruire_Arbre(Tranche* racine);


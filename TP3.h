

typedef struct Produit T_Produit;
struct Produit
{
char marque[20];
float prix;
char qualite;
int quantite_en_stock;
T_Produit *suivant;
};


typedef struct Rayon T_Rayon;
struct Rayon {
char nom_rayon[20];
int nombre_produits;
T_Produit *premier;
T_Rayon *suivant;
};


typedef struct Magasin T_Magasin;
struct Magasin {
char nom[20];
T_Rayon *premier;
};


T_Produit *creerProduit(char *marque, float prix, char qualite, int quantite);

T_Rayon *creerRayon(char *nom);

T_Magasin *creerMagasin(char *nom);

int ajouterRayon(T_Magasin *magasin, T_Rayon *rayon);

int ajouterProduit(T_Rayon *rayon, T_Produit *produit);

void afficherMagasin(T_Magasin *magasin);

void afficherRayon(T_Rayon *rayon);

int supprimerProduit(T_Rayon *rayon, char* marque_produit);

int supprimerRayon(T_Magasin *magasin, char *nom_rayon);

void rechercheProduits(T_Magasin *magasin, float prix_min, float prix_max);

void fusionnerRayons(T_Magasin *magasin);

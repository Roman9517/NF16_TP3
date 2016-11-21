#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include "TP3.h";

T_Produit *creerProduit(char *marque, float prix, char qualite, int quantite)
{
T_Produit *nouveau= malloc(sizeof(T_Produit));
strcpy(nouveau->marque,marque);
nouveau->prix=prix;
nouveau->qualite=qualite;
nouveau->quantite_en_stock=quantite;
nouveau->suivant=NULL;
return nouveau;
}

T_Rayon *creerRayon(char *nom)
{
T_Rayon *nouveau = malloc(sizeof(T_Rayon));
strcpy(nouveau->nom_rayon,nom);
nouveau ->nombre_produits = 0;
nouveau->suivant=NULL;
nouveau->premier=NULL;
return (nouveau);
}

T_Magasin *creerMagasin(char *nom)
{
T_Magasin *nouveau = malloc(sizeof(T_Magasin));
strcpy(nouveau->nom, nom);
nouveau->premier=NULL;
return (nouveau);
}



int ajouterRayon(T_Magasin *magasin,T_Rayon *rayon)
{


    if (magasin->premier==NULL)
        {
            magasin->premier=rayon;
            rayon->suivant=NULL;
            return 1;   // on l'avait oublié
        }

   else if(strcmp(rayon->nom_rayon,magasin->premier->nom_rayon)<0)   // Ajout en tete de liste
        {
        rayon->suivant = magasin->premier;
        magasin->premier=rayon;
        return (1);
        }

   else if ((magasin->premier->suivant==NULL) && (strcmp(rayon->nom_rayon,magasin->premier->nom_rayon)!=0))
    {
        magasin->premier->suivant=rayon;
        rayon->suivant=NULL;
        return 1;
    }
    else if (strcmp(rayon->nom_rayon,magasin->premier->nom_rayon)>0)  //si pas ajout en tete de liste
    {   T_Rayon *temp=magasin->premier;
        T_Rayon *temp2=temp->suivant;
        if ((temp2->suivant == NULL) && (strcmp(rayon->nom_rayon,temp2->nom_rayon)<0) )
        {
            temp->suivant = rayon;
            rayon->suivant = temp2;
            return 1;
        }
        while ((strcmp(rayon->nom_rayon,temp2->nom_rayon)>0) && temp2->suivant!=NULL)   //tant que nom plus bas dans alphabet
            {
            temp=temp2;    //on se décalle dans la liste
            temp2 = temp2->suivant;
            }
        if  ((temp2->suivant != NULL) && strcmp(temp2->nom_rayon, rayon->nom_rayon)!=0)   // si on est pas à la fin et que le nom de temp2 différent de notre rayon
        {
            temp->suivant = rayon;
            rayon->suivant = temp2;  //on insere notre rayon
            return(1);
        }
        else if ((temp2->suivant == NULL) && (strcmp(rayon->nom_rayon,temp2->nom_rayon)<0) )
        {
            temp->suivant = rayon;
            rayon->suivant = temp2;
            return 1;
        }
        else if (temp2->suivant == NULL && strcmp(temp2->nom_rayon,rayon->nom_rayon)!=0)    //sinon si on est a la fin de la liste et que les noms sont différents, alors on insere notre rayon a la fin
            {
                rayon->suivant = NULL;
                temp2->suivant=rayon;  //rayon->suivant est initié a null de base!
                return(1);
            }
        }
    else return (0);
        }


T_Rayon *rechercheRayon (char *nom, T_Magasin *mag)
{
    T_Rayon *temp=mag->premier;
    while ((strcmp(nom, temp->nom_rayon)!=0) && (temp->suivant!=NULL))  //Tant que le nom demandé n'est pas trouvé on change de rayon
    {
        temp=temp->suivant;
    }
    if (temp==NULL) return NULL;
    else return temp;
}




int ajouterProduit(T_Rayon *rayon,T_Produit *produit)
{



    if (rayon->premier==NULL)   //Cas du rayon vide
    {
        rayon->premier=produit;
        rayon->premier->suivant=NULL;
        rayon->nombre_produits = rayon->nombre_produits + 1;
        return 1;
    }

    T_Produit *tmp = rayon ->premier;                           //Parcours de la liste pour voir si la marque est deja presente
    while ((tmp !=NULL) && (strcmp(tmp->marque, produit->marque)!=0))
    {
        tmp=tmp->suivant;
    }
    if (strcmp(tmp->marque, produit->marque)==0)
    {
        printf("erreur marque deja presente");
        return 0;
    }


    // Si on arrive ici, la marque n'est pas deja presente

    if (produit->prix <= rayon->premier->prix)   // Cas où produit qu'on ajoute est le moins cher
             {
                 produit->suivant = rayon->premier;
                 rayon->premier = produit;
                 rayon->nombre_produits = rayon->nombre_produits + 1;
                 return 1;
             }
    else if (rayon->premier->suivant == NULL)   //Cas si seulement un produit et qu'il est moins cher que celui qu'on ajoute
        {
            rayon->premier->suivant = produit;
            produit->suivant = NULL;
            rayon->nombre_produits = rayon->nombre_produits + 1;
            return 1;
        }

    else if (produit->prix > rayon->premier->prix)
        {
            T_Produit *temp = rayon->premier;
            T_Produit *temp2 = temp->suivant;
            if ((temp2->suivant == NULL) && (produit->prix <= temp2->prix))
            {
                temp->suivant = produit;
                produit->suivant = temp2;
                rayon->nombre_produits = rayon->nombre_produits + 1;
                return 1;
            }
            while ((produit->prix > temp2->prix) && (temp2->suivant != NULL))
            {
                temp = temp2;
                temp2 = temp2->suivant;
            }

            if ((temp2->suivant != NULL) && (produit->prix <= temp2->prix))
            {
                temp->suivant = produit;
                produit->suivant = temp2;
                rayon->nombre_produits = rayon->nombre_produits + 1;
                return 1;
            }
            else if ((temp2->suivant == NULL) && (produit->prix <= temp2->prix))
            {
                temp->suivant = produit;
                produit->suivant = temp2;
                rayon->nombre_produits = rayon->nombre_produits + 1;
                return 1;
            }
            else if ((temp2->suivant == NULL) && (produit->prix > temp2->prix))
            {
                produit->suivant = NULL;
                temp2->suivant = produit;
                rayon->nombre_produits = rayon->nombre_produits + 1;
                return 1;
            }
        }

}



void afficherMagasin(T_Magasin *magasin)  //Affiche les rayons du magasin
{
printf("Nom \t| Nombre de produits \n");
T_Rayon *temp = magasin->premier;

while (temp != NULL)            // on affiche les infos pour chaque rayon
    {
    printf("%s\t|",temp->nom_rayon);
    printf("%d \t\n", temp->nombre_produits);
    temp = temp->suivant;
    }
}



void afficherRayon(T_Rayon *rayon)   //Affiche les produits dans un rayon
{
printf("Marque \t\t| Prix \t\t| Qualite \t\t| Quantite en stock \n");
T_Produit *temp = rayon->premier;
while (temp != NULL){
    printf("%s\t\t|",temp->marque);
    printf("%f\t\t|",temp->prix);
    printf("%c\t\t|", temp->qualite);
    printf("%d\n", temp->quantite_en_stock);
    temp = temp->suivant;
}
}


int supprimerProduit(T_Rayon *rayon, char *marque_produit)
{
T_Produit *temp, *temp2;
if (rayon->premier==NULL) return 0; // si il n'y a rien à supprimer
else if (strcmp(rayon->premier->marque, marque_produit)==0)  //Supprimer le premier produit du rayon
{
  temp2 = rayon->premier;
  rayon->premier=rayon->premier->suivant;
  free(temp2);
  rayon->nombre_produits = rayon->nombre_produits - 1;
  return 1;
}
else
    {
        temp=rayon->premier;
        temp2=rayon->premier->suivant;
        while(temp2 !=NULL)  // on avance tant qu'on peut
        {
            if (strcmp(temp2->marque, marque_produit)==0)  // si on trouve la bonne marque on supprime et décrémente le nombre de produits dans le rayon
            {
                temp->suivant=temp2->suivant;
                free(temp2);
                rayon->nombre_produits = rayon->nombre_produits - 1;
                return 1;
            }
            temp=temp2;
            temp2=temp2->suivant;
        }

    }

}




T_Produit *supprimerProduitTete(T_Produit *premier)         //Supprime le produit en tête de liste
    {
        T_Produit *temp;
        if (premier !=NULL)
        {
            temp=premier;
            premier=premier->suivant;
            free(temp);
        }
        return premier;
    }




int supprimerRayon(T_Magasin *magasin, char *nom_rayon)         //Supprime le rayon et tous ses produits
{
T_Rayon *temp = magasin->premier;
T_Rayon *temp2 = temp->suivant;

if (magasin->premier==NULL) return 0; //Cas où il n'y a pas de rayons dans le magasin
else if (strcmp(magasin->premier->nom_rayon, nom_rayon)==0) //Si c'est le premier alors on le supprime
{
  temp2 = magasin->premier;
  magasin->premier=magasin->premier->suivant;
  while (temp2->premier!=NULL)
  {
      temp2->premier = supprimerProduitTete(temp2->premier); //on enleve le produit de tete tant qu'il y en a
      temp2->nombre_produits=temp2->nombre_produits - 1;
  }
  free(temp2);
  return 1;
}
else
    {
        temp=magasin->premier;
        temp2=magasin->premier->suivant;
        while(temp2 !=NULL)  //on avance dans les rayons
        {
            if (strcmp(temp2->nom_rayon, nom_rayon)==0)  //quand on a trouvé le bon on le supprime
            {
                temp->suivant=temp2->suivant;
                 while (temp2->premier!=NULL)
                    {
                        temp2->premier = supprimerProduitTete(temp2->premier);
                        temp2->nombre_produits=temp2->nombre_produits - 1;
                    }
                free(temp2);
                return 1;
            }
            temp=temp2;
            temp2=temp2->suivant;
        }

    }

}




void rechercheProduits(T_Magasin *magasin, float prix_min, float prix_max){
	T_Rayon *rayon=magasin->premier;
	T_Rayon *tete=(T_Rayon *)malloc(sizeof(T_Rayon));
	T_Rayon *tmp=(T_Rayon*)malloc(sizeof(T_Rayon));
	T_Rayon *tmp1=(T_Rayon*)malloc(sizeof(T_Rayon));
	T_Rayon *tmp2=(T_Rayon*)malloc(sizeof(T_Rayon));
	T_Produit *produit=rayon->premier;
	tete=NULL;
	while(rayon!=NULL){ // tant qu'on a des rayons dans le magasin
		produit=rayon->premier;
		while(produit!=NULL){ // tant qu'on a des produits dans le rayon
			if((produit->prix<=prix_max)&&(produit->prix>=prix_min)){ // si le produit correspond aux prix demandés
				tmp=creerRayon(rayon->nom_rayon); //on crée un rayon et on y ajoute le produit en tete
				tmp->premier=produit;
				if(tete==NULL)       
					tete=tmp;       
				else{
					tmp1=tete;   //sinon tmp1 devient tete
					while(tmp1!=NULL&&tmp1->premier->prix<produit->prix){
						tmp2=tmp1;
						tmp1=tmp1->suivant;
					}
					tmp->suivant=tmp1; //on relie tmp1 à tmp
					tmp2->suivant=tmp; //et tmp à tmp2
				}
			}
			produit=produit->suivant; //on passe au produit suivant
		}
		rayon=rayon->suivant; //on passe au rayon suivant
	}
    printf("| Marque \t\t | Prix \t | Qualite \t | Quantite en stock | Rayon \n");
	printf("------------------------------------------------------------------\n");
	tmp=tete;
	while(tmp!=NULL){  // On affiche les produits trouvés
		printf("| %-9s \t",tmp->premier->marque);
		printf("| %0.2f \t",tmp->premier->prix);
		printf("| %c \t\t",tmp->premier->qualite);
		printf("| %d \t\t\t\t ",tmp->premier->quantite_en_stock);
		printf("| %-5s \t \n",tmp->nom_rayon);
		tmp=tmp->suivant;
	}
}




/* T_Produit *triprix(T_Produit *p1, T_Produit *p2)
{
T_Produit *temp=malloc(sizeof(T_Produit));
   if (p1->prix <= p2->prix)
   {
       temp=p1;
       p1=p1->suivant;
    }
    else
        {
            temp=p2;
            p2=p2->suivant;
        }
return temp;
} */



/*void fusionnerRayons(T_Magasin *magasin)   //Fonction non terminé et remplacé par celle d'après, mais complexité aurait été meilleure.
{
char nom[20];
T_Rayon *tab[2] ;
int i;
for (i=0; i<2; i++)
{
    T_Rayon *temp=magasin->premier;          //On créer deux sites de stockage et on cherche les rayons à fusionner
   printf("quel nom de rayon ?\n");
    scanf("%s",nom);
    while (strcmp(temp->nom_rayon, nom)!=0)
    {
    temp=temp->suivant;
    }
    if (temp!=NULL)
        tab[i]=temp;           //On range les 2 rayons dans un tableau
}
T_Rayon *temp=malloc(sizeof(T_Rayon));
T_Produit *temp1; //=malloc(sizeof(T_Produit));
T_Produit *temp2; //=malloc(sizeof(T_Produit));
temp = magasin->premier ;
temp1=tab[0]->premier;
temp2=tab[1]->premier;
T_Produit *tmp=malloc(sizeof(T_Produit));
tmp=triprix(temp1,temp2);
temp->premier=tmp;
while (temp1!=NULL && temp2!=NULL)          //On compare les prix des deux rayons à chaque étape
{
    T_Produit *tmp1=malloc(sizeof(T_Produit));
    tmp1=triprix(temp1,temp2);
    tmp->suivant=tmp1;
    tmp = tmp->suivant;
}
while (temp1==NULL && temp2!=NULL)          //Si on a finit le premier rayon, mais qu'il reste des produits dans le deuxième
{
    tmp=temp2;
    temp2=temp2->suivant;
    tmp=tmp->suivant;
}
while (temp2==NULL && temp1!=NULL)          //Si on a finit le deuxième rayon, mais qu'il reste des produits dans le premier
{
    tmp=temp1;
    temp1=temp1->suivant;
    tmp=tmp->suivant;
}
return;
} */



void fusionnerRayonsBis(T_Magasin *magasin)
{
    char nom1[20];
    char nom2[20];
    printf("Quel rayon ?\n");
    scanf("%s", nom1);
    T_Rayon *rayon1=magasin->premier;
    while(strcmp(rayon1->nom_rayon, nom1)!=0)
    {
        rayon1=rayon1->suivant;       // On trouve le deuxième rayons en fonction des noms rentrées
    }
    printf("Quel rayon ?\n");
    scanf("%s", nom2);
    T_Rayon *rayon2 =magasin->premier;
    while(strcmp(rayon2->nom_rayon, nom2)!=0)
    {
        rayon2=rayon2->suivant;     // On trouve le deuxième rayons en fonction des noms rentrées
    }
    T_Produit *prod = rayon2->premier;
    while(prod != NULL)
    {
        ajouterProduit(rayon1, prod);  // On ajoute chaque produit du rayon 2 au rayon 1
        prod=prod->suivant;
    }
    supprimerRayon(magasin, rayon2); //on supprime le deuxieme rayon
}




void fusionnerRayonsTer(T_Magasin *magasin)
{
    char nom1[20];
    char nom2[20];
    printf("Quel rayon ?\n");
    scanf("%s", nom1);
    T_Rayon *rayon1=rechercheRayon(nom1, magasin);
    printf("Quel nom pour le second rayon ?\n");
    scanf("%s", nom2);
    T_Rayon *rayon2 =rechercheRayon(nom2, magasin);
    if (rayon1->nombre_produits > rayon2->nombre_produits)    //On ajoute les produits dans le rayon en contenant le plus, pour avoir le moins d'opérations possibles à faire
        {
            T_Produit *prod = rayon2->premier;
            while(prod != NULL)
                {
                    ajouterProduit(rayon1, prod);
                    prod=prod->suivant;
                }
            supprimerRayon(magasin,rayon2);             //On supprime le rayon qu'on a fusionné dans l'autre
        }
    else
        {
            T_Produit *prod = rayon1->premier;
            while(prod != NULL)
                {
                    ajouterProduit(rayon2, prod);
                    prod=prod->suivant;
                }
            supprimerRayon(magasin,rayon1);
        }
}

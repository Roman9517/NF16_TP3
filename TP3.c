#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include "TP3.h";

T_Produit *creerProduit(char *marque, float prix, char qualite, int quantite)
{
T_Produit *nouveau= malloc(sizeof(T_Produit));
strcpy(nouveau->marque,marque);
nouveau->prix=prix;
//if(qualite==A || qualite==B || qualite== C)
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

T_Magasin *creerMagasin(char *nom){
T_Magasin *nouveau = malloc(sizeof(T_Magasin));
strcpy(nouveau->nom, nom);
nouveau->premier=NULL;
return (nouveau);
}

int ajouterRayon(T_Magasin *magasin,T_Rayon *rayon) //OK
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
    {   T_Rayon *temp=magasin->premier;   //probleme si magasin est vide, on initialise sur NULL donc ca bug
        T_Rayon *temp2=temp->suivant;       // de meme ici
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


T_Rayon *rechercheRayon (char *nom, T_Magasin *mag)  //OK
{
    T_Rayon *temp=mag->premier;
    while ((strcmp(nom, temp->nom_rayon)!=0) && (temp->suivant!=NULL))
    {
        temp=temp->suivant;
    }
    if (temp==NULL) return NULL;
    else return temp;
}


int ajouterProduit(T_Rayon *rayon,T_Produit *produit) //A Changer ? On a pas parcouru tout le tableau pour savoir si la marque était déjà présente..
{



    if (rayon->premier==NULL)
    {
        rayon->premier=produit;
        rayon->premier->suivant=NULL;
        rayon->nombre_produits = rayon->nombre_produits + 1;
        return 1;
    }
    else if ((produit->prix <= rayon->premier->prix) && (strcmp(produit->marque,rayon->premier->marque) != 0))
             {
                 produit->suivant = rayon->premier;
                 rayon->premier = produit;
                 rayon->nombre_produits = rayon->nombre_produits + 1;
                 return 1;
             }
    else if (rayon->premier->suivant == NULL)
        {
            rayon->premier->suivant = produit;
            produit->suivant = NULL;
            rayon->nombre_produits = rayon->nombre_produits + 1;
            return 1;
        }
        else if ((produit->prix > rayon->premier->prix) && (strcmp(produit->marque,rayon->premier->marque) != 0))
        {
            T_Produit *temp = rayon->premier;
            T_Produit *temp2 = temp->suivant;
            if ((temp2->suivant == NULL) && (produit->prix <= temp2->prix) && (strcmp(produit->marque,temp2->marque) != 0))
            {
                temp->suivant = produit;
                produit->suivant = temp2;
                rayon->nombre_produits = rayon->nombre_produits + 1;
                return 1;
            }
            while ((produit->prix > temp2->prix) && (temp2->suivant != NULL) && (strcmp(produit->marque,temp2->marque) != 0))
            {
                temp = temp2;
                temp2 = temp2->suivant;
            }
            if ((strcmp(produit->marque,temp2->marque) == 0))
                    return 0;

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


void afficherMagasin(T_Magasin *magasin)  //OK, juste faire la mise en page
{
printf("Nom \t| Nombre de produits \n");
T_Rayon *temp = magasin->premier;

while (temp != NULL)
    {
    printf("%s\t|",temp->nom_rayon);
    printf("%d \t\n", temp->nombre_produits);
    temp = temp->suivant;
    }
}



void afficherRayon(T_Rayon *rayon)   //OK, juste faire la mise en page
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


int supprimerProduit(T_Rayon *rayon, char *marque_produit)    //OK
{
T_Produit *temp, *temp2;
if (rayon->premier==NULL) return 0;
else if (strcmp(rayon->premier->marque, marque_produit)==0)
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
        while(temp2 !=NULL)
        {
            if (strcmp(temp2->marque, marque_produit)==0)
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




T_Produit *supprimerProduitTete(T_Produit *premier)         //OK
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




int supprimerRayon(T_Magasin *magasin, char *nom_rayon)         //OK
{
T_Rayon *temp = magasin->premier;
T_Rayon *temp2 = temp->suivant;

if (magasin->premier==NULL) return 0;
else if (strcmp(magasin->premier->nom_rayon, nom_rayon)==0)
{
  temp2 = magasin->premier;
  magasin->premier=magasin->premier->suivant;
  while (temp2->premier!=NULL)
  {
      temp2->premier = supprimerProduitTete(temp2->premier);
      temp2->nombre_produits=temp2->nombre_produits - 1;
  }
  free(temp2);
  return 1;
}
else
    {
        temp=magasin->premier;
        temp2=magasin->premier->suivant;
        while(temp2 !=NULL)
        {
            if (strcmp(temp2->nom_rayon, nom_rayon)==0)
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




void RechercheProduits(T_Magasin *magasin, float prix_min, float prix_max)   //Bizarre, à chaque fois ça m'affiche que le premier produit, que son prix soit inférieur à prix_min ou non
{
printf("Marque \t| Prix\t| Qualite\t| Quantite en stock\t| Rayon | \n");
T_Rayon *temp=magasin->premier;
T_Produit *temp1;
while(temp!=NULL) //tant qu'on es pas à la fin de la liste des magasins
    {
    temp1=temp->premier;
    while  ((temp1->prix < prix_min) && (temp1!=NULL))  //Tant qu'on est à un prix trop bas mais en dessous de prix_max
        {
            temp1=temp1->suivant;   //on avance dans le rayon
        }
    while ((temp1!=NULL) && (temp1->prix < prix_max)&& (temp1->prix > prix_min)) //Tant qu'on est dans la fourchette pour ce rayon
        {
            printf("%s \t| %f\t| %c\t| %d\t| %s|\n", temp1->marque, temp1->prix, temp1->qualite, temp1->quantite_en_stock, temp->nom_rayon);
            temp1=temp1->suivant; //on passe au produit suivant
        }
   temp=temp->suivant;           //on passe au rayon suivant
    }
}



T_Produit *triprix(T_Produit *p1, T_Produit *p2)  //J'ai l'impression que p1->suivant et p2->suivant ne sont pas modifiés hors de la fonction
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
}



void fusionnerRayons(T_Magasin *magasin)    //Une fois que j'ai rentré les noms des deux rayons à fusionner, le programme reste bloqué et n'avance plus.
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
}



void fusionnerRayonsBis(T_Magasin *magasin)
{
    char nom1[20];
    char nom2[20];
    printf("quel rayon ?\n");
    scanf("%s", nom1);
    T_Rayon *rayon1=magasin->premier;
    while(strcmp(rayon1->nom_rayon, nom1)!=0)
    {
        rayon1=rayon1->suivant;
    }
    printf("quel rayon ?\n");
    scanf("%s", nom2);
    T_Rayon *rayon2 =magasin->premier;
    while(strcmp(rayon2->nom_rayon, nom2)!=0)
    {
        rayon2=rayon2->suivant;
    }
    T_Produit *prod = rayon2->premier;
    while(prod != NULL)
    {
        ajouterProduit(rayon1, prod);
        prod=prod->suivant;
    }
    supprimerRayon(rayon2);
}

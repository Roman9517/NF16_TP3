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

int ajouterRayon(T_Magasin *magasin,T_Rayon *rayon)
{
T_Rayon *temp=magasin->premier;   //probleme si magasin est vide, on initialise sur NULL donc ca bug
T_Rayon *temp2=temp->suivant;       // de meme ici

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


    else if (strcmp(rayon->nom_rayon,magasin->premier->nom_rayon)>0)  //si pas ajout en tete de liste
        {while ((strcmp(rayon->nom_rayon,temp->nom_rayon)>0) && temp2->suivant!=NULL)   //tant que nom plus bas dans alphabet
            {
            temp=temp2;    //on se décalle dans la liste
            temp2 = temp2->suivant;
            }
        if  ((temp2->suivant != NULL) || strcmp(temp2->nom_rayon, rayon->nom_rayon)!=0)   // si on est pas à la fin et que le nom de temp2 différent de notre rayon
        {
            temp->suivant = rayon;
            rayon->suivant = temp2;  //on insere notre rayon
            return(1);
        }
        else if (temp2->suivant == NULL && strcmp(temp2->nom_rayon,rayon->nom_rayon)!=0)    //sinon si on est a la fin de la liste et que les noms sont différents, alors on insere notre rayon a la fin
            {
                temp2->suivant=rayon;  //rayon->suivant est initié a null de base!
                return(1);
            }
        }
    else return (0);
        }



int ajouterProduit(T_Rayon *rayon,T_Produit *produit)
{



    if (rayon->premier==NULL)
    {
        rayon->premier=produit;
        rayon->premier->suivant=NULL;
    }

    else
    {
        T_Produit *temp=rayon->premier;
        T_Produit *temp2=temp;
    do {
        temp=temp2;  //on se décalle dans la liste
        temp2 = temp2->suivant;
        if (/*(strcmp(temp->marque, produit->marque)==0) ||*/ (strcmp(temp2->marque, produit->marque)==0))
        {
            return 0; //on s'arrete ici si la marque existe déjà
        }
       } while (temp2->suivant != NULL);
    //arrivé ici, nous sommes sur de ne pas avoir 2 fois la même marque


    temp=rayon->premier; // on reinitialise nos variables
    temp2=temp;

    if(produit->prix < rayon->premier->prix)  //on ajoute en tete         !!! Ce "if" n'a pas de "else" donc on peut ne rien retourner !
        {
            produit->suivant = rayon->premier;
            rayon->premier = produit;
            return 1;
        }

        else
        {
            while (produit->prix > temp->prix)
                {
                    temp=temp2;    //on se décalle dans la liste
                    temp2 = temp2->suivant;
                }
           if (temp2->suivant != NULL)
                {
                    temp->suivant = produit;
                    produit->suivant=temp2;
                    return 1;
                }
            else
            {
                temp2->suivant = produit;
                produit->suivant=NULL;
                return 1;
            }
        }
    }


}


void afficherMagasin(T_Magasin *magasin)
{
printf("Nom \t| Nombre de produits \n");
T_Magasin *temp = magasin;

while (temp->premier != NULL)
    {
    printf("%s\t|",temp->premier->nom_rayon);
    printf("%d\n", temp->premier->nombre_produits);
    temp->premier = temp->premier->suivant;
    }
}



void afficherRayon(T_Rayon *rayon)
{
printf("Marque \t| Prix \t| Qualite \t| Quantite en stock \n");
T_Rayon *temp = rayon->premier;   //a quoi ca sert ? pourquoi on pointe sur le premier produit alors que Temp est un pointeur sur rayon ?

while (temp->premier != NULL){
    printf("%s\t|",temp->premier->marque);
    printf("%f\t|",temp->premier->prix);
    printf("%c\t|", temp->premier->qualite);
    printf("%d\n", temp->premier->quantite_en_stock);
    temp->premier = temp->premier->suivant;
}
}


int supprimerProduit(T_Rayon *rayon, char *marque_produit)
{

if (rayon->premier==NULL) return 0;    // pareil regarder les "if" et "else" car on risque de rien retourner
else if(rayon->premier->suivant==NULL)
{
        free(rayon->premier);
        rayon->premier=NULL;
}

else
{
    T_Produit *temp = rayon->premier;
    T_Produit *temp2 = temp->suivant;


if (strcmp(temp->marque, marque_produit)==0)  //supprime la tete de liste
    {
        rayon->premier = temp2;
        free(temp);
        return 1;
    }

else {
        while((strcmp(temp2->marque,marque_produit)>0) && (temp2 != NULL))   //Tant que on a pas le même nom de marque et qu'on est pas à la fin de la liste
            {
                temp=temp2;
                temp2= temp2->suivant;      //On avance
            }

        if (strcmp(temp2->marque, marque_produit)==0)       //Si on a trouvé la marque, on supprime temp2 (ça marche même si temp2 est la queue de liste
            {
              temp->suivant=temp2->suivant;
              free(temp2);
              return 1;
            }

        else if ((temp2->suivant==NULL)  && (strcmp(temp2->marque, marque_produit)!=0))   //Si on a pas le nom de la marque dans la liste
            {
                return 0;
            }
    }

}

}



int supprimerRayon(T_Magasin *magasin, char *nom_rayon)
{
if (magasin->premier==NULL) return 0;
else if (magasin->premier->suivant==NULL)    // meme probleme
{
    free(magasin->premier);
    magasin->premier==NULL; // == ou juste = ?
}
else
{
    T_Rayon *temp = magasin->premier;
T_Rayon *temp2 = temp->suivant;

if (strcmp(temp->nom_rayon, nom_rayon)==0)  //supprime la tete de liste
    {
        magasin->premier = temp2;
        free(temp);
        return 1;
    }

else {
        while((strcmp(temp2->nom_rayon,nom_rayon)>0) && (temp2->suivant != NULL))   //Tant que on a pas le même nom de rayon et qu'on est pas à la fin de la liste
            {
                temp=temp2;
                temp2= temp2->suivant;      //On avance
                temp->suivant=temp2;
            }

        if (strcmp(temp2->nom_rayon, nom_rayon)==0)       //Si on a trouvé le rayon, on supprime temp2 (ça marche même si temp2 est la queue de liste)
            {
              temp->suivant=temp2->suivant;
              free(temp2);
              return 1;
            }

        else if ((temp2->suivant==NULL)  && (strcmp(temp2->nom_rayon, nom_rayon)!=0))   //Si on a pas le nom du rayon dans la liste
            {
                return 0;
            }
    }

}

}


void RechercheProduits(T_Magasin *magasin, float prix_min, float prix_max)
{
printf("Marque \t| Prix\t| Qualite\t| Quantite en stock\t| Rayon | \n");
T_Rayon *temp=magasin->premier;
T_Produit *temp1=temp->premier;
while(temp!=NULL) //tant qu'on es pas à la fin de la liste des magasins
    {
    while ((temp1->prix < prix_max) && (temp1->prix < prix_min))  //Tant qu'on est à un prix trop bas mais en dessous de prix_max
        {
            temp1=temp1->suivant;   //on avance dans le rayon
        }
    while ((temp1!=NULL) && (temp1->prix < prix_max)) //Tant qu'on est dans la fourchette pour ce rayon
        {
            printf("%s \t| %f\t| %c\t| %d\t| %s|\n", temp1->marque, temp1->prix, temp1->qualite, temp1->quantite_en_stock, temp->nom_rayon);
            temp1=temp1->suivant; //on passe au produit suivant
        }
   temp=temp->suivant;           //on passe au rayon suivant
   temp1=temp->premier;          //on reinitialise temp1 pour être au debut du rayon
    }
}

//faire si magasin->premier->premier->prix > prix_max alors sortir, Omega(1)
//J'ai l'impression que c'est juste quand même ce que j'ai fait

T_Produit *triprix(T_Produit *p1, T_Produit *p2)
{
T_Produit *temp=malloc(sizeof(T_Produit));

{
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
}
return temp;
}



void fusionnerRayons(T_Magasin *magasin)
{
char nom[20];
T_Rayon tab[2] ;
int i;
for (i=0; i<2; i++)
{
    T_Rayon *temp=magasin->premier;          //On créer deux sites de stockage et on cherche les rayons à fusionner
   printf("quel nom de rayon ?");
    scanf("%s",nom);
    while (strcmp(temp->nom_rayon, nom)!=0)
    {
    temp=temp->suivant;
    }
    if (temp!=NULL)
        tab[i]=*temp;           //On range les 2 rayons dans un tableau
}

T_Rayon *temp=malloc(sizeof(T_Rayon));
T_Produit *temp1=malloc(sizeof(T_Produit));
T_Produit *temp2=malloc(sizeof(T_Produit));
temp = magasin->premier ;
temp1=tab[0].premier;
temp2=tab[1].premier;

while (temp1!=NULL && temp2!=NULL)          //On compare les prix des deux rayons à chaque étape
{
    temp->premier=triprix(temp1,temp2);
    temp->premier=temp->premier->suivant;
}

while (temp1==NULL && temp2!=NULL)          //Si on a finit le premier rayon, mais qu'il reste des produits dans le deuxième
{
    temp->premier=temp2;
    temp2=temp2->suivant;
    temp->premier=temp->premier->suivant;
}

while (temp2==NULL && temp1!=NULL)          //Si on a finit le deuxième rayon, mais qu'il reste des produits dans le premier
{
    temp->premier=temp1;
    temp1=temp1->suivant;
    temp->premier=temp->premier->suivant;
}
}




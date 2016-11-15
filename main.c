#include <stdio.h>
#include <stdlib.h>
#include "TP3.h";
#include<string.h>



void main()
{
    printf("Hello world!\n");
   // creerProduit("BBC", 5.25, 'B', 5); // passer caractere unique entre '' et pas entre ""  !!!!!
   int i;
   int p;
   float min, max;
   char *marque;
   char nomM[20];
   char nom[20];
   T_Magasin *mag=creerMagasin("mag");
   T_Rayon *ray=creerRayon("ray");
   T_Produit *prod=creerProduit("prod", 1.5, 'B', 5 );
   T_Magasin *nouveaum;
    while(i!=9)
        {
            printf("Que souhaitez vous faire ? : \n1=Creer un magasin \n2=Ajouter un rayon au magasin \n3=Ajouter un produit dans un rayon \n4=Afficher les rayons du magasins \n5=Afficher les produits d'un rayon\n6=Supprimer un produit \n7=Supprimer un rayon \n8=Rechercher un produit par prix \n9=Quitter\n");
            scanf(" %d", &i);
            switch (i)
            {
            case 1 :  printf("Saisir le nom du magasin : \n");
                        scanf("%s", nomM);
                        nouveaum=creerMagasin(nomM);
                        break;

            case 2 :   ajouterRayon(mag,ray);
                        break;


            case 3 :  do { p=ajouterProduit(ray, prod); }while (p!=1);
                        break;


            case 4 : afficherMagasin(mag);
                       break;


            case 5 : afficherRayon(ray);
                       break;


            case 6 : printf("Saisir la marque du produit a supprimer\n");
                       scanf("%s", marque);
                       do {p=supprimerProduit(ray, marque);} while (p!=1);
                       break;


            case 7 :  printf("Quel rayon supprimer?\n");
                        scanf("%s",nom);
                        do {p=supprimerRayon(mag, nom);} while (p!=1);
                        break;


            case 8 :  printf("Saisir le prix minimum\n");
                       scanf("%f", &min);
                       printf("Saisir le prix maximum\n");
                       scanf("%f", &max);
                       RechercheProduits(mag, min, max);
                       break;


            case 9 :   printf("Au revoir\n");
                        break;


            default :  printf("Erreur : saisir un choix entre 1 et 9");
                        break;


            }
        }

}



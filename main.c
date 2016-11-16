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
   float p_prix;
   char *marque;
   char nomM[20];
   char nom[20];
   char nomR[20];
   char p_marque[20];
   char p_qualite;
   int p_quantite;


   T_Produit *prod=creerProduit("prod", 1.5, 'B', 5 );
   T_Magasin *mag =creerMagasin("mag");
    while(i!=9)
        {
            printf("Que souhaitez vous faire ? : \n1=Creer un magasin \n2=Ajouter un rayon au magasin \n3=Ajouter un produit dans un rayon \n4=Afficher les rayons du magasins \n5=Afficher les produits d'un rayon\n6=Supprimer un produit \n7=Supprimer un rayon \n8=Rechercher un produit par prix \n9=Quitter\n");
            scanf(" %d", &i);
            switch (i)
            {
            case 1 :  printf("Saisir le nom du magasin : \n");
                        scanf("%s", nomM);
                        strcpy(mag->nom, nomM);
                        break;

            case 2 :   printf("Saisir le nom du rayon : \n");
                        scanf("%s", nomR);
                        T_Rayon *ray=creerRayon(nomR);
                       ajouterRayon(mag,ray);
                       printf("\n");
                        break;


            case 3 :  //do { p=ajouterProduit(ray, prod); }while (p!=1);
                        printf("Saisir le nom du rayon ou on ajoute le produit: \n");
                        scanf("%s", nomR);
                        printf("Saisir la marque du produit: \n");
                        scanf("%s", p_marque);
                        printf("Saisir le prix du produit \n");
                        scanf("%f", &p_prix);
                        printf("Saisir la qualite du produit: \n");
                        while ((p_qualite=getchar()) != '\n' && p_qualite != EOF);
                        scanf("%c", &p_qualite);
                        printf("Saisir la quantite du produit: \n");
                        scanf("%d",&p_quantite);
                        ajouterProduit(rechercheRayon(nomR, mag), creerProduit(p_marque, p_prix, p_qualite, p_quantite));
                        break;


            case 4 : afficherMagasin(mag);
                       break;


            case 5 :    printf("Saisir le nom du rayon a afficher: \n");
                        scanf("%s", nomR);
                       afficherRayon(rechercheRayon(nomR, mag));
                       break;


            case 6 :   printf("Saisir le nom du rayon ou se situe le produit: \n");
                        scanf("%s", nomR);
                        afficherRayon(rechercheRayon(nomR, mag));
                       printf("Saisir la marque du produit a supprimer\n");
                       scanf("%s", p_marque);
                       supprimerProduit(rechercheRayon(nomR, mag), p_marque);
                       afficherRayon(rechercheRayon(nomR, mag));
                       break;


            case 7 :  printf("Quel rayon supprimer?\n");
                        scanf("%s",nomR);
                        afficherMagasin(mag);
                        supprimerRayon(mag,nomR);
                        afficherMagasin(mag);
                        break;


            case 8 :  printf("Saisir le prix minimum\n");           //Il ne reste plus que ça et le bonus :D
                       scanf("%f", &min);
                       printf("Saisir le prix maximum\n");
                       scanf("%f", &max);
                       RechercheProduits(mag, min, max);
                       break;


            case 9 :   printf("Au revoir\n");
                        break;
                    
                    
           case 10 : fusionnerRayons(mag);
                      break;


            default :  printf("Erreur : saisir un choix entre 1 et 9");
                        break;


            }
        }

}




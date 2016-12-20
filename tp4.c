#include <stdio.h>
#include <stdlib.h>
#include "tp4bisbis.h"
#include<time.h>
#include <string.h>



Benevole *nouveauBen(char *nom, char *prenom, int CIN, char sexe, int annee)  //OK
{
    Benevole *ben=malloc(sizeof(Benevole));
    strcpy(ben->nom, nom);
    strcpy(ben->prenom, prenom);
    ben->CID=CIN;
    ben->sexe=sexe;
    ben->annee=annee;
    ben->suivant=NULL;
    return ben;
}


Tranche *nouvelleTranche(int borneSup)   //OK
{
    Tranche *tr=malloc(sizeof(Tranche));
    tr->BorneSup=borneSup;
    tr->filsD=NULL;
    tr->filsG=NULL;
    tr->pere=NULL;
    tr->liste=nouvelleListe();
    return tr;
}


ListBenevoles *nouvelleListe()   //OK
{
    ListBenevoles *list=malloc(sizeof(ListBenevoles));
    list->nb=0;
    list->premier=NULL;
    return list;
}



Tranche *ajoutTranche(Tranche *racine, int borneSup)
{
    if(borneSup%5 ==0){  // on veut une borne sup tous les 5 ans (dans l'exemple en tout cas)
    if (racine==NULL)
    {
        racine=nouvelleTranche(borneSup);
        return racine;
    }
    else
    {
        Tranche *tr=nouvelleTranche(borneSup);
        Tranche *tmp=racine;
        Tranche *tmp1;
        if((racine->filsD==NULL) && (racine->filsG==NULL))  //un seul element : la racine
        {
            if(borneSup > racine->BorneSup)
            {
                racine->filsD=tr;
                tr->pere=racine;
            }
            else if(borneSup < racine->BorneSup)
            {
                racine->filsG=tr;
                tr->pere=racine;
            }
            else if (borneSup == racine->BorneSup) free(tr); //si la tranche existe déjà, on libère l'espace memoire alloué inutilement à tr
            return racine; //si on a pas ajouté car la borne sup existe deja on renvoie le meme arbre
        }
        while((tmp!=NULL) && (tmp->BorneSup != borneSup))   //
        {
            if (tmp->BorneSup > tr->BorneSup)
            {
                tmp1=tmp;
                tmp=tmp->filsG;
            }
            else if (tmp->BorneSup < tr->BorneSup)
            {
                tmp1=tmp;
                tmp=tmp->filsD;
            }
            else free(tr); //si la tranche existe deja
        }
        if (tmp==NULL)   //Si le noeud n'existe pas déjà
        {
            if(tmp1->BorneSup > borneSup) tmp1->filsG=tr;
            else if (tmp1->BorneSup < borneSup) tmp1->filsD=tr;
            tr->pere=tmp1;
            return racine;
        }
        else //la tranche existe déjà
            return racine;
}
    } return racine;
}


int anneeActuelle()
{
    time_t secondes;
    struct tm instant;
    time(&secondes);
    instant = *localtime(&secondes);
    return instant.tm_year + 1900;
}


int attribuerBorne(int annee)  //OK
{
    int age = anneeActuelle()-annee;
    int b=0;
    while(b <age)
        b=b+4;
    return b;
}


ListBenevoles *insererlist(Tranche *tr, Benevole *bene)
{
    if (tr->liste->nb==0)
    {
        tr->liste->premier=bene;
        tr->liste->nb=1;
        printf("nb=0\n");
        return bene;                            //OK jusque ici
    }
    else if (tr->liste->premier->annee >= bene->annee)  //ajout en tete
    {
        bene->suivant=tr->liste->premier;
        tr->liste->nb++;
        tr->liste->premier=bene;
        printf("entete\n");
        return bene;
    }
    else
    {
        Benevole *tmp=tr->liste->premier;
        Benevole *tmp1=tr->liste->premier;
        while((tmp->annee < bene->annee)  && tmp!=NULL)   //On se deplace
        {
            tmp1=tmp;
            tmp=tmp->suivant;
        }
        if (tmp==NULL) //ajout en queue
        {
            tmp1->suivant=bene;
            tr->liste->nb++;
            printf("queue\n");
            return tr->liste->premier;
        }
        else if(bene->CID!=tmp->CID || (strcmp(bene->nom, tmp->nom)!=0) || (strcmp(bene->prenom, tmp->prenom)!=0) || bene->sexe!=tmp->sexe || bene->annee!=tmp->annee)
        {
            bene->suivant=tmp;
            tmp1->suivant=bene;
            tr->liste->nb++;
            printf("autre\n");
            return tr->liste->premier;
        }
        else //on a pas ajouté mais on renvoie la liste telle quelle
            return tr->liste->premier;
    }
}


Benevole *insererBen(Tranche *racine, Benevole *benevole)
{
    int bs;
    Tranche *tr; //=malloc(sizeof(Tranche));
    //tr=NULL;
    bs=attribuerBorne(benevole->annee);
    if (racine==NULL)
    {
        racine = nouvelleTranche(bs);
        printf("ok nouvelle racine\n");
        racine->liste=insererlist(racine, benevole);
        printf("ok nouvelle liste racine\n");
        afficherArbre(racine);
        return racine->liste->premier;              //OK jusque ici
    }
    else
    {
        racine = ajoutTranche(racine,bs); //Si la tranche existe déjà on ne la rajoute pas, c'est défini dans la fonction
        printf("ok ajout tranche2\n");  //probleme car la tranche n'est pas ajoutée quand on ne l'a pas mise direct dans le 2
        afficherArbre(racine);
        printf("ok\n");
        tr=chercherTranche(racine, bs);
        printf("ok chercher tranche\n");
        tr->liste = insererlist(tr, benevole);
        printf("ok insere liste 2\n");
        return tr->liste->premier;
    }
}


Benevole *chercherBen(Tranche *racine,int CIN, int *annee)
{
    Tranche *tmp=racine;
    int b=attribuerBorne(*annee);
    while (tmp->BorneSup != b && tmp!=NULL)
    {
        if (tmp->BorneSup > b)
            tmp=tmp->filsG;
        else tmp=tmp->filsD;
    }
    if (tmp->BorneSup==b) //on a bien trouvé le bon noeud
    {
        Benevole *tmp1=tmp->liste->premier;
        while(tmp1!=NULL && tmp1->annee < *annee)
            tmp1=tmp1->suivant;
        if(tmp1->annee == *annee && tmp1!=NULL)  //pas en queue de liste, et on est à la bonne année
        {
            while(tmp1->annee== *annee && tmp1->CID!=CIN)  //on avance tant qu'on a la bonne année mais pas le bon CIN
            {
                tmp1=tmp1->suivant;
            }
            if (tmp1->CID==CIN && tmp1->annee== *annee)  //Si on a trouvé le benevole
                return tmp1;
        }
        return NULL;  //si on a pas trouvé le benevole
    }

}



Tranche *chercherTranche(Tranche *racine, int Bornesup )  //OK
{
    Tranche *tmp=racine;
    while ((tmp->BorneSup != Bornesup) && tmp!=NULL)
    {
        if (tmp->BorneSup > Bornesup)
            tmp=tmp->filsG;
        else tmp=tmp->filsD;
    }
    if(tmp->BorneSup!=NULL)
            return tmp; //probleme à cette ligne...
    else return NULL;
}



int supprimerBen(Tranche *racine, int CIN, int annee)
{
    Benevole *ben=chercherBen(racine, CIN, &annee);
    if(ben !=NULL)
    {
        int b=attribuerBorne(ben->annee);
        Tranche *tr=chercherTranche(racine,b);
        if(tr!=NULL)  //si la tranche existe bien
        {
                free(ben);
                tr->liste->nb--;
                if(tr->liste->nb==0) //c'était le seul élément de la liste et du noeud
                    free(tr);
                return 0;
        }
    }
    return 1;
}



int supprimerTranche(Tranche *racine, int borneSup)   //probleme : remplace par une valeur quelconque, il faudrait faire une liste chainee de tranches pour pouvoir vraiment supprimer la tranche de la liste chainee
{
    int c=1;
    int borne=borneSup;
    Tranche *tranche=racine;
    while(c==1){
    Tranche *tr=chercherTranche(racine, borne);  //toujours un probleme dans chercherTranche()
    if(tr!=NULL)
    {
        while(tr->liste->nb != 0)
        {
            Benevole *tmp=tr->liste->premier;   //on supprime en tete
            free(tmp);
            tr->liste->nb--;
        }
        if (tr->filsG==NULL)
        {
            Tranche *sauv=tr;
            tr->filsG->pere=tr;
            tr=tr->filsG;
            free(tr);
            c=0;
        }
        else if(tr->filsD==NULL)
        {
            Tranche *sauv=tr->filsD;
            tr->filsD->pere=tr;
            tr=tr->filsD;
            free(tr);
            c=0;
        }
        else
        {
            Tranche *courant=tr->filsD;
            while(courant->filsG!=NULL) courant=courant->filsG;  //on prend le min du sous arbre drooit
            tr->BorneSup = courant->BorneSup;
            borne=tr->BorneSup;
            tranche=tr->filsD;
        }
        return 0;
    }
    return 1;
}
}





ListBenevoles *BenDhonneur(Tranche *racine)
{
    if (racine==NULL) return NULL;
    else
    {
        Tranche *tmp=racine;
        while(tmp->filsD != NULL)
            tmp=tmp->filsD;
        Benevole *tmp1=tmp->liste->premier;
        Benevole *tmp2=tmp->liste->premier;
        if (tmp->liste->nb!=0)   //si la liste est non vide
        {
            while(tmp1->suivant!=NULL)
            {
                while(tmp1->suivant->annee != tmp1->annee)
                    tmp1=tmp1->suivant;
                tmp2=tmp1;
                while(tmp1->suivant==tmp1 && tmp1->suivant!=NULL)
                    tmp1=tmp1->suivant;
            }
            //on a tmp1 sur le dernier element de la liste, et tmp2 sur le premier element de la liste ayant la meme annee de naissance
            ListBenevoles *honneur=nouvelleListe();
            Benevole *tmp3;
            while(tmp2!=tmp1->suivant) //on insere de tmp2 à tmp1 inclus
            {
                if(honneur->nb==0) //si liste vide
                {
                    honneur->premier=tmp2;
                    honneur->nb=1;
                    tmp3=honneur->premier;
                }
                else
                {
                    tmp3->suivant=tmp2;   //on ajoute tmp2 à la suite de la nouvelle liste(dejà triée)
                    honneur->nb++;
                }
                tmp2=tmp2->suivant;
            }
            return honneur;
        }
        else return NULL; //si liste vide

    }
}


int actualiser(Tranche *racine)
{
    int nb=0;
    int b=21;
    int max=bornemax(racine);
    Tranche *tr;
    Benevole *tmp, *tmp1;
    while(b<=max )
    {
        if(tr=chercherTranche(racine, b)!=NULL)
        {
            tmp=tr->liste->premier;
            while(tmp!=NULL && tmp->annee <=tr->BorneSup)
            {
                tmp=tmp->suivant;
            }
            while (tmp->annee > tr->BorneSup)
            {
                tmp1=tmp;
                tmp=tmp->suivant;
                insererBen(racine, tmp1);   //On insere a la bonne borne sup
                free(tmp1); //on supprime de la liste actuelle
                nb++;
            }
        }
        b+=4;
    }
    return nb;
}





int totalBenTranche(Tranche *racine, int borneSup)
{
    int nb=0;
    Tranche *tr=chercherTranche(racine, borneSup);
    Benevole *tmp=tr->liste->premier;
    while(tmp!=NULL)
    {
        nb++;
        tmp=tmp->suivant;
    }
    return nb;
}



int bornemax(Tranche *racine)
{
    Tranche *tmp=racine;
    while(tmp->filsD != NULL)
            tmp=tmp->filsD;
    return tmp->BorneSup;
}



int totalBen(Tranche *racine)  //Le plus optimum ?
{
    int borneSup=20;
    int tot;
    int bmax = bornemax(racine);
    do
    {
        tot += totalBenTranche(racine, borneSup);
        borneSup = borneSup + 4;
    } while (borneSup <= bmax);
    return tot;
}



float pourcentageTranche(Tranche *racine, int borneSup)
{
    float res=0;
    if(totalBen(racine)!=0)
        res=(((float)totalBenTranche(racine, borneSup)) / (totalBen(racine)));
    return res*100;
}

void afficherBen(Benevole *ben)
{
    while(ben!=NULL)
    {
        printf("%20s | %20s | %6c | %20d | %6d \n", ben->nom, ben->prenom, ben->sexe, ben->CID, ben->annee);
        ben=ben->suivant;
    }
}

void afficherTranche(Tranche *racine, int borneSup)
{
    Tranche *tr=chercherTranche(racine, borneSup);
    Benevole *tmp=tr->liste->premier;
    if(tmp==NULL) printf("liste vide \n");
    else
    {
        printf("       nom         |        prenom       | sexe |        CID          | annee \n");
        afficherBen(tmp);
    }
}


// Ensemble des fonctions pour creer une liste chainee de Tranches et les afficher


/*Elem *creerel(int borneSup)
{
    Elem *e=malloc(sizeof(Elem));
    e->val=BorneSup;
    e->suivant=NULL;
    return e;
}*/




/*ListeTranche *ajouterElem(ListeTranche *l, Elem *elem)
{
    if (l->premier==NULL)
    {
        l->premier=elem;
        l->nb=1;
        return l;
    }
    else
    {
        Elem *tmp=l->premier;
        Elem *tmp1;
        while((tmp!=NULL) && (tmp->val < elem->val))
        {
            tmp1=tmp;
            tmp=tmp->suivant;
        }
        if(tmp==NULL)  //ajout en queue
        {
            tmp1->suivant=elem;
            l->nb++;
            return l;
        }
        else //on a trouve la place
        {
            tmp1->suivant=elem;
            elem->suivant=tmp;
            l->nb++;
            return l;
        }
    }
}*/




/*void AfficherArbreListe(Tranche *racine)
{
    ListeTranche *l=creerListeTranche();
    if (l->premier==NULL) printf("aucune tranche\n");
    else
    {
        printf("%d ", l->premier->val);
        Elem *tmp=l->premier->suivant;
        while(tmp!=NULL)
        {
            printf("-> %d ", tmp->val);
            tmp=tmp->suivant;
        }
    }
}*/

/*void afficherArbre(Tranche *racine)   //on fait un parcours_infixe  Ne marche pas encore
{
    if(racine!=NULL)
    {
        Tranche *node=racine;
        ListeTranche *list=creerListeTranche();
        list->premier=racine;
        Benevole *tmp;
        node=node->flisG;
        while(list->nb!=0)
        {
            while(node!=NULL)
            {
                tmp=node->flisG;
                tmp->suivant=list->premier;  //ajout en tete (on empile)
                list->premier=tmp;
                node=node->flisG;
            }
            Tranche *tmp1=list->premier;
            list->premier=list->premier->suivant;
            afficherTranche(racine, tmp1->BorneSup);
            node=tmp1->filsD;
            if((list->nb == 0) && node !=NULL)
               {
                   tmp=node;
                   tmp->suivant=list->premier;
                   list->premier=tmp;
                   node=node->flisG;
               }
        }
    }
}*/


/*void afficherArbre(Tranche *racine)  //nouvelle tentative, pas fini
{
    if(racine!=NULL)
    {
        Tranche *courant=racine;
        while(courant->filsD)
        while(courant->filsG!=NULL)
        {
            courant=courant->filsG;
        }
        afficherTranche(racine, courant->BorneSup);   //on affiche le fils gauche
        courant=courant->pere;
        supprimerTranche(racine, courant->filsG->BorneSup); //on le supprime
        if(courant->filsD==NULL)
        {
            afficherTranche(racine, courant->BorneSup);
            courant=courant->pere;
            supprimerTranche(racine, courant->filsG);
        }
        else
        {
            afficherTranche(racine, courant->BorneSup);
            courant=courant->filsD;
        }
    }
}*/

void afficherArbre(Tranche *racine)
{
    if (racine != NULL)
    {
        afficherArbre(racine->filsD);
        if (racine->filsD != NULL)
        {
            printf(",");
        }
        printf("%d ", racine->BorneSup);
        if (racine->filsG !=NULL)
        {
            printf(",");
        }
        afficherArbre(racine->filsG);
    }
}

void detruire_Arbre(Tranche* racine)
{
    if (racine != NULL)
    {
    detruire_Arbre(racine->filsG);
    detruire_Arbre(racine->filsD);
    free(racine);  // les éléments de l'arbre sont mis à des valeurs aléatoires
    }
}



#include <stdio.h>
#include <stdlib.h>
#include "tp4.h"
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



Tranche *ajoutTranche(Tranche *racine, int borneSup)  //OK, c'est plus propre !
{
    if(borneSup%5 ==0) {
    if (racine==NULL)
    {
        racine=nouvelleTranche(borneSup);
        return racine;
    }
    else
    {
        if (borneSup < racine->BorneSup)
        {
            racine->filsG = ajoutTranche(racine->filsG, borneSup);
        }
        else if (borneSup > racine->BorneSup)
        {
            racine->filsD = ajoutTranche(racine->filsD, borneSup);
        }
        return racine;
    }

} return racine; //On ne change rien puisque la borne sup n'est pas modulo 5
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
        b=b+5;
    return b;
}


ListBenevoles *insererlist(Tranche *tr, Benevole *bene)  //OK
{
    if (tr->liste->nb==0)
    {
        tr->liste->premier=bene;
        tr->liste->nb=1;
        printf("nb=0\n");
        return bene;                            //OK jusque ici
    }
    else if (tr->liste->premier->annee <= bene->annee)  //ajout en tete
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
        if (tmp1->suivant==NULL) //ajout en queue
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


Benevole *insererBen(Tranche *racine, Benevole *benevole)  //ok
{
    int bs;
    Tranche *tr; //=malloc(sizeof(Tranche));
    //tr=NULL;
    bs=attribuerBorne(benevole->annee); //borne sup
    racine = ajoutTranche(racine, bs); //tranche ajouté correctement si racine a déjà une tranche.
    tr = chercherTranche(racine, bs);  // on est sur le bon noeud
    insererlist(tr, benevole);
}




Benevole *chercherBen(Tranche *racine,int CIN, int *annee)  //OK
{
    Tranche *tmp=racine;
    int b=attribuerBorne(annee);
    while (tmp->BorneSup != b && tmp!=NULL)
    {
        if (tmp->BorneSup > b)
            tmp=tmp->filsG;
        else tmp=tmp->filsD;
    }
    if (tmp->BorneSup==b) //on a bien trouvé le bon noeud
    {
        Benevole *tmp1=tmp->liste->premier;
        while(tmp1!=NULL && tmp1->annee < annee)
            tmp1=tmp1->suivant;
        if(tmp1->annee == annee && tmp1!=NULL)  //pas en queue de liste, et on est à la bonne année
        {
            while(tmp1->annee== annee && tmp1->CID!=CIN)  //on avance tant qu'on a la bonne année mais pas le bon CIN
            {
                tmp1=tmp1->suivant;
            }
            if (tmp1->CID==CIN && tmp1->annee== annee)  //Si on a trouvé le benevole
                return tmp1;
        }
        return NULL;  //si on a pas trouvé le benevole
    }

}



Tranche *chercherTranche(Tranche *racine, int Bornesup )  //OK
{
    if (racine == NULL)
    {
        return NULL;
    }
    else if (Bornesup == racine->BorneSup)
    {
        return racine;
    }
    else if (Bornesup < racine->BorneSup)
    {
        return chercherTranche(racine->filsG, Bornesup);
    }
    else
    {
        return chercherTranche(racine->filsD, Bornesup);
    }
        return NULL;
}



int supprimerBen(Tranche *racine, int CIN, int annee)  //OK, il manque juste la suppression de la tranche
{
    int b=attribuerBorne(annee);
    Tranche *tr=chercherTranche(racine,b);
    if(tr!=NULL)
    {
        Benevole *courant=tr->liste->premier;
        Benevole *prec = courant;
        if (tr->liste->nb ==0) // liste vide
            return 1;
        else
        {
            while (courant!=NULL && courant ->annee > annee)  // on a les plus jeunes au début de la liste, donc on avance dans la liste pour descendre en année
            {
                prec=courant;
                courant=courant->suivant;
            }
            while (courant != NULL && courant->annee == annee) //on est au premier dont l'annee de naissance est la bonne
            {
                if(courant->CID == CIN)
                {
                        if (prec->CID == courant->CID ) //En tete
                        {
                            if (tr->liste == 1)
                            {
                                tr->liste->premier = NULL;
                                tr->liste->nb--;
                                free(courant);
                                //supprimerTranche(tr, b);
                                return 0;
                            }
                            tr->liste->premier = courant->suivant;
                            tr->liste->nb--;
                            free(courant);
                            return 0;
                        }
                        else if (courant->suivant != NULL)
                        {
                            prec->suivant = courant->suivant;
                            tr->liste->nb--;
                            free(courant);
                            return 0;
                        }
                        else if (courant->suivant == NULL)
                        {
                            prec->suivant = NULL;
                            tr->liste->nb--;
                            free(courant);
                            return 0;
                        }


                }
            }
            if ((courant == NULL) || (courant->annee > annee))
                return 1;

        }
    }
    return 1;
}



int supprimerTranche(Tranche *racine, int bornesup) //Le miens
{
    int i;
    Tranche *p;
    p=chercherTranche(racine, bornesup);
    if(p==NULL) return 1;
    else
    {
        Benevole *courant, *supp;
        courant=p->liste->premier;
        while(p->liste->nb != 0) //supression de la liste de bénévoles
        {
            Benevole *tmp=p->liste->premier;   //on supprime en tete
            Benevole *tmp1=p->liste->premier->suivant;
            free(tmp);
            p->liste->premier=tmp1;
            p->liste->nb--;
        }
        if(p->filsG==NULL && p->filsD==NULL)
        {
            if(p==p->pere->filsD)
                p->pere->filsD=NULL;
            else p->pere->filsG=NULL;
            free(p);
            return 0;
        }
        else
        {
            if(p->filsG==NULL || p->filsD==NULL)
            {
                if(p->filsG!=NULL)
                {
                    if(p==p->pere->filsD)
                    {
                        p->pere->filsD=p->filsG;
                        p->filsG=NULL;
                    }
                    else
                    {
                        p->pere->filsG=p->filsG;
                        p->filsG=NULL;
                    }
                }
                else
                {
                    if(p==p->pere->filsD)
                    {
                        p->pere->filsD=p->filsD;
                        p->filsD=NULL;
                    }
                    else
                    {
                        p->pere->filsG=p->filsD;
                        p->filsD=NULL;
                    }
                }
                free(p);
                return 0;
            }
            else //si le noeud a 2 fils
            {
                Tranche *succ=p->filsD;
                while(succ->filsG!=NULL)
                {
                    succ=succ->filsG;
                }
                int tmp;
                ListBenevoles *ltmp;
                tmp=p->BorneSup;
                p->BorneSup = succ->BorneSup;
                succ->BorneSup=tmp;
                ltmp=p->liste;
                p->liste=succ->liste;
                succ->liste=ltmp;
                i=supprimerTranche(succ, succ->BorneSup);
            }
        }
    }
}



int supprimerTranche(Tranche *racine, int borneSup) //celui de Laure
{
    Benevole *ben = malloc(sizeof(Benevole));
    Tranche *parcours = racine;
    
    //si l'arbre est vide on renvoi une erreur
    if (parcours == NULL)
    {
        printf("l'arbre est vide ou n'existe pas");
        return 1;
    }
    
    //on se positionne sur la tranche à supprimer
    parcours = succ_rec(racine, borneSup);
    
    //Si la tranche n'a aucun fils
    if(parcours->filsG == NULL && parcours->filsD == NULL)
    {
        //on vide la tranche de ces benevole pour pouvoir liberer la memoire
        ben=parcours->ListBenevoles.Benevole;
        while(ben!=NULL)
        {
            supprimerBen(racine, ben->CIN, ben->Annee);
            ben=ben->Suivant;
        }
        
        if(parcours->pere->filsD == parcours)
            parcours->pere->filsD = NULL;
        else parcours->pere->filsG = NULL;
        
        free(parcours);
        return 0;
    }
    
    //Si la tranche n'a pas de fils gauche
    if(parcours->filsG==NULL)
    {
        Tranche *tmp = parcours;
        ben=parcours->ListBenevoles.Benevole;
        while(ben!=NULL)
        {
            supprimerBen(racine, ben->CIN, ben->Annee);
            ben=ben->Suivant;
        }
        parcours->BorneSup=parcours->filsD->BorneSup;
        parcours->ListBenevoles=parcours->filsD->ListBenevoles;
        parcours->filsD=NULL;
        
        free(tmp);
        return 0;
    }
    
    //si la tranche n'a pas de fils droit
    if (parcours->filsD==NULL)
    {
        Tranche *tmp = parcours;
        ben=parcours->ListBenevoles.Benevole;
        while(ben!=NULL)
        {
            supprimerBen(racine, ben->CIN, ben->Annee);
            ben=ben->Suivant;
        }
        
        parcours->BorneSup=parcours->filsG->BorneSup;
        parcours->ListBenevoles=parcours->filsG->ListBenevoles;
        parcours->filsG=NULL;
        
        free(tmp);
        return 0;
    }
    
    //Si la tranche a deux fils
    
    Tranche *tmp = parcours;
    //on cherche la tranche minimum du fils droit
    tmp=my_min(parcours->filsD);
    
    ben=parcours->ListBenevoles.Benevole;
    while(ben!=NULL)
    {
        supprimerBen(racine, ben->CIN, ben->Annee);
        ben=ben->Suivant;
    }
    
    parcours->BorneSup=tmp->BorneSup;
    parcours->ListBenevoles=tmp->ListBenevoles;
    supprimerTranche(tmp, tmp->BorneSup);
    return 0;   
}


int supprimerTranche2(Tranche *racine, int bornesup) //celui de ROMAN
{
    Tranche * tmp;
    Tranche * p;
    if (racine==NULL)
        return 1;
    if (chercherTranche(racine, bornesup) == NULL)
    {
        printf("La tranche demandee n'existe pas. \n");
        return 1;
    }
    if(chercherTranche(racine, bornesup) != NULL)
    {
        printf("La tranche existe, nous allons la supprimer. \n");
    }
    tmp = chercherTranche(racine, bornesup);
         while(tmp->liste->nb != 0) //supression de la liste de bénévoles
        {
            Benevole *ben=tmp->liste->premier;   //on supprime en tete
            Benevole *ben1=tmp->liste->premier->suivant;
            free(ben);
            tmp->liste->premier=ben1;
            tmp->liste->nb--;
        }
        if(tmp->filsG == NULL)  // Cas pas de fils gauche
        {
            if (tmp->filsD == NULL)
            {
                tmp->pere = NULL;
                free(tmp);
                return 0;
            }
            else //filsD != NULL
            {
                tmp->pere = tmp->filsD;
                free(tmp);
                return 0;
            }
        }
        else // filG!=NULL
        {
            if (tmp->filsD == NULL)
            {
                tmp->pere = tmp->filsG;
                free(tmp);
                return 0;
            }
            else //filsD != NULL
            {
                printf("La ca fonctionne pas ! \n");
                Tranche * courant = tmp->filsD;
                while (courant->filsG != NULL)
                {
                    courant = courant->filsG;
                    printf("test : %d", courant->BorneSup);
                }
                //tmp->BorneSup = courant->BorneSup;
                //tmp->liste = courant->liste;
                printf("passage 1 !!! \n");
                if (courant->pere->filsG == courant)
                {
                    printf("passage 2 !!! \n");
                    courant->pere->filsG = NULL;

                }
                else
                {
                    printf("passage 3 !!! \n");
                    courant->pere->filsD = NULL;

                }
                free(courant);
                return 0;
            }
            return 1;
        }

}



int supprimerTranche(Tranche *racine, int borneSup) //celui de Laure modifié par moi --> mais peut être faire des suppressions en tete comme j'avais fait pour les benevoles
{
    Tranche *parcours = racine;

    //si l'arbre est vide on renvoi une erreur
    if (parcours == NULL)
    {
        printf("l'arbre est vide ou n'existe pas");
        return 1;
    }

    //on se positionne sur la tranche à supprimer
    parcours = chercherTranche(racine, borneSup);

    //Si la tranche n'a aucun fils
    if(parcours->filsG == NULL && parcours->filsD == NULL)
    {
        //on vide la tranche de ses benevole pour pouvoir liberer la memoire
        while(parcours->liste->premier!=NULL)
        {
            Benevole *ben=parcours->liste->premier;
            parcours->liste->premier=ben->suivant;
            parcours->liste->nb--;
            free(ben);
        }
            

        if(parcours->pere->filsD == parcours)
            parcours->pere->filsD = NULL;
        else parcours->pere->filsG = NULL;

        free(parcours);
        return 0;
    }

    //Si la tranche n'a pas de fils gauche
    if(parcours->filsG==NULL)
    {
        Tranche *tmp = parcours;
        while(parcours->liste->premier!=NULL)
        {
            Benevole *ben=parcours->liste->premier;
            parcours->liste->premier=ben->suivant;
            parcours->liste->nb--;
            free(ben);
        }
               
        parcours->BorneSup=parcours->filsD->BorneSup;
        parcours->liste=parcours->filsD->liste;
        parcours->filsD=NULL;

        free(tmp);
        return 0;
    }

    //si la tranche n'a pas de fils droit
    if (parcours->filsD==NULL)
    {
        Tranche *tmp = parcours;
        ben=parcours->liste->premier;
        while(ben!=NULL) //idem faire plutôt en tete non ?
        {
            supprimerBen(racine, ben->CID, ben->annee);
            ben=ben->suivant;
        }

        parcours->BorneSup=parcours->filsG->BorneSup;
        parcours->liste=parcours->filsG->liste;
        parcours->filsG=NULL;

        free(tmp);
        return 0;
    }

    //Si la tranche a deux fils

    Tranche *tmp = parcours->filsD;
    //on cherche la tranche minimum du fils droit
    while(tmp->filsG!=NULL)
        tmp=tmp->filsG;
    //Maintenant je vide la liste de la tranche à supprimer
    Benevole *ben=parcours->liste->premier;
    while(parcours->liste->premier!=NULL)
        {
            Benevole *ben=parcours->liste->premier;
            parcours->liste->premier=ben->suivant;
            parcours->liste->nb--;
            free(ben);
        }
    //Je remplie à nouveau la liste avec celle de la tranche successeur (min du ss arbre droit), bene par bene
    //Je change aussi la borne sup
    parcours->BorneSup=tmp->BorneSup;
    Benevole *courant = tmp->liste->premier;
    while(courant!=NULL)
    {
        insererlist(parcours, courant);
        courant=courant->suivant;
    }
    //Je supprime le successeur en faisant appel à supprimerTranche() --> 0 ou 1 fils donc suppression facile
    supprimerTranche(tmp, tmp->BorneSup);
    return 0;
}





ListBenevoles *BenDhonneur(Tranche *racine) //On part du principe qu'il n'y a pas de tranche d'age vide. OK
{
    if (racine==NULL) return NULL;
    ListBenevoles *honneur;
    ListBenevoles *honneur2 = (ListBenevoles*)malloc(sizeof(ListBenevoles));
    Tranche *tmp=racine;
    Tranche *tmp1= tmp;
    while(tmp->filsD !=NULL)
    {
        tmp1 = tmp;
        tmp = tmp->filsD;
    }  //A la fin de la boucle, tmp pointe sur la tranche d'age la plus vieille
    honneur = tmp->liste;
    Benevole *ben = honneur->premier;
    while (ben->suivant != NULL)
    {
        ben = ben->suivant;
    }
    printf("Le benevole le plus age a %d ans \n", (anneeActuelle() - ben->annee));
   // honneur2->premier = ben;
    //honneur2->nb=1;
    Benevole *ben1 = ben;
    ben = honneur->premier;
    honneur2 = honneur;

    while(ben->suivant !=NULL)
    {
        if (ben->annee != ben1->annee)
        {
            honneur2->premier = ben->suivant;
        }
        ben=ben->suivant;
    }

    return honneur2;
}


/*int actualiser(Tranche *racine)
{
    int nb=0;
    int b=20;
    int max=bornemax(racine);
    Tranche *tr;
    Benevole *tmp, *tmp1, tmp2;
    while(b<=max )
    {
        if(tr=chercherTranche(racine, b)!=NULL)
        {
            tmp=tr->liste->premier;
            while(tmp!=NULL && attribuerBorne(tmp->annee) <=tr->BorneSup)
            {
                tmp2=tmp;
                tmp=tmp->suivant;
            }
            while (attribuerBorne(tmp->annee) > tr->BorneSup)
            {
                tmp1=tmp;
                tmp=tmp->suivant;
                tmp2->suivant=tmp;
                insererBen(racine, tmp1);   //On insere a la bonne borne sup
                nb++;
            }
        }
        b+=5;
    }
    return nb;
} */




/*
/*int actualiser(Tranche *racine) //fonctionne pour pas mal de cas
{
    int max=bornemax(racine);
    int nb=0;
    int b=15;
    Tranche *tr;
    Benevole *tmp, *tmp1, *tmp2;
    while (b <= bornemax(racine))
    {
        if (chercherTranche(racine, b) != NULL) //On entre dans la tranche si elle existe
        {
            tr = chercherTranche(racine, b);
            if (tr->liste->premier != NULL) //si il y a au moins un benevole on le récupère avec tmp
            {
                tmp = tr->liste->premier;
                tmp2 = tmp;
            }
            while(tmp!=NULL) //tant qu'on a un benevole
            {
                if (attribuerBorne(tmp->annee) >tr->BorneSup) //si on est supérieur à la borne sup on insère là où il faut!
                {
                    tmp1 = tmp;
                    insererBen(racine, tmp);   //On insere a la bonne borne sup
                    tmp = tmp1;
                    if (tmp == tr->liste->premier) //si c'est le premier
                    {
                        if (tmp ->suivant == NULL) //si il est seul    Ce cas fonctionne
                        {
                            tr->liste->premier = NULL; //on met à nul
                            tmp = NULL;
                            printf("Actualisation de type1\n");
                        }
                        else //sinon on met au suivant
                        {
                            tr->liste->premier = tmp->suivant;
                            tmp = tmp->suivant;
                            printf("type2 : %d\n", tmp1->CID);
                        }
                    }
                    else if (tmp->suivant != NULL) //si c'est le cas général
                    {
                        tmp2->suivant = tmp->suivant;
                        tmp1 = tmp;
                        tmp = tmp->suivant;
                        tmp1->suivant = NULL;
                        printf("Actualisation de type3\n");
                    }
                    else if(tmp ->suivant == NULL)
                    {
                        tmp2->suivant = NULL;
                        tmp = NULL;
                        printf("Actualisation de type4\n");
                    }
                    nb++;
                }
                else
                {
                    if (tmp2->CID != tmp->CID) //pour que tmp2 soit juste derriere tmp
                    {
                      tmp2=tmp2->suivant;
                    }
                    tmp = tmp->suivant; //On avance
                }

            }
        }
        b = b+1;
    }
    return nb;
}*/
*/
Tranche * racinePremiere(Tranche * racine){
	Tranche *tmp=racine;
    while(tmp->pere != NULL){
        tmp = tmp->pere;
    }
    return tmp;
}

int actualiser(Tranche *racine){   //nouveau test
	int annee=anneeActuelle();
	int total=0;
	Tranche *tmp=racine;
	Benevole *tmp_pre=NULL;
	Benevole *tmp_ben;
	if(tmp->filsD!=NULL)
		total+=actualiser(tmp->filsD);
	if(tmp->filsG!=NULL)
		total+=actualiser(tmp->filsG);
	tmp_ben=tmp->liste->premier;
	while(tmp_ben!=NULL){
		//printf("**\n");
		if(attribuerBorne(tmp_ben->annee)!=tmp->BorneSup){
			//printf("sss\n");
			insererBen(racinePremiere(tmp),tmp_ben);
			total++;
			//supprimerBen(tmp,tmp_ben->id,tmp_ben->annee);
			if(tmp_pre==NULL){
				tmp->liste->premier=tmp_ben->suivant;
			}
			else{
				tmp_pre->suivant=tmp_ben->suivant;
			}
		}
		tmp_pre=tmp_ben;
		tmp_ben=tmp_ben->suivant;
	}
	return total;

}





int totalBenTranche(Tranche *racine, int borneSup)  //OK
{
    int nb=0;
    Tranche *tr=chercherTranche(racine, borneSup);
    if (tr == NULL)
    {
        return 0;
    }
    Benevole *tmp=tr->liste->premier;
    while(tmp!=NULL)
    {
        nb++;
        tmp=tmp->suivant;
    }
    return nb;
}



int bornemax(Tranche *racine) //OK
{
    Tranche *tmp=racine;
    while(tmp->filsD != NULL)
            tmp=tmp->filsD;
    return tmp->BorneSup;
}



int totalBen(Tranche *racine)  //OK !
{
    int borneSup=20;
    int tot = 0;
    int bmax = bornemax(racine);
    do
    {
        tot += totalBenTranche(racine, borneSup);
        borneSup = borneSup + 5;
    } while (borneSup <= bmax);
    return tot;
}



float pourcentageTranche(Tranche *racine, int borneSup) //ok
{
    float res=0;
    int t;
    if(t=totalBen(racine)!=0)
        res=(((float)totalBenTranche(racine, borneSup)) / t);
    return res*100;
}

void afficherBen(Benevole *ben)  //OK
{
    while(ben!=NULL)
    {
        printf("%20s | %20s | %6c | %20d | %6d \n", ben->nom, ben->prenom, ben->sexe, ben->CID, ben->annee);
        ben=ben->suivant;
    }
}

void afficherTranche(Tranche *racine, int borneSup)  //OK
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



void afficherArbre(Tranche *racine) //OK mais plutôt faire affichahe en ordre croissant
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

void detruire_Arbre(Tranche* racine) //Il faut faire appel à supprimerTranche non ?
{
    if (racine != NULL)
    {
    detruire_Arbre(racine->filsG);
    detruire_Arbre(racine->filsD);
    supprimerTranche(racine, racine->BorneSup) ;  // les éléments de l'arbre sont mis à des valeurs aléatoires
    }
}




//
//  gestion_matrice.h
//  xochiro_256_starstar
//
//  Created by Jessica LAURENT on 09/04/2022.
//

#ifndef gestion_matrice_h
#define gestion_matrice_h

#include <stdio.h>
#include <stdlib.h>
#include "calculs.h"
// ################################## Gestion des matrices ##################################
typedef struct mat_h
{
    uint64_t **m;
    int nbCol; //nombre de colonne
    int nbLig; //nombre de ligne
}mat;

/*
 entree: l le nombre ligne et c le nombre de colonne
 sortie: une matrice de taille l*c remplit de zéro
 */

mat * init_mat(int l, int c);

/*
 entree: m une matrice
         affichage de la matrice m
 */
void affichage_mat(mat * m);

/*
 entree: m une matrice
         libération de l'espace allouer lors de la création de la matrice m
 */
void free_mat(mat *m);

//################################## Calculs Matriciels de base ##################################
/*
 entree: m et n deux matrices de la meme taille
 sortie: m+n mod 2
 */
mat * p(mat *m, mat *n);

/*
 entree: m et n deux matrices de la meme taille
 sortie: m-n mod 2
 */
mat * m(mat *m, mat *n);

/*
 entree: m de taille l*c et n de taille c*k
 sortie: m*n mod 2
 */
mat * mult(mat *m, mat *n);

/*
 entree: A de taille l*c et b de taille c*1
 sortie: x mod 2 tels que Ax=b
 */
mat * GaussEliminationAlgo(mat* A,mat *b);
#endif /* gestion_matrice_h */

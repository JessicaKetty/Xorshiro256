//
//  prochain_nombre_256+.h
//  xochiro_256_starstar
//
//  Created by Jessica LAURENT on 21/05/2022.
//

#ifndef prochain_nombre_256__h
#define prochain_nombre_256__h

#include <stdio.h>
#include <unistd.h>
#include <time.h>

#include "gestion_matrice.h"

/*
 Entrée: ligne une vecteur ligne 1x256 , m une matrice 256* 256, l une nombre entre 0 et 255
         Cette fonction modifie la m tel que m[l][0:255]=ligne[0][0:255]
 */
void copie_ligne(mat * ligne, mat * m, int l);

/*
 Entrée: n une matrice t*t et mn une matrice t*t
         Cette fonction modifie la n tel que n=mn et libere l'espace alloué de mn
 */
void copie_matrice (mat * n, mat * mn);

/*
 Entrée: m une vecteur ligne 1*t et n une matrice t*t
 Sortie: o=m*n de taille 1*t
 */
mat * mult_2 (mat * m, mat * n);

/*
 Sortie: le prochain nombre de xoshiro256++
 */
uint64_t prochain_nombre_xoshiro_p (void);
#endif /* prochain_nombre_256__h */

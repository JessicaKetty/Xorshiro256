//
//  prochain_nombre_x256**.h
//  xochiro_256_starstar
//
//  Created by Jessica LAURENT on 10/04/2022.
//

#ifndef prochain_nombre_x256___h
#define prochain_nombre_x256___h

#include <stdint.h>
#include <stdio.h>
#include <stdlib.h>
#include <string.h>


#include "calculs.h"
#include "gestion_matrice.h"
#include "xoshiro256**.h"


//etat du generateur
typedef struct etat_h
{
    uint64_t a;
    uint64_t b;
    uint64_t c;
    uint64_t d;
}etat;

//################################## Matrices Speciales ##################################

/*
 Entrée: a un nombre
 Sortie: un vecteur v de taille 64*1 qui a les bits de a qui commence par le bit de poids fort
 */
mat * vecteur_bin(uint64_t x);

/*
 Entrée: a, b, c, d, les sorties du genérateur xoshiro
 Sortie: un vecteur v de taille 256*1 qui a les bits des nombres  a, b, c, d qui commence par le bit de poids fort
 */
mat * vecteur_xoshiro(uint64_t a, uint64_t b, uint64_t c, uint64_t d);

/*
 Entrée: n un nombre
 Sortie: I une matrice identité de taille n*n
 */
mat * matrice_In(int n);

/*
 Entrée: n un nombre
 Sortie: I une matrice bineaire de taille n*n tels que seul la surdiagonale a des 1
 exemple: [0 1 0 0
           0 0 1 0
           0 0 0 1
           0 0 0 0]
 */
mat * shift_left(int n);

/*
 Entrée: n un nombre
 Sortie: I une matrice bineaire de taille n*n tels que seul la sousdiagonale a des 1
 exemple: [0 0 0 0
           1 0 0 0
           0 1 0 0
           0 0 1 0]
 */
mat * shift_right(int n);

/*
 Entrée: n un nombre
 Sortie: I une matrice bineaire de taille n*n tels que I=shift_right(n)^(67-r)+shift_left(n)^r
 exemple: [0 0 1 0
           0 0 0 1
           0 0 0 0
           0 0 0 0]
 */
mat * rotation(int n, int r);

/*
 Entrée:
 Sortie: la matrice de taille 256*256, représentent les calcules que l'on trouve dans xoshiro256 
 exemple: [I I 0 I
           I I I 0
           I S I 0
           0 R 0 R]
 Où I sont des matrices identité, R(64,45) matrice de rotation et S(64) matrice shift_left
 */
mat * xoshiro(void);
mat * xoshiro_inverse(void);
/*
 Entrée: une vecteur bineaire de taille 256*1
 Sortie: l'etat e où e.a=nombre en base 10 de v[0][0] a v[63][0]
                     e.b=nombre en base 10 de v[64][0] a v[127][0]
                     e.c=nombre en base 10 de v[128][0] a v[191][0]
                     e.d=nombre en base 10 de v[192][0] a v[255][0]
 */
etat vecteur_to_etat(mat *v);

/*
 Entrée: une vecteur bineaire de taille 64*1
 Sortie: 4 nombres en base 10 de v[0][0] a v[63][0]
 */
uint64_t vecteur_to_int (mat * v);

/*
 Entrée: une sortie du generateur xoshiro256**
 Sortie: le nombre que contient l'etat e.b
 */
uint64_t inverse_quart2_etat(uint64_t y);

/*
 Entrée:
 Sortie: une matrice m de taille 256*256 tels que
            m =[0 I 0 0
                   X
                   X^2
                   X^3  ]
 où X sont les lignes 64 à 127 de  xoshiro_starstar
    X^2 sont les lignes 64 à 127 de  xoshiro_starstar^2
    X^3 sont les lignes 64 à 127 de  xoshiro_starstar^3
    I la matrice identité de taille 64*64
 */
mat * matrice_xoshiro_256ss(void);

/*
 Entrée:
 Sortie: Inverse de la matrice xoshiro_256ss
 */
mat * inv_matrice_xoshiro_256ss(void);


/*
 Entrée: les quatres premieres sortie de xoshiro256**
 Sortie: le prochain nombre de xoshiro256**
 */
uint64_t prochain_nombre (uint64_t a, uint64_t b, uint64_t c, uint64_t d);

#endif /* prochain_nombre_x256___h */

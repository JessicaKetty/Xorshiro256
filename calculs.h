//
//  calculs.h
//  xochiro_256_starstar
//
//  Created by Jessica LAURENT on 09/04/2022.
//

#ifndef calculs_h
#define calculs_h

#include <stdio.h>
#include <stdlib.h>

// ################################## Calcule Z/2Z ##################################
/*
 entree: x
 sortie: x%2 > 0
 */
uint64_t modulo (uint64_t x);

/*
 entree: x,y
 sortie: (x+y) %2 > 0
 */
uint64_t add_Z_2Z(uint64_t x, uint64_t y);

/*
 entree: x,y
 sortie: (x-y) %2 > 0
 */
uint64_t sous_Z_2Z(uint64_t x, uint64_t y);

/*
 entree: x,y
 sortie: (x*y) %2 > 0
 */
uint64_t mult_Z_2Z(uint64_t x, uint64_t y);

/*
 entree: a,b
 sortie: q tels que a=q*b+r
 */
uint64_t EuclidAlgorithm_q (uint64_t a, uint64_t b );

/*
 entree: a,b
 sortie: r tels que a=q*b+r
 */
uint64_t EuclidAlgorithm_r (uint64_t a, uint64_t b );

/*
 entree: a,b
 sortie: v tels que au + bv= a^b
 */
uint64_t inverse(uint64_t a, uint64_t b);

/*
 entree: n tels que 0≤n<63
 sortie: 2^n
 */
uint64_t pwd(int n);

#endif /* calculs_h */

//
//  main.c
//  xochiro_256_starstar
//
//  Created by Jessica LAURENT on 22/03/2022.

#include <stdint.h>
#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <time.h>

#include "calculs.h"
#include "gestion_matrice.h"

#include "xoshiro256**.h"
#include "prochain_nombre_x256**.h"

#include "xoshiro256+.h"
#include "prochain_nombre_256+.h"

#include <unistd.h>


// ################################## Main ##################################
int main()
{
    uint64_t sortie[4], next, prochain;
    struct xoshiro256ss_state x;
    srand( (unsigned int) time( NULL ) );
    
    printf("\n################################## Projet xoshiro256** ##################################\n\n");
    
    x.s[0]=(uint64_t) rand();
    x.s[1]=(uint64_t) rand();
    x.s[2]=(uint64_t) rand();
    x.s[3]=(uint64_t) rand();
  
    
    for(int i=0; i<4; i++)
    {
        sortie[i]=xoshiro256ss(&x);
    }
    prochain=xoshiro256ss(&x);
    
    printf("Les quatres premiers sorties du générateur sont : \n%llu, %llu, %llu, %llu\n\n", sortie[0],sortie[1],sortie[2],sortie[3]);
    //autre exemple qui est ok
    next= prochain_nombre (sortie[0], sortie[1], sortie[2], sortie[3]);
    printf("\nLe prochain nombre est %llu:\t",next);
    
    if(prochain== next)
        printf("vrai.\n");
    else
        printf("false. On attend %llu\n", prochain);
        
    printf("\n\n################################## Projet xoshiro256+ ##################################\n\n");
    
    prochain_nombre_xoshiro_p();
    
    return EXIT_SUCCESS;
}



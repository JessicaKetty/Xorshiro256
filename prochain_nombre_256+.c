//
//  prochain_nombre_256+.c
//  xochiro_256_starstar
//
//  Created by Jessica LAURENT on 21/05/2022.
//
#include <stdio.h>
#include <unistd.h>
#include <time.h>

#include "gestion_matrice.h"
#include "prochain_nombre_256+.h"
#include "xoshiro256+.h"
#include "prochain_nombre_x256**.h"

void copie_ligne(mat * ligne, mat * m, int l)
{
    if (ligne->nbCol!=256 || ligne->nbLig!=1 || m->nbCol!=256 || m->nbLig!=256 || m==NULL)
    {
        perror("copie_ligne");
        exit(0);
    }
    for(int j=0; j<256; j++)
    {
        m->m[l][j]=ligne->m[0][j];
    }
}
void copie_matrice (mat * n, mat * mn)
{
    for(int i=0; i<256; i++)
    {
        for(int j=0; j<256; j++)
        {
            n->m[i][j]=mn->m[i][j];
        }
    }
    free_mat(mn);
}
mat * mult_2 (mat * m, mat * n)
{
    mat * o=init_mat(1, 256);
    
    
    for (int j=0; j<256; j++)
    {
        o->m[0][j]=0;
        for (int k=0; k<256; k++)
        {
            o->m[0][j]+=m->m[0][k]*n->m[k][j];
        }
        o->m[0][j]=o->m[0][j]%2;
    }
    
    return o;
}
uint64_t prochain_nombre_xoshiro_p(void)
{
    uint64_t prochain=0,next,first=0,a;
    mat * m=xoshiro(), *n=xoshiro(), *xor=init_mat(1,256), *M=init_mat(256, 256), *sortie=init_mat(256, 1),*k, *mn, *first_state, *last_state;
    struct xoshiro256p_state y;
    
    srand( (unsigned int) time( NULL ) );
    y.s[0]=(uint64_t) rand();
    y.s[1]=(uint64_t) rand();
    y.s[2]=(uint64_t) rand();
    y.s[3]=(uint64_t) rand();
    
    xor->m[0][63]=1;
    xor->m[0][255]=1;
    
    //creation de la matrice Xorshiro256+
    for (int i=0; i<256; i++)
    {
        if(i==0)
        {
            copie_ligne(xor, M, i);
        }
        else if (i==1)
        {
            k=mult_2(xor, m);
            copie_ligne(k, M, i);
            free_mat(k);
        }
        else
        {
            mn=mult(m, n);
            
            k=mult_2(xor, mn);
            copie_ligne(k, M, i);
            copie_matrice (n, mn);
            free_mat(k);
        }
        a=xoshiro256p(&y);
        if (i==0)
            first=a;
        sortie->m[i][0]=a%2;
        printf("Creation de la matrice Xorshiro256+ en cours: ligne %d/256 Ok\r",i+1);
        fflush(stdout);
        //sleep(1);
    }
    prochain=xoshiro256p(&y);
    first_state=GaussEliminationAlgo(M, sortie);
    printf("\n\n");
    printf("La premier sortie est: %llu\n",first);
    
    etat e=vecteur_to_etat(first_state);
    printf("Le premier etat etat est :\n%llu, %llu, %llu, %llu\n\n", e.a, e.b, e.c, e.d);
    
    
    k=mult(m, n);
    last_state=mult(k, first_state);
    
    e=vecteur_to_etat(last_state);
    printf("Le dernier etat etat est :\n%llu, %llu, %llu, %llu\n\n", e.a, e.b, e.c, e.d);
    
    next=e.a+e.d;
    if (next == prochain)
        printf("La 257e sortie est %llu: vrai.\n\n", next);
    else
        printf("La 257e sortie est %llu: faux.\n\n", next);
    free_mat(m);
    free_mat(xor);
    free_mat(M);
    free_mat(sortie);
    free_mat(n);
    free_mat(first_state);
    free_mat(last_state);
    free_mat(k);
    
    return prochain;
}

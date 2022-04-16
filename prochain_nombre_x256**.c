//
//  prochain_nombre_x256**.c
//  xochiro_256_starstar
//
//  Created by Jessica LAURENT on 10/04/2022.
//

#include "prochain_nombre_x256**.h"

#include <stdint.h>
#include <stdio.h>
#include <stdlib.h>
#include <string.h>


#include "calculs.h"
#include "gestion_matrice.h"

//################################## Matrice Speciale ##################################

mat * vecteur_bin(uint64_t x)
{
    mat * bin=init_mat(64, 1);
    int o=63;
    
    while (x>0 && o>0)
    {
        bin->m[o][0]=x%2;
        x/=2;
        o--;
    }
    
    return bin;
}
mat * vecteur_xoshiro(uint64_t a, uint64_t b, uint64_t c, uint64_t d)
{
    mat * v=init_mat(256, 1);
    int o=63;
    
    // nombre a 0 a 63
    while (a>0 && o>=0)
    {
        v->m[o][0]=a%2;
        a/=2;
        o--;
    }
    // nombre b 64 a 127
    o=127;
    while (b>0 && o>=64)
    {
        v->m[o][0]=b%2;
        b/=2;
        o--;
    }
    // nombre c 128 a 191
    o=191;
    while (c>0 && o>=128)
    {
        v->m[o][0]=c%2;
        c/=2;
        o--;
    }
    // nombre c 192 a 255
    o=255;
    while (d>0 && o>=192)
    {
        v->m[o][0]=d%2;
        d/=2;
        o--;
    }
    
    return v;
}
mat * matrice_In(int n)
{
    if (n<=0)
    {
        perror(" erreur: matrice_In \n");
        exit(0);
    }
    mat * I= init_mat(n, n);
    for( int i=0; i<n; i++)
    {
        I->m[i][i]=1;
    }
    return I;
}
mat * shift_left(int n)
{
    if (n<=0)
    {
        perror(" erreur: shift_left \n");
        exit(0);
    }
    mat * I= init_mat(n, n);
    for( int i=0; i<n-1; i++)
    {
        I->m[i][i+1]=1;
    }
    return I;
}
mat * shift_right(int n)
{
    if (n<=0)
    {
        perror(" erreur: shift_right \n");
        exit(0);
    }
    mat * I= init_mat(n, n);
    for( int i=1; i<n; i++)
    {
        I->m[i][i-1]=1;
    }
    return I;
}

mat * rotation(int n, int k)
{
    mat * r=shift_right(n);
    mat * l=shift_left(n);

    
    mat *l1=mult(l,l);
    for(int i=1;i<k;i++)
    {
        l1=mult(l,l1);
    }
    
    mat *r1=mult(r,r);
    for(int i=1;i<64-k;i++)
    {
        r1=mult(r,r1);
    }
    
    mat * o = p(r1,l1);
    free_mat(l);
    free_mat(r);
    free_mat(l1);
    free_mat(r1);
    
    return o;
}

mat * xoshiro_starstar(void)
{
    mat * xo=init_mat(256, 256);
    int j;
    
    //colonne 0 à 63
    for(int i=0; i<64; i++)
    {
        xo->m[i][i]=1;
    }
    j=0;
    for(int i=64; i<128; i++)
    {
        xo->m[i][j]=1;
        j++;
    }
    j=0;
    for(int i=128; i<192; i++)
    {
        xo->m[i][j]=1;
        j++;
    }
    
    //colonne 64 à 127
    j=64;
    for(int i=0; i<64; i++)
    {
        xo->m[i][j]=1;
        j++;
    }
    j=64;
    for(int i=64; i<128; i++)
    {
        xo->m[i][j]=1;
        j++;
    }
    j=64;
    for(int i=128; i<192; i++)
    {
        if (j+1*17<128)
            xo->m[i][j+1*17]=1;
        j++;
    }
    j=64;
    for(int i=192; i<256; i++)
    {
        if (j+1*45<128)
            xo->m[i][j+1*45]=1;
        if(i+1*(64-45)<256)
            xo->m[i+1*(64-45)][j]=1;
        j++;
    }
    
    //colonne 128 a 191
    j=128;
    for(int i=64; i<128; i++)
    {
        xo->m[i][j]=1;
        j++;
    }
    j=128;
    for(int i=128; i<192; i++)
    {
        xo->m[i][j]=1;
        j++;
    }
    
    //colonne 192 a 256
    j=192;
    for(int i=0; i<64; i++)
    {
        xo->m[i][j]=1;
        j++;
    }
    j=192;
    for(int i=192; i<256; i++)
    {
        if (j+1*45<256)
            xo->m[i][j+1*45]=1;
        if(i+1*(64-45)<256)
            xo->m[i+1*(64-45)][j]=1;
        j++;
    }
    
    return xo;
}

etat vecteur_to_etat(mat *v)
{
    etat e;
    int o,h=0;
    
    e.a=0;
    e.b=0;
    e.c=0;
    e.d=0;
    
    o=63;
    while (o>=0)
    {
        if (v->m[o][0]==1)
        {
            e.a+=pwd(h);
        }
        o--;
        h++;
    }
    
    o=127;
    h=0;
    while (o>=64)
    {
        if (v->m[o][0]==1)
        {
            e.b+=pwd(h);
        }
        o--;
        h++;
    }
    
    o=191;
    h=0;
    while (o>=128)
    {
        if (v->m[o][0]==1)
        {
            e.c+=pwd(h);
        }
        o--;
        h++;
    }
    
    o=255;
    h=0;
    while (o>=192)
    {
        if (v->m[o][0]==1)
        {
            e.d+=pwd(h);
            //printf("%lld %d\n",e.d,h);
        }
        o--;
        h++;
    }
    /*
    printf("\n%llu\n", e.a);
    printf("%llu\n", e.b);
    printf("%llu\n", e.c);
    printf("%llu\n", e.d);*/
    return e;
}

uint64_t vecteur_to_int (mat * v)
{
    if (v==NULL)
    {
        perror("vecteur_to_int : null\n");
        exit(0);
    }
    uint64_t x=0;
    int h=0,o=63;
    
    o=63;
    while (o>=0)
    {
        if (v->m[o][0]==1)
        {
            x+=pwd(h);
        }
        o--;
        h++;
    }
    
    return x;
}

uint64_t inverse_quart2_etat(uint64_t y)
{
    uint64_t x;
    x=y* 10248191152060862009ull;
    x= (x<<57)|(x>>7);
    x *= 14757395258967641293ull;
    return x;
}
mat * matrice_xochiro_final(void)
{
    mat *m=init_mat(256, 256);
    mat * xochiro=xoshiro_starstar();
    mat * xochiro2=mult(xochiro, xochiro);
    mat * xochiro3=mult(xochiro2, xochiro);
    
    int j,i,k;
    
    //ligne 0 a 63
    j=64;
    for(i=0; i<64; i++)
    {
        m->m[i][j]=1;
        j++;
    }
    
    //ligne 64 a 127
    for(i=64;i<128;i++)
    {
        for (j=0;j<256;j++)
        {
            m->m[i][j]=xochiro->m[i][j];
        }
    }
    
   
    k=64;
    //ligne 128 a 191
    for(i=128;i<192;i++)
    {
        for (j=0;j<256;j++)
        {
            m->m[i][j]=xochiro2->m[k][j];
        }
        k++;
    }
    
    
    //ligne 191 a 255
    k=64;
    for(i=192;i<256;i++)
    {
        for (j=0;j<256;j++)
        {
            m->m[i][j]=xochiro3->m[k][j];
        }
        k++;
    }
    
    
    free_mat(xochiro);
    free_mat(xochiro2);
    free_mat(xochiro3);
    
    return m;
}

uint64_t prochain_nombre (uint64_t a, uint64_t b, uint64_t c, uint64_t d)
{
    uint64_t next;
    etat e,e2;
    
    mat * xoshiro1=xoshiro_starstar();
    mat * xoshiro2=mult(xoshiro1, xoshiro1);
    mat * xoshiro3=mult(xoshiro1, xoshiro2);
    mat * xoshiro4=mult(xoshiro1, xoshiro3);
    mat *v=vecteur_xoshiro( inverse_quart2_etat(a),inverse_quart2_etat(b),inverse_quart2_etat(c),inverse_quart2_etat(d));

    mat *xochirof=matrice_xochiro_final();
    mat * x=GaussEliminationAlgo(xochirof, v);
    
    e2=vecteur_to_etat(x);
    
    printf("Le premier état est:\n%llu\t", e2.a);
    printf("%llu\t", e2.b);
    printf("%llu\t", e2.c);
    printf("%llu\n", e2.d);
    
    mat * vec=vecteur_xoshiro(e2.a, e2.b, e2.c, e2.d);
    
    mat * final=mult(xoshiro4, vec);
    
    e=vecteur_to_etat(final);
    printf("Le dernier état est:\n%llu\t", e.a);
    printf("%llu\t", e.b);
    printf("%llu\t", e.c);
    printf("%llu\n", e.d);
    
    next=rol64(e.b * 5, 7)*9;
   
    
    free_mat(xoshiro1);
    free_mat(xoshiro2);
    free_mat(xoshiro3);
    free_mat(xoshiro4);

    free_mat(v);
    free_mat(xochirof);
    free_mat(x);
    
    return next;
}




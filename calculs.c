//
//  calculs.c
//  xochiro_256_starstar
//
//  Created by Jessica LAURENT on 09/04/2022.
//

#include "calculs.h"
#include <stdio.h>
#include <stdlib.h>

// ################################## Calcule Z/pZ ##################################
uint64_t modulo (uint64_t x)
{
    x%=2;
    while (x<0)
       x+=2;
    
    return (uint64_t)x;
}

uint64_t add_Z_2Z(uint64_t x, uint64_t y)
{
    x+=y;
    return modulo(x);
}
uint64_t sous_Z_2Z(uint64_t x, uint64_t y)
{
    x-=y;
    return modulo(x);
}
uint64_t mult_Z_2Z(uint64_t x, uint64_t y)
{
    x*=y;
    return modulo(x);
}


uint64_t EuclidAlgorithm_q (uint64_t a, uint64_t b )
{
    int64_t q=a/b;
    
    return q;
}
uint64_t EuclidAlgorithm_r (uint64_t a, uint64_t b )
{
    int64_t r=a%b;
    
    return r;
}

uint64_t inverse(uint64_t a, uint64_t b)
{
    uint64_t r=b,  q=-1, R=a, u=1, v=0, u_2=0, v_2=1,tmp;
    
    //printf("u, v, r, q\n%d  %d  %d  %d\n",u,v,r,q);
  
    while (R>1)
    {
        q= EuclidAlgorithm_q ( r, R);
        r= EuclidAlgorithm_r ( r, R);
        
        u=u-q*u_2;
        v=v-q*v_2;
        
        tmp=r;
        r=R;
        R=tmp;
        
        tmp=u;
        u=u_2;
        u_2=tmp;
        
        tmp=v;
        v=v_2;
        v_2=tmp;
        
        
       //printf("%llu, %llu, %llu, %llu\n",u,v,r,q);
    }
    
    v_2=(v_2+b)%b;
    
    return v_2;
}
uint64_t pwd(int n)
{
    uint64_t x=1;
    
    while (n>0)
    {
        x*=2;
        n--;
    }
    return x;
}

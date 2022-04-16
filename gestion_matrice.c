//
//  gestion_matrice.c
//  xochiro_256_starstar
//
//  Created by Jessica LAURENT on 09/04/2022.
//

#include "gestion_matrice.h"
#include <stdio.h>
#include <stdlib.h>

// ################################## Gestion matrice ##################################
mat * init_mat(int l, int c)
{
    mat *m=malloc(sizeof(int32_t));
    m->nbCol=c;
    m->nbLig=l;
    
    //init des lignes
    m->m=(uint64_t**)malloc(l*sizeof(uint64_t*));
    if(m->m==NULL)
    {
        perror("erreur 1: intialisation_mat ");
        exit(0);
    }
    
    //init des colonnes
    for (int i=0; i<l;i++)
    {
        m->m[i]=(uint64_t*)malloc(c*sizeof(uint64_t));
        if(m->m[i]==NULL)
        {
            perror("erreur 2: intialisation_mat ");
            exit(0);
        }
    }
    for(int i=0; i<l; i++)
    {
        for(int j=0; j<c ;j++)
        {
            m->m[i][j]=0;
        }
    }
    return m;
}
 
void affichage_mat(mat * m)
{
    if (m != NULL)
    {
        for(int i=0; i<m->nbLig; i++)
        {
            for (int j=0; j< m->nbCol; j++)
            {
                printf("%llu\t",m->m[i][j]);
            }
            printf("\n");
        }
        printf("\n");
    }
    else
        printf("error");
}

void free_mat(mat *m)
{
    if (m!=NULL)
    {
        for (int i=0; i<m->nbLig;i++)
        {
          free(m->m[i]);
        }
        free(m->m);
        free(m);
    }
    
}

//################################## Calcul Matriciel ##################################
mat * p(mat *m, mat *n)
{
    if (n== NULL || m==NULL)
    {
        perror("erreur 1: p\n ");
        exit(0);
    }
    if(m->nbLig != n->nbLig || m->nbCol != n->nbCol)
    {
        perror("erreur 2: p\n");
        exit(0);
    }
    mat * o=init_mat(m->nbLig, m->nbCol);
    
    for(int i=0; i<m->nbLig; i++)
    {
        for(int j=0; j<m->nbCol;j++)
        {
            o->m[i][j]=add_Z_2Z(m->m[i][j], n->m[i][j]);
        }
    }
    
    return o;
}
mat * m(mat *m, mat *n)
{
    if (n== NULL || m==NULL)
    {
        perror("erreur 1: m \n ");
        exit(0);
    }
    
    if(m->nbLig != n->nbLig || m->nbCol != n->nbCol)
    {
        perror("erreur : m \n");
        exit(0);
    }
    mat * o=init_mat(m->nbLig, m->nbCol);
    
    for(int i=0; i<m->nbLig; i++)
    {
        for(int j=0; j<m->nbCol;j++)
        {
            o->m[i][j]=sous_Z_2Z(m->m[i][j], n->m[i][j]);
        }
    }
    
    return o;
}
mat * mult(mat *m, mat *n)
{
    if (n== NULL || m==NULL)
    {
        perror("erreur 1: x \n ");
        exit(0);
    }
    if (m->nbCol!=n->nbLig)
    {
        perror("erreur 2: x \n ");
        exit(0);
    }
    int64_t a=0;
    mat *o= init_mat(m->nbLig,n->nbCol);
   
    
    for (int i=0; i<m->nbLig; i++)
    {
        for (int j=0; j<n->nbCol; j++)
        {
            a=0;
            for (int k=0; k<m->nbLig; k++)
            {
                a=a+m->m[i][k]*n->m[k][j];
            }
            o->m[i][j]=a%2;
            //o->m[i][j]=(int)a;
        }
    }
    
    return o;
}

mat * GaussEliminationAlgo(mat *A,mat *b)
{
    mat * x=init_mat(b->nbLig,b->nbCol);
    mat * t=init_mat(1,A->nbCol);
    
    int j;
    double u;
    
    for (int i=0; i<A->nbCol; i++ )
    {
        j=i;
        while (j<A->nbCol && A->m[j][i]==0)
        {
            j++;
        }
        if (j==A->nbCol)
        {
            perror("pas de soulution Gauss\n");
            exit(0);
        }
        
        for(int o=i;o<A->nbCol;o++)
        {
            t->m[0][o]=A->m[i][o];
        }
        
        for(int o=i;o<A->nbCol;o++)
        {
            A->m[i][o]=A->m[j][o];
        }
        
        for(int o=i;o<A->nbCol;o++)
        {
            A->m[j][o]=t->m[0][o];
        }
        u=b->m[i][0];
        b->m[i][0]=b->m[j][0];
        b->m[j][0]=u;
        
        
        double pivot;
        
        for(int j=i+1;j<A->nbCol;j++)
        {
            pivot=A->m[j][i];
            b->m[j][0]=modulo(b->m[j][0]-pivot/A->m[i][i]*b->m[i][0]);
            
            for (int o=i;o<A->nbCol;o++)
            {
                A->m[j][o]=modulo(A->m[j][o]-A->m[i][o]*pivot/A->m[i][i]);
            }
        }
       
    }
    
    
    for (int i=A->nbCol-1; i>=0; i--)
    {
        x->m[i][0]=b->m[i][0];
    }
    for (int i=A->nbCol-1; i>=0; i--)
    {
        x->m[i][0]/=A->m[i][i];
        for (int j=i-1;j>=0;j--)
        {
            x->m[j][0]=modulo(x->m[j][0]-x->m[i][0]*A->m[j][i]);
        }
    }
   
    free_mat(t);
    return x;
}


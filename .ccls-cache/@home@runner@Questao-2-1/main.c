#include <stdio.h>
#include<stdlib.h>
#include<string.h>
#include<math.h>

double** LeMatriz(char nome[20],int *m, int *n)
{
  FILE *arq;
  int i,j;
  double **a;
  
  arq=fopen(nome,"r");
  
  fscanf(arq,"%d",m);
  fscanf(arq,"%d",n);

  a=(double **) malloc(sizeof(double *) * *m);
  
  for(i=0; i<*m; i++) a[i]=(double *)malloc(*n * sizeof(double));
  
  for(i=0; i<*m; i++)
  {
    for(j=0;j<*n; j++)
    {
      fscanf(arq,"%lf",&a[i][j]);
    }
  }
  
  return a;
}

void ImprimeMatriz(double **M, int m, int n)
{
  int i,j;
  
  for (i=0; i<m; i++) 
  {
    for(j=0;j<n;j++)
    {
      printf("%.2lf ",M[i][j]);
    }
    puts("");
  }  
  puts("");
}

void ImprimeVetor(double *V, int m)
{
  int i;
  for (i=0; i<m; i++) 
  {
    printf("%.2lf ",V[i]);  
    puts("");
  }  
}

double *SubstituicaoReversa(double **M, int m, int n)
{
  double *S,t;
  int i,j;
  
  S= malloc(m* sizeof(double));
  
  for(i=m-1;i>=0;i--)
  {
    t=0;
    for(j=(n-2);j>i;j--) 
    {
      t+=M[i][j]*S[j];
    }
    S[i]=(M[i][n-1]-t)/M[i][i];
  }
  
  return S;
}

void TrocaLinhaMestre(double **k, double **l)
{
  double *temp;
  
  temp=*k;
  *k=*l;
  *l=temp;
}

double **EliminacaoGaussiana(double **M, int m, int n)
{
  int i,j,k,troca;  
  double l,pivot;
  
  for(k=0; k<n-1;k++)
  {
    pivot=M[k][k];
    troca=k;
    
    for(j=k;j<m-1;j++)
    {
      if(fabs(M[j][k])>fabs(pivot))
      {
        pivot= fabs(M[j][k]);
        troca=j;
      }
    }
    
    if(pivot==0)
    {
      printf("Sistema sem solucao!\n");
      return M;
    }

    if(j!=k) TrocaLinhaMestre(&M[j],&M[k]);    
    
    for(i=k+1; i<=m-1;i++)
    { 
      l= M[i][k]/M[k][k];
    
      for(j=0; j<n; j++)
      {
        M[i][j]=l*M[k][j]-M[i][j];
      }
    }
  }
  
  return M;
}

double **MultiplicaMatriz(double **M, int m1, int m2, double **N, int n1, int n2)
{
  double **S,t;
  int i, j,k;
  
  if(m2!=n1)
  {
    printf("A mutiplicacao nao pode ser feita!\n"); 
    return NULL;
  }
  
  S=malloc(m1*sizeof(double *));
  for(i=0; i<m1; i++) S[i]=malloc(n2 * sizeof(double));

  for(i=0; i<m1; i++)
  {
    for(j=0; j<n2; j++)
    {
      t=0;
      for(k=0; k<m2; k++)
      {
        t+=M[i][k]*N[k][j];
      }
      S[i][j]=t;
    }
  }
  
  return S;
}

double TestaSistema(double **M, int m1, int m2, double **Raizes)
{
  double **S,sum=0;
  int i;

  S= MultiplicaMatriz(M, m1, m1, Raizes, m1, 1);
  /*
  for(i=0; i<m1; i++)
  {
    sum+=(S[i][1])*(S[i][1]);    
  }
  printf("%g", sum);
  */
  return sum;
}

int main(int argc, char **argv) 
{
  double **M, **Triang, *Raizes,Soma;
  int m1, m2; 
  
  M = LeMatriz(argv[1], &m1, &m2);
  ImprimeMatriz(M, m1, m2);
  Triang = EliminacaoGaussiana(M, m1, m2);
  ImprimeMatriz(Triang, m1, m2);
  Raizes = SubstituicaoReversa(Triang, m1, m2);
  ImprimeVetor(Raizes, m1);
  Soma = TestaSistema(M, m1, m2, &Raizes);
  if(Soma) printf("Sistema resolvido corretamente\n");
  
  return 0;
}
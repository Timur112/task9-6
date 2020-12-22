#include <stdio.h>
#include <stdlib.h>
#include <math.h>
#include <string.h>

void swap(float *a, float *b)
{
    float c;
    c=*a;
    *a=*b;
    *b=c;
}
void toptriangle(float **a, int n, int d)
{
    int i,j;
    float p;
    if(d<n-1)
    {
        if(a[d][d]==0)
        {
            i=d;
            while(a[i][d]==0)
            {
                i++;
            }
             for(j=0;j<2*n;j++)
            {
                swap(&a[d][j],&a[i][j]);
            }
        }
        for(i=d+1;i<n;i++)
        {
            p=a[i][d]/a[d][d];
            for(j=d;j<2*n;j++)
            {
                a[i][j]=a[i][j]-a[d][j]*p;
            }
        }
        toptriangle(a,n,d+1);
    }
}
void bottomtriangle(float **a,int k,int n)
{
    int i,j;
    float p;
    if(k>1)
    {
        for(i=k-2;i>=0;i--)
        {
            p=a[i][k-1]/a[k-1][k-1];
            for(j=2*n-1;j>=0;j--)
            {
                a[i][j]=a[i][j]-a[k-1][j]*p;

            }
        }
        bottomtriangle(a,k-1,n);
    }
}
float** Gauss2(float **a, int n)
{
    int i,j;
    float **b;
    b=(float**) malloc(n*sizeof(float*));
    for(i=0;i<n;i++)
    {
        b[i]=(float*) malloc((2*n)*sizeof(float));
    }
    for(i=0;i<n;i++)
    {
        for(j=0;j<n;j++)
        {
            b[i][j]=a[i][j];
        }
        for(j=n;j<2*n;j++)
        {
            if(j-i==n)
            {
                b[i][j]=1;
            }
            else
            {
                b[i][j]=0;
            }
        }
    }
    toptriangle(b,n,0);
    bottomtriangle(b,n,n);
    for(i=0;i<n;i++)
    {
        for(j=n;j<2*n;j++)
        {
            b[i][j]=b[i][j]/b[i][i];
        }
    }
    return b;
}
float** proof(float **a,float **b, int n)
{
    int i,j,k;
    float **c;
    c=(float**) malloc(n*sizeof(float*));
    for(i=0;i<n;i++)
    {
        c[i]=(float*) malloc(n*sizeof(float));
    }
    for(i=0;i<n;i++)
    {
        for(j=0;j<n;j++)
        {
            c[i][j]=0;
            for(k=0;k<n;k++)
            {
                c[i][j]=c[i][j]+a[i][k]*b[k][j+n];
            }
        }
    }
    return c;
}

int main()
{
    int n,i,j;
    float **a,*x;
    printf("Введите порядок вашей матрицы\n");
    scanf("%d", &n);
    a=(float**) malloc(n*sizeof(float*));
    for(i=0;i<n;i++)
    {
        a[i]=(float*) malloc(n*sizeof(float));
    }
    for(i=0;i<n;i++)
    {
        for(j=0;j<n;j++)
        {
            printf("Введите значение a[%d][%d]\n", i,j);
            scanf("%f", &a[i][j]);
        }
    }
    printf("Вот обратная матрица\n");
     for(i=0;i<n;i++,printf("\n"))
    {
        for(j=n;j<2*n;j++)
        {
            printf("%4f ", Gauss2(a,n)[i][j]);
        }
    }
    printf("Проверка\n");
     for(i=0;i<n;i++,printf("\n"))
    {
        for(j=0;j<n;j++)
        {
            printf("%4f ", proof(a,Gauss2(a,n),n)[i][j]);
        }
    }
    return 0;
}

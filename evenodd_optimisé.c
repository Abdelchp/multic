#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <math.h>

#define SIZEX 1000
#define SIZEY 100000



void even(float *a, float *b, int *d,int n) 
{
    int i;
    for (i=0; i<n; i++) 
    {
        int index = d[i];
        float v = a[index-1] + a[index+1] + a[index-SIZEY] + a[index+SIZEY];
        float m = sqrt(v);
        b[index] = (v/m + (1+1/m)*b[index]);
    }
}

int main() 
{
    float *a,*b;
    int *d,n=0;
    int i,j;
  
    a=(float *)malloc(sizeof(float)*SIZEX*SIZEY);
    b=(float*)malloc(sizeof(float)*SIZEX*SIZEY);
    d=(int*)malloc(sizeof(int)*SIZEX*SIZEY/2);
  
    /* Initialization */
    for (i=0; i<SIZEX*SIZEY; i++) 
    {
        a[i]=b[i]=i;
    }
    for (i=1; i<SIZEX-1; i++) 
    {
        for (j=1; j<SIZEY-1; j++) 
        {
            if ((i+j)%2==0) 
            {
                d[n++]=i*SIZEY+j;
            }
        }
    }
    /* Computation */
    for(i=0;i<100;i++) 
    {
        even(a,b,d,n);
        even(b,a,d,n);
        fprintf(stderr,".");
    }
    fprintf(stderr,"\n%f",a[10]);
    free(a);
    free(b);
    return 0;
}


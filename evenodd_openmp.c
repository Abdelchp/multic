#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <math.h>
#include <omp.h>
#include <time.h>

#define SIZEX 1000
#define SIZEY 100000



void wr_time(int echo, double sum_main, double sum){
  int j;
  FILE *fpp;
  fpp = fopen ("time.txt", "a");
  if(echo == 0){fputs("temps cpu:    main          func compute   \n", fpp );}
  fprintf(fpp, " evenodd1.c %f   %f  \n", sum_main, sum );
  fclose(fpp);
}



void even(float *a, float *b, int *d,int n) 
{
    int i;
    #pragma omp parallel for private(i) 
    for (i=0; i<n; i++) 
    {
        float v=0,m;
        v+=a[d[i]-1];
        v+=a[d[i]+1];
        v+=a[d[i]-SIZEY];
        v+=a[d[i]+SIZEY];
        m=sqrt(v);
        b[d[i]]=(v/m+(1+1/m)*b[d[i]]);
    }
}



int main() 
{
  int i,j;
  float *a,*b;
  int *d,n=0;
  
  clock_t tm1, tm2, tc1, tc2;
  double sum_main, sum;
  tm1 = tm2 = tc1 = tc2 = sum = 0.0;
  
  a=(float *)malloc(sizeof(float)*SIZEX*SIZEY);
  b=(float*)malloc(sizeof(float)*SIZEX*SIZEY);
  d=(int*)malloc(sizeof(int)*SIZEX*SIZEY/2);
  
  /* Initialization */
  tm1 = clock();
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
  
  double begin_time =  omp_get_wtime();
  
  for(i=0;i<100;i++) 
  {
    
    
    even(a,b,d,n);
    even(b,a,d,n);
    
    
    fprintf(stderr,".");
  }
  
  double end_time = omp_get_wtime();
 // cout << end_time - begin_time <<endl;
  
 // tm2 = clock();
 // sum_main = ((double) (tm2-tm1))/CLOCKS_PER_SEC;
  
  fprintf(stderr,"\n%f",a[10]);
  int echo=1;
  wr_time(echo, 1,end_time - begin_time);

  free(a);
  free(b);
  return 0;
  
}

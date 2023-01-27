#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <math.h>
#include <omp.h>


//using namespace std;
#define SIZEX 1000
#define SIZEY 10000

void even(float **a, float **b, int **d,int n) {
  int i,j;
  #pragma omp simd
  for (i=1; i<n; i+=2) {
    int i1,j1,i2,j2;
    float v1=0,m1;
    float v2=0,m2;
    
    i1=d[i][0];
    j1=d[i][1];
    v1+=a[i1-1][j1];
    v1+=a[i1+1][j1];
    v1+=a[i1][j1-1];
    v1+=a[i1][j1+1];
    m1=sqrt(v1);
    b[i1][j1]=(v1/m1+(1+1/m1)*b[i1][j1]);
    
    i2=d[i+1][0];
    j2=d[i+1][1];
    v2+=a[i2-1][j2];
    v2+=a[i2+1][j2];
    v2+=a[i2][j2-1];
    v2+=a[i2][j2+1];
    m2=sqrt(v2);
    b[i2][j2]=(v2/m2+(1+1/m2)*b[i2][j2]);
    
  }}

int main() {
   int i,j,k;

   float** a1;
   float** b1;
   int n=0;
   int** d1;
   
   a1=(float**)malloc((SIZEY)*sizeof(float*));
   for (int i = 0; i < SIZEY; i++) {
     a1[i] = (float*)malloc(SIZEX * sizeof(float));
   }

   b1=(float**)malloc((SIZEY)*sizeof(float*));
   for (int i = 0; i < SIZEY; i++) {
     b1[i] = (float*)malloc(SIZEX * sizeof(float));
   }

   
   d1=(int**)malloc((SIZEX*SIZEY/2)*sizeof(int*));
   for (int i = 0; i < SIZEX*SIZEY/2; i++) {
     d1[i] = (int*)malloc(2 * sizeof(int));
   }
   
   memset(d1, 0, sizeof d1);
   
   /* Initialization */
   for (i=0; i<SIZEY; i++)
     for (j=0; j<SIZEX; j++) 
       a1[i][j]=b1[i][j]=j*SIZEY+i;
   for (i=1; i<SIZEX-1; i++) 
     for (j=1; j<SIZEY-1; j++) 
       if ((i+j)%2==0) {
	 n++;
	 
	 d1[n][0]=j;
	 d1[n][1]=i;
	 //cout <<"n= "<<n<<" and dni = "<<d1[n][0]<<" and dnj = "<<d1[n][1]<<endl;
       }

   
   
   for(i=0;i<100;i++) {         
     even(a1,b1,d1,n);
     even(b1,a1,d1,n);              
     fprintf(stderr,".");        
   }                             
   fprintf(stderr,"\n%f",a1[500][500]); 
   
   
   for (int i = 0; i < SIZEX*SIZEY/2; i++) {
     free(d1[i]);
   }
   free(d1);

   for (int i = 0; i < SIZEY; i++) {
     free(a1[i]);
   }
   free(a1);

   for (int i = 0; i < SIZEY; i++) {
     free(b1[i]);
   }
   free(b1);


   
   return 0;
}


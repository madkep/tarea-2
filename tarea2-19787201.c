/* Tarea 2
   Felipe Ignacio Céspedes Cordero
   19787201-2
   ICI2341
*/



#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <unistd.h>
#include <pthread.h>
#include <sys/syscall.h>

typedef struct {
    int filas;
    int columnas;
    int **matriz;

}Matriz;

typedef struct{
  int i;
  int j;
}Filasycol;


Matriz mat1,mat2,mat3;


void coordinador();
int **crearMatriz(int filas,int columnas);
void mostrarMatriz(Matriz m);
void *calcular(void *param);

int main(){
  coordinador();
  return 0;
}

void coordinador(){
  int buffer1,buffer2,i,j,contador=0;
  FILE *fp;

	fp = fopen( "mat.txt","r");
	if (fp==NULL) {fputs ("File error",stderr); exit (1);}

  fscanf(fp,"%d",&buffer1);
  mat1.filas=buffer1;
  fscanf(fp,"%d",&buffer2);
  mat1.columnas=buffer2;
  mat1.matriz=crearMatriz(buffer1,buffer2);

  for(i=0;i<mat1.filas;i++){
    for(j=0;j<mat1.columnas;j++){
        fscanf(fp,"%d",&buffer1);
        mat1.matriz[i][j]=buffer1;
    }
  }

  fscanf(fp,"%d",&buffer1);
  mat2.filas=buffer1;
  fscanf(fp,"%d",&buffer2);
  mat2.columnas=buffer2;
  mat2.matriz=crearMatriz(buffer1,buffer2);

  for(i=0;i<mat2.filas;i++){
    for(j=0;j<mat2.columnas;j++){
        fscanf(fp,"%d",&buffer1);
        mat2.matriz[i][j]=buffer1;
    }
  }

  if(mat1.columnas!=mat2.filas){
    printf("Las Matrices no se pueden multiplicar\n");
    exit(0);
  }

  printf("Matriz A\n");
  mostrarMatriz(mat1);
  printf("\n");
  printf("Matriz B\n");
  mostrarMatriz(mat2);
  printf("\n");

    mat3.filas=mat1.filas;
    mat3.columnas=mat2.columnas;
    mat3.matriz=crearMatriz(mat3.filas,mat3.columnas);

    for(i = 0; i < mat3.filas; i++) {
       for(j = 0; j < mat3.columnas; j++) {

          Filasycol *vector = (Filasycol*) malloc(sizeof(Filasycol));
          vector->i = i;
          vector->j = j;
          pthread_t tid;
          pthread_create(&tid,NULL,calcular,(void *)vector);
          pthread_join(tid, NULL);
          contador++;
       }
    }
    printf("\nMatriz 3\n");
    mostrarMatriz(mat3);
  }

  int **crearMatriz(int filas,int columnas){
    int **matriz=(int**)malloc(sizeof(int*)*filas);
    if(matriz!=NULL){
      for(int i=0;i<filas;i++){
        matriz[i]=(int*)malloc(sizeof(int)*columnas);
        if(matriz[i]==NULL) return NULL;
      }
    }
    else return NULL;
    return matriz;
  }

  void mostrarMatriz(Matriz m){
    for(int i=0;i<m.filas;i++){
      for(int j=0;j<m.columnas;j++){
          printf("%d ",m.matriz[i][j]);
      }
      printf("\n");
    }
  }


  void *calcular(void *param){
    Filasycol *vector = (Filasycol*)param;
    int n, sum = 0,mayor;
    if(mat3.filas>=mat3.columnas) mayor=mat3.filas;
    else mayor=mat3.columnas;
    pid_t pidt = syscall(SYS_gettid);

    for(n = 0; n< mayor; n++){
       sum += mat1.matriz[vector->i][n] * mat2.matriz[n][vector->j];
    }

    mat3.matriz[vector->i][vector->j] = sum;

    printf("Proceso(%d) calculando elemento [%d,%d]\n",pidt,vector->i,vector->j );

    pthread_exit(0);

  }

#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <unistd.h>
#include <pthread.h>

typedef struct {
    int filas;
    int columnas;
    int **matriz;

}Matriz;

typedef struct{
  int filas;
  int columnas;
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
  int buffer1,buffer2,i,j;
  //Filasycol matfc1, matfc2, matfc3;
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

  printf("Matriz A\n");
  mostrarMatriz(mat1);
  printf("\n");
  printf("Matriz B\n");
  mostrarMatriz(mat2);





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
    


  }

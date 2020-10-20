//
// Created by Christian Silvero
//

#ifndef PUBLICACION_H_
#define PUBLICACION_H_

#include "cliente.h"

#define SIZE_PUBLICACION 64
#define TRUE 1
#define FALSE 0
#define ACTIVO 1
#define PAUSADO 0
#define UP 1
#define DOWN 0
#define RETRY 2
#define QTY_PUBLICACIONES 1000
#define MIN_RUBRO 1
#define MAX_RUBRO 10

typedef struct
{
  int idPublicacion;
  int isEmpty;
  int estado;
  char textoPublicacion[SIZE_PUBLICACION];
  int numeroRubro;
  int idCliente;
}sPublicacion;

int publicacion_initArray(sPublicacion* pArray, int limite);
int publicacion_alta(sPublicacion* pArray, int limite, int idCliente);
int publicacion_modificar(sPublicacion* pArray, int limite, int indice);
int publicacion_baja(sPublicacion* pArray, int limite, int indice);
int publicacion_buscarLibre(sPublicacion* pArray, int limite, int* pIndice);
int publicacion_buscarPorId(sPublicacion* pArray, int limite, int idAviso);
int publicacion_buscarPorIdCliente(sPublicacion* pArray, int limite, int idCliente);
int publicacion_imprimir(sPublicacion* pArray, int limite);
int publicacion_imprimirPorIndice(sPublicacion* pArray, int limite, int indice);
int publicacion_ordenarPorNombre(sPublicacion* pArray, int limite, int orden);
int publicacion_altaForzada(sPublicacion* pArray, int limite, int indice, int* idAviso, int idCliente, char* textoAviso, int numeroRubro, int estado);
int publicacion_estadoPausado(sPublicacion* pArray, int limite, int getId);
int publicacion_estadoActivo(sPublicacion* pArray, int limite, int getId);

#endif /* PUBLICACION_H_ */

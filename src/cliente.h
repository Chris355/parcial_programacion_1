//
// Created by Christian Silvero
//

#ifndef CLIENTE_H_
#define CLIENTE_H_

#define SIZE_STRING 1024
#define SIZE_CUIT 1024
#define TRUE 1
#define FALSE 0
#define UP 1
#define DOWN 0
#define RETRY 2
#define QTY_CLIENTES 100

typedef struct
{
  char nombre[SIZE_STRING];
  char apellido[SIZE_STRING];;
  char cuit[SIZE_CUIT];
  int isEmpty;
  int idCliente;
}sCliente;

int cliente_initArray(sCliente* pArrayClientes, int limite);
int cliente_alta(sCliente* pArrayClientes, int limite);
int cliente_modificar(sCliente* pArrayClientes, int limite);
int cliente_baja(sCliente* pArrayClientes, int limite);
int cliente_buscarLibre(sCliente* pArrayClientes, int limite, int* pIndice);
int cliente_buscarId(sCliente* pArrayClientes, int limite, int idCliente);
int cliente_imprimir(sCliente* pArrayClientes, int limite);
int cliente_imprimirPorIndice(sCliente* pArrayClientes, int limite, int indice);
int cliente_imprimirPorId(sCliente* pArrayClientes, int limite, int id);
int cliente_ordenarPorNombre(sCliente* pArrayClientes, int limite, int orden);
int cliente_altaForzadaArray(sCliente* pArrayClientes, int limite, int indice, int* id, char* nombre, char* apellido, char* cuit);

#endif /* CLIENTE_H_ */

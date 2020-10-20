//
// Created by Christian Silvero
//

#ifndef INFORME_H_
#define INFORME_H_

#include "publicacion.h"

#define QTY_RUBROS 20

typedef struct
{
    int rubro;
    int isEmpty;
}sRubro;

int rubro_initArray(sRubro*, int);
int rubro_existeRubro(sRubro*, int, int);
int rubro_generarRubros(sRubro*, int, sPublicacion*);

int informe_imprimirPublicacionesPorIdCliente(sPublicacion* pArrayPublicaciones, int publicacionesLen, sCliente* pArrayClientes, int clientesLen, int getIdCliente);
int informe_imprimirPublicacionPorSuId(sPublicacion* pArrayPublicaciones, int publicacionesLen, sCliente* pArrayClientes, int clientesLen, int getIdPublicacion);
int generarListaDeIdsClientes(sPublicacion* pArrayPublicaciones, int lenPublicaciones, int* pArrayIdsClientes);
int informe_imprimirPublicacionesPorCliente(int* pArrayIdsClientes, sPublicacion* pArrayPublicaciones, int lenPublicaciones, sCliente* pArrayClientes, int lenClientes);
int informe_bajaClientePublicacion(sPublicacion* pArrayPublicaciones, int publicacionesLen, sCliente* pArrayClientes, int clientesLen);
int informe_pausarPublicacion(sPublicacion* pArrayPublicaciones, int publicacionesLen, sCliente* pArrayClientes, int clientesLen);
int informe_reanudarPublicacion(sPublicacion* pArrayPublicaciones, int publicacionesLen, sCliente* pArrayClientes, int clientesLen);
int informe_imprimirClientesConTotalAvisosActivos(sPublicacion* pArrayPublicaciones, int publicacionesLen, sCliente* pArrayClientes, int clientesLen);

int informe_contadorAvisosPorIdCliente(sPublicacion* pArrayPublicaciones, int publicacionesLen, int idCliente, int *contadorAvisos);
int informe_clientesConMasAvisos(sPublicacion* pArrayPublicaciones, int publicacionesLen, sCliente* pArrayClientes, int clientesLen, int *bufferIndex, int *contadorAvisos);
int informe_cantidadDeAvisosPausados(sPublicacion* pArrayPublicaciones, int publicacionesLen, int *contador);
int informe_contadorRubroPorIdCliente(sPublicacion* pArrayPublicaciones, int publicacionesLen, int idRubro, int *contador);
int informe_rubroConMasAvisos(sRubro* pArrayRubro, int rubrosLen, sPublicacion* pArrayPublicaciones, int publicacionesLen, int* pRubro, int* pContador);

int informe_contadorAvisosActivosPorIdCliente(sPublicacion* pArrayPublicaciones, int publicacionesLen, int idCliente, int *contador);
int informe_clienteConMasAvisosActivos(sPublicacion* pArrayPublicaciones,int publicacionesLen,sCliente* pArrayClientes,int clientesLen,int* bufferIndex,int* contador);
int informe_contadorAvisosPausadosPorIdCliente(sPublicacion* pArrayPublicaciones, int publicacionesLen, int idCliente, int *contador);
int informe_clienteConMasAvisosPausados(sPublicacion* pArrayPublicaciones,int publicacionesLen,sCliente* pArrayClientes,int clientesLen,int* bufferIndex,int* contador);

int informe_ordenarRubroMenorAMayor(sRubro* pArrayRubro, int rubrosLen, sPublicacion* pArrayPublicaciones);
int informe_cantidadAvisosActivosTotales(sPublicacion* pArrayPublicaciones, int publicacionesLen, int *contador);
int informe_clienteConMenosAvisos(sPublicacion* pArrayPublicaciones,int publicacionesLen,sCliente* pArrayClientes,int clientesLen,int* bufferIndex,int* contador);
int informe_contadorAvisosPorRubro(sPublicacion* pArrayPublicaciones, int publicacionesLen, int getRubro, int* contador);
int informe_imprimirAvisosPorRubro(sPublicacion* pArrayPublicaciones, int publicacionesLen, int getRubro);
int informe_contadorAvisosPorCuit(sPublicacion* pArrayPublicaciones, int publicacionesLen, sCliente* pArrayClientes, int clientesLen, char* getCuit, int* contador);
int informe_imprimirAvisosPorCuit(sPublicacion* pArrayPublicaciones, int publicacionesLen, sCliente* pArrayClientes, int clientesLen, char* getCuit);
int informe_imprimirRubrosSinRepetir(sRubro* pArrayRubro, int rubrosLen, sPublicacion* pArrayPublicaciones);
int informe_imprimirRubros(sRubro* pArrayRubro, int rubrosLen);

#endif /* INFORME_H_ */

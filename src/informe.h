//
// Created by Christian Silvero
//

#ifndef INFORME_H_
#define INFORME_H_

#include "publicacion.h"

int informe_imprimirPublicacionesPorIdCliente(sPublicacion* pArrayPublicaciones, int publicacionesLen, sCliente* pArrayClientes, int clientesLen, int getIdCliente);
int informe_imprimirPublicacionPorSuId(sPublicacion* pArrayPublicaciones, int publicacionesLen, sCliente* pArrayClientes, int clientesLen, int getIdPublicacion);
int generarListaDeIdsClientes(sPublicacion* pArrayPublicaciones, int lenPublicaciones, int* pArrayIdsClientes);
int informe_imprimirPublicacionesPorCliente(int* pArrayIdsClientes, sPublicacion* pArrayPublicaciones, int lenPublicaciones, sCliente* pArrayClientes, int lenClientes);
int informe_bajaClientePublicacion(sPublicacion* pArrayPublicaciones, int publicacionesLen, sCliente* pArrayClientes, int clientesLen);

#endif /* INFORME_H_ */

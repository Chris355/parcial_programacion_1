//
// Created by Christian Silvero
//
#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include "utn.h"
#include "publicacion.h"
#include "cliente.h"

static int generarListaDeIdsClientes(sPublicacion* pArrayPublicaciones, int lenPublicaciones, int* pArrayIdsClientes);

//------------------------- FUNCIONES INFORMES -----------------------------------

/**
 * \brief imprime la lista de publicaciones de cada cliente por su id
 * \param sPublicacion* pArrayPublicaciones, Es el array de publicaciones
 * \param int lenPublicaciones, Es el limite array de publicaciones
 * \param sCliente* pArrayClientes, Es el array de clientes
 * \param int lenClientes, Es el limite array de clientes
 * \param int getIdCliente, id del cliente pedido
 * \return (-1) Error / (0) Ok
 *
*/
int informe_imprimirPublicacionesPorIdCliente(sPublicacion* pArrayPublicaciones, int publicacionesLen, sCliente* pArrayClientes, int clientesLen, int getIdCliente)
{
  int retorno = -1;
  int i;
  int bufferIndiceCliente;
  if(pArrayPublicaciones != NULL && publicacionesLen > 0 && pArrayClientes != NULL && clientesLen > 0 && getIdCliente >= 0)
  {
    for(i=0; i<publicacionesLen; i++)
    {
      if(pArrayPublicaciones[i].idCliente == getIdCliente)
      {
        bufferIndiceCliente = cliente_buscarId(pArrayClientes, clientesLen, getIdCliente);
        printf("\nId CLiente: %d - Texto publicacion: %s - Id Publicacion: %d - Estado: %d - Numero rubro: %d- Nombre: %s - Apellido: %s - Cuit: %sf",
               pArrayPublicaciones[i].idCliente,
               pArrayPublicaciones[i].textoPublicacion,
               pArrayPublicaciones[i].idPublicacion,
               pArrayPublicaciones[i].estado,
               pArrayPublicaciones[i].numeroRubro,
               pArrayClientes[bufferIndiceCliente].nombre,
               pArrayClientes[bufferIndiceCliente].apellido,
               pArrayClientes[bufferIndiceCliente].cuit);
        retorno = 0;
      }
    }
  }
  return retorno;
}

/**
 * \brief imprime la lista de publicaciones de cada cliente por su id
 * \param sPublicacion* pArrayPublicaciones, Es el array de publicaciones
 * \param int lenPublicaciones, Es el limite array de publicaciones
 * \param sCliente* pArrayClientes, Es el array de clientes
 * \param int lenClientes, Es el limite array de clientes
 * \param int getIdCliente, id de la publicacion pedida
 * \return (-1) Error / (0) Ok
 *
*/
int informe_imprimirPublicacionPorSuId(sPublicacion* pArrayPublicaciones, int publicacionesLen, sCliente* pArrayClientes, int clientesLen, int getIdPublicacion)
{
  int retorno = -1;
  int i;
  int bufferIndicePublicacion;
  if(pArrayPublicaciones != NULL && publicacionesLen > 0 && pArrayClientes != NULL && clientesLen > 0 && getIdPublicacion >= 0)
  {
    for(i=0; i<clientesLen; i++)
    {
      if(pArrayPublicaciones[i].idPublicacion == getIdPublicacion)
      {
        bufferIndicePublicacion = publicacion_buscarId(pArrayPublicaciones, publicacionesLen, getIdPublicacion);
        printf("\nId CLiente: %d - Texto publicacion: %s - Id Publicacion: %d - Estado: %d- Numero rubro: %d- Nombre: %s - Apellido: %s - Cuit: %sf",
               pArrayPublicaciones[bufferIndicePublicacion].idCliente,
               pArrayPublicaciones[bufferIndicePublicacion].textoPublicacion,
               pArrayPublicaciones[bufferIndicePublicacion].idPublicacion,
               pArrayPublicaciones[bufferIndicePublicacion].estado,
               pArrayPublicaciones[bufferIndicePublicacion].numeroRubro,
               pArrayClientes[i].nombre,
               pArrayClientes[i].apellido,
               pArrayClientes[i].cuit);
        retorno = 0;
      }
    }
  }
  return retorno;
}

/**
 * \brief genera una lista de arrays de ids del cliente
 * \param sPublicacion* pArrayPublicaciones, Es el array de publicaciones
 * \param int lenPublicaciones, Es el limite array de publicaciones
 * \param int* pArrayIdsClientes, Es el array de ids de clientes
 * \return (-1) Error / (0) Ok
 *
*/
static int generarListaDeIdsClientes(sPublicacion* pArrayPublicaciones, int lenPublicaciones, int* pArrayIdsClientes)
{
  int retorno = -1;
  int i;
  int j;
  int flagExisteId;
  int indiceId = 0;

  if(pArrayPublicaciones != NULL && lenPublicaciones > 0 && pArrayIdsClientes != NULL)
  {
    for(i=0; i<lenPublicaciones; i++)
    {
      flagExisteId = 0;
      if(pArrayPublicaciones[i].isEmpty==FALSE)
      {
        for(j=0; j<indiceId; j++)
        {
          if(pArrayPublicaciones[i].idCliente==pArrayIdsClientes[j])
          {
            flagExisteId = 1;
            break;
          }
        }
        if(flagExisteId == 0)
        {
          pArrayIdsClientes[indiceId] = pArrayPublicaciones[i].idCliente;
          indiceId++;
        }
      }
    }
    retorno = indiceId;
  }
  return retorno;
}

/**
 * \brief imprime la lista de publicaciones de cada cliente por su id
 * \param int* pArrayIdsClientes, Es el array de ids de clientes
 * \param sPublicacion* pArrayPublicaciones, Es el array de publicaciones
 * \param int lenPublicaciones, Es el limite array de publicaciones
 * \param sCliente* pArrayClientes, Es el array de clientes
 * \param int lenClientes, Es el limite array de clientes
 * \return (-1) Error / (0) Ok
 *
*/
int informe_imprimirPublicacionesPorCliente(int* pArrayIdsClientes, sPublicacion* pArrayPublicaciones, int lenPublicaciones, sCliente* pArrayClientes, int lenClientes)
{
	int retorno = -1;
  int indiceIdMax;

  indiceIdMax = generarListaDeIdsClientes(pArrayPublicaciones, lenPublicaciones, pArrayIdsClientes);
	for(int i = 0; i<indiceIdMax; i++)
	{
		printf("\n\nListado del id cliente: %d\n", pArrayIdsClientes[i]);
		informe_imprimirPublicacionesPorIdCliente(pArrayPublicaciones, lenPublicaciones, pArrayClientes, lenClientes, pArrayIdsClientes[i]);
	}

  return retorno;
}

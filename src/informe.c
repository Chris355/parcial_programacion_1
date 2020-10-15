//
// Created by christian on 12/10/20.
//

#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include "utn.h"
#include "publicacion.h"
#include "cliente.h"

//----------------------- informe_imprimirPublicacionPorSuId --------------------------------------------
/**
 * \brief Imprimi todas las publicaciones por el id cliente
 * \param sPublicacion* pArrayPublicaciones, es el array de publicaciones
 * \param int lenPublicaciones, es el limite de array
 * \param sCliente* pArrayClientes, es el array del cliente
 * \param int lenClientes, es el limite de array
 * \param int getIdCliente, es el id solicitado
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
      if(pArrayPublicaciones[i].isEmpty == FALSE &&
         pArrayPublicaciones[i].idCliente == getIdCliente)
      {
        bufferIndiceCliente = cliente_buscarId(pArrayClientes, clientesLen, getIdCliente);
        printf("\nId CLiente: %d - Texto publicacion: %s - Id Publicacion: %d - Estado: %d - Numero rubro: %d- Nombre: %s - Apellido: %s - Cuit: %s",
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

//----------------------- informe_imprimirPublicacionPorSuId --------------------------------------------
/**
 * \brief Imprimi todas las publicaciones por el id publicacion
 * \param sPublicacion* pArrayPublicaciones, es el array de publicaciones
 * \param int lenPublicaciones, es el limite de array
 * \param sCliente* pArrayClientes, es el array del cliente
 * \param int lenClientes, es el limite de array
 * \param int getIdPublicacion, es el id solicitado
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
      if(pArrayPublicaciones[i].isEmpty == FALSE &&
         pArrayPublicaciones[i].idPublicacion == getIdPublicacion)
      {
        bufferIndicePublicacion = publicacion_buscarId(pArrayPublicaciones, publicacionesLen, getIdPublicacion);
        printf("\nId CLiente: %d - Texto publicacion: %s - Id Publicacion: %d - Estado: %d- Numero rubro: %d- Nombre: %s - Apellido: %s - Cuit: %s",
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

//----------------------- generarListaDeIdsClientes --------------------------------------------
/**
 * \brief Inicializa el array de cuits
 * \param sPublicacion* pArrayPublicaciones, es el array de publicaciones
 * \param int lenPublicaciones, es el limite de array
 * \param int* pArrayIdsClientes, Es el puntero al array de ids
 * \return (-1) Error / (0) Ok
 *
*/
int generarListaDeIdsClientes(sPublicacion* pArrayPublicaciones, int lenPublicaciones, int* pArrayIdsClientes)
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

//----------------------- informe_imprimirPublicacionesPorCliente --------------------------------------------
/**
 * \brief Imprimi todas las publicaciones de un cliente
 * \param int* pArrayIdsClientes, Es el puntero al array de ids
 * \param sPublicacion* pArrayPublicaciones, es el array de publicaciones
 * \param int lenPublicaciones, es el limite de array
 * \param sCliente* pArrayClientes, es el array del cliente
 * \param int lenClientes, es el limite de array
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

//----------------------- informe_bajaClientePublicacion --------------------------------------------
/**
 * \brief Baja el cliente con sus publicaciones
 * \param sPublicacion* pArrayPublicaciones, es el array de publicaciones
 * \param int lenPublicaciones, es el limite de array
 * \param sCliente* pArrayClientes, Es el puntero al array de clientes
 * \param int clientesLen, es el limite de array
 * \return (-1) Error / (0) Ok
 *
*/
int informe_bajaClientePublicacion(sPublicacion* pArrayPublicaciones, int publicacionesLen, sCliente* pArrayClientes, int clientesLen)
{
  int retorno = -1;
  int auxIdCliente;
  int auxIndice;
  int bufferRespuesta;

  printf("\n=============== Listado de Clientes ==========================\n");
  cliente_imprimir(pArrayClientes, clientesLen);
  printf("\n==============================================================\n");

  if(utn_getInt(&auxIdCliente, "Indique Id del cliente para dar de baja: ", "Error! ", 0, 1000, RETRY)==0)
  {
    auxIndice = cliente_buscarId(pArrayClientes, clientesLen, auxIdCliente);
    if (auxIndice == -1)
    {
      printf("**Id no existe!**\n");
    }
    else
    {
      printf("**Ingreso correcto de ID**\n");
      printf("\n========== Listado de publicaciones del Cliente ==============\n");
      informe_imprimirPublicacionesPorIdCliente(pArrayPublicaciones, publicacionesLen, pArrayClientes, clientesLen, auxIdCliente);
      printf("\n==============================================================\n");
      if (utn_getInt(&bufferRespuesta, "Confirma baja?. Indique 1 (si) o 0 (no): ", "Error! ", FALSE, TRUE, RETRY) == 0 &&
          bufferRespuesta == TRUE)
      {
        for(int i=0; i<publicacionesLen; i++)
        {
          if(pArrayPublicaciones[i].idCliente == auxIdCliente)
          {
            publicacion_baja(pArrayPublicaciones, publicacionesLen, i);
            cliente_baja(pArrayClientes, clientesLen,auxIndice);
          }
        }
        printf("**Baja correcta**\n");
      }
      else
      {
        printf("**Baja cancelada**\n");
      }
    }
    retorno = 0;
  }
  else
  {
    printf("**Error en ingreso de Id**\n");
  }
  return retorno;
}

//
// Created by christian on 12/10/20.
//

#include "cliente.h"

#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include "utn.h"

static int generarIdNuevo(void);

//----------------------- FUNCIONES ENTIDAD ----------------------------------------------

//----------------------- generarIdNuevo -------------------------------------------------
/**
 * \brief Cada vez que la llamo me devuelve un ID nuevo que nunca me devolvio antes.
 * \return idCliente generado
*/
static int generarIdNuevo(void)
{
  static int idCliente = 0; //variable global de la funcion
  idCliente = idCliente+1;
  return idCliente;
}

//----------------------- cliente_initArray ---------------------------------------------
/**
 * \brief Inicializa el array de clientes
 * \param sCliente* pArrayClientes, Es el puntero al array de clientes
 * \param int limite, es el limite de array
 * \return (-1) Error / (0) Ok
 *
*/
int cliente_initArray(sCliente* pArrayClientes, int limite)
{
  int retorno = -1;
  int i;
  if(pArrayClientes != NULL && limite > 0)
  {
    for(i=0; i<limite; i++)
    {
      pArrayClientes[i].isEmpty = TRUE;
    }
    retorno = 0;
  }
  return retorno;
}

//----------------------- cliente_alta --------------------------------------------------
/**
 * \brief Realiza el alta de un cliente solo si el indice corresponde a un Empty
 * \param sCliente* pArrayClientes, Es el puntero al array de clientes
 * \param int limite, es el limite de array
 * \return (-1) Error / (idCliente) Ok
 *
*/
int cliente_alta(sCliente* pArrayClientes, int limite)
{
  int retorno = -1;
  int indice;
  sCliente buffersCliente;
  if(	pArrayClientes != NULL &&
      limite > 0 &&
      cliente_buscarLibre(pArrayClientes, limite, &indice) == 0 )
  {
    if(	utn_getNombre(buffersCliente.nombre, "Nombre? ", "Error", RETRY, SIZE_STRING) == 0 &&
        utn_getNombre(buffersCliente.apellido, "Apellido? ", "Error", RETRY, SIZE_STRING) == 0 &&
        utn_getCuit(buffersCliente.cuit, "Cuit? ", "Error", RETRY, SIZE_CUIT) == 0 )
    {
      buffersCliente.idCliente = generarIdNuevo();
      pArrayClientes[indice] = buffersCliente;
      pArrayClientes[indice].isEmpty = FALSE;
      retorno = buffersCliente.idCliente;
    }
  }
  return retorno;
}

//----------------------- cliente_altaForzada --------------------------------------------
/**
 * \brief Realiza el alta forzada de un cliente solo si el indice corresponde a un Empty
 * \param sCliente* pArrayClientes, Es el puntero al array de clientes
 * \param int limite, es el limite de array
 * \return (-1) Error / (0) Ok
 *
*/
int cliente_altaForzadaArray(sCliente* pArrayClientes, int limite, int indice, int* id, char* nombre, char* apellido, char* cuit)
{
  int retorno = -1;
  sCliente bufferCliente;

  if(pArrayClientes != NULL && limite > 0 && indice < limite && indice >= 0 && id != NULL)
  {
    strncpy(bufferCliente.nombre, nombre, SIZE_STRING);
    strncpy(bufferCliente.apellido, apellido, SIZE_STRING);
    strncpy(bufferCliente.cuit, cuit, SIZE_STRING);
    bufferCliente.idCliente = *id;
    bufferCliente.isEmpty = FALSE;
    pArrayClientes[indice] = bufferCliente;
    (*id)++;
    retorno = 0;
  }
  return retorno;
}

//----------------------- cliente_buscarLibre --------------------------------------------
/**
 * \brief Busca el indice de un item vacio
 * \param sCliente* pArrayClientes, Es el puntero al array de clientes
 * \param int limite, es el limite de array
 * \param int* pIndice, puntero del indice encontrado
 * \return (-1) Error / (0) Ok
 *
 */
int cliente_buscarLibre(sCliente* pArrayClientes, int limite, int* pIndice)
{
  int retorno = -1;
  int i;

  if(pArrayClientes != NULL && limite > 0)
  {
    for(i=0; i<limite; i++)
    {
      if(pArrayClientes[i].isEmpty == TRUE)
      {
        *pIndice = i;
        retorno = 0;
        break;
      }
    }
  }
  return retorno;
}

//----------------------- cliente_buscarPorId ----------------------------------------------
/**
 * \brief Busca el idCliente solicitado
 * \param sCliente* pArrayClientes, Es el puntero al array de clientes
 * \param int limite, es el limite de array
 * \return (-1) Error / (i) Ok, indice buscado
 *
*/
int cliente_buscarPorId(sCliente* pArrayClientes, int limite, int idCliente)
{
  int retorno = -1;
  int i;
  if (pArrayClientes != NULL && limite > 0)
  {
    for(i=0; i<limite; i++)
    {
      if(pArrayClientes[i].isEmpty == FALSE &&
         pArrayClientes[i].idCliente == idCliente)
      {
        retorno = i;
        break;
      }
    }
  }
  return retorno;
}

//----------------------- cliente_buscarPorCuit ----------------------------------------------
/**
 * \brief Busca el cuit solicitado y devuelve id CLiente
 * \param sCliente* pArrayClientes, Es el puntero al array de clientes
 * \param int limite, es el limite de array
 * \return (-1) Error / (idCliente) Ok
 *
*/
int cliente_buscarPorCuit(sCliente* pArrayClientes, int limite, char* auxCuit)
{
  int retorno = -1;
  int i;

  if (pArrayClientes != NULL && limite > 0)
  {
    for(i=0; i<limite; i++)
    {
      if(pArrayClientes[i].isEmpty == FALSE &&
         strncmp(pArrayClientes[i].cuit, auxCuit, SIZE_CUIT)==0)
      {
        retorno = i;
        break;
      }
    }
  }
  return retorno;
}

//----------------------- cliente_modificar ---------------------------------------------
/**
 * \brief Modifica los datos de un cliente solo si el indice corresponde a un NO Empty
 * \param sCliente* pArrayClientes, Es el puntero al array de clientes
 * \param int limite, es el limite de array
 * \param int indice, es el indice donde se cargara el cliente
 * \return (-1) Error / (idCliente) Ok
 *
*/
int cliente_modificar(sCliente* pArrayClientes, int limite)
{
  int retorno = -1;
  int indice;
  sCliente bufferEntidad;
  int bufferId;

  if(pArrayClientes != NULL && limite > 0)
  {
    if(utn_getInt(&bufferId, "Indique Id a modificar: \n", "Error!", 0, 1000, RETRY)==0)
    {
      if(cliente_buscarPorId(pArrayClientes, limite, bufferId)!=-1)
      {
        indice = cliente_buscarPorId(pArrayClientes, limite, bufferId);
        bufferEntidad = pArrayClientes[indice];
        if(utn_getNombre(bufferEntidad.nombre, "Indique nombre a modificar: ", "Error! dato invalido.\n", RETRY, SIZE_STRING)==0)
        {
          strncpy(pArrayClientes[indice].nombre, bufferEntidad.nombre, SIZE_STRING);
          if(utn_getNombre(bufferEntidad.apellido, "Indique apellido a modificar: ", "Error! dato invalido.\n", RETRY, SIZE_STRING)==0)
          {
            strncpy(pArrayClientes[indice].apellido, bufferEntidad.apellido, SIZE_STRING);
            if(utn_getCuit(bufferEntidad.cuit, "Indique cuit a modificar: ", "Error! dato invalido.\n", RETRY, SIZE_CUIT)==0)
            {
              strncpy(pArrayClientes[indice].cuit, bufferEntidad.cuit, SIZE_STRING);
              retorno = bufferId;
            }
          }
        }
      }
      else
      {
        printf("No se encontró Id!\n");
      }
    }
  }
  return retorno;
}

//----------------------- cliente_baja --------------------------------------------------
/**
 * \brief Baja el cliente solicitado por indice
 * \param sCliente* pArrayClientes, Es el puntero al array de clientes
 * \param int limite, es el limite de array
 * \return (-1) Error / (0) Ok
 *
*/
int cliente_baja(sCliente* pArrayClientes, int limite, int indice)
{
  int retorno = -1;

  if(pArrayClientes != NULL && limite > 0  && indice >= 0)
  {
    pArrayClientes[indice].isEmpty = TRUE;
    retorno = 0;
  }
  return retorno;
}

//----------------------- cliente_imprimir ----------------------------------------------
/**
 * \brief Imprime los clientes cargados
 * \param sCliente* pArrayClientes, Es el puntero al array de clientes
 * \param int limite, es el limite de array
 * \return (-1) Error / (0) Ok
 *
*/
int cliente_imprimir(sCliente* pArrayClientes, int limite)
{
  int retorno = -1;
  int i;
  if(pArrayClientes != NULL && limite > 0)
  {
    for(i=0; i<limite; i++)
    {
      if(pArrayClientes[i].isEmpty == FALSE)
      {
        printf("\nId: %d - Nombre: %s - Apellido: %s - Cuit: %s",
               pArrayClientes[i].idCliente,
               pArrayClientes[i].nombre,
               pArrayClientes[i].apellido,
               pArrayClientes[i].cuit);
      }
    }
    retorno = 0;
  }
  return retorno;
}

//----------------------- cliente_imprimirPorIndice ----------------------------------------
/**
 * \brief Imprime los clientes cargados en un indice determinado
 * \param sCliente* pArrayClientes, Es el puntero al array de clientes
 * \param int limite, es el limite de array
 * \param int indice, indice a imprimir
 * \return (-1) Error / (0) Ok
 *
*/
int cliente_imprimirPorIndice(sCliente* pArrayClientes, int limite, int indice)
{
  int retorno = -1;
  if(pArrayClientes != NULL && limite > 0 && indice < limite)
  {
    if(pArrayClientes[indice].isEmpty == FALSE)
    {
      printf("\nId: %d - Nombre: %s - Apellido: %s - Cuit: %s",
             pArrayClientes[indice].idCliente,
             pArrayClientes[indice].nombre,
             pArrayClientes[indice].apellido,
             pArrayClientes[indice].cuit);
      retorno = 0;
    }
  }
  return retorno;
}

//----------------------- cliente_imprimirPorId ----------------------------------------
/**
 * \brief Imprime los clientes cargados en un id determinado
 * \param sCliente* pArrayClientes, Es el puntero al array de clientes
 * \param int limite, es el limite de array
 * \param int id, id a imprimir
 * \return (-1) Error / (0) Ok
 *
*/
int cliente_imprimirPorId(sCliente* pArrayClientes, int limite, int id)
{
  int retorno = -1;
  int bufferIndice;
  if(pArrayClientes != NULL && limite > 0 && id >= 0)
  {
    bufferIndice = cliente_buscarPorId(pArrayClientes, limite, id);
    if(pArrayClientes[bufferIndice].isEmpty == FALSE)
    {
      printf("\nId: %d - Nombre: %s - Apellido: %s - Cuit: %s\n",
             pArrayClientes[bufferIndice].idCliente,
             pArrayClientes[bufferIndice].nombre,
             pArrayClientes[bufferIndice].apellido,
             pArrayClientes[bufferIndice].cuit);
      retorno = 0;
    }
  }
  return retorno;
}

//----------------------- cliente_ordenarPorNombre --------------------------------------
/**
 * \brief Ordena los clientes cargados en un orden determinado
 * \param sCliente* pArrayClientes, Es el puntero al array de clientes
 * \param int limite, es el limite de array
 * \return (-1) Error / (0) Ok
 *
*/
int cliente_ordenarPorNombre(sCliente* pArrayClientes, int limite, int orden)
{
  int retorno = -1;
  int i;
  int flagSwap;
  sCliente buffersCliente;
  int auxCmpString;

  if(pArrayClientes != NULL && limite > 0 && (orden == UP || orden == DOWN))
  {
    do
    {
      flagSwap = 0;
      for(i=0; i<limite-1 ;i++)
      {
        auxCmpString = strncmp(pArrayClientes[i].nombre, pArrayClientes[i+1].nombre, SIZE_STRING);
        if(
            ((orden == UP && auxCmpString > 0) || (orden == DOWN && auxCmpString < 0)) ||
            ((orden == UP && auxCmpString == 0 && pArrayClientes[i].idCliente > pArrayClientes[i+1].idCliente) ||
             (orden == DOWN && auxCmpString == 0 && pArrayClientes[i].idCliente < pArrayClientes[i+1].idCliente) )
            )
        {
          buffersCliente = pArrayClientes[i];
          pArrayClientes[i] = pArrayClientes[i+1];
          pArrayClientes[i+1] = buffersCliente;
          flagSwap = 1;
        }
      }
    }while(flagSwap == 1);
    retorno = 0;
  }
  return retorno;
}

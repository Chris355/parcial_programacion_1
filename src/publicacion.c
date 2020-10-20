//
// Created by christian on 12/10/20.
//

#include "publicacion.h"
#include <stdio.h>
#include <string.h>
#include "utn.h"
#include "cliente.h"

static int generarIdNuevo(void);

//----------------------- FUNCIONES ENTIDAD --------------------------------------------

//----------------------- generarIdNuevo --------------------------------------------
/**
 * \brief Cada vez que la llamo me devuelve un ID nuevo que nunca me devolvio antes.
 * \return idPublicacion generado
 */
static int generarIdNuevo(void) {
  static int idPublicacion = 0; //variable global de la funcion
  idPublicacion = idPublicacion+1;
  return idPublicacion;
}

//----------------------- publicacion_initArray --------------------------------------------
/**
 * \brief Inicializa el array de publicaciones
 * \param sPublicacion* pArray, Es el puntero al array de publicaciones
 * \param int limite, es el limite de array
 * \return (-1) Error / (0) Ok
 *
 */
int publicacion_initArray(sPublicacion* pArray, int limite)
{
  int retorno = -1;
  int i;
  if(pArray != NULL && limite > 0)
  {
    for(i=0; i<limite; i++)
    {
      pArray[i].isEmpty = TRUE;
      pArray[i].estado = TRUE;
    }
    retorno = 0;
  }
  return retorno;
}

//----------------------- publicacion_alta --------------------------------------------
/**
 * \brief Realiza el alta de un publicacion solo si el indice corresponde a un Empty
 * \param sPublicacion* pArray, Es el puntero al array de publicaciones
 * \param int limite, es el limite de array
 * \return (-1) Error / (0) Ok
 *
 */
int publicacion_alta(sPublicacion* pArray, int limite, int idCliente)
{
  int retorno = -1;
  int indice;
  sPublicacion bufferPublicacion;

  if(pArray != NULL &&
     limite > 0 &&
     idCliente >= 0)
  {
    indice = publicacion_buscarPorId(pArray, limite, idCliente);
    if(utn_getDescripcion(bufferPublicacion.textoPublicacion, "Texto Publicacion? ", "Error! ", RETRY, SIZE_PUBLICACION) == 0 &&
         utn_getInt(&bufferPublicacion.numeroRubro, "Numero Rubro? ", "Error! ", MIN_RUBRO, MAX_RUBRO, RETRY) == 0)
    {
      bufferPublicacion.isEmpty = FALSE;
      bufferPublicacion.estado = TRUE;
      bufferPublicacion.idPublicacion = generarIdNuevo();
      bufferPublicacion.idCliente = idCliente;
      pArray[indice] = bufferPublicacion;
      retorno = 0;
    }
  }
  return retorno;
}

//----------------------- publicacion_altaForzada --------------------------------------------
/**
 * \brief Realiza el alta forzada de un publicacion solo si el indice corresponde a un Empty
 * \param sPublicacion* pArray, Es el puntero al array de publicaciones
 * \param int limite, es el limite de array
 * \return (-1) Error / (0) Ok
 *
*/
int publicacion_altaForzada(sPublicacion* pArray, int limite, int indice, int* idPublicacion, int idCliente, char* textoPublicacion, int numeroRubro, int estado)
{
  int retorno = -1;
  sPublicacion bufferPublicacion;

  if(pArray != NULL && limite > 0 && indice < limite && indice >= 0 && idPublicacion != NULL)
  {
    strncpy(bufferPublicacion.textoPublicacion, textoPublicacion, SIZE_PUBLICACION);
    bufferPublicacion.numeroRubro = numeroRubro;
    bufferPublicacion.idCliente = idCliente;
    bufferPublicacion.idPublicacion = *idPublicacion;
    bufferPublicacion.estado = estado;
    bufferPublicacion.isEmpty = 0;
    pArray[indice] = bufferPublicacion;
    (*idPublicacion)++;
    retorno = 0;
  }
  return retorno;
}

//----------------------- publicacion_buscarLibre --------------------------------------------
/**
 * \brief Busca el indice de un item vacio
 * \param sPublicacion* pArray, Es el puntero al array de publicaciones
 * \param int limite, es el limite de array
 * \param int* pIndice, puntero del indice encontrado
 * \return (-1) Error / (0) Ok
 *
*/
int publicacion_buscarLibre(sPublicacion* pArray, int limite, int* pIndice)
{
  int retorno = -1;
  int i;

  if(pArray != NULL && limite > 0)
  {
    for(i=0; i<limite; i++)
    {
      if(pArray[i].isEmpty == TRUE)
      {
        *pIndice = i;
        retorno = 0;
        break;
      }
    }
  }
  return retorno;
}

//----------------------- publicacion_buscarId -----------------------------------------------
/**
 * \brief Busca pucblicacion por el idPublicacion indicado
 * \param sPublicacion* pArray, Es el puntero al array de publicaciones
 * \param int limite, es el limite de array
 * \param int* pIndex, puntero del indice buscado
 * \return (-1) Error / (i) Ok, indice del id buscado
 *
*/
int publicacion_buscarPorId(sPublicacion* pArray, int limite, int idPublicacion)
{
  int retorno = -1;
  if (pArray != NULL && limite > 0)
  {
    for (int i = 0; i < limite; i++)
    {
      if(pArray[i].isEmpty == FALSE )
      {
        if(pArray[i].idPublicacion == idPublicacion)
        {
          retorno = i;
          break;
        }
      }
    }
  }
  return retorno;
}

//----------------------- publicacion_buscarPorIdCliente -----------------------------------------------
/**
 * \brief Busca pucblicacion por el idCliente indicado
 * \param sPublicacion* pArray, Es el puntero al array de publicaciones
 * \param int limite, es el limite de array
 * \param int* pIndex, puntero del indice buscado
 * \return (-1) Error / (i) Ok, indice del id buscado
 *
*/
int publicacion_buscarPorIdCliente(sPublicacion* pArray, int limite, int idCliente)
{
  int retorno = -1;
  if (pArray != NULL && limite > 0)
  {
    for (int i = 0; i < limite; i++)
    {
      if(pArray[i].isEmpty == FALSE )
      {
        if(pArray[i].idCliente == idCliente)
        {
          retorno = i;
          break;
        }
      }
    }
  }
  return retorno;
}

//----------------------- publicacion_modificar -----------------------------------------------
/**
 * \brief Modifica los datos de un publicacion solo si el indice corresponde a un NO Empty
 * \param sPublicacion* pArray, Es el puntero al array de publicaciones
 * \param int limite, es el limite de array
 * \param int indice, es el indice donde se cargara el publicacion
 * \return (-1) Error / (0) Ok
 *
*/
int publicacion_modificar(sPublicacion* pArray, int limite, int indice)
{
  int retorno = -1;
  sPublicacion bufferEntidad;

  if(pArray != NULL && limite > 0 && indice >= 0)
  {
    if(utn_getInt(&bufferEntidad.numeroRubro, "Indique rubro: \n", "Error!", MIN_RUBRO, MAX_RUBRO, RETRY)==0)
    {
      pArray[indice].numeroRubro = bufferEntidad.numeroRubro;
      retorno = 0;
    }
  }
  return retorno;
}

//----------------------- publicacion_baja --------------------------------------------
/**
 * \brief Da de baja los datos de un publicacion solo si el indice corresponde a un NO Empty
 * \param sPublicacion* pArray, Es el puntero al array de publicaciones
 * \param int limite, es el limite de array
 * \return (-1) Error / (0) Ok
 *
*/
int publicacion_baja(sPublicacion* pArray, int limite, int indice)
{
  int retorno = -1;

  if(pArray != NULL && limite > 0 && indice >= 0)
  {
    pArray[indice].isEmpty = TRUE;
    retorno = 0;
  }
  return retorno;
}

//----------------------- publicacion_estadoPausado --------------------------------------------
/**
 * \brief Cambia a estado pausado un publicacion solo si el indice corresponde a un NO Empty
 * \param sPublicacion* pArray, Es el puntero al array de publicaciones
 * \param int limite, es el limite de array
 * \return (-1) Error / (0) Ok
 *
*/
int publicacion_estadoPausado(sPublicacion* pArray, int limite, int getId)
{
  int retorno = -1;
  int indice;
  int bufferRespuesta;

  if(pArray != NULL && limite > 0 && getId > 0)
  {
		indice = publicacion_buscarPorId(pArray, limite, getId);
		if (utn_getInt(&bufferRespuesta, "Confirma pausar la publicacion?. Indique 1 (si) o 0 (no): ", "Error! ", FALSE, TRUE, RETRY) == 0 &&
				bufferRespuesta == TRUE)
		{
			pArray[indice].estado = FALSE;
			retorno = 0;
		}
  }

  return retorno;
}

//----------------------- publicacion_estadoActivo --------------------------------------------
/**
 * \brief Cambia a estado activo un publicacion solo si el indice corresponde a un NO Empty
 * \param sPublicacion* pArray, Es el puntero al array de publicaciones
 * \param int limite, es el limite de array
 * \return (-1) Error / (0) Ok
 *
*/
int publicacion_estadoActivo(sPublicacion* pArray, int limite, int getId)
{
  int retorno = -1;
  int indice;
  int bufferRespuesta;

  if(pArray != NULL && limite > 0 && getId > 0)
  {
  	indice = publicacion_buscarPorId(pArray, limite, getId);
		if (utn_getInt(&bufferRespuesta, "Confirma activar la publicacion?. Indique 1 (si) o 0 (no): ", "Error! ", FALSE, TRUE, RETRY) == 0 &&
				bufferRespuesta == TRUE)
		{
			pArray[indice].estado = TRUE;
			retorno = 0;
		}
  }
  return retorno;
}

//----------------------- publicacion_imprimir --------------------------------------------
/**
 * \brief Imprime los publicaciones cargados
 * \param sPublicacion* pArray, Es el puntero al array de publicaciones
 * \param int limite, es el limite de array
 * \return (-1) Error / (0) Ok
 *
*/
int publicacion_imprimir(sPublicacion* pArray, int limite)
{
  int retorno = -1;
  if(pArray != NULL && limite > 0)
  {
    for(int i=0; i<limite; i++)
    {
      if(pArray[i].isEmpty == FALSE)
      {
        printf("\nId publicacion: %d - Estado: %d - Texto Publicacion: %s - Numero Rubro: %d - Id Cliente: %d",
               pArray[i].idPublicacion,
               pArray[i].estado,
               pArray[i].textoPublicacion,
               pArray[i].numeroRubro,
               pArray[i].idCliente);
      }
    }
    retorno = 0;
  }
  return retorno;
}

//----------------------- publicacion_imprimirIndice ---------------------------------------
/**
 * \brief Imprime los publicaciones cargados en un indice determinado
 * \param sPublicacion* pArray, Es el puntero al array de publicaciones
 * \param int limite, es el limite de array
 * \return (-1) Error / (0) Ok
 *
*/
int publicacion_imprimirPorIndice(sPublicacion* pArray, int limite, int indice)
{
  int retorno = -1;
  if(pArray != NULL && limite > 0 && indice < limite)
  {
    if(pArray[indice].isEmpty == FALSE)
    {
      printf("\nId publicacion: %d - Estado: %d -Texto Publicacion: %s - Numero Rubro: %d - Id Cliente: %d",
             pArray[indice].idPublicacion,
             pArray[indice].estado,
             pArray[indice].textoPublicacion,
             pArray[indice].numeroRubro,
             pArray[indice].idCliente);
      retorno = 0;
    }
  }
  return retorno;
}

//----------------------- publicacion_ordenarPorNombre --------------------------------------
/**
 * \brief Ordena los publicaciones cargados en un orden determinado
 * \param sPublicacion* pArray, Es el puntero al array de publicaciones
 * \param int limite, es el limite de array
 * \return (-1) Error / (0) Ok
 *
*/
int publicacion_ordenarPorNombre(sPublicacion* pArray, int limite, int orden)
{
  int retorno = -1;
  int i;
  int flagSwap;
  sPublicacion buffersPublicacion;
  int auxCmpString;

  if (pArray != NULL && limite > 0 && (orden == UP || orden == DOWN))
  {
    do
    {
      flagSwap = 0;
      for(i=0; i<limite-1 ;i++)
      {
        auxCmpString = strncmp(pArray[i].textoPublicacion, pArray[i + 1].textoPublicacion, SIZE_STRING);
        if(
            ((orden == UP && auxCmpString > 0) || (orden == DOWN && auxCmpString < 0)) ||
            ((orden == UP && auxCmpString == 0 && pArray[i].idPublicacion > pArray[i + 1].idPublicacion) ||
             (orden == DOWN && auxCmpString == 0 && pArray[i].idPublicacion < pArray[i + 1].idPublicacion) )
            )
        {
          buffersPublicacion = pArray[i];
          pArray[i] = pArray[i+1];
          pArray[i+1] = buffersPublicacion;
          flagSwap = 1;
        }
      }
    }while(flagSwap == 1);
    retorno = 0;
  }
  return retorno;
}

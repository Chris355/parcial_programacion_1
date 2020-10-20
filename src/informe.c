//
// Created by christian on 12/10/20.
//

#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include "utn.h"
#include "publicacion.h"
#include "cliente.h"
#include "informe.h"

//-----------------------// ENTIDAD AUXILIAR RUBRO //-----------------------------------------------------------

/**
 * \brief Inicializa el array de Rubros
 * \param pArrayRubro, es el array de Rubros
 * \param lenRubro, es el limite de array
 * \return (-1) Error / (0) OK
 */
int rubro_initArray(sRubro* pArrayRubro, int rubrosLen)
{
  int retorno = -1;
  int i;
  if(pArrayRubro != NULL && rubrosLen > 0)
  {
    for(i=0; i<rubrosLen; i++)
    {
    	pArrayRubro[i].isEmpty = TRUE;
    }
    retorno = 0;
  }
  return retorno;
}

//----------------------- rubro_existeRubro --------------------------------------------
/**
 * \brief verifica si existe un rubro en el array
 * \param pArrayRubro, es el array de Rubros
 * \param lenRubro, es el limite de array
 * \param bufferRubro, El numero de rubro a ser analizado
 * \return (0) FALSE (1) TRUE
 */
int rubro_existeRubro(sRubro* pArrayRubro, int rubrosLen, int bufferRubro)
{
  int retorno = 0;
  int i;
  if(pArrayRubro!=NULL && rubrosLen>0 && bufferRubro>0)
  {
    for(i=0; i<rubrosLen; i++)
    {
      if(pArrayRubro[i].isEmpty == FALSE && pArrayRubro[i].rubro == bufferRubro)
      {
      	retorno = 1;
        break;
      }
    }
  }
  return retorno;
}

//----------------------- rubro_generarRubros --------------------------------------------
/**
 * \brief genera rubros sin repetir
 * \param pArrayRubro, es el array de Rubros
 * \param lenRubro, es el limite de array
 * \param pArrayPublicaciones, es el array de publicaciones
 * \return (-1) Error (0) OK
 */
int rubro_generarRubros(sRubro* pArrayRubro, int rubrosLen, sPublicacion* pArrayPublicaciones)
{
  int retorno = -1;
  int indiceContador = 0;
  int i;

  rubro_initArray(pArrayRubro, rubrosLen);
  if (pArrayRubro != NULL && rubrosLen > 0 && pArrayPublicaciones != NULL)
  {
    for(i=0; i<rubrosLen; i++)
    {
      if( rubro_existeRubro(pArrayRubro, rubrosLen, pArrayPublicaciones[i].numeroRubro)==0 &&
      	  pArrayPublicaciones[i].isEmpty == FALSE )
      {
      	pArrayRubro[indiceContador].rubro = pArrayPublicaciones[i].numeroRubro;
      	pArrayRubro[indiceContador].isEmpty = FALSE;
      	indiceContador++;
        retorno = 0;
      }
    }
  }
  return retorno;
}

//----------------------- informe_contadorRubroPorIdCliente --------------------------------------------
/**
 * \brief calcula la cantidad total por el id rubro
 * \param sPublicacion* pArrayPublicaciones, es el array de publicaciones
 * \param int lenPublicaciones, es el limite de array
 * \param int idRubro, id rubro a comparar
 * \param int *contador, Es el puntero del contador de rubros
 * \return (-1) Error / (0) Ok
 *
*/
int informe_contadorRubroPorIdCliente(sPublicacion* pArrayPublicaciones, int publicacionesLen, int idRubro, int *contador)
{
	int retorno = -1;
	int auxContador = 0;
	int i;

	if(pArrayPublicaciones != NULL && publicacionesLen > 0 && idRubro >= 0 && contador != NULL)
	{
		for(i=0; i<publicacionesLen; i++)
		{
			if( pArrayPublicaciones[i].isEmpty == FALSE &&
				  idRubro == pArrayPublicaciones[i].numeroRubro )
			{
				auxContador++;
				*contador = auxContador;
				retorno = 0;
			}
		}
	}
	return retorno;
}

//----------------------- informe_rubroConMasAvisos --------------------------------------------
/**
 * \brief calcula el rubro que aparece en mas avisos
 * \param pArrayRubro, es el array de Rubros
 * \param lenRubro, es el limite de array
 * \param pArrayPublicaciones, es el array de publicaciones
 * \param publicacionesLen, es el limite de array
 * \param pResultado: El puntero a int donde se guardara el numero de Rubro que aparece en mas avisos
 * \return (-1) Error (0) OK
 */
int informe_rubroConMasAvisos(sRubro* pArrayRubro, int rubrosLen, sPublicacion* pArrayPublicaciones, int publicacionesLen, int* pRubro, int* pContador)
{
  int retorno = -1;
  int auxContador;
  int maximo;
  int i;

  rubro_generarRubros(pArrayRubro, rubrosLen, pArrayPublicaciones);
  if(pArrayRubro != NULL && rubrosLen > 0 && pArrayPublicaciones != NULL && publicacionesLen > 0 && pRubro != NULL)
  {
    for(i=0; i<rubrosLen; i++)
    {
      if( informe_contadorRubroPorIdCliente(pArrayPublicaciones, publicacionesLen, pArrayRubro[i].rubro, &auxContador) == 0 &&
					pArrayRubro[i].isEmpty == FALSE)
      {
        if(i == 0 || maximo < auxContador)
        {
        	maximo = auxContador;
          *pRubro = pArrayRubro[i].rubro;
          *pContador = maximo;
          retorno = 0;
        }
      }
    }
  }
  return retorno;
}

//----------------------- informe_imprimirRubrosSinRepetir --------------------------------------------
/**
 * \brief imprimir la lista de rubros sin repetir
 * \param pArrayRubro, es el array de Rubros
 * \param lenRubro, es el limite de array
 * \param pArrayPublicaciones, es el array de publicaciones
 * \param publicacionesLen, es el limite de array
 * \param pResultado: El puntero a int donde se guardara el numero de Rubro que aparece en mas avisos
 * \return (-1) Error (0) OK
 */
int informe_imprimirRubrosSinRepetir(sRubro* pArrayRubro, int rubrosLen, sPublicacion* pArrayPublicaciones)
{
  int retorno = -1;
  int i;

  rubro_generarRubros(pArrayRubro, rubrosLen, pArrayPublicaciones);
  if(pArrayRubro != NULL && rubrosLen > 0 && pArrayPublicaciones != NULL)
  {
    for(i=0; i<rubrosLen; i++)
    {
    	if(pArrayRubro[i].isEmpty == FALSE)
    	{
				printf("Indice: %d - Rubro: %d\n", i, pArrayRubro[i].rubro);
    	}
    }
  }
  return retorno;
}

//----------------------- informe_imprimirRubros --------------------------------------------
/**
 * \brief imprimir la lista de rubros
 * \param pArrayRubro, es el array de Rubros
 * \param lenRubro, es el limite de array
 * \param pArrayPublicaciones, es el array de publicaciones
 * \param publicacionesLen, es el limite de array
 * \param pResultado: El puntero a int donde se guardara el numero de Rubro que aparece en mas avisos
 * \return (-1) Error (0) OK
 */
int informe_imprimirRubros(sRubro* pArrayRubro, int rubrosLen)
{
  int retorno = -1;
  int i;

  if(pArrayRubro != NULL && rubrosLen > 0)
  {
    for(i=0; i<rubrosLen; i++)
    {
    	if(pArrayRubro[i].isEmpty == FALSE)
    	{
				printf("Indice: %d - Rubro: %d\n", i, pArrayRubro[i].rubro);
    	}
    }
  }
  return retorno;
}

//----------------------- informe_rubroOrdenarPorNombre --------------------------------------
/**
 * \brief Ordena los clientes cargados en un orden determinado
 * \param sCliente* pArrayClientes, Es el puntero al array de clientes
 * \param int limite, es el limite de array
 * \return (-1) Error / (0) Ok
 *
*/
int informe_ordenarRubroMenorAMayor(sRubro* pArrayRubro, int rubrosLen, sPublicacion* pArrayPublicaciones)
{
	int retorno = -1;
	int i;
	sRubro auxRubro;
	int flagEstadoDesordenado=1;

	rubro_generarRubros(pArrayRubro, rubrosLen, pArrayPublicaciones);
	if(pArrayRubro != NULL && rubrosLen > 0 && pArrayPublicaciones != NULL)
	{
		while(flagEstadoDesordenado==1)// no esta ordenado
		{
			flagEstadoDesordenado=0;
			// la pasadita
			for(i=0 ; i<(rubrosLen-1) ;i++)
			{
				if(pArrayRubro[i].rubro > pArrayRubro[i+1].rubro)
				{
					// intercambiar (swap)
					auxRubro = pArrayRubro[i];
					pArrayRubro[i] = pArrayRubro[i+1];
					pArrayRubro[i+1] = auxRubro;
					flagEstadoDesordenado = 1;
				}
			}
		}
		retorno = 0;
	}
	return retorno;
}

//----------------------- informe_imprimirPublicacionesPorIdCliente --------------------------------------------
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
        bufferIndiceCliente = cliente_buscarPorId(pArrayClientes, clientesLen, getIdCliente);
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
        bufferIndicePublicacion = publicacion_buscarPorId(pArrayPublicaciones, publicacionesLen, getIdPublicacion);
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

  if(pArrayPublicaciones != NULL && publicacionesLen > 0 && pArrayClientes != NULL && clientesLen > 0)
  {
    printf("\n=============== Listado de Clientes ==========================\n");
    cliente_imprimir(pArrayClientes, clientesLen);
    printf("\n==============================================================\n");

    if(utn_getInt(&auxIdCliente, "Indique Id del cliente para dar de baja: ", "Error! ", 0, 1000, RETRY)==0)
    {
      auxIndice = cliente_buscarPorId(pArrayClientes, clientesLen, auxIdCliente);
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
  }
  return retorno;
}

//----------------------- informe_pausarPublicacion --------------------------------------------
/**
 * \brief Baja el cliente con sus publicaciones
 * \param sPublicacion* pArrayPublicaciones, es el array de publicaciones
 * \param int lenPublicaciones, es el limite de array
 * \param sCliente* pArrayClientes, Es el puntero al array de clientes
 * \param int clientesLen, es el limite de array
 * \return (-1) Error / (0) Ok
 *
*/
int informe_pausarPublicacion(sPublicacion* pArrayPublicaciones, int publicacionesLen, sCliente* pArrayClientes, int clientesLen)
{
	int retorno = -1;
	int auxIdPublicacion;
	int auxIndiceId;

	if(pArrayPublicaciones != NULL && publicacionesLen > 0 && pArrayClientes != NULL && clientesLen > 0)
	{
		printf("\n=============== Listado de Publicaciones =====================\n");
		  publicacion_imprimir(pArrayPublicaciones, publicacionesLen);
		  printf("\n=======================================================\n");
		  if(utn_getInt(&auxIdPublicacion, "Indique id de la publicacion: ", "Error! ", 1, 1000, RETRY) == 0)
		  {
		  	auxIndiceId = publicacion_buscarPorId(pArrayPublicaciones, publicacionesLen, auxIdPublicacion);
		  	if(auxIndiceId == 0)
		  	{
					if(pArrayPublicaciones[auxIndiceId].estado == TRUE)
					{
						printf("**Ingreso correcto de id**\n");
						printf("\n========== Informacion del Cliente de la publicacion ==============\n");
						informe_imprimirPublicacionPorSuId(pArrayPublicaciones, publicacionesLen, pArrayClientes, clientesLen, auxIdPublicacion);
						printf("\n===========================================================\n");

						if(publicacion_estadoPausado(pArrayPublicaciones, publicacionesLen, auxIdPublicacion) == 0)
						{
							printf("**Publicacion pausada correctamente**\n");
						}
						else
						{
							printf("**Publicacion no modificada**\n");
						}
					}
					else
					{
						printf("**La publicación ya estaba pausada!**\n");
					}
		  	}
		  	else
		  	{
		  		printf("**La publicación no existe!**\n");
		  	}
		  }
		  else
		  {
		    printf("**Error en ingreso de id**\n");
		  }
	}
	return retorno;
}

//----------------------- informe_reanudarPublicacion --------------------------------------------
/**
 * \brief Reanuda el cliente con sus publicaciones
 * \param sPublicacion* pArrayPublicaciones, es el array de publicaciones
 * \param int lenPublicaciones, es el limite de array
 * \param sCliente* pArrayClientes, Es el puntero al array de clientes
 * \param int clientesLen, es el limite de array
 * \return (-1) Error / (0) Ok
 *
*/
int informe_reanudarPublicacion(sPublicacion* pArrayPublicaciones, int publicacionesLen, sCliente* pArrayClientes, int clientesLen)
{
	int retorno = -1;
	int auxIdPublicacion;
	int auxIndiceId;

	if(pArrayPublicaciones != NULL && publicacionesLen > 0 && pArrayClientes != NULL && clientesLen > 0)
	{
		printf("\n=============== Listado de Publicaciones =====================\n");
		  publicacion_imprimir(pArrayPublicaciones, publicacionesLen);
		  printf("\n=======================================================\n");
		  if(utn_getInt(&auxIdPublicacion, "Indique id de la publicacion: ", "Error! ", 1, 1000, RETRY) == 0)
		  {
		  	auxIndiceId = publicacion_buscarPorId(pArrayPublicaciones, publicacionesLen, auxIdPublicacion);
		  	if(auxIndiceId == 0)
		  	{
					if(pArrayPublicaciones[auxIndiceId].estado == FALSE)
					{
						printf("**Ingreso correcto de id**\n");
						printf("\n========== Informacion del Cliente de la publicacion ==============\n");
						informe_imprimirPublicacionPorSuId(pArrayPublicaciones, publicacionesLen, pArrayClientes, clientesLen, auxIdPublicacion);
						printf("\n===========================================================\n");

						if(publicacion_estadoActivo(pArrayPublicaciones, publicacionesLen, auxIdPublicacion) == 0)
						{
							printf("**Publicacion activada correctamente**\n");
						}
						else
						{
							printf("**Publicacion no modificada**\n");
						}
					}
					else
					{
						printf("**La publicación ya estaba activada!**\n");
					}
		  	}
		  	else
		  	{
		  		printf("**La publicación no existe!**\n");
		  	}
		  }
		  else
		  {
		    printf("**Error en ingreso de id**\n");
		  }
	}
	return retorno;
}

//----------------------- informe_imprimirClientesConTotalAvisosActivos --------------------------------------------
/**
 * \brief Imprime listado de los clientes con el total de avisos activos
 * \param sPublicacion* pArrayPublicaciones, es el array de publicaciones
 * \param int lenPublicaciones, es el limite de array
 * \param sCliente* pArrayClientes, Es el puntero al array de clientes
 * \param int clientesLen, es el limite de array
 * \return (-1) Error / (0) Ok
 *
*/
int informe_imprimirClientesConTotalAvisosActivos(sPublicacion* pArrayPublicaciones, int publicacionesLen, sCliente* pArrayClientes, int clientesLen)
{
	int retorno = -1;
	int contadorAvisos = 0;
	int i;
	int k;

	if(pArrayPublicaciones != NULL  && publicacionesLen > 0 && pArrayClientes != NULL && clientesLen > 0)
	{
		for(i=0; i<clientesLen; i++)
		{
			if(pArrayClientes[i].isEmpty == FALSE)
			{
				for(k=0; k<publicacionesLen; k++)
				{
					if(pArrayClientes[i].idCliente == pArrayPublicaciones[k].idCliente &&
						 pArrayPublicaciones[k].isEmpty == FALSE &&
						 pArrayPublicaciones[k].estado == TRUE)
					{
						contadorAvisos++;
					}
				}
				if(contadorAvisos > 0)
				{
	        printf("\nId CLiente: %d - Nombre: %s - Apellido: %s - Cuit: %s - Avisos activos: %d",
	        			 pArrayClientes[i].idCliente,
	               pArrayClientes[i].nombre,
	               pArrayClientes[i].apellido,
	               pArrayClientes[i].cuit,
								 contadorAvisos);
	        retorno = 0;
				}
				contadorAvisos = 0;
			}
		}
	}
	return retorno;
}

//----------------------- informe_contadorPublicacionesPorIdCliente --------------------------------------------
/**
 * \brief calcula la cantidad total por el id cliente
 * \param sPublicacion* pArrayPublicaciones, es el array de publicaciones
 * \param int lenPublicaciones, es el limite de array
 * \param int idCliente, id cliente a comparar
 * \param int *contadorAvisos, Es el puntero del contador de avisos
 * \return (-1) Error / (0) Ok
 *
*/
int informe_contadorAvisosPorIdCliente(sPublicacion* pArrayPublicaciones, int publicacionesLen, int idCliente, int* contador)
{
	int retorno = -1;
	int auxContador = 0;
	int i;

	if(pArrayPublicaciones != NULL && publicacionesLen > 0 && idCliente > 0 && contador != NULL)
	{
		for(i=0; i<publicacionesLen; i++)
		{
			if(pArrayPublicaciones[i].isEmpty == FALSE &&
				 idCliente == pArrayPublicaciones[i].idCliente)
			{
				auxContador++;
				*contador = auxContador;
				retorno = 0;
			}
		}
	}
	return retorno;
}

//----------------------- informe_clientesConMasAvisos --------------------------------------------
/**
 * \brief calcula el cliente con mas avisos
 * \param sPublicacion* pArrayPublicaciones, es el array de publicaciones
 * \param int lenPublicaciones, es el limite de array
 * \param sCliente* pArrayClientes, Es el puntero al array de clientes
 * \param int* bufferIndice, es el puntero al indice del cliente
 * \param int *contador, Es el puntero del contador de avisos maximo
 * \return (-1) Error / (0) Ok
 *
*/
int informe_clientesConMasAvisos(sPublicacion* pArrayPublicaciones, int publicacionesLen, sCliente* pArrayClientes, int clientesLen, int* bufferIndice, int* contador)
{
	int retorno = -1;
	int auxContador;
	int maximo;
	int i;

	if(pArrayPublicaciones != NULL && publicacionesLen > 0 && pArrayClientes != NULL && clientesLen > 0 && bufferIndice!= NULL && contador != NULL)
	{
		for(i=0; i<clientesLen; i++)
		{
			if( pArrayClientes[i].isEmpty == FALSE &&
				  informe_contadorAvisosPorIdCliente(pArrayPublicaciones, publicacionesLen, pArrayClientes[i].idCliente, &auxContador) == 0 )
			{
				if(i == 0 || maximo < auxContador)
				{
					maximo = auxContador;
					*bufferIndice = i;
					*contador = maximo;
					retorno = 0;
				}
			}
		}
	}
	return retorno;
}

//----------------------- informe_cantidadDeAvisosPausados --------------------------------------------
/**
 * \brief calcula la cantidad de avisos pausados
 * \param sPublicacion* pArrayPublicaciones, es el array de publicaciones
 * \param int lenPublicaciones, es el limite de array
 * \param int *contador, Es el puntero del contador de avisos pausados
 * \return (-1) Error / (0) Ok
 *
*/
int informe_cantidadDeAvisosPausados(sPublicacion* pArrayPublicaciones, int publicacionesLen, int* contador)
{
  int retorno = -1;
  int auxContador = 0;

  for(int i = 0; i< publicacionesLen; i++)
  {
    if(pArrayPublicaciones[i].isEmpty == FALSE &&
    	 pArrayPublicaciones[i].estado == FALSE)
    {
    	auxContador++;
      retorno = 0;
    }
  }
  *contador = auxContador;
  return retorno;
}

//----------------------- informe_contadorAvisosActivosPorIdCliente --------------------------------------------
/**
 * \brief calcula la cantidad total de avisos activos por el id cliente
 * \param sPublicacion* pArrayPublicaciones, es el array de publicaciones
 * \param int lenPublicaciones, es el limite de array
 * \param int idCliente, id cliente a comparar
 * \param int *contadorAvisos, Es el puntero del contador de avisos
 * \return (-1) Error / (0) Ok
 *
*/
int informe_contadorAvisosActivosPorIdCliente(sPublicacion* pArrayPublicaciones, int publicacionesLen, int idCliente, int *contador)
{
	int retorno = -1;
	int auxContador = 0;
	int i;

	if(pArrayPublicaciones != NULL && publicacionesLen > 0 && idCliente >= 0 && contador != NULL)
	{
		for(i=0; i<publicacionesLen; i++)
		{
			if( pArrayPublicaciones[i].isEmpty == FALSE &&
				  idCliente == pArrayPublicaciones[i].idCliente &&
					pArrayPublicaciones[i].estado == ACTIVO )
			{
				auxContador++;
				*contador = auxContador;
				retorno = 0;
			}
		}
	}
	return retorno;
}

//----------------------- informe_clienteConMasAvisosActivos --------------------------------------------
/**
 * \brief calcula el cliente con mas avisos
 * \param sPublicacion* pArrayPublicaciones, es el array de publicaciones
 * \param int lenPublicaciones, es el limite de array
 * \param sCliente* pArrayClientes, Es el puntero al array de clientes
 * \param int* bufferIndice, es el puntero al indice del cliente
 * \param int *contador, Es el puntero del contador de avisos maximo
 * \return (-1) Error / (0) Ok
 *
*/
int informe_clienteConMasAvisosActivos(sPublicacion* pArrayPublicaciones,int publicacionesLen,sCliente* pArrayClientes,int clientesLen,int* bufferIndex,int* contador)
{
  int retorno = -1;
  int auxContador;
  int maximo;
  int i;

  if(pArrayPublicaciones != NULL && publicacionesLen > 0 && pArrayClientes != NULL && clientesLen > 0 && bufferIndex != NULL && contador != NULL)
  {
    for(i=0; i<clientesLen; i++)
    {
      if( pArrayClientes[i].isEmpty == FALSE &&
      		informe_contadorAvisosActivosPorIdCliente(pArrayPublicaciones, publicacionesLen, pArrayClientes[i].idCliente, &auxContador) == 0)
      {
        if(i == 0 || maximo < auxContador)
        {
        	maximo = auxContador;
          *bufferIndex = i;
          *contador = maximo;
          retorno = 0;
        }
      }
    }
  }
  return retorno;
}

//----------------------- informe_contadorAvisosPausadosPorIdCliente --------------------------------------------
/**
 * \brief calcula la cantidad total de avisos activos por el id cliente
 * \param sPublicacion* pArrayPublicaciones, es el array de publicaciones
 * \param int lenPublicaciones, es el limite de array
 * \param int idCliente, id cliente a comparar
 * \param int *contadorAvisos, Es el puntero del contador de avisos
 * \return (-1) Error / (0) Ok
 *
*/
int informe_contadorAvisosPausadosPorIdCliente(sPublicacion* pArrayPublicaciones, int publicacionesLen, int idCliente, int *contador)
{
	int retorno = -1;
	int auxContador = 0;
	int i;

	if(pArrayPublicaciones != NULL && publicacionesLen > 0 && idCliente >= 0 && contador != NULL)
	{
		for(i=0; i<publicacionesLen; i++)
		{
			if( pArrayPublicaciones[i].isEmpty == FALSE &&
					pArrayPublicaciones[i].estado == PAUSADO &&
				  idCliente == pArrayPublicaciones[i].idCliente )
			{
				auxContador++;
				*contador = auxContador;
				retorno = 0;
			}
		}
	}
	return retorno;
}

//----------------------- informe_clienteConMasAvisosPausados --------------------------------------------
/**
 * \brief calcula el cliente con mas avisos pausados
 * \param sPublicacion* pArrayPublicaciones, es el array de publicaciones
 * \param int lenPublicaciones, es el limite de array
 * \param sCliente* pArrayClientes, Es el puntero al array de clientes
 * \param int* bufferIndice, es el puntero al indice del cliente
 * \param int *contador, Es el puntero del contador de avisos maximo
 * \return (-1) Error / (0) Ok
 *
*/
int informe_clienteConMasAvisosPausados(sPublicacion* pArrayPublicaciones,int publicacionesLen,sCliente* pArrayClientes,int clientesLen,int* bufferIndex,int* contador)
{
  int retorno = -1;
  int auxContador;
  int maximo;
  int i;

  if(pArrayPublicaciones != NULL && publicacionesLen > 0 && pArrayClientes != NULL && clientesLen > 0 && bufferIndex != NULL && contador != NULL)
  {
    for(i=0; i<clientesLen; i++)
    {
      if( pArrayClientes[i].isEmpty == FALSE &&
      		informe_contadorAvisosPausadosPorIdCliente(pArrayPublicaciones, publicacionesLen, pArrayClientes[i].idCliente, &auxContador) == 0)
      {
        if(i == 0 || maximo < auxContador)
        {
        	maximo = auxContador;
          *bufferIndex = i;
          *contador = maximo;
          retorno = 0;
        }
      }
    }
  }
  return retorno;
}

//----------------------- informe_cantidadAvisosActivosTotales--------------------------------------------
/**
 * \brief calcula la cantidad total de avisos activos
 * \param sPublicacion* pArrayPublicaciones, es el array de publicaciones
 * \param int lenPublicaciones, es el limite de array
 * \param int idCliente, id cliente a comparar
 * \param int *contadorAvisos, Es el puntero del contador de avisos
 * \return (-1) Error / (0) Ok
 *
*/
int informe_cantidadAvisosActivosTotales(sPublicacion* pArrayPublicaciones, int publicacionesLen, int *contador)
{
	int retorno = -1;
	int auxContador = 0;
	int i;

	if(pArrayPublicaciones != NULL && publicacionesLen > 0 && contador != NULL)
	{
		for(i=0; i<publicacionesLen; i++)
		{
			if( pArrayPublicaciones[i].isEmpty == FALSE &&
					pArrayPublicaciones[i].estado == ACTIVO)
			{
				auxContador++;
				*contador = auxContador;
				retorno = 0;
			}
		}
	}
	return retorno;
}

//----------------------- informe_clienteConMenosAvisos --------------------------------------------
/**
 * \brief calcula el cliente con menos avisos
 * \param sPublicacion* pArrayPublicaciones, es el array de publicaciones
 * \param int lenPublicaciones, es el limite de array
 * \param sCliente* pArrayClientes, Es el puntero al array de clientes
 * \param int* bufferIndice, es el puntero al indice del cliente
 * \param int *contador, Es el puntero del contador de avisos maximo
 * \return (-1) Error / (0) Ok
 *
*/
int informe_clienteConMenosAvisos(sPublicacion* pArrayPublicaciones,int publicacionesLen,sCliente* pArrayClientes,int clientesLen,int* bufferIndex,int* contador)
{
  int retorno = -1;
  int auxContador;
  int minimo;
  int i;

  if(pArrayPublicaciones != NULL && publicacionesLen > 0 && pArrayClientes != NULL && clientesLen > 0 && bufferIndex != NULL && contador != NULL)
  {
    for(i=0; i<clientesLen; i++)
    {
      if( pArrayClientes[i].isEmpty == FALSE &&
      		informe_contadorAvisosPorIdCliente(pArrayPublicaciones, publicacionesLen, pArrayClientes[i].idCliente, &auxContador) == 0)
      {
        if(i == 0 || minimo > auxContador)
        {
        	minimo = auxContador;
          *bufferIndex = i;
          *contador = minimo;
          retorno = 0;
        }
      }
    }
  }
  return retorno;
}

//----------------------- informe_contadorAvisosPorRubro --------------------------------------------
/**
 * \brief cuenta todas las publicaciones por el numero de rubro indicado
 * \param sPublicacion* pArrayPublicaciones, es el array de publicaciones
 * \param int lenPublicaciones, es el limite de array
 * \param sCliente* pArrayClientes, es el array del cliente
 * \param int lenClientes, es el limite de array
 * \param int getIdCliente, es el id solicitado
 * \return (-1) Error / (0) Ok
 *
*/
int informe_contadorAvisosPorRubro(sPublicacion* pArrayPublicaciones, int publicacionesLen, int getRubro, int* contador)
{
  int retorno = -1;
  int i;
  int auxContador=0;
  if(pArrayPublicaciones != NULL && publicacionesLen > 0 && getRubro >= 0)
  {
    for(i=0; i<publicacionesLen; i++)
    {
      if(pArrayPublicaciones[i].isEmpty == FALSE &&
         pArrayPublicaciones[i].numeroRubro == getRubro)
      {
      	auxContador++;
      	*contador = auxContador;
        retorno = 0;
      }
    }
  }
  return retorno;
}

//----------------------- informe_imprimirAvisosPorRubro --------------------------------------------
/**
 * \brief Imprimi todas las publicaciones por el numero de rubro indicado
 * \param sPublicacion* pArrayPublicaciones, es el array de publicaciones
 * \param int lenPublicaciones, es el limite de array
 * \param sCliente* pArrayClientes, es el array del cliente
 * \param int lenClientes, es el limite de array
 * \param int getIdCliente, es el id solicitado
 * \return (-1) Error / (0) Ok
 *
*/
int informe_imprimirAvisosPorRubro(sPublicacion* pArrayPublicaciones, int publicacionesLen, int getRubro)
{
  int retorno = -1;
  int i;
  //int bufferIndiceRubro;
  if(pArrayPublicaciones != NULL && publicacionesLen > 0 && getRubro >= 0)
  {
    for(i=0; i<publicacionesLen; i++)
    {
      if(pArrayPublicaciones[i].isEmpty == FALSE &&
         pArrayPublicaciones[i].numeroRubro == getRubro)
      {
      	//bufferIndiceRubro = publicacion_buscarPorRubro(pArrayPublicaciones, publicacionesLen, getRubro);
        printf("\nNumero rubro: %d - Id CLiente: %d - Texto publicacion: %s - Id Publicacion: %d - Estado: %d",
               pArrayPublicaciones[i].numeroRubro,
               pArrayPublicaciones[i].idCliente,
               pArrayPublicaciones[i].textoPublicacion,
               pArrayPublicaciones[i].idPublicacion,
               pArrayPublicaciones[i].estado);
        retorno = 0;
      }
    }
  }
  return retorno;
}

//----------------------- informe_contadorAvisosPorCuit --------------------------------------------
/**
 * \brief cuenta todas las publicaciones por el numero de cuit indicado
 * \param sPublicacion* pArrayPublicaciones, es el array de publicaciones
 * \param int lenPublicaciones, es el limite de array
 * \param sCliente* pArrayClientes, es el array del cliente
 * \param int lenClientes, es el limite de array
 * \param int getIdCliente, es el id solicitado
 * \return (-1) Error / (0) Ok
 *
*/
int informe_contadorAvisosPorCuit(sPublicacion* pArrayPublicaciones, int publicacionesLen, sCliente* pArrayClientes, int clientesLen, char* getCuit, int* contador)
{
  int retorno = -1;
  int i;
  int auxContador=0;
  int bufferIndice;

  if(pArrayPublicaciones != NULL && publicacionesLen > 0 && getCuit != NULL)
  {
  	bufferIndice = cliente_buscarPorCuit(pArrayClientes, clientesLen, getCuit);
  	if(bufferIndice != -1)
  	{
      for(i=0; i<publicacionesLen; i++)
      {
        if( pArrayPublicaciones[i].isEmpty == FALSE &&
        		pArrayPublicaciones[i].idCliente == pArrayClientes[bufferIndice].idCliente)
        {
        	auxContador++;
        	*contador = auxContador;
          retorno = 0;
        }
      }
  	}
  }
  return retorno;
}

//----------------------- informe_imprimirAvisosPorCuit --------------------------------------------
/**
 * \brief Imprimi todas las publicaciones por el numero de rubro indicado
 * \param sPublicacion* pArrayPublicaciones, es el array de publicaciones
 * \param int lenPublicaciones, es el limite de array
 * \param sCliente* pArrayClientes, es el array del cliente
 * \param int lenClientes, es el limite de array
 * \param int getIdCliente, es el id solicitado
 * \return (-1) Error / (0) Ok
 *
*/
int informe_imprimirAvisosPorCuit(sPublicacion* pArrayPublicaciones, int publicacionesLen, sCliente* pArrayClientes, int clientesLen, char* getCuit)
{
  int retorno = -1;
  int i;
  int bufferIdCliente;

  if(pArrayPublicaciones != NULL && publicacionesLen > 0 && getCuit != NULL)
  {
  	bufferIdCliente = cliente_buscarPorCuit(pArrayClientes, clientesLen, getCuit);
    for(i=0; i<publicacionesLen; i++)
    {
      if(pArrayPublicaciones[i].isEmpty == FALSE &&
         pArrayPublicaciones[i].idCliente == bufferIdCliente)
      {
        printf("\nNumero rubro: %d - Id CLiente: %d - Texto publicacion: %s - Id Publicacion: %d - Estado: %d",
               pArrayPublicaciones[i].numeroRubro,
               pArrayPublicaciones[i].idCliente,
               pArrayPublicaciones[i].textoPublicacion,
               pArrayPublicaciones[i].idPublicacion,
               pArrayPublicaciones[i].estado);
        retorno = 0;
      }
    }
  }
  return retorno;
}

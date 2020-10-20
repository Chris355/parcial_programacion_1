/*
 ============================================================================
 Name        : Parcial_1.c
 Author      : Christian Silvero
 ============================================================================
 */

#include <stdio.h>
#include <stdlib.h>
#include "utn.h"
#include "cliente.h"
#include "publicacion.h"
#include "informe.h"

#define MIN_MENU 1
#define MAX_MENU 9
#define MAX_SUBMENU 11

int main(void)
{
  int opcion;
  int auxIdCliente;
  int auxIndice;
  int auxRubro;
  char auxCuit[SIZE_CUIT];
  int contador;
  int idCliente=10;
  int idPublicaciones=10;
  sCliente arrayClientes[QTY_CLIENTES];
  sPublicacion arrayPublicaciones[QTY_PUBLICACIONES];
  sRubro arrayRubros[QTY_RUBROS];

  char mensajeErrorMenu[SIZE_STRING] = "Error! opcion invalida.\n";
  char mensajeMenu[SIZE_STRING] = "\n"
                                  "\n===== Menú de Opciones ===== "
                                  "\n 1 - Alta de cliente "
                                  "\n 2 - Modificar cliente por ID "
                                  "\n 3 - Baja cliente por ID "
                                  "\n 4 - Publicar "
                                  "\n 5 - Pausar publicacion"
                                  "\n 6 - Reaunudar publicacion "
                                  "\n 7 - Imprimir clientes "
                                  "\n 8 - Informar "
                                  "\n 9 - Salir"
                                  "\n============================ "
                                  "\n";
  char mensajeSubMenu[SIZE_STRING] = "\n"
                                  "\n===== Informar ============= "
                                  "\n 1 - Cliente con más publicaciones "
                                  "\n 2 - Cantidad de publicaciones pausados "
                                  "\n 3 - Rubro con mas publicaciones "
      														"\n 4 - Cliente con más avisos activos "
      														"\n 5 - Cliente con más avisos pausados "
																	"\n 6 - Lista de rubros ordenados de menor a mayor"
																	"\n 7 - Cantidad de avisos activos totales "
																	"\n 8 - Cliente con menos avisos "
																	"\n 9 - Cantidad por rubro "
																	"\n10 - Cantidad por cliente "
                                  "\n11 - Salir"
                                  "\n============================ "
                                  "\n";

  cliente_initArray(arrayClientes, QTY_CLIENTES);
  publicacion_initArray(arrayPublicaciones, QTY_PUBLICACIONES);


  cliente_altaForzadaArray(arrayClientes, QTY_CLIENTES, 0, &idCliente, "Andres", "Florida", "20-22000022-2");
  cliente_altaForzadaArray(arrayClientes, QTY_CLIENTES, 1, &idCliente, "Maria", "Perez", "27-33000033-3");
  cliente_altaForzadaArray(arrayClientes, QTY_CLIENTES, 2, &idCliente, "Bart", "Mitre", "20-11000011-1");
  cliente_altaForzadaArray(arrayClientes, QTY_CLIENTES, 3, &idCliente, "Chris", "Silvero", "1234");

  publicacion_altaForzada(arrayPublicaciones, QTY_PUBLICACIONES, 0, &idPublicaciones, 10, "Publicacion del rubro 1", 1, PAUSADO);
  publicacion_altaForzada(arrayPublicaciones, QTY_PUBLICACIONES, 1, &idPublicaciones, 12, "Publicacion del rubro 10", 10, ACTIVO);
  publicacion_altaForzada(arrayPublicaciones, QTY_PUBLICACIONES, 2, &idPublicaciones, 13, "Publicacion del rubro 2", 2, ACTIVO);
  publicacion_altaForzada(arrayPublicaciones, QTY_PUBLICACIONES, 3, &idPublicaciones, 11, "Publicacion del rubro 5", 5, ACTIVO);
  publicacion_altaForzada(arrayPublicaciones, QTY_PUBLICACIONES, 4, &idPublicaciones, 10, "Publicacion del rubro 10", 10, PAUSADO);
  publicacion_altaForzada(arrayPublicaciones, QTY_PUBLICACIONES, 5, &idPublicaciones, 11, "Publicacion del rubro 15", 15, ACTIVO);
  publicacion_altaForzada(arrayPublicaciones, QTY_PUBLICACIONES, 6, &idPublicaciones, 13, "Publicacion del rubro 2", 2, ACTIVO);
  publicacion_altaForzada(arrayPublicaciones, QTY_PUBLICACIONES, 7, &idPublicaciones, 10, "Publicacion del rubro 1", 1, PAUSADO);
  publicacion_altaForzada(arrayPublicaciones, QTY_PUBLICACIONES, 8, &idPublicaciones, 10, "Publicacion del rubro 2", 2, ACTIVO);
  publicacion_altaForzada(arrayPublicaciones, QTY_PUBLICACIONES, 9, &idPublicaciones, 13, "Publicacion del rubro 1", 1, PAUSADO);

  do
  {
    if(utn_getInt(&opcion, mensajeMenu, mensajeErrorMenu, MIN_MENU, MAX_MENU, RETRY)==0)
    {
      switch(opcion)
      {
        case 1: //ALTA CLIENTE
          auxIdCliente = cliente_alta(arrayClientes, QTY_CLIENTES);
          if(auxIdCliente != -1)
          {
            cliente_imprimirPorId(arrayClientes, QTY_CLIENTES, auxIdCliente);
            printf("**Ingreso correcto**\n");
          }
          else
          {
            printf("**Error en ingreso**\n");
          }
        break;
        case 2: //MODIFICAR CLIENTE
          printf("\n=============== Listado de Clientes ===================\n");
          cliente_imprimir(arrayClientes, QTY_CLIENTES);
          printf("\n=======================================================\n");
          auxIdCliente = cliente_modificar(arrayClientes, QTY_CLIENTES);
          if(auxIdCliente != -1)
          {
            cliente_imprimirPorId(arrayClientes, QTY_CLIENTES, auxIdCliente);
            printf("**Modificación correcta**\n");
          }
          else
          {
            printf("**Error en la modificación**\n");
          }
        break;
        case 3:	//BAJA CLIENTE
          informe_bajaClientePublicacion(arrayPublicaciones,QTY_PUBLICACIONES,arrayClientes,QTY_CLIENTES);
        break;
        case 4: //PUBLICAR
          printf("\n=============== Listado de Clientes ===================\n");
          cliente_imprimir(arrayClientes, QTY_CLIENTES);
          printf("\n=======================================================\n");
          if(utn_getInt(&auxIdCliente, "Id cliente? ", "Error! ", 0, 100, RETRY) == 0 &&
             cliente_buscarPorId(arrayClientes, QTY_CLIENTES, auxIdCliente) != -1)
          {
            printf("\n**Id valido**\n");
            if(publicacion_alta(arrayPublicaciones, QTY_PUBLICACIONES, auxIdCliente) == 0)
            {
              printf("**Ingreso correcto**\n");
              printf("\n========== Listado de publicaciones del Cliente ==============\n");
              informe_imprimirPublicacionesPorIdCliente(arrayPublicaciones, QTY_PUBLICACIONES, arrayClientes, QTY_CLIENTES, auxIdCliente);
              printf("\n=======================================================\n");
            }
            else
            {
              printf("**Error en ingreso**\n");
            }
          }
          else
          {
            printf("**Id invalido**\n");
          }
          break;
        case 5: //PAUSAR PUBLICACION
        	informe_pausarPublicacion(arrayPublicaciones, QTY_PUBLICACIONES, arrayClientes, QTY_CLIENTES);
          break;
        case 6: //REANUDAR PUBLICACION
        	informe_reanudarPublicacion(arrayPublicaciones, QTY_PUBLICACIONES, arrayClientes, QTY_CLIENTES);
          break;
        case 7: //IMPRIMIR CLIENTES
          informe_imprimirClientesConTotalAvisosActivos(arrayPublicaciones, QTY_PUBLICACIONES, arrayClientes, QTY_CLIENTES);
          break;
        case 8: //INFORMAR
          if(utn_getInt(&opcion, mensajeSubMenu, mensajeErrorMenu, MIN_MENU, MAX_SUBMENU, RETRY)==0)
          {
            switch(opcion)
            {
              case 1: //Cliente con más publicaciones
              	if(informe_clientesConMasAvisos(arrayPublicaciones, QTY_PUBLICACIONES, arrayClientes, QTY_CLIENTES, &auxIndice, &contador)==0)
              	{
              		printf("\nEl cliente con mas publicaciones es %s %s - Total: %d\n",
              				arrayClientes[auxIndice].nombre, arrayClientes[auxIndice].apellido, contador);
              	}
                break;
              case 2: //Cantidad de publicaciones pausados
              	publicacion_imprimir(arrayPublicaciones, QTY_PUBLICACIONES);
              	if(informe_cantidadDeAvisosPausados(arrayPublicaciones, QTY_PUBLICACIONES, &contador)==0)
              	{
              		printf("\nLa cantidad de avisos pausados es: %d\n", contador);
              	}
                break;
              case 3: //Rubro con mas publicaciones
              	if(informe_rubroConMasAvisos(arrayRubros, QTY_RUBROS, arrayPublicaciones, QTY_PUBLICACIONES, &auxRubro, &contador)==0)
              	{
              		printf("\nEl rubro con mas publicaciones es el %d - Total: %d\n", auxRubro, contador);
              	}
                break;
              case 4: //Cliente con más avisos activos
              	if(informe_clienteConMasAvisosActivos(arrayPublicaciones, QTY_PUBLICACIONES, arrayClientes, QTY_CLIENTES, &auxIndice, &contador)==0)
              	{
              		printf("\nEl cliente con mas publicaciones activas es %s %s - Total: %d\n",
              				arrayClientes[auxIndice].nombre, arrayClientes[auxIndice].apellido, contador);
              	}
                break;
              case 5: //Cliente con más avisos pausados
              	if(informe_clienteConMasAvisosPausados(arrayPublicaciones, QTY_PUBLICACIONES, arrayClientes, QTY_CLIENTES, &auxIndice, &contador)==0)
              	{
              		printf("\nEl cliente con mas publicaciones pausadas es %s %s - Total: %d\n",
              				arrayClientes[auxIndice].nombre, arrayClientes[auxIndice].apellido, contador);
              	}
                break;
              case 6: //Imprimir lista de rubros ordenados
              	if(informe_ordenarRubroMenorAMayor(arrayRubros, QTY_RUBROS, arrayPublicaciones)==0)
              	{
              		informe_imprimirRubros(arrayRubros, QTY_RUBROS);
              	}
                break;
              case 7: //Cantidad de avisos activos totales
              	if(informe_cantidadAvisosActivosTotales(arrayPublicaciones, QTY_PUBLICACIONES, &contador)==0)
              	{
              		printf("\nLa cantidad de avisos activos totales es: %d\n", contador);
              	}
                break;
              case 8: //Cliente con menos avisos
              	if(informe_clienteConMenosAvisos(arrayPublicaciones, QTY_PUBLICACIONES, arrayClientes, QTY_CLIENTES, &auxIndice, &contador)==0)
              	{
              		printf("\nEl cliente con menos avisos es %s %s - Total: %d\n",
              				arrayClientes[auxIndice].nombre, arrayClientes[auxIndice].apellido, contador);
              	}
                break;
              case 9: //Cantidad por rubro: Ingresar por consola un numero de rubro e imprimir la cantidad de avisos que existen de dicho rubro.
              	if(utn_getInt(&auxRubro, "Indique rubro del 1/50: ", "Error!", 1, 50, RETRY)==0)
              	{
              		if(informe_contadorAvisosPorRubro(arrayPublicaciones, QTY_PUBLICACIONES, auxRubro, &contador)==0)
              		{
              			printf("\nLa cantidad de avisos del RUBRO %d es: %d\n", auxRubro, contador);
              			informe_imprimirAvisosPorRubro(arrayPublicaciones, QTY_PUBLICACIONES, auxRubro);
              		}
              	}
                break;
              case 10: //Cantidad por cliente: Ingresar por consola un cuit e imprimir la cantidad de avisos que existen de dicho cliente.
              	if(utn_getCuit(auxCuit, "Cuit? ", "Error", RETRY, SIZE_CUIT) == 0)
              	{
              		if(informe_contadorAvisosPorCuit(arrayPublicaciones, QTY_PUBLICACIONES, arrayClientes, QTY_CLIENTES, auxCuit, &contador)==0)
              		{
              			printf("\nLa cantidad de avisos del CLIENTE %s es: %d\n", auxCuit, contador);
              			informe_imprimirAvisosPorCuit(arrayPublicaciones, QTY_PUBLICACIONES, arrayClientes, QTY_CLIENTES, auxCuit);
              		}
              	}
                break;
            }
          }
          break;
      }
    }
  }while(opcion != 9);

  return EXIT_SUCCESS;
}

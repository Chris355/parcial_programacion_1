/*
 ============================================================================
 Name        : Parcial_1.c
 Author      : Christian Silvero
 ============================================================================
 */

#include <stdio.h>
#include <stdlib.h>
#include "cliente.h"
#include "publicacion.h"
#include "utn.h"
#include "informe.h"

#define MIN_MENU 1
#define MAX_MENU 10
#define MAX_SUBMENU 4

int main(void)
{
  int opcion;
  int auxIdCliente;
  int auxIdPublicacion;
  int arrayIdsClientes[QTY_CLIENTES];
  int idCliente=1;
  int idPublicaciones=1;
  sCliente arrayClientes[QTY_CLIENTES];
  sPublicacion arrayPublicaciones[QTY_PUBLICACIONES];
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
                                  "\n 9 -  "
                                  "\n10 - Salir"
                                  "\n============================ "
                                  "\n";
  char mensajeSubMenu[SIZE_STRING] = "\n"
                                  "\n===== Informar ===== "
                                  "\n1 - Cliente con más publicaciones "
                                  "\n2 - Cantidad de publicaciones pausados "
                                  "\n3 - Rubro con mas publicaciones "
                                  "\n4 - Salir"
                                  "\n============================ "
                                  "\n";

  cliente_initArray(arrayClientes, QTY_CLIENTES);
  publicacion_initArray(arrayPublicaciones, QTY_PUBLICACIONES);


  cliente_altaForzadaArray(arrayClientes, QTY_CLIENTES, 0, &idCliente, "Andres", "Florida", "20-22000022-2");
  cliente_altaForzadaArray(arrayClientes, QTY_CLIENTES, 1, &idCliente, "Maria", "Perez", "27-33000033-3");
  cliente_altaForzadaArray(arrayClientes, QTY_CLIENTES, 2, &idCliente, "Bart", "Mitre", "20-11000011-1");
  cliente_altaForzadaArray(arrayClientes, QTY_CLIENTES, 3, &idCliente, "Chris", "Silvero", "20-31000031-1");


  publicacion_altaForzada(arrayPublicaciones, QTY_PUBLICACIONES, 0, &idPublicaciones, 2, "Publicacion del rubro 1", 1, FALSE);
  publicacion_altaForzada(arrayPublicaciones, QTY_PUBLICACIONES, 1, &idPublicaciones, 2, "Publicacion del rubro 10", 10, TRUE);
  publicacion_altaForzada(arrayPublicaciones, QTY_PUBLICACIONES, 2, &idPublicaciones, 3, "Publicacion del rubro 2", 2, TRUE);
  publicacion_altaForzada(arrayPublicaciones, QTY_PUBLICACIONES, 3, &idPublicaciones, 1, "Publicacion del rubro 5", 5, TRUE);
  publicacion_altaForzada(arrayPublicaciones, QTY_PUBLICACIONES, 4, &idPublicaciones, 3, "Publicacion del rubro 10", 10, FALSE);
  publicacion_altaForzada(arrayPublicaciones, QTY_PUBLICACIONES, 5, &idPublicaciones, 1, "Publicacion del rubro 15", 15, TRUE);
  publicacion_altaForzada(arrayPublicaciones, QTY_PUBLICACIONES, 6, &idPublicaciones, 3, "Publicacion del rubro 2", 2, TRUE);
  publicacion_altaForzada(arrayPublicaciones, QTY_PUBLICACIONES, 7, &idPublicaciones, 2, "Publicacion del rubro 1", 1, FALSE);
  publicacion_altaForzada(arrayPublicaciones, QTY_PUBLICACIONES, 6, &idPublicaciones, 4, "Publicacion del rubro 2", 2, TRUE);
  publicacion_altaForzada(arrayPublicaciones, QTY_PUBLICACIONES, 7, &idPublicaciones, 4, "Publicacion del rubro 1", 1, FALSE);


  do
  {
    if(utn_getInt(&opcion, mensajeMenu, mensajeErrorMenu, MIN_MENU, MAX_MENU, RETRY)==0)
    {
      switch(opcion)
      {
        case 1: //ALTA CLIENTE
          auxIdCliente = cliente_alta(arrayClientes, QTY_CLIENTES);
          if(auxIdCliente != 0)
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
          if(cliente_modificar(arrayClientes, QTY_CLIENTES)==0)
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
          printf("\n=============== Listado de Clientes ===================\n");
          cliente_imprimir(arrayClientes, QTY_CLIENTES);
          printf("\n=======================================================\n");
          if(utn_getInt(&auxIdCliente, "Id del cliente a listar publicaciones? ", "Error! ", 0, 1000, RETRY)==0)
          {
            cliente_buscarId(arrayClientes, QTY_CLIENTES, auxIdCliente);
            printf("**Ingreso correcto de ID**\n");
            printf("\n========== Listado de publicaciones del Cliente ==============\n");
            informe_imprimirPublicacionesPorIdCliente(arrayPublicaciones, QTY_PUBLICACIONES, arrayClientes, QTY_CLIENTES, auxIdCliente);
            printf("\n=======================================================\n");
            if(cliente_baja(arrayClientes, QTY_CLIENTES) == 0)
            {
              printf("**Baja correcta**\n");
            }
            else
            {
              printf("**La baja no se ha realizado**\n");
            }
          }
          else
          {
            printf("**Error en ingreso de Id**\n");
          }
        break;
        case 4: //PUBLICAR
          printf("\n=============== Listado de Clientes ===================\n");
          cliente_imprimir(arrayClientes, QTY_CLIENTES);
          printf("\n=======================================================\n");
          if(utn_getInt(&auxIdCliente, "Id cliente? ", "Error! ", 0, 100, RETRY) == 0 &&
             cliente_buscarId(arrayClientes, QTY_CLIENTES, auxIdCliente) != -1)
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
          printf("\n=============== Listado de Publicaciones =====================\n");
          publicacion_imprimir(arrayPublicaciones, QTY_PUBLICACIONES);
          printf("\n=======================================================\n");
          if(utn_getInt(&auxIdPublicacion, "Id de la pupblicacion a listar: ", "Error! ", 1, 1000, RETRY) == 0)
          {
            printf("**Ingreso correcto de id**\n");
            printf("\n========== Informacion de la pupblicacion del Cliente ==============\n");
            informe_imprimirPublicacionPorSuId(arrayPublicaciones, QTY_PUBLICACIONES, arrayClientes, QTY_CLIENTES, auxIdPublicacion);
            printf("\n===========================================================\n");

            if(publicacion_estadoPausado(arrayPublicaciones, QTY_PUBLICACIONES) == 0)
            {
              printf("**Publicacion pausado correctamente**\n");
            }
            else
            {
              printf("**Publicacion no modificado**\n");
            }
          }
          else
          {
            printf("**Error en ingreso de id**\n");
          }
          break;
        case 6: //REANUDAR PUBLICACION
          printf("\n=============== Listado de Publicaciones =====================\n");
          publicacion_imprimir(arrayPublicaciones, QTY_PUBLICACIONES);
          printf("\n=======================================================\n");
          if(utn_getInt(&auxIdPublicacion, "Id de la pupblicacion a listar: ", "Error! ", 1, 1000, RETRY) == 0)
          {
            printf("**Ingreso correcto de id**\n");
            printf("\n========== Informacion de la pupblicacion del Cliente ==============\n");
            informe_imprimirPublicacionPorSuId(arrayPublicaciones, QTY_PUBLICACIONES, arrayClientes, QTY_CLIENTES, auxIdPublicacion);
            printf("\n===========================================================\n");

            if(publicacion_estadoActivo(arrayPublicaciones, QTY_PUBLICACIONES) == 0)
            {
              printf("**Publicacion activo correctamente**\n");
            }
            else
            {
              printf("**Publicacion no modificado**\n");
            }
          }
          else
          {
            printf("**Error en ingreso de id**\n");
          }
          break;
        case 7: //IMPRIMIR CLIENTES
          informe_imprimirPublicacionesPorCliente(arrayIdsClientes, arrayPublicaciones, QTY_PUBLICACIONES,arrayClientes, QTY_CLIENTES);
          break;
        case 8: //INFORMAR
          if(utn_getInt(&opcion, mensajeSubMenu, mensajeErrorMenu, MIN_MENU, MAX_SUBMENU, RETRY)==0)
          {
            switch(opcion)
            {
              case 1: //Cliente con más publicaciones.
                break;
              case 2: //Cantidad de publicaciones pausados.
                break;
              case 3: //Rubro con mas publicaciones.
                break;
            }
          }
          break;
        case 9:
          break;
      }
    }
  }while(opcion != 10);

  return EXIT_SUCCESS;
}

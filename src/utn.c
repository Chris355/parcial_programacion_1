//
// Created by Christian Silvero
//

#include <stdio.h>
#include <stdlib.h>
#include <stdio_ext.h>
#include <string.h>

#define LIMITE_BUFFER_STRING 4096

static int myGets(char* cadena, int longitud);
static int getInt(int* pResultado);
static int esNumerica(char* cadena);
static int getFloat(float* pResultado);
static int esFlotante(char* cadena);
static int esUnNombreValido(char* cadena);
static int esUnaDireccion(char* cadena);
static int esUnCuit(char* cadena);
static int esUnArchivo(char* cadena);

//------------------------- FUNCIONES STATIC -----------------------------------

//------------------------- static myGets --------------------------------------
/**
 * \brief Lee de stdin hasta que se encuentra un '\n' o hasta que haya copiado en cadena un maximo de 'longitud-1' caracteres.
 * \param int* pResultado, puntero al espacio de memoria donde se dejara el valor obtenido
 * \param int longitud, define el tamaño de cadena.
 * \return Retorno: (0) si esta OK.
 * 									(-1) Si hubo un error
*/
static int myGets(char* cadena, int longitud)
{
	int retorno = -1;

  if(cadena != NULL &&
     longitud > 0 &&
     fgets(cadena, longitud, stdin) == cadena)
  {
  	__fpurge(stdin);
    if(cadena[strlen(cadena)-1] == '\n' )
    {
      cadena[strlen(cadena)-1] = '\0' ;
    }
    retorno = 0;
  }
  return retorno;
}

//------------------------- static getInt -----------------------------------
/**
 * \brief Verifica si la cadena ingresada es numerica y obtiene un entero
 * \param pResultado Puntero al espacio de memoria donde se dejara el resultado de la funcion
 * \return Retorno: (0) si esta OK.
 * 									(-1) Si hubo un error
*/
static int getInt(int* pResultado)
{
	int retorno = -1;
	char buffer[4096];

	if(pResultado != NULL)
	{
		if(myGets(buffer, sizeof(buffer)) == 0 && esNumerica(buffer))
		{
			*pResultado = atoi(buffer); //convierto un string a numerica
			retorno = 0;
		}
	}
	return retorno;
}

//------------------------- static esNumerica -----------------------------------
/**
 * \brief Verifica si la cadena ingresada es numerica
 * \ param cadena Cadena de caracteres a ser analizada
 * \return Retorno: (1) Si es Verdadero
 * 									(0) Si es Falso
*/
static int esNumerica(char* cadena)
{
	int retorno = 1; //inicializo con el OK
	int i = 0;

	if(cadena[0] == '-') //1ra posición es menos, ok
	{
		i = 1;
	}
	for( ; cadena[i] != '\0';i++)
	{
		if(cadena[i] < '0' || cadena[i] > '9')
		{
			retorno = 0; //Error
			break;
		}
	}
	return retorno;
}

//------------------------- static getFloat -----------------------------------
/**
 * \brief Verifica si la cadena ingresada es flotante y obtiene un flotante
 * \param pResultado Puntero al espacio de memoria donde se dejara el resultado de la funcion
 * \return Retorno: (0) si esta OK.
 * 									(-1) Si hubo un error
*/
static int getFloat(float* pResultado)
{
	int retorno = -1;
	char buffer[4096];

	if(pResultado != NULL)
	{
		if(myGets(buffer, sizeof(buffer)) == 0 && esFlotante(buffer))
		{
			*pResultado = atof(buffer); //convierto un string a flotante
			retorno = 0;
		}
	}
	return retorno;
}

//------------------------- static esFlotante -----------------------------------
/**
 * \brief Verifica si la cadena ingresada es flotante
 * \ param cadena Cadena de caracteres a ser analizada
 * \return Retorno: (1) Si es Verdadero
 * 									(0) Si es Falso
*/
static int esFlotante(char* cadena)
{
	int retorno = 1; //inicializo con el OK
	int i = 0;
	int contadorPuntos = 0;

	if(cadena[0] == '-') //1ra posición es menos, ok
	{
		i = 1;
	}
	for( ; cadena[i] != '\0';i++)
	{
		if(cadena[i] == '.')
		{
			contadorPuntos++;
		}
		if((cadena[i] < '0' || cadena[i] > '9') && contadorPuntos > 1)
		{
			retorno = 0; //Error
			break;
		}
	}
	return retorno;
}

//------------------------- esUnNombreValido -----------------------------------
/**
 * \brief, Verifica una cadena recibida como parametro para determinir si es un nombre valido
 * \param char* pArray, Cadena a analizar
 * \return Retorno: (1) Si es Verdadero
 * 									(0) Si es Falso
*/
static int esUnNombreValido(char* cadena)
{
	int retorno = 1; //inicializo con el OK
	int i;
	if(cadena != NULL)
	{
	//el limite de la cadena es \0
		for(i=0; cadena[i]!='\0'; i++)
		{
			//condiciones para romper
			if((cadena[i] < 'a' || cadena[i] > 'z') &&
				 (cadena[i] < 'A' || cadena[i] > 'Z'))
			{
				retorno = 0; //no esta dentro del rango
				break;
			}
		}
	}
	return retorno;
}

//------------------------- esUnaDireccion-----------------------------------
/**
 * \brief, Verifica una cadena recibida como parametro para determinir si es una direccion valida
 * \param char* pArray, Cadena a analizar
 * \return Retorno: (1) Si es Verdadero
 * 									(0) Si es Falso
*/
static int esUnaDireccion(char* cadena)
{
	int retorno = 1; //inicializo con el OK
	int i;
	if(cadena != NULL)
	{
	//el limite de la cadena es \0
		for(i=0; cadena[i]!='\0'; i++)
		{
			//condiciones para romper
			if((cadena[i] < 'a' || cadena[i] > 'z') &&
				 (cadena[i] < 'A' || cadena[i] > 'Z') &&
				 (cadena[i] < '0' || cadena[i] > '9') &&
				 (cadena[i] < ' '))
			{
				retorno = 0; //no esta dentro del rango
				break;
			}
		}
	}
	return retorno;
}

//------------------------- esUnCuit-----------------------------------
/**
 * \brief, Verifica una cadena recibida como parametro para determinir si es un cuit valido
 * \param char* pArray, Cadena a analizar
 * \return Retorno: (1) Si es Verdadero
 * 									(0) Si es Falso
*/
static int esUnCuit(char* cadena)
{
	int retorno = 1; //inicializo con el OK
	int i;
	if(cadena != NULL)
	{
	//el limite de la cadena es \0
		for(i=0; cadena[i]!='\0'; i++)
		{
			//condiciones para romper
			if((cadena[i] < '0' || cadena[i] > '9') &&
				 (cadena[2] != '-') &&
				 (cadena[11] != '-'))
			{
				retorno = 0; //no esta dentro del rango
				break;
			}
		}
	}
	return retorno;
}

//------------------------- esUnArchivo-----------------------------------
/**
 * \brief, Verifica una cadena recibida como parametro para determinir si es un archivo valido
 * \param char* pArray, Cadena a analizar
 * \return Retorno: (1) Si es Verdadero
 * 									(0) Si es Falso
*/
static int esUnArchivo(char* cadena)
{
	int retorno = 1;
	int i;
	if(cadena != NULL)
	{
	//el limite de la cadena es \0
		for(i=0; cadena[i]!='\0'; i++)
		{
			//condiciones para romper
			if((cadena[i] < '0' || cadena[i] > '9') &&
				 (cadena[i] < 'a' || cadena[i] > 'z') &&
				 (cadena[i] != '.'))
			{
				retorno = 0; //no esta dentro del rango
				break;
			}
		}
	}
	return retorno;
}

//------------------------- esUnaDescripcion-----------------------------------
/**
 * \brief, Verifica una cadena recibida como parametro para determinir si es una descripcion valida
 * \param char* pArray, Cadena a analizar
 * \return Retorno: (1) Si es Verdadero
 * 									(0) Si es Falso
*/
static int esUnaDescripcion(char* cadena)
{
	int retorno = 1;
	int i;
	if(cadena != NULL)
	{
	//el limite de la cadena es \0
		for(i=0; cadena[i]!='\0'; i++)
		{
			//condiciones para romper
			if((cadena[i] < '0' || cadena[i] > '9') &&
				 (cadena[i] < 'A' || cadena[i] > 'Z') &&
				 (cadena[i] < 'a' || cadena[i] > 'z') &&
				 (cadena[i] != '.') &&
				 (cadena[i] != ',') &&
				 (cadena[i] != ' '))
			{
				retorno = 0; //no esta dentro del rango
				break;
			}
		}
	}
	return retorno;
}

//------------------------- FUNCIONES GET -----------------------------------

//------------------------- utn_getInt -----------------------------------
/**
 * \brief utn_getInt : Pide al usuario un numero entero
 * \param pResultado: Direccion de memoria de la variable donde escribe el valor ingresado por el usuario
 * \param mensaje: El mensaje que imprime para pedir un valor
 * \param mensajeError: mensaje que imprime si el rango no es valido
 * \param minimo: valor minimo valido (inclusive)
 * \param maximo: valor maximo valido (inclusive)
 * \param reintentos: cantidad de intentos en caso de error
 * \return Retorno: (0) si esta OK.
 * 									(-1) Si hubo un error
*/
int utn_getInt(int* pResultado, char* mensaje, char* mensajeError, int minimo, int maximo, int reintentos)
{
	int retorno = -1;
	int bufferInt;

	if(pResultado != NULL &&
		 mensaje != NULL &&
		 mensajeError != NULL &&
		 reintentos >= 0 &&
		 maximo >= minimo)
	{
		do
		{
			printf("%s", mensaje);
			if(getInt(&bufferInt) == 0 && bufferInt >= minimo && bufferInt <= maximo)
			{
				*pResultado = bufferInt;
				retorno = 0;
				break;
			}
			else
			{
				printf("%s",mensajeError);
				reintentos--;
			}
		}while(reintentos >= 0);
	}
	return retorno;
}

//------------------------- utn_getFloat -----------------------------------
/**
 * \brief utn_getFloat : Pide al usuario un numero flotante
 * \param pResultado: Direccion de memoria de la variable donde escribe el valor ingresado por el usuario
 * \param mensaje: El mensaje que imprime para pedir un valor
 * \param mensajeError: mensaje que imprime si el rango no es valido
 * \param minimo: valor minimo valido (inclusive)
 * \param maximo: valor maximo valido (inclusive)
 * \param reintentos: cantidad de intentos en caso de error
 * \return Retorno: (0) si esta OK.
 * 									(-1) Si hubo un error
*/
int utn_getFloat(float* pResultado, char* mensaje, char* mensajeError, float minimo, float maximo, int reintentos)
{
	int retorno = -1;
	float bufferFloat;

	if(pResultado != NULL &&
		 mensaje != NULL &&
		 mensajeError != NULL &&
		 reintentos >= 0 &&
		 maximo >= minimo)
	{
		do
		{
			printf("%s", mensaje);
			//__fpurge(stdin);
			//resultadoScanf = scanf("%f",&bufferFloat);
			if(getFloat(&bufferFloat) == 0 && bufferFloat >= minimo && bufferFloat <= maximo)
			{
				*pResultado = bufferFloat;
				retorno = 0;
				break;
			}
			else
			{
				printf("%s",mensajeError);
				reintentos--;
			}
		}while(reintentos >= 0);
	}
	return retorno;
}

//------------------------- utn_getNombre -----------------------------------
/**
 * \brief Solicita un nombre al usuario
 * \param int* pResultado, puntero al espacio de memoria donde se dejara el valor obtenido
 * \param char* mensaje, Es el mensaje a ser mostrado al usuario
 * \param char* mensaje, Es el mensaje de error a ser mostrado al usuario
 * \param int reintentos, cantidad de oportunidades para ingresar el dato
 * \param int limite, indica la cantidad de letras maxima del nombre
 * \return Retorno: (0) si esta OK.
 * 									(-1) Si hubo un error
*/
int utn_getNombre(char* pResultado, char* mensaje, char* mensajeError, int reintentos, int limite)
{
	char bufferString[LIMITE_BUFFER_STRING];
	int retorno = -1;

	if(	pResultado != NULL &&
			mensaje != NULL &&
			mensajeError != NULL &&
			reintentos >= 0 &&
			limite > 0)
	{
		do
		{
			printf("%s", mensaje);
			if( myGets(bufferString, LIMITE_BUFFER_STRING) == 0 &&
					strnlen(bufferString, sizeof(bufferString)-1)<= limite &&
					esUnNombreValido(bufferString) != 0 )
			{
				retorno = 0;
				strncpy(pResultado, bufferString, limite);
				break;
			}
			else
			{
				printf("%s", mensajeError);
				reintentos--;
			}
		}while(reintentos >= 0);
	}
	return retorno;
}

//------------------------- utn_getDireccion -----------------------------------
/**
 * \brief Solicita una direccion al usuario
 * \param int* pResultado, puntero al espacio de memoria donde se dejara el valor obtenido
 * \param char* mensaje, Es el mensaje a ser mostrado al usuario
 * \param char* mensaje, Es el mensaje de error a ser mostrado al usuario
 * \param int reintentos, cantidad de oportunidades para ingresar el dato
 * \param int limite, indica la cantidad de letras maxima del nombre
 * \return Retorno: (0) si esta OK.
 * 									(-1) Si hubo un error
*/
int utn_getDireccion(char* pResultado, char* mensaje, char* mensajeError, int reintentos, int limite)
{
	char bufferString[LIMITE_BUFFER_STRING];
	int retorno = -1;

	if(	pResultado != NULL &&
			mensaje != NULL &&
			mensajeError != NULL &&
			reintentos >= 0 &&
			limite > 0)
	{
		do
		{
			printf("%s",mensaje);
			if( myGets(bufferString,LIMITE_BUFFER_STRING) == 0 &&
					strnlen(bufferString,sizeof(bufferString)-1)<= limite &&
					esUnaDireccion(bufferString) != 0 )
			{
				retorno = 0;
				strncpy(pResultado,bufferString,limite);
				break;
			}
			else
			{
				printf("%s",mensajeError);
				reintentos--;
			}
		}while(reintentos >= 0);
	}
	return retorno;
}

//------------------------- utn_getCuit -----------------------------------
/**
 * \brief Solicita una cuit al usuario
 * \param int* pResultado, puntero al espacio de memoria donde se dejara el valor obtenido
 * \param char* mensaje, Es el mensaje a ser mostrado al usuario
 * \param char* mensaje, Es el mensaje de error a ser mostrado al usuario
 * \param int reintentos, cantidad de oportunidades para ingresar el dato
 * \param int limite, indica la cantidad de letras maxima del nombre
 * \return Retorno: (0) si esta OK.
 * 									(-1) Si hubo un error
*/
int utn_getCuit(char* pResultado, char* mensaje, char* mensajeError, int reintentos, int limite)
{
	char bufferString[LIMITE_BUFFER_STRING];
	int retorno = -1;

	if(	pResultado != NULL &&
			mensaje != NULL &&
			mensajeError != NULL &&
			reintentos >= 0 &&
			limite > 0)
	{
		do
		{
			printf("%s",mensaje);
			if( myGets(bufferString,LIMITE_BUFFER_STRING) == 0 &&
					strnlen(bufferString,sizeof(bufferString)-1) <= limite &&
					esUnCuit(bufferString) != 0 )
			{
				retorno = 0;
				strncpy(pResultado,bufferString,limite);
				break;
			}
			else
			{
				printf("%s",mensajeError);
				reintentos--;
			}
		}while(reintentos >= 0);
	}
	return retorno;
}

//------------------------- utn_getArchivo -----------------------------------
/**
 * \brief Solicita un nombre de archivo al usuario
 * \param int* pResultado, puntero al espacio de memoria donde se dejara el valor obtenido
 * \param char* mensaje, Es el mensaje a ser mostrado al usuario
 * \param char* mensaje, Es el mensaje de error a ser mostrado al usuario
 * \param int reintentos, cantidad de oportunidades para ingresar el dato
 * \param int limite, indica la cantidad de letras maxima del nombre
 * \return Retorno: (0) si esta OK.
 * 									(-1) Si hubo un error
*/
int utn_getArchivo(char* pResultado, char* mensaje, char* mensajeError, int reintentos, int limite)
{
	char bufferString[LIMITE_BUFFER_STRING];
	int retorno = -1;

	if(	pResultado != NULL &&
			mensaje != NULL &&
			mensajeError != NULL &&
			reintentos >= 0 &&
			limite > 0)
	{
		do
		{
			printf("%s",mensaje);
			if( myGets(bufferString,LIMITE_BUFFER_STRING) == 0 &&
					strnlen(bufferString,sizeof(bufferString)-1) <= limite &&
					esUnArchivo(bufferString) != 0 )
			{
				retorno = 0;
				strncpy(pResultado,bufferString,limite);
				break;
			}
			else
			{
				printf("%s",mensajeError);
				reintentos--;
			}
		}while(reintentos >= 0);
	}
	return retorno;
}

//------------------------- utn_getDescripcion -----------------------------------
/**
 * \brief Solicita una descripcion de archivo al usuario
 * \param int* pResultado, puntero al espacio de memoria donde se dejara el valor obtenido
 * \param char* mensaje, Es el mensaje a ser mostrado al usuario
 * \param char* mensaje, Es el mensaje de error a ser mostrado al usuario
 * \param int reintentos, cantidad de oportunidades para ingresar el dato
 * \param int limite, indica la cantidad de letras maxima del nombre
 * \return Retorno: (0) si esta OK.
 * 									(-1) Si hubo un error
*/
int utn_getDescripcion(char* pResultado, char* mensaje, char* mensajeError, int reintentos, int limite)
{
	char bufferString[LIMITE_BUFFER_STRING];
	int retorno = -1;

	if(	pResultado != NULL &&
			mensaje != NULL &&
			mensajeError != NULL &&
			reintentos >= 0 &&
			limite > 0)
	{
		do
		{
			printf("%s",mensaje);
			if( myGets(bufferString,LIMITE_BUFFER_STRING) == 0 &&
					strnlen(bufferString,sizeof(bufferString)-1) <= limite &&
					esUnaDescripcion(bufferString) != 0 )
			{
				retorno = 0;
				strncpy(pResultado,bufferString,limite);
				break;
			}
			else
			{
				printf("%s",mensajeError);
				reintentos--;
			}
		}while(reintentos >= 0);
	}
	return retorno;
}












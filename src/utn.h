//
// Created by Christian Silvero
//

#ifndef UTN_H_
#define UTN_H_

int utn_getInt(int* pResultado, char* mensaje, char* mensajeError, int minimo, int maximo, int reintentos);
int utn_getFloat(float* pResultado, char* mensaje, char* mensajeError, float minimo, float maximo, int reintentos);
int utn_getNombre(char* pResultado, char* mensaje, char* mensajeError, int reintentos, int limite);
int utn_getDireccion(char* pResultado, char* mensaje, char* mensajeError, int reintentos, int limite);
int utn_getCuit(char* pResultado, char* mensaje, char* mensajeError, int reintentos, int limite);
int utn_getArchivo(char* pResultado, char* mensaje, char* mensajeError, int reintentos, int limite);
int utn_getDescripcion(char* pResultado, char* mensaje, char* mensajeError, int reintentos, int limite);

#endif /* UTN_H_ */

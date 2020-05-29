/**
  * @file UtilidadesFicheros.h
  * @brief Contiene las cabeceras de algunas funciones útiles para ficheros.
  */

#ifndef UTILIDADES_FICHERO_H
#define UTILIDADES_FICHERO_H

#include <string>
using namespace std;

//****************************************************************************
//Control
//****************************************************************************
//----------------------------------------------------------------------------
/**
  * @brief Informa de la existencia del fichero `nombre`
  * @param nombre Nombre del fichero a comprobar
  * @return `true` si existe y está disponible, `false` en caso contrario
  */
bool ExisteFichero (const string & nombre);
//----------------------------------------------------------------------------


#endif

/**
  * @file Estimaciones.cpp
  * @brief Lee un fichero que contiene nombres de fichero imágenes. Estos sólo
  *   	   contienen el contenido, por lo que se deberá de estimar las
  * 	   dimensiones de la imagen.
  */

//*****************************************************************************
#include <iostream>
#include <fstream>
#include <iomanip>

#include "Imagen.h"
#include "UtilidadesFicheros.h"
#include "Secuencia.h"

using namespace std;
//*****************************************************************************
/**
  * @brief Lee en una secuencia los píxeles que se encuentran en el fichero
  *        pasado por argumento.
  * @param nombre_in Nombre del fichero que contiene una secuencia de píxeles
  * @pre Los píxeles deben estar representados como enteros separados por
  *	     espacios
  */
Secuencia LeerPixeles (const string & nombre_in);
//*****************************************************************************
int main (int argc, char ** argv){

	cout.setf(ios::showpoint);
	cout.setf(ios::fixed);

	//Comprobación de argumentos

	if (argc != 2)
	{
		cerr << "Error: número de argumentos incorrecto. Uso: " << endl
			 << argv[0] << " <fichero con nombres de ficheros con píxeles>"
			 << endl;

		exit (1);
	}

	//Compruebo el fichero de entrada
	string nombre_in = argv[1];

	if (!ExisteFichero(nombre_in))
	{
		cerr << "Error: No puedo abrir el fichero " << nombre_in << endl;
		exit (2);
	}

	ifstream fi (nombre_in);

	//Procesamiento
	string nombre_fichero;

		//Procesamiento línea a línea
	while (getline(fi,nombre_fichero))
	{
		if (ExisteFichero(nombre_fichero)){		//Procesar

			//Leer pixeles
			Secuencia pixeles = LeerPixeles (nombre_fichero);

			//Crear imagen
			Imagen img (pixeles);
			img.AniadeComentario("# Fichero de datos: " + nombre_fichero);

			//Salida
				//Nombre del fichero
			string nombre_salida = nombre_fichero + ".pgm";

				//Pregunto si se desea sobreescribir
			char respuesta;
			if (ExisteFichero(nombre_salida)){
				do {
					cout << endl;
					cout << "¿Desea sobreescribir los datos en el fichero "
						 << nombre_salida << "? (S | N) : ";

					cin >> respuesta;

				}while (respuesta != 'S' && respuesta != 'N');
			}

			//MENSAJE PARA TERMINAR
			if (respuesta == 'N')
			{
				cout << endl;
				cout << "No se sobreescibe la imagen sobre " << nombre_salida;
				cout << endl << endl;
			}
			else{
				//IMPRIMIR IMAGEN
				img.ToP2(nombre_salida);
			}

		} // SI EXISTE EL FICHERO
		else {
			cerr << "No he podido abrir el fichero " << nombre_fichero << endl;
		}
	}


	return 0;
}
//****************************************************************************
Secuencia LeerPixeles (const string &nombre_in)
{
	Secuencia pixeles;
	ifstream f_pixeles (nombre_in);

	//Leo píxeles
	int leido;
	f_pixeles >> leido;

	while (!f_pixeles.fail())
	{
		pixeles+=leido;

		//Lectura adelantada
		f_pixeles >> leido;
	}

	f_pixeles.close();

	return pixeles;

}

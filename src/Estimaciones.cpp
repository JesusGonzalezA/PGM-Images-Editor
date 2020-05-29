/**
  * @file Estimacinoes.cpp
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
int main (int argc, char ** argv){

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
			Secuencia pixeles;
			ifstream f_pixeles (nombre_fichero);

			//Lectura adelantada
			int leido;
			f_pixeles >> leido;

			while (!f_pixeles.fail())
			{
				pixeles+=leido;

				//Lectura adelantada
				f_pixeles >> leido;
			}
			cout << nombre_fichero << " --> " << pixeles.TotalUtilizados() << endl;
			ofstream fo(nombre_fichero+".pgm");
			fo << pixeles;
			fo.close();
			f_pixeles.close();
		}
		else {
			cerr << "No he podido abrir el fichero " << nombre_fichero << endl;
		}
	}


	return 0;
}

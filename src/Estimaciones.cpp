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
#include <limits.h>
#include <math.h>

#include "Imagen.h"
#include "UtilidadesFicheros.h"
#include "Secuencia.h"

using namespace std;

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
			int mayor_leido = 0;
			Secuencia pixeles;
			ifstream f_pixeles (nombre_fichero);

			//Leo píxeles
			int leido;
			f_pixeles >> leido;

			while (!f_pixeles.fail())
			{
				if (leido > mayor_leido) mayor_leido = leido;

				pixeles+=leido;

				//Lectura adelantada
				f_pixeles >> leido;
			}

			f_pixeles.close();

			//Procesamiento para encontrar las filas y columnas

				//Variables
					//Para el resultado
			int columnas=0, filas=0, max_lum = mayor_leido;
					//Para el procesamiento
			int tam = pixeles.TotalUtilizados();
			int it_f = 2, it_c = tam/it_f;
			double v_min = LONG_MAX;

			//Procesar
			while (it_c>2){

				//Calcular las filas y columnas de la configuración
				while ((it_f * it_c) != tam){
					it_f++;
					it_c = tam/it_f;
				}

				//Calcular media de las desviaciones al cuadrado entre dos filas
				double med_dev = 0;

				for (int i=1, contador=0; i<it_f; ++i){

					int suma_c = 0;

					for (int j=1; j<=it_c; ++j, contador++){
						suma_c += pow ( (pixeles[(i-1)*it_c + j]
											-
									 pixeles[i*it_c + j] )
									  , 2);
					}

					med_dev += (( (double)1/it_c) * suma_c);
				}

				//Calcular el valor V
				double v = (( (double)1 / (it_f-1) ) * med_dev);

				//Actualizar el mejor V
				if (v < v_min ){
					v_min = v;
					filas = it_f;
					columnas = it_c;
				}

				//Siguiente
				it_f++;

			}//Fin de procesamiento


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
				ofstream f_imagen (nombre_salida);
				f_imagen << "P2" << endl;
				f_imagen << "# Creada por: ESTIMACION DE DIMENSIONES " << endl;
				f_imagen << "# Fichero de datos: " << nombre_fichero << endl;
				f_imagen << columnas << " " << filas << endl;
				f_imagen << max_lum << endl;
				f_imagen << pixeles;
				f_imagen.close();
			}

		} // SI EXISTE EL FICHERO
		else {
			cerr << "No he podido abrir el fichero " << nombre_fichero << endl;
		}
	}


	return 0;
}

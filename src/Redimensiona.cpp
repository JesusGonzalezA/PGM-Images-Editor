/**
  * @file Redimensiona.cpp
  * @brief Redimensiona una imagen contenida en un fichero proporcionado por
  *        el usuario como argumento. Se crea una nueva imagen siguiendo las
  * 	   proporciones de la original.
  */

//*****************************************************************************
#include <iostream>
#include <fstream>
#include <iomanip>

#include "Imagen.h"
#include "UtilidadesFicheros.h"

using namespace std;

//*****************************************************************************
int main (int argc, char ** argv){

	cout.setf(ios::showpoint);
 	cout.setf(ios::fixed);

	/************************************************************************/
	// Comprobación del número y validez de los argumentos

	if (argc < 4 || argc > 5) {
		cerr << "Error: num. de parametros incorrecto" << endl;
		cerr << "Formato: " << argv[0] << "<Imagen_PGM_original>";
		cerr << " [ <prop> | -f  <filas> | -c <cols> | <filas> <cols> ] ";
		cerr << "<Imagen_PGM_redimensionada>" << endl;
		exit (1);
	}

	// Nombres de los fichweros de las imágenes de entrada y salida
	string nombre_in, nombre_out;
	nombre_in = argv[1]; // El fichero de entrada siempre es argv[1]

	// Comprobar la existencia del fichero de entrada
	if (!ExisteFichero (nombre_in)) {
		cerr << "Error: " << nombre_in << " no puede abrirse" << endl;
		exit (2);
	}

	int tipo = 0; // Puede ser 1, 2, 3 y 4

	double prop = 1.0;

	// Número de filas y columnas de la imagen de salida
	int filas_out;
	int cols_out;


	// Discriminar el tipo de ejecución, validar los parámetros específicos
	// de cada tipo y determinar el nombre del fichero de salida.

	if (argc == 4) { // Solo se indica la proporcion

		prop = atof(argv[2]);

		if (prop<=0.0 || prop>1.0) {
			cerr << "Error: proporcion incorrecta. ";
			cerr << "Debe ser 0<prop<=1" << endl;
			exit (3);
		}

		tipo = 1;
		nombre_out = argv[3];

		cout << endl;
		cout << "Generando imagen de salida con proporcion = "
		     << setw(4) << setprecision(2) << prop << endl;
		cout << endl;
	}
	else { // argc == 5

		if (!strcmp(argv[2],"-f")) { // -f filas

			filas_out = atoi(argv[3]);

			if (filas_out<=0) {
				cerr << "Error: Num.filas debe ser mayor que cero" << endl;
				exit (4);
			}

			tipo = 2;
			nombre_out = argv[4];

			cout << endl;
			cout << "Generando imagen de salida con "
			     << setw(4) << filas_out << " filas" << endl;
			cout << endl;
   		}
		else {

			if (!strcmp(argv[2],"-c")) { // -f filas

				cols_out = atoi(argv[3]);

				if (cols_out<=0) {
					cerr << "Error: Num.cols debe ser mayor que cero" << endl;
					exit (5);
				}

				tipo = 3;
				nombre_out = argv[4];

				cout << endl;
				cout << "Generando imagen de salida con "
				     << setw(4) << cols_out << " columnas" << endl;
   				cout << endl;
			}
			else { // filas cols

				filas_out = atoi(argv[2]);
				cols_out  = atoi(argv[3]);

				if (filas_out<=0 || cols_out<=0) {
					cerr << "Error: Num.fils y num. cols deben ser ";
					cerr << "mayor que cero" << endl;
					exit (6);
				}

				tipo = 4;
				nombre_out = argv[4];

				cout << endl;
				cout << "Generando imagen de salida de dimensiones: "
				     << setw(4) << filas_out << " x "
				     << setw(4) << cols_out << endl;
   				cout << endl;
			}
		}

	}

	/************************************************************************/

	/************************************************************************/
	// Necesitamos saber las dimensiones del fichero de entrada, por lo
	// que vamos a leer los datros de la cabecera

	Imagen entrada (argv[1]);

	int
		filas 	   = entrada.GetFils(),
		columnas   = entrada.GetCols(),
		maximo     = entrada.GetMaxLuminosidad(),
		num_pixels =  filas*columnas;

	cout << "Dimensiones de " << nombre_in << ":"<< endl;
	cout << "filas = " << setw(4) << filas << endl;
	cout << "cols  = " << setw(4) << columnas << endl;
	cout << endl;

	/************************************************************************/
	// Calcular "saltos" entre filas y columnas

	double salto_real_filas;
	double salto_real_cols;

	switch (tipo) {

		case (1) : // <Imagen_PGM_original> <prop> <Imagen_PGM_redim>

			filas_out = (int) (filas * prop);
			cols_out  = (int) (columnas * prop);

			break;

		case (2) : // <Imagen_PGM_original> -f <filas> <Imagen_PGM_redim>

			prop = ((double)filas_out) / filas;

			cout << "Prop. columnas= " << setw(8) << setprecision(6)
			     << prop << endl;

			cols_out  = (int) (columnas * prop);

			break;

		case (3) : // <Imagen_PGM_original> -c <cols> <Imagen_PGM_redim>

			prop = ((double)cols_out) / columnas;

			cout << "Prop. filas   = " << setw(8) << setprecision(6)
			     << prop << endl;

			filas_out  = (int) (filas * prop);

			break;

		case (4) : // <Imagen_PGM_original> <filas> <cols> <Imagen_PGM_redim>

			double prop_filas    = ((double)filas_out) / filas;
			double prop_columnas = ((double)cols_out) / columnas;

			cout << "Prop filas    = " << setw(8) << setprecision(6)
			     << prop_filas << endl;
			cout << "Prop columnas = " << setw(8) << setprecision(6)
			     << prop_columnas << endl;

			filas_out = (int) (filas * prop_filas);
			cols_out  = (int) (columnas * prop_columnas);

			break;

	}; // switch (tipo)


	if (filas_out>filas || cols_out>columnas) {
		cerr << endl;
		cerr << "Error: Se ha indicado un numero de filas o columnas ";
		cerr << "mayor que el original." << endl;
		cerr << endl;
		exit (7);
	}

	salto_real_filas =  ((double)filas)/filas_out;
	salto_real_cols  =  ((double)columnas)/cols_out;

	cout << "Salto filas   = " << setw(8) << setprecision(6)
	     << salto_real_filas << endl;
	cout << "Salto columnas= " << setw(8) << setprecision(6)
	     << salto_real_cols << endl;

	cout << endl;
	cout << "Dimensiones de " << nombre_out << ":"<< endl;
	cout << "filas = " << setw(4) << filas_out << endl;
	cout << "cols  = " << setw(4) << cols_out << endl;
	cout << endl;

	/************************************************************************/
	// Crear imagen de salida: reservar espacio para la imagen resultado

	Imagen image_out (filas_out, cols_out,entrada.GetMaxLuminosidad());


	// Rellenar cada pixel de la imagen de salida

	double f_orig = 1;
	ofstream foo;
	foo.open("datos_salida");
	for (int f=1; f<=filas_out; f++) {

		int la_fila = (int)f_orig; // fila de la imagen original

		double c_orig = 1;

		for (int c=1; c<=cols_out; c++) {

			int la_columna = (int)c_orig; // columna de la imagen original

			image_out(f,c) = entrada(la_fila,la_columna);
			foo << (int)entrada(la_fila,la_columna) << " ";
			//int num_pixels_out = filas_out * cols_out;
			//byte *image_out = new byte[num_pixels_out];

			//byte * image = new byte[num_pixels]; // Reservar espacio para la imagen

			//image_out[(f*cols_out)+c] = image[(la_fila*columnas)+la_columna];

			c_orig += salto_real_cols; // Nueva columna en la imagen original

		} // for c

		f_orig += salto_real_filas; // Nueva fila en la imagen original

	} // for f
	foo.close();

	/************************************************************************/
	// Guardar el resultado en un fichero PGM

	image_out.AniadeComentario("# Imagen Redimensionada desde " + nombre_in);
	image_out.ToP5(nombre_out);

	/************************************************************************/

	return 0;

}
//*****************************************************************************

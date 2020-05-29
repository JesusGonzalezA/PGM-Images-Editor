/**
  * @file Binariza.cpp
  * @brief Binariza una `Imagen` PGM que el usuario pasa como argumento. La
  * 	   imagen se binariza a partir de un valor umbral pasado por el usuario.
  *		   Los píxeles por debajo del mismo valdrán 0, y los superiores o
  *	       iguales valdrán `max_luminosidad`. Se escribe la imagen en un
  *        fichero indicado por el usuario en los argumentos.
  */

//*****************************************************************************
#include <iostream>

#include "Imagen.h"
#include "UtilidadesFicheros.h"

using namespace std;

//*****************************************************************************
/**
  * @brief Binariza una imagen
  * @param imagen Imagen a binarizar
  * @param valor_umbral Valor a partir del cual se binariza
  * @return Se devuelve una imagen binarizada
  */
Imagen Binariza (const Imagen & imagen, int valor_umbral);
//*****************************************************************************
int main (int argc, char **argv){

	//Compruebo los argumentos
	if (argc != 4)
	{
		cerr << "Error: los argumentos no son válidos." << endl;
		cerr << "Uso correcto:" << endl
			 << argv[0] << " <fichero_Imagen>  <valor_umbral> <fichero_salida>";
		cerr << endl;

		exit (1);
	}

	if (atoi(argv[2]) < 0){
		cerr << "Error: <valor_umbral> debe ser mayor o igual a 0" << endl;

		exit (2);
	}

	// Comprobar la existencia del fichero de entrada
	if (!ExisteFichero (argv[1])) {
		cerr << "Error: " << argv[1] << " no puede abrirse" << endl;
		exit (3);
	}

	//Preguntar al usuario si quiere sobreescribir los datos
	char respuesta;

	if (ExisteFichero(argv[3])){
		do {
			cout << endl;
			cout << "¿Desea sobreescribir los datos en el fichero "
				 << argv[3] << "? (S | N) : ";

			cin >> respuesta;

		}while (respuesta != 'S' && respuesta != 'N');
	}

	//MENSAJE PARA TERMINAR
	if (respuesta == 'N')
	{
		cout << endl;
		cout << "Se termina la ejecución del programa sin sobreescribir "
		     << "la imagen" << endl;
	}

	//PROCESAMIENTO
	else{
		//Leo la imagen de entrada
		Imagen entrada(argv[1]);

		//Binarizo
		Imagen binarizada = Binariza (entrada, atoi(argv[2]));

		//Escribo la imagen en la salida
		(binarizada).ToP2(argv[3]);
	}

	return 0;
}
//******************************************************************************
Imagen Binariza (const Imagen & imagen, int valor_umbral)
{
	//Declaración de variables
	const int
		max      = imagen.GetMaxLuminosidad(),
		filas    = imagen.GetFils(),
		columnas = imagen.GetCols();

	//Creo la imagen al máximo de luminosidad
	Imagen binarizada (filas,columnas, max);

	//Binarizo la imagen
	for (int i=1; i<=filas; ++i)
		for (int j=1; j<=columnas; ++j)
			if (imagen(i,j)<valor_umbral)
				binarizada(i,j) = 0;

	return binarizada;
}
//*****************************************************************************

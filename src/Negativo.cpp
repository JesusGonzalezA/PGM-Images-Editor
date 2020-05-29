/**
  * @file Negativo.cpp
  * @brief Negativiza una `Imagen` PGM que el usuario pasa como argumento. Si
  * 	   sólo pasa un argumento la imagen será alterada. Si el usuario pasa
  *        dos imágenes, la imagen original no se verá modificada y se obtendrá
  *        la nueva imagen negativizada en el fichero que se pase como segundo
  *        argumento.
  */

//*****************************************************************************
#include <iostream>

#include "Imagen.h"
#include "UtilidadesFicheros.h"

using namespace std;
//*****************************************************************************
int main (int argc, char **argv){

	//Compruebo los argumentos
	if (argc > 3 || argc==1)
	{
		cerr << "Error: los argumentos no son válidos." << endl;
		cerr << "Uso correcto:" << endl
			 << argv[0] << " <fichero_Imagen>  : se altera la imagen." << endl
			 << argv[0] << " <fichero_Imagen>  <fichero_salida>" << endl;

		exit (1);
	}

	//Preguntar al usuario si quiere sobreescribir los datos
	string nombre_fichero = (argc == 2)? argv[1] : argv[2];
	char respuesta;

	if (ExisteFichero(nombre_fichero)){
		do {
			cout << endl;
			cout << "¿Desea sobreescribir los datos en el fichero "
				 << nombre_fichero << "? (S | N) : ";

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
		Imagen entrada(argv[1]);
		Imagen copia(entrada);
		(!copia).ToP2(nombre_fichero);
	}

	return 0;
}
//*****************************************************************************

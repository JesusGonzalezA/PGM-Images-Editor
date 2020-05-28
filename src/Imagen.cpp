/**
  * @file Imagen.cpp
  * @brief Implementación de la clase `Imagen`
  *
  */

#include <iostream>
#include <fstream>
#include <stdio.h>
#include <iomanip>
#include <string.h>

#include "Imagen.h"

using namespace std;

//****************************************************************************
//****************************************************************************

//****************************************************************************
//	Constructores y destructor
//****************************************************************************

//----------------------------------------------------------------------------


//----------------------------------------------------------------------------

Imagen :: Imagen (const Imagen & otra)
{
	ReservaEspacio(otra.fils, otra.cols);
	max_luminosidad = otra.max_luminosidad;

	//Copio los comentarios
	comentarios = otra.comentarios;

	//Copio el contenido
	memcpy (img, otra.img, fils*cols);
}

//----------------------------------------------------------------------------

Imagen :: Imagen (const int f, const int c, const int valor)
	: fils(f), cols(c), max_luminosidad(valor), comentarios()
{
	(*this) = valor;
	ReservaEspacio(f,c);
}

//----------------------------------------------------------------------------

Imagen :: Imagen (string nombre_fichero){}

//----------------------------------------------------------------------------

Imagen :: ~Imagen ()
{
	LiberaEspacio();
}

//----------------------------------------------------------------------------

//****************************************************************************
//	Operaciones sobre la imagen
//****************************************************************************

//----------------------------------------------------------------------------

int Imagen :: GetFils() const
{
	return fils;
}

//----------------------------------------------------------------------------

int Imagen :: GetCols() const
{
	return cols;
}

//----------------------------------------------------------------------------

pixel & Imagen :: ValorPixel (const int fila, const int columna) const
{
	return img[fila][columna];
}

//----------------------------------------------------------------------------

int Imagen :: GetNumComentarios(void) const
{
	return comentarios.GetNumComentarios();
}

//----------------------------------------------------------------------------

string Imagen :: GetComentario (const int index) const
{
	return comentarios[index];
}

//----------------------------------------------------------------------------

void Imagen :: ToP2 (const string &out)
{
	ofstream fo(out);

	if (!fo){
		cerr << "No he podido abrir el fichero " << out;
		exit(1);
	}

	//Imprimir cabecera
	fo << "P2" << endl;
	fo << comentarios;
	fo << setw(3) << fils << " " << setw(3) << cols << endl;
	fo << setw(3) << max_luminosidad << endl;



	//Imprimir el contenido de la imagen
	for (int i=0, contador=0; i<fils; ++i)
		for (int j=0; j<cols; ++j,++contador){
			fo << setw(3) << (int) img[i][j];
			fo << ((contador%20 == 0)? "\n" : " ");
		}
	fo << endl;

	//Cerrar el fichero
	fo.close();
}

//----------------------------------------------------------------------------

void Imagen :: ToP5 (const string &out)
{
	ofstream fo(out, ios::binary);

	if (!fo){
		cerr << "No he podido abrir el fichero " << out << endl;
		exit(1);
	}

	//Imprimir cabecera
	fo << "P5" << endl;
	fo << comentarios;
	fo << setw(3) << fils << " " << setw(3) << cols << endl;
	fo << setw(3) << max_luminosidad << endl;


	//Imprimir el contenido de la imagen
	for (int i=0; i<fils; ++i)
		fo.write ((const char *) img[i],cols);
	fo << endl;

	//Cerrar el fichero
	fo.close();
}

//----------------------------------------------------------------------------

//****************************************************************************
//	Métodos privados
//****************************************************************************

//----------------------------------------------------------------------------

void Imagen :: LiberaEspacio ()
{
	//Borrar imagen
	for (int i=0; i<fils ; ++i)
		delete [] img[i];
	delete[] img;

	//Borrar comentarios
	comentarios.Limpiar();

	//Actualizar los atributos
	fils = cols = max_luminosidad = 0;
	img = nullptr;
}

//----------------------------------------------------------------------------

void Imagen :: ReservaEspacio (const int f, const int c)
{
	//Actualizar atributos
	fils = f;
	cols = c;

	//Reservar espacio
	img = new pixel* [f];
	for (int i=0; i<f; ++i)
		img[i] = new pixel[c];
}

//----------------------------------------------------------------------------

//****************************************************************************
//	Sobrecarga de operadores
//****************************************************************************

//----------------------------------------------------------------------------

pixel & Imagen :: operator () (const int f, const int c) {
	return ValorPixel(f,c);
}

pixel & Imagen :: operator () (const int f, const int c) const{
	return ValorPixel(f,c);
}

//----------------------------------------------------------------------------

Imagen & Imagen :: operator = (const Imagen &otra){}

//----------------------------------------------------------------------------

Imagen & Imagen :: operator = (const int valor)
{
	for (int i=0; i<fils; ++i)
		for (int j=0; j<cols; ++j)
			img[i][j] = valor;

	return *this;
}

//----------------------------------------------------------------------------

Imagen & Imagen :: operator ! (){}

//----------------------------------------------------------------------------

Imagen & Imagen :: operator * (const Imagen & mascara){}

//----------------------------------------------------------------------------

istream & operator >> (istream & in, Imagen &i)
{
	string tipo;

	//Leo tipo
	getline (in,tipo);
	if ((tipo != "P2") && (tipo != "P5"))
	{
		cerr << "Error al leer la imagen. Debe ser de tipo P2 ó P5";
	}

	else{
		//Leo comentarios
		in >> i.comentarios;
		//Leo las dimensiones de la Imagen
		int f, c;
		in >> f >> c;

		if (!in.fail() && f>0 && c>0)
		{
			i.ReservaEspacio(f,c);

			//Leo el máximo valor de lumninosidad
			in >> i.max_luminosidad;

			//Leo el contenido de la imagen
			if (tipo == "P2"){
				int num;
				for (int z=0; z<f; ++z)
					for (int j=0; j<c; ++j){
						in >> num;
						i(z,j) = (pixel) num;
					}
			}
			else //P5
			{
				int num_pixels = f*c;
				pixel * image = new pixel [num_pixels];
				in.read (reinterpret_cast<char*> (image), num_pixels);

				if (in.gcount() != num_pixels) {
					cerr << "Error: No se pudo leer correctamente la imagen."
					     << endl;
					i.LiberaEspacio();
				}

				for (int z=0, contador = 0; z<f; ++z)
					for (int j = 0; j<c; ++j, contador++)
						i(z,j) = image[contador];
			}

		}//Lectura imagen

	}//Lectura imagen+comentarios

}//FIN

//----------------------------------------------------------------------------

//****************************************************************************
//****************************************************************************

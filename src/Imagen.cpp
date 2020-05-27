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

Imagen :: Imagen ()
	: fils(0), cols(0), max_luminosidad(255), img(nullptr), comentarios()
	{}

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

pixel & Imagen :: ValorPixel (const int fila, const int columna)
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

	fo << "P2" << endl;
	fo << setw(3) << fils << " " << setw(3) << cols;
	fo << setw(3) << max_luminosidad;

	//Imprimir cabecera
	fo << comentarios;

	//Imprimir el contenido de la imagen
	for (int i=0, contador=0; i<fils; ++i)
		for (int j=0; j<cols; ++j,++contador){
			fo << setw(3) << (int) img[i][j];
			fo << ((contador%20 == 0)? "\n" : " ");
		}

	//Cerrar el fichero
	fo.close();
}

//----------------------------------------------------------------------------

void Imagen :: ToP5 (const string &out)
{
	ofstream fo(out);

	if (!fo){
		cerr << "No he podido abrir el fichero " << out << endl;
		exit(1);
	}

	fo << "P5" << endl;
	fo << setw(3) << fils << " " << setw(3) << cols;
	fo << setw(3) << max_luminosidad;

	//Imprimir cabecera
	fo << comentarios;

	//Imprimir el contenido de la imagen
		//Abrir en modo binario
	fo.close();
	fo.open(out, ios::binary | ios::app);

	if (!fo){
		cerr << "No he podido abrir el fichero " << out << endl;
		exit(1);
	}

	for (int i=0; i<fils; ++i)
		for (int j=0; j<cols; ++j)
			fo << setw(3) << img[i][j];

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

istream & operator >> (istream & in, Imagen &img);

//----------------------------------------------------------------------------

//****************************************************************************
//****************************************************************************

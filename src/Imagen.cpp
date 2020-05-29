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
	for (int i=0; i<fils; ++i)
		for (int j=0; j<cols; ++j)
			img[i][j] = otra.img[i][j];

	//Actualizo comentarios
	comentarios+="#Creada por copia";
}

//----------------------------------------------------------------------------

Imagen :: Imagen (const int f, const int c, const int valor)
	: fils(f), cols(c), max_luminosidad(valor), comentarios()
{
	ReservaEspacio(f,c);
	(*this) = valor;

	//Comentarios
	string comentario = (f*c==0)?
					"#Creada vacia"
					:
					("#Creada " + to_string(f) + " x " + to_string(c)
					  + " a valor " + to_string(valor));

	comentarios += comentario;
}

//----------------------------------------------------------------------------

Imagen :: Imagen (string nombre_fichero)
	: Imagen()
{
	ifstream fi (nombre_fichero, ios::binary);

	if (!fi){
		cerr << "Error: No se pudo abrir el fichero " << nombre_fichero << endl;
	}
	else
	{
		fi >> (*this);
		comentarios+=("#Creada desde " + nombre_fichero);
	}
}

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
	return img[fila-1][columna-1];
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
	for (int i=0, contador=1; i<fils; ++i)
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

void Imagen :: LeerDeFichero (const string nombre_fichero)
{
	ifstream fi (nombre_fichero, ios::binary);

	if (!fi)
		cerr << "Error: No se pudo abrir el fichero " << nombre_fichero << endl;
	else
	{
		LiberaEspacio();
		fi >> (*this);
		comentarios += ("#Reiniciada desde " + nombre_fichero);
	}
}
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

pixel & Imagen :: operator () (const int f, const int c)
{
	return ValorPixel(f,c);
}

pixel & Imagen :: operator () (const int f, const int c) const
{
	return ValorPixel(f,c);
}

//----------------------------------------------------------------------------

Imagen & Imagen :: operator = (const Imagen &otra)
{
	if (this != &otra){
		LiberaEspacio();

		//Actualizo los atributos
		ReservaEspacio(otra.fils,otra.cols);
		max_luminosidad = otra.max_luminosidad;

		//Copio los comentarios
		comentarios = otra.comentarios;

		//Copio el contenido de la imagen
		for (int i=0; i<fils; i++)
			memcpy (img[i],otra.img[i],cols);

		//Añado comentario
		comentarios+="#Reiniciada desde otro objeto de la clase.";
	}

	return *this;
}

//----------------------------------------------------------------------------

Imagen & Imagen :: operator = (const int valor)
{
	for (int i=0; i<fils; ++i)
		for (int j=0; j<cols; ++j)
			img[i][j] = valor;

	if (valor>max_luminosidad) max_luminosidad = valor;

	comentarios+=("#Reiniciada al valor " + to_string(valor));

	return *this;
}

//----------------------------------------------------------------------------

Imagen & Imagen :: operator ! ()
{
	//Alterar el contenido de la imagen
	for (int i=0; i<fils; ++i)
		for (int j=0; j<cols; ++j)
			img[i][j] = (pixel)(max_luminosidad - (int)img[i][j]);

	//Actualizar los comentarios
	comentarios += "#Negativo";

	return (*this);
}

//----------------------------------------------------------------------------

Imagen Imagen :: operator * (const Imagen & mascara) const
{
	Imagen nueva;

	//Si tienen las mismas dimensiones
	if (mascara.GetCols() == cols && mascara.GetFils() == fils){

		nueva = (*this);

		//Procesar la imagen
		for (int i=1; i<=fils; ++i)
			for (int j=1; j<=cols; ++j)
				nueva(i,j) = ((int)mascara(i,j)==0)? img[i-1][j-1] : 0;

		//Actualizar los comentarios
		stringstream ioss;

			//Los escribo

		ioss << "#" << setfill('-') << setw(20) << ""<< endl;
		ioss << mascara.comentarios;
		ioss << "#" << setfill('-') << setw(20) << ""<< endl;
		ioss << "# Creada por: ENMASCARAMIENTO" << endl;

			//Los leo y actualizo
		string c;
		while (getline(ioss,c))
			nueva.comentarios += c;

	}

	return nueva;
}

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
				for (int z=1; z<=f; ++z)
					for (int j=1; j<=c; ++j){
						in >> num;
						i(z,j) = (pixel) num;
					}
			}
			else //P5
			{
				int num_pixels = f*c;
				pixel * image = new pixel [num_pixels];
				in.read (reinterpret_cast<char*> (image), num_pixels);

				//Fallo  en lectura --> vacía
				if (in.gcount() != num_pixels) {
					cerr << "Error: No se pudo leer correctamente la imagen."
					     << endl;
					i.LiberaEspacio();
				}
				//Lectura correcta --> actualizar píxeles
				else{
					for (int z=1, contador = 0; z<=f; ++z)
						for (int j = 1; j<=c; ++j, contador++)
							i(z,j) = image[contador];
				}
			}

		}//Lectura imagen

	}//Lectura imagen+comentarios

}//FIN

//----------------------------------------------------------------------------

//****************************************************************************
//****************************************************************************

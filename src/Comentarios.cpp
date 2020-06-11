/**
  * @file Comentarios.cpp
  * @brief Implementación de la clase `Comentarios`
  *
  */

#include <iostream>
#include <iomanip>
#include <sstream>
#include <stdio.h>
#include <string.h>

#include "Comentarios.h"

using namespace std;

//*****************************************************************************
//*****************************************************************************

//*****************************************************************************
//	Constructores y destructor
//*****************************************************************************
//----------------------------------------------------------------------------

Comentarios :: Comentarios () : num_comentarios(0), capacidad(0),
								los_comentarios(nullptr)
{}

//----------------------------------------------------------------------------

Comentarios :: Comentarios (const Comentarios &otro)
{
	ReservaEspacio (otro.capacidad);

	//Copiar los datos
	for (int i=0; i<otro.num_comentarios; ++i)
		los_comentarios[i] = otro.los_comentarios[i];

	num_comentarios = otro.num_comentarios;
}

//----------------------------------------------------------------------------

Comentarios :: ~Comentarios (void)
{
	LiberaEspacio();
}

//----------------------------------------------------------------------------

//*****************************************************************************
//	Operaciones
//*****************************************************************************
//----------------------------------------------------------------------------

int Comentarios :: GetNumComentarios (void) const
{
	return num_comentarios;
}

//----------------------------------------------------------------------------

void Comentarios :: LiberaEspacio ()
{
	//Sólo borro si hay algo que borrar
	if (los_comentarios != nullptr)
	{
		//Libero la memoria
		delete [] los_comentarios;

		//Actualizo los atributos
		los_comentarios = nullptr;
		num_comentarios = capacidad = 0;
	}
}

//----------------------------------------------------------------------------

void Comentarios :: ReservaEspacio (const int tam)
{
	//Reservamos espacio para tam comentarios
	los_comentarios = new string [tam];

	capacidad = tam;
}

//----------------------------------------------------------------------------

void Comentarios :: Limpiar (void)
{
	LiberaEspacio();
}

//----------------------------------------------------------------------------

void Comentarios :: Inserta (const string c, const int index)
{
	//Se cuenta desde el 1
	int index_ajustado = index-1;

	if (num_comentarios == 0){
		(*this)+=c;
	}

	else {
		//Debo reservar espacio para más comentarios
		if (num_comentarios == capacidad){
			//Copio los comentarios en un auxiliar
			string * aux = new string [capacidad];
			swap (aux,los_comentarios);

			//Reservo espacio para más comentarios
			ReservaEspacio (capacidad + AUMENTO);

			//Restauro los comentarios originales
			for (int i=0; i<num_comentarios; ++i)
				los_comentarios[i] = aux[i];

			delete[] aux;
		}

		string * aux = new string [num_comentarios-index_ajustado];

		//Copiar los comentarios en el vector auxiliar
		for (int i=0; i<(num_comentarios-index_ajustado); ++i)
			 aux [i] = los_comentarios[index_ajustado + i];

		//Añado el nuevo comentario
		los_comentarios[index_ajustado] = c;

		//Volver a poner los comentarios
		for (int i=1; i<=(num_comentarios-index_ajustado); ++i)
			 los_comentarios [index_ajustado + i] = aux[i-1];

		delete[] aux;
		num_comentarios++;
	}
}

//----------------------------------------------------------------------------

//*****************************************************************************
//	Sobrecarga de operadores
//*****************************************************************************
//----------------------------------------------------------------------------

Comentarios & Comentarios :: operator = (const Comentarios &otro)
{
	//Sólo si son iguales --> evitamos la autoasignación
	if (this != &otro)
	{
		LiberaEspacio();
		ReservaEspacio (otro.capacidad);

		//Copiar los datos
		for (int i=0; i<otro.num_comentarios; ++i)
			los_comentarios[i] = otro.los_comentarios[i];

		num_comentarios = otro.num_comentarios;
	}

	return (*this);
}

//----------------------------------------------------------------------------

Comentarios & Comentarios :: operator += (string c)
{
	if (num_comentarios == capacidad){

		//Copia de los datos
		Comentarios aux(*this);

		//Reservo memoria para nuevos comentarios
		LiberaEspacio ();
		ReservaEspacio (aux.capacidad + AUMENTO);

		//Copio los datos
		for (int i=0; i<aux.num_comentarios; ++i)
			los_comentarios[i] = aux.los_comentarios[i];

		num_comentarios = aux.num_comentarios;
	}

	//Añado el nuevo comentario
	los_comentarios[num_comentarios] = c;
	num_comentarios++;

	return *this;
}

//----------------------------------------------------------------------------

istream & operator >> (istream & in, Comentarios &c)
{
	//Reseteo
	c.LiberaEspacio();

	//Leo los comentarios
	bool continuar = true;
	string linea;

	while (continuar){
		linea.clear();

		//Leo la línea
		getline (in, linea);

		//Me posiciono en el primer caracter distinto de espacio, tabulación...
		istringstream iss (linea);
		string s;
		iss >> s;

		//Si es '#' es un comentario, sino he leído una línea de más
		//así que me salgo de la lectura para devolverla al flujo
		if (s.length() == 0 || !in.good())
			continuar = false;

		if(s[0] == '#' && continuar)
			c += (linea);
		else
			continuar = false;

	}//while

	//Devuelvo al flujo la línea que me ha hecho salir del anterior bucle
	in.putback('\n');	//getline elimina el delimitador

	for (int i=linea.length()-1; i>=0; --i)
		in.putback(linea[i]);

}

//----------------------------------------------------------------------------

string Comentarios :: operator [] (const int index) const
{
	return los_comentarios[index-1];
}

//----------------------------------------------------------------------------

ostream & operator << (ostream & out, const Comentarios &c)
{
	for (int i=0; i<c.num_comentarios; ++i)
		out << c.los_comentarios[i] << endl;
}

//----------------------------------------------------------------------------

//*****************************************************************************
//*****************************************************************************

/**
  * @file Comentarios.cpp
  * @brief Implementación de la clase `Comentarios`
  *
  */

#include <iostream>
#include <iomanip>
#include <sstream>

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

//*****************************************************************************
//	Sobrecarga de operadores
//*****************************************************************************
//----------------------------------------------------------------------------

Comentarios & Comentarios :: operator = (const Comentarios &otro)
{
	//Sólo si son iguales --> evitamos la autoasignación
	if (this != &otro)
	{
		Comentarios aux (otro);

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
		getline (in,linea);

		istringstream iss (linea);
		string s;
		iss >> s;

		if (s[0] == '#')
			c += (linea);
		else
			continuar = false;
	}

	for (int i=linea.length()-1; i>=0; --i)
		in.putback(linea[i]);
}

//----------------------------------------------------------------------------

ostream & operator << (ostream & out, Comentarios &c)
{
	for (int i=0; i<c.num_comentarios; ++i)
		out << c.los_comentarios[i] << endl;
}

//----------------------------------------------------------------------------

//*****************************************************************************
//*****************************************************************************

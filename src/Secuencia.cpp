/***************************************************************************/
/***************************************************************************/
// FUNDAMENTOS DE PROGRAMACIÓN
//
// (C) FRANCISCO JOSÉ CORTIJO BON
// DEPARTAMENTO DE CIENCIAS DE LA COMPUTACIÓN E INTELIGENCIA ARTIFICIAL
//
// Clase "Secuencia"
//
// Representación: array dinámico para alojar los datos en el Heap.
// Los datos son de tipo "TipoBaseSecuencia"
//
// Definición de la clase Secuencia (versión 2).
// Incluye:
//		* constructor de copia
//		* destructor
//      * Operador =
//      * Operadores de acceso
//      * Operadores varios
//
// Fichero: Secuencia.cpp
//
/***************************************************************************/
/***************************************************************************/

#include "Secuencia.h"
#include "TipoBase_Secuencia.h"

#include <cstring>
#include <string>
#include <iostream>
using namespace std;

/***************************************************************************/
/***************************************************************************/
// Constructores
// Si se llama sin argumentos crea una secuencia con capacidad = TAMANIO.
// Si se llama con un argumento, su valor será la capacidad inicial.
// POST: La secuencia creada estará vacía (EstaVacia()== true)

Secuencia :: Secuencia (int la_capacidad)
	: capacidad (la_capacidad),
	  total_utilizados (0)
{
	ReservarMemoria (capacidad);
}

/***************************************************************************/
/***************************************************************************/
// Constructor de copia

Secuencia :: Secuencia (const Secuencia & otro)
{
	ReservarMemoria (otro.capacidad);
	CopiarDatos (otro);
}

/***************************************************************************/
/***************************************************************************/
// Destructor

Secuencia :: ~Secuencia (void)
{
	LiberarMemoria();
}

/***************************************************************************/
/***************************************************************************/
// Devuelve el número de casillas ocupadas

int Secuencia :: TotalUtilizados (void) const
{
	return (total_utilizados);
}

/***************************************************************************/
/***************************************************************************/
// Devuelve el número de casillas disponibles

int Secuencia :: Capacidad (void) const
{
	return (capacidad);
}

/***************************************************************************/
/***************************************************************************/
// Devuelve "true" si la secuencia está vacía (total_utilizados == 0)

bool Secuencia :: EstaVacia (void) const
{
	return (total_utilizados == 0);
}

/***************************************************************************/
/***************************************************************************/
// "Vacía" completamente la secuencia
// POST: EstaVacia() == true
// POST: Capacidad() == TAMANIO.

void Secuencia :: EliminaTodos()
{
	LiberarMemoria();		// La secuencia queda vacía
	ReservarMemoria (TAMANIO);	// Capacidad = TAMANIO
}

/***************************************************************************/
/***************************************************************************/
// Busca la posición de un valor.
// Parámetros: valor, el valor buscado.
// Devuelve la posición del primer valor coincidente con "valor",
//      o -1 si no se encuentra.
// Posiciones: 1, 2, ..., TotalUtilizados()

int Secuencia :: Buscar (TipoBaseSecuencia valor) const
{
    bool sigo = true;
    bool encontrado = false;

	int pos = 0;

    while ((pos < total_utilizados) && sigo) {

        if (vector_privado[pos] == valor) {
            sigo = false;
            encontrado = true;
        }
        else
            pos++;
	}

	return (encontrado ? (pos+1) : -1);
}

/***************************************************************************/
/***************************************************************************/
// Inserta el valor "nuevo" en la posición dada por "indice".
// "Desplaza" todos los enteros una posición a la derecha antes de
// copiar en "indice" en valor "nuevo".
// Se redimensionará el vector dinámico de datos si no tuviera suficiente
// espacio disponible.
// PRE: 1 <= indice <= TotalUtilizados()

void Secuencia :: Inserta (int pos, TipoBaseSecuencia nuevo)
{
	// Comprobar si hay que redimensionar el array dinámico

	int umbral_redimension = (PORC_PETICION*capacidad)/100;

	// cout << "umbral_redimension = " << umbral_redimension << endl;

	if (total_utilizados >= umbral_redimension)
		Redimensionar ();

	// "Desplazar" los valores desde la casilla "indice" hasta el final
	// una posición a la derecha
	memmove (&vector_privado[pos], &vector_privado[pos-1],
                 total_utilizados-pos+1*sizeof(TipoBaseSecuencia));

	// Escribir "nuevo" en la casilla "indice" y actualizar "total_utilizados"
	vector_privado [pos-1] = nuevo;
	total_utilizados++;
}

/***************************************************************************/
/***************************************************************************/
// Eliminar el contenido de la "casilla" cuya posición es "pos".
// PRE: 1 <= pos <= TotalUtilizados()
/*
	Una consecuencia de la eliminación podría ser la reducción de la
	capacidad de la secuencia. Esto ocurrirá cuando el número de casillas
	usadas es inferior al "PROC_REDUCCION" de la capacidad actual.

	El número de casillas finales no será fijo, sino que será un "PORC_EXTRA"
	superior a la ocupación de la secuencia después de la eliminación.
*/

void Secuencia :: Elimina (int pos)
{
    if ((pos >= 1) && (pos <= total_utilizados)) {

		// "Desplazar" los valores desde la casilla siguiente a "indice"
		// hasta el final una posición a la izquierda

		memmove (&vector_privado[pos-1], &vector_privado[pos],
                 (total_utilizados-pos)*sizeof(TipoBaseSecuencia));

		// Actualizar "total_utilizados"
        total_utilizados--;
    }
}

/***********************************************************************/
/***********************************************************************/
// Metodo de acceso individual a elementos
// Metodo de lectura
// PRE: 1 <= pos <=TotalUtilizados()

TipoBaseSecuencia & Secuencia :: operator [] (const int pos)
{
	return (Valor(pos));
}

TipoBaseSecuencia & Secuencia :: operator [] (const int pos) const
{
	return (Valor(pos));
}

/***********************************************************************/
/***********************************************************************/
// Operador de asignación desde otro dato Secuencia
// Parámetros: otra (referencia), objeto que sirve de modelo.

Secuencia & Secuencia :: operator = (const Secuencia & otro)
{
	if (this != &otro) { // Evitar autoasignación

		// Libera la memoria ocupada
		LiberarMemoria();

		// Reserva de memoria para los datos del otro vector
		ReservarMemoria (otro.capacidad);

		// Copia los campos privados y los coeficientes
		CopiarDatos(otro);
	}
	return (*this);  // Devuelve el objeto implicito:
					 // parte izquierda de la asignación
}

/***********************************************************************/
/***********************************************************************/
// Operador de asignación desde un dato TipoBaseSecuencia
// Parámetros: valor (referencia), dato que sirve de modelo para ser
//		copiado en todas las casillas de la Secuencia.

Secuencia & Secuencia :: operator = (const TipoBaseSecuencia & valor)
{
	for (int i=0; i < total_utilizados; i++)
		vector_privado[i] = valor;

	return (*this); // devuelve el objeto implicito:
					// parte izquierda de la asignación
}

/***********************************************************************/
/***********************************************************************/
// Operador binario de adición para concatenar dos secuencias
// Parámetros: otra (referencia), la secuencia que se va a concatenar
//		a una copia de la secuencia "sec"
// Devuelve una nueva secuencia, resultado de concatenar una copia de la
// 		secuencia "sec" y "otra".
// POST: No se modifican las secuencias "sec" ni "otra".

 Secuencia operator + (const Secuencia & sec, const Secuencia & otra)
 {
	Secuencia tmp (sec); // Copia de la primera secuencia

	for (int pos=0; pos<otra.total_utilizados; pos++)
		tmp.AniadeValor (otra.vector_privado[pos]);

	return (tmp);
}

/***********************************************************************/
/***********************************************************************/
// Operador binario de adición para añadir un valor TipoBaseSecuencia a
// una copia de la secuencia "sec".
// Parámetros: valor, el valor que se va a añadir a en la copia de la
//		secuencia "sec".
// Devuelve una nueva secuencia, resultado de añadir "valor" a una copia
// 		de la secuencia "sec".
// POST: No se modifican las secuencias "sec" ni "otra".

Secuencia operator + (const Secuencia & sec, const TipoBaseSecuencia valor)
{
	Secuencia tmp (sec); // Copia de la primera secuencia

	tmp.AniadeValor (valor);

	return (tmp);
}

/***********************************************************************/
/***********************************************************************/
// Operador binario de adición para insertar un valor TipoBaseSecuencia
// al principio de una copia de la secuencia "sec".
// Parámetros: valor, el valor que se va a insertar en la copia de la
// 		secuencia "sec".
// Devuelve una nueva secuencia, resultado de añadir "valor" a una copia
// 		de la secuencia "sec".
// POST: No se modifican las secuencias "sec" ni "otra".

Secuencia operator + (const TipoBaseSecuencia valor, const Secuencia & sec)
{
	Secuencia tmp (sec); // Copia de la primera secuencia

	tmp.Inserta (0, valor); // Inserta enl casilla 0

	return (tmp);
}

/***********************************************************************/
/***********************************************************************/
// Operador binario de borrado entre dos secuencias.
// Parámetros: otra (referencia), la secuencia que contiene los valores
// 		que se van a eliminar de una copia de la secuencia implícita.
// Devuelve una nueva secuencia, resultado de eliminar de una copia de
// 		la secuencia implícita los valores de la secuencia "otra".
// POST: No se modifican las secuencias implícita ni "otra".

Secuencia Secuencia :: operator - (const Secuencia & otra)
{
	Secuencia tmp (*this);	// Copia del objeto implícito

	for (int pos=0; pos<otra.total_utilizados; pos++) {
		tmp.EliminarValor (otra.vector_privado[pos]);
	}

	return (tmp);
}

/***********************************************************************/
/***********************************************************************/
// Operador binario de borrado en una secuencia.
// Parámetros: valor, el valor que se va a eliminar de una copia de
//		la secuencia implícita.
// Devuelve una nueva secuencia, resultado de eliminar de una copia de
// 		la secuencia implícita el valor "valor".
// POST: No se modifica la secuencia implícita.

Secuencia Secuencia :: operator - (const TipoBaseSecuencia valor)
{
	Secuencia tmp (*this);	// Copia del objeto implícito

	tmp.EliminarValor (valor);

	return (tmp);
}

/***********************************************************************/
/***********************************************************************/
// Operador combinado +=
// Operador combinado de adición para añadir un valor de tipo
// TipoBaseSecuencia a la secuencia implícita.
// Parámetros: valor, el valor que se va a añadir a la secuencia implícita.
// POST: Se modifica la secuencia implícita.

Secuencia & Secuencia :: operator += (TipoBaseSecuencia valor)
{
	// Añade (al final) un nodo con "valor"
	AniadeValor (valor);

	return (*this);
}

/***********************************************************************/
/***********************************************************************/
// Operador combinado -=
// Operador combinado de adición para añadir un valor de tipo
// TipoBaseSecuencia a la secuencia implícita.
// Parámetros: valor, el valor que se va a añadir a la secuencia implícita.
// POST: Se modifica la secuencia implícita.

Secuencia & Secuencia :: operator -= (TipoBaseSecuencia valor)
{
	// Elimina el primer nodo con "valor"
	EliminarValor (valor);

	return (*this);
}

/***********************************************************************/
/***********************************************************************/
// Compone un string con todos los caracteres que están
// almacenados en la secuencia y lo devuelve.

string Secuencia :: ToString() const
{
    string cadena;

	cadena = "[ ";

    for (int i=0; i<total_utilizados; i++) {

		#ifdef INT
        cadena = cadena + "  " + to_string(vector_privado[i]);
		#else
		#ifdef CHAR
        cadena = cadena + "  " + vector_privado[i];
		#else
		#ifdef DOUBLE
        cadena = cadena + "  " + to_string(vector_privado[i]);
		#endif
		#endif
		#endif
	}

	cadena = cadena + "]";

    return (cadena);
}

/***********************************************************************/
/***********************************************************************/
// Operador ==
// Dos datos Secuencia son iguales si tienen el mismo número de casillas
// y los cobntenidos son iguales y en las mismas posiciones

bool Secuencia :: operator == (const Secuencia & otro) const
{
	// Si las dimensiones son diferentes, los vectores son distintos
	bool iguales = (total_utilizados == otro.total_utilizados);

	if (iguales) { // Comparar valor a valor

		for (int pos = 0; (pos<total_utilizados) && iguales; pos++)

			// Se supone que los datos de tipo TipoBaseSecuencia son
			// comparables con el operador !=

			if (vector_privado[pos] != otro.vector_privado[pos])
				iguales = false;
	}
	return (iguales);
}

/***********************************************************************/
/***********************************************************************/
// Operador !=

bool Secuencia :: operator != (const Secuencia & otro) const
{
	return !((*this) == otro);
}

/***********************************************************************/
/***********************************************************************/
// Operador >
// Se usa un criterio similar al que se sigue en la comparación (strcmp)
// de dos cadenas de caracteres clásicas.

bool Secuencia :: operator > (const Secuencia & otro) const
{
	int fin1 = total_utilizados;		// Número de elementos de los
	int fin2 = otro.total_utilizados;	// dos vectores a commparar

	// Recorrer los dos vectores mientras queden elementos por
	// explorar y continúen siendo iguales en los dos vectores

	int pos=0; // Posición común en ambos vectores

	bool iguales = true;

	TipoBaseSecuencia valor_este; // valor del nodo del objeto implícito
	TipoBaseSecuencia valor_otro; // valor del nodo del objeto "otro"

	while ((pos<=fin1) && (pos<=fin2) && (iguales)) {

		valor_este = vector_privado[pos];
		valor_otro = otro.vector_privado[pos];

		if (valor_este != valor_otro) iguales = false;
		else pos++;
	}

	bool mayor = false;

	// No se ha alcanzado el final en ningún vector, pero se ha
	// encontrado una discrepancia
	if ((pos<=fin1) && (pos<=fin2) && (valor_este > valor_otro))
		mayor = true;

	// Se ha agotado el vector "otro"
	if ((pos<=fin1) && (pos>fin2))
		mayor = true;

	return (mayor);
}

/***********************************************************************/
/***********************************************************************/
// Operador  <

bool Secuencia :: operator < (const Secuencia & otro) const
{
	return (!(((*this) > otro) || ((*this) == otro)));
}

/***********************************************************************/
/***********************************************************************/
// Operador >=

bool Secuencia :: operator >= (const Secuencia & otro) const
{
	return (((*this) > otro) || ((*this) == otro));
}

/***********************************************************************/
/***********************************************************************/
// Operador <=

bool Secuencia :: operator <= (const Secuencia & otro) const
{
	return (((*this) < otro) || ((*this) == otro));
}

/***********************************************************************/
/***********************************************************************/


/***************************************************************************/
/***************************************************************************/
// MÉTODOS PRIVADOS DE LA CLASE Secuencia
/***************************************************************************/
/***************************************************************************/

/***************************************************************************/
/***************************************************************************/
// Pide memoria para guardar "num_casillas" datos

void Secuencia :: ReservarMemoria (const int num_casillas)
{
	vector_privado = new TipoBaseSecuencia[num_casillas];
	capacidad = num_casillas;
}

/***************************************************************************/
/***************************************************************************/
// Libera memoria

void Secuencia :: LiberarMemoria (void)
{
	if (vector_privado) {

		delete [] vector_privado;

		vector_privado = 0;
		capacidad = 0;
		total_utilizados = 0;
	}
}

/***************************************************************************/
/***************************************************************************/
// Copiar datos desde otro objeto de la clase
// PRE: Se ha reservado memoria para los datos

void Secuencia :: CopiarDatos (const Secuencia & otro)
{
	// Copia los valores de los campos privados desde "otro"
	capacidad = otro.capacidad;
	total_utilizados = otro.total_utilizados;

	// Copiar los valores de los datos
	memcpy (vector_privado, otro.vector_privado,
            total_utilizados*sizeof(TipoBaseSecuencia));
}

/***************************************************************************/
/***************************************************************************/
// Redimensiona el vector dinámico y copia los datos en el nuevo almacén.
//
// Pedirá memoria adicional si el número de casillas usadas es superior al
// "PROC_PETICION" de la capacidad actual. El número de casillas adicionales
// será el "PORC_CRECIMIENTO" de la capacidad actual (no será un valor fijo).

void Secuencia :: Redimensionar (void)
{
	int casillas_adicionales = (PORC_CRECIMIENTO*capacidad)/100;

	int minimo = MIN_CRECIMIENTO;
 	capacidad += max(casillas_adicionales,minimo);

	//cout << endl;
	//cout << "REDIMENSIONADO HASTA --> " << capacidad << " CASILLAS" << endl;
	//cout << endl;

	// Pedir memoria para el nuevo almacen
	TipoBaseSecuencia * tmp = new TipoBaseSecuencia[capacidad];

	// Copiar los datos
	memcpy (tmp, vector_privado, total_utilizados*sizeof(TipoBaseSecuencia));

	// Liberar la memoria del antiguo almacén
	delete [] vector_privado;

	// Reasignacion del puntero "vector_privado" para que referencie
	// a la nueva zona de memoria ampliada y con los datos copiados.
	vector_privado = tmp;
}

/***************************************************************************/
/***************************************************************************/
// Devuelve una referencia al elemento de la casilla "indice"
// PRE: 1 <= pos <= TotalUtilizados()

TipoBaseSecuencia & Secuencia :: Valor (const int pos) const
{
    return (vector_privado[pos-1]);
}

/***************************************************************************/
/***************************************************************************/
// Añade un elemento a la secuencia.
// El nuevo elemento se coloca al final.
// Se redimensionará el vector dinámico de datos si no tuviera suficiente
// espacio disponible.
// Parámetros: nuevo, el valor que se va a añadir.

void Secuencia :: AniadeValor (TipoBaseSecuencia nuevo)
{
	// Comprobar si hay que redimensionar el array dinámico

	int umbral_redimension = (PORC_PETICION*capacidad)/100;

	// cout << "umbral_redimension = " << umbral_redimension << endl;

	if (total_utilizados >= umbral_redimension)
		Redimensionar ();

	// Añadir al final del array dinámico y actualizar "total_utilizados"
	vector_privado [total_utilizados] = nuevo;
	total_utilizados++;
}

/***************************************************************************/
/***************************************************************************/
// Borra la primera aparición del valor "valor" de la secuencia.
// Parámetros: valor, el valor que se va a eliminar.

void Secuencia :: EliminarValor (TipoBaseSecuencia valor)
{
	int pos = Buscar (valor);

	// Si pos > 0 se encontró el alumno buscado: eliminarlo
	if (pos > 0) Elimina (pos);
}

/***************************************************************************/
/***************************************************************************/

ostream & operator << (ostream & os, const Secuencia & s)
{
	string cadena;

	for (int i=0; i<s.total_utilizados; i++) {

		#ifdef INT
		cadena = cadena + "  " + to_string(s.vector_privado[i]);
		#else
		#ifdef CHAR
		cadena = cadena + "  " + s.vector_privado[i];
		#else
		#ifdef DOUBLE
		cadena = cadena + "  " + to_string(s.vector_privado[i]);
		#endif
		#endif
		#endif
	}

	os << cadena;

	return os;
}

/***************************************************************************/
/***************************************************************************/

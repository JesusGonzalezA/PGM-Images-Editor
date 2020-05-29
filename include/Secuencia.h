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
// Declaración de la clase Secuencia (versión 2).
// Incluye:
//		* constructor de copia
//		* destructor
//      * Operador =
//      * Operadores de acceso
//      * Operadores varios
//
// Fichero: Secuencia.h
//
/***************************************************************************/

#ifndef CLASS_SECUENCIA_TIPOBASE_SECUENCIA
#define CLASS_SECUENCIA_TIPOBASE_SECUENCIA

#include "TipoBase_Secuencia.h"

#include <string>
#include <iostream>
using namespace std;

/////////////////////////////////////////////////////////////////////////////

class Secuencia {

private:

	// Núm.casillas disponibles (capacidad) por defecto
    static const int TAMANIO = 50;

	// Si el porcentaje de casillas usadas > PORC_PETICION --> Crecimiento
    static const int PORC_PETICION = 75;
	// La capacidad aumenta PORC_CRECIMIENTO sobre la capacida actual
    static const int PORC_CRECIMIENTO = 10;
	// El valor mínimo de casillas para el crecimiento será MIN_CRECIMIENTO
    static const int MIN_CRECIMIENTO = 5;

	// Si el porcentaje de casillas usadas < PORC_REDUCCION --> Decrecimiento
    static const int PORC_REDUCCION = 50;
	// La capacidad queda PORC_EXTRA sobre la ocupación actual
    static const int PORC_EXTRA = 20;


	// "vector_privado" es un puntero a un array dinámico de
	// datos "TipoBaseSecuencia"
    TipoBaseSecuencia * vector_privado;

    // PRE: 0 <= capacidad
    int capacidad; // Núm.casillas ocupadas

    // PRE: 0 <= total_utilizados <= capacidad
    int total_utilizados; // Núm.casillas ocupadas

public:

    /***********************************************************************/
    // Constructores
	// Si se llama sin argumentos crea una secuencia con capacidad = TAMANIO.
	// Si se llama con un argumento, su valor será la capacidad inicial.
	// POST: La secuencia creada estará vacía (EstaVacia()== true)

    Secuencia (int la_capacidad=TAMANIO);

    /***********************************************************************/
    // Constructor de copia

    Secuencia (const Secuencia & otro);

    /***********************************************************************/
    // Destructor

    ~Secuencia (void);

    /***********************************************************************/
    /***********************************************************************/


    /***********************************************************************/
    // Devuelve el número de casillas ocupadas

    int TotalUtilizados (void) const;

    /***********************************************************************/
    // Devuelve el número de casillas disponibles

    int Capacidad (void) const;

    /***********************************************************************/
    // Devuelve "true" si la secuencia está vacía (total_utilizados == 0)

	bool EstaVacia (void) const;

    /***********************************************************************/
    // "Vacía" completamente la secuencia
	// POST: Capacidad() == TAMANIO.
	// POST: EstaVacia() == true

	void EliminaTodos();

    /***********************************************************************/
    // Busca la posición de un valor.
    // Parámetros: valor, el valor buscado.
    // Devuelve la posición del primer valor coincidente con "valor",
    //      o -1 si no se encuentra.
    // Posiciones: 1, 2, ..., TotalUtilizados()
    /***********************************************************************/

    int Buscar (TipoBaseSecuencia valor) const;

    /***********************************************************************/
    // Inserta el valor "nuevo" en la posición dada por "indice".
    // "Desplaza" todos los enteros una posición a la derecha antes de
	// copiar en "indice" en valor "nuevo".
	// PRE: 1 <= indice <= TotalUtilizados()

	void Inserta (int pos, TipoBaseSecuencia nuevo);

    /***********************************************************************/
    // Eliminar el contenido de la "casilla" cuya posición es "pos".
    // PRE: 1 <= pos <= TotalUtilizados()

    void Elimina (int pos);

    /***********************************************************************/
    // Compone un string con todos los caracteres que están
    // almacenados en la secuencia y lo devuelve.

    string ToString() const;

    /***********************************************************************/
    // Metodo de acceso individual a elementos: operator []
    // Metodo de escritura / lectura
    // PRE: 1 <= indice <= TotalUtilizados()

    TipoBaseSecuencia & operator [] (const int indice);
    TipoBaseSecuencia & operator [] (const int indice) const;

    /***********************************************************************/
    // Operador de asignación

    Secuencia & operator = (const Secuencia & otro);
    Secuencia & operator = (const TipoBaseSecuencia & valor);

    /***********************************************************************/
    // Operador binarios de adición y borrado

    friend Secuencia operator + (const Secuencia & sec,
                                 const Secuencia & otra);
    friend Secuencia operator + (const Secuencia & sec,
                                 const TipoBaseSecuencia valor);
    friend Secuencia operator + (const TipoBaseSecuencia valor,
                                 const Secuencia & sec);

    Secuencia operator - (const Secuencia & otra);
    Secuencia operator - (const TipoBaseSecuencia valor);

    /***********************************************************************/
    // Operadores combinados

    Secuencia & operator += (const TipoBaseSecuencia valor);
    Secuencia & operator -= (const TipoBaseSecuencia valor);

    /***********************************************************************/
    // Operadores relacionales

    bool operator == (const Secuencia & otro) const;
    bool operator != (const Secuencia & otro) const;
    bool operator >  (const Secuencia & otro) const;
    bool operator <  (const Secuencia & otro) const;
    bool operator >= (const Secuencia & otro) const;
    bool operator <= (const Secuencia & otro) const;

    /***********************************************************************/

	friend ostream & operator << (ostream & os, const Secuencia & s);

	/***********************************************************************/


private:

    /***********************************************************************/

	// Pide memoria para guardar "num_casillas" datos

	void ReservarMemoria (const int num_casillas);

    /***********************************************************************/
	// Libera memoria

	void LiberarMemoria (void);

    /***********************************************************************/
	// Copiar datos desde otro objeto de la clase
	// PRE: Se ha reservado memoria para los datos

	void CopiarDatos (const Secuencia & otro);

	/***********************************************************************/
	// Redimensiona el vector dinámico y copia los datos en el nuevo almacén.
	//
	// Pedirá memoria adicional si el número de casillas usadas es superior
	// al "PROC_PETICION" de la capacidad actual. El número de casillas
	// adicionales será el "PORC_CRECIMIENTO" de la capacidad actual.

	void Redimensionar (void);

    /***********************************************************************/
    // Devuelve una referencia al elemento de la casilla "indice"
    // PRE: 1 <= pos <= TotalUtilizados()

    TipoBaseSecuencia & Valor (const int pos) const;

    /***********************************************************************/
    // Añade un elemento a la secuencia.
    // El nuevo elemento se coloca al final del vector.

    void AniadeValor (const TipoBaseSecuencia nuevo);

    /***********************************************************************/
    // Borra la primera aparición del valor "valor"

    void EliminarValor (TipoBaseSecuencia valor);

    /***********************************************************************/

};

/////////////////////////////////////////////////////////////////////////////

#endif

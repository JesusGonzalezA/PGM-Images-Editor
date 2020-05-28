/**
  * @file Imagen.h
  * @brief Interfaz de la clase `Imagen`
  *
  */

#ifndef _IMAGEN_H_
#define _IMAGEN_H_

#include <string.h>

#include "Comentarios.h"

using namespace std;

/**
  * @class Imagen
  *
  */

typedef unsigned char pixel;

class Imagen{
	private:
		/**
		  * @brief Filas
 		  * @pre 0 <= fils
		  */
		int fils;

		/**
		  * @brief Columnas
 		  * @pre 0 <= cols
		  */
		int cols;

		/**
		  * @brief Máximo valor de luminosidad
		  * @pre 0 <= max_luminosidad
		  */
		int max_luminosidad;

		/**
		  * @brief Contenido de la imagen
		  */
		pixel ** img;

		/**
		  * @brief Comentarios de la imagen
		  */
		Comentarios comentarios;


		/**
		  * @brief Borra la imagen
		  */
		void LiberaEspacio ();

		/**
		  * @brief Reserva espacio para guardar una imagen con las dimensiones
		   	   	   pasadas como argumento
		  * @param f : filas a reservar
		  * @param c : columnas a reservar
		  * @pre `f` >= 0
		  * @pre `c` >= 0
		  * @post `fils` = `f`
		  * @post `cols` = `c`
		  * @post `img` tiene espacio para `fxc` píxeles
		  */
		void ReservaEspacio (const int f, const int c);

	public:

		/**
		  * @brief Constructor por copia
		  * @param otra Imagen a copiar
		  */
		Imagen (const Imagen & otra);

		/**
		  * @brief Constructor. Crea una imagen rectangular vacía.
		  * @param f filas
		  * @param c columnas
		  * @param v valor al que se inicializan los píxeles de la imagen
		  * @pre (f>=0)
		  * @pre (c>=0)
		  * @pre (valor>=0)
		  * @post Se crea una imagen de `fxc` dimensiones cuyos píxeles valen v
		  */
		Imagen (const int f = 0, const int c = 0, const int valor = 0);

		/**
		  * @brief Constructor. Crea una imagen a partir de un fichero PGM.
		  * @param nombre_fichero nombre del fichero PGM
		  */
		Imagen (string nombre_fichero);

		/**
		  * @brief Destructor
		  */
		~Imagen ();

		/**
		  * @brief Consultor para filas
		  * @return `fils`
		  */
		int GetFils() const;

		/**
		  * @brief Consultor para columnas
		  * @return `cols`
		  */
		int GetCols() const;

		/**
		  * @brief Consultor/Modificador del píxel en la posición
		  		   `fila x columna`
		  * @param fila Fila en la que se encuentra el píxel
		  * @param columna Columna en la que se encuentra el píxel
		  * @pre (fila>=0) && (fila<=fils)
		  * @pre (columna>=0) && (columna<=cols)
		  * @return Devuelve una referencia al píxel apuntado por
		  	`fila x columna`
		  */
		pixel & ValorPixel (const int fila, const int columna) const;

		/**
		  * @brief Devuelve el número de comentarios guardados
		  * @return Número de comentarios guardados
		  */
		int GetNumComentarios(void) const;

		/**
		  * @brief Consulta un comentario dado por un índice
		  * @param index índice del comentario a consultar
		  * @return Devuelve el comentario en el índice `index` o un string
		            vacío si `index < 0  ||  index >= GetNumComentarios()`
	 	  */
		string GetComentario (const int index) const;

		/**
		  * @brief Guarda la imagen como PGM P2 en el fichero de salida
		  * @param out nombre del fichero donde se guardará la imagen
		  */
		void ToP2 (const string &out);

		/**
		  * @brief Guarda la imagen como PGM P5 en el fichero de salida
		  * @param out nombre del fichero donde se guardará la imagen
		  */
		void ToP5 (const string &out);

		/**
		  * @brief Operador de asignación
		  * @param otro : Imagen a copiar
		  * @post Se añade el comentario: "Reiniciada
		          desde otro objeto de la clase"
		  * @return Devuelve una referencia al objeto apuntado por `this`
	 	  */
		Imagen & operator = (const Imagen &otra);

		/**
		  * @brief Operador de acceso
		  * @param f : fila
		  * @param c : columna
		  * @pre `f >= 0` y `f<fils`
		  * @pre `c >= 0` y `c<cols`
		  * @return Devuelve una copia del valor del pixel indicado
	 	  */
		pixel & operator () (const int f, const int c) const;

		/**
		  * @brief Operador de acceso
		  * @param f : fila
		  * @param c : columna
		  * @pre `f >= 0` y `f<fils`
		  * @pre `c >= 0` y `c<cols`
		  * @return Devuelve una referencia al pixel indicado
	 	  */
		pixel & operator () (const int f, const int c);

		/**
		  * @brief Operador de asignación
		  * @param valor : Valor asignado a todos los píxeles
		  * @post Se añade el comentario: "Reiniciada al valor `valor`"
		  * @return Devuelve una referencia al objeto apuntado por `this`
	 	  */
		Imagen & operator = (const int valor);

		/**
		  * @brief Operador `!`
		  * @brief Calcula el negativo de la imagen
		  * @post Se altera el valor de cada píxel a su negativo
		  * @post Añade el comentario: `Negativo`
		  * @return Devuelve una referencia al objeto apuntado por `this`
	 	  */
		Imagen & operator ! ();

		/**
		  * @brief Operador `!`
		  * @brief Crea una imagen en la que sólo es visible lo índicado por la
		  *        máscara
		  * @param mascara Imagen que actúa como máscara
		  * @post Añade una línea formada por guiones a los comentarios y
		          los comentarios de `mascara`.
		  * @post Añade una línea formada por guiones a los comentaros y
		          el comentario: `Creada por: ENMASCARAMIENTO`
		  * @post Si no tienen el mismo tamaño se devuelve una imagen vacía
		  * @return Devuelve una referencia al objeto apuntado por `this`
	 	  */
		Imagen & operator * (const Imagen & mascara);

		/**
		  * @brief Operador de extracción de flujo
		  * @brief Lee una imagen de un flujo de entrada
		  * @param in : flujo de entrada
		  * @param c : imagen a leer
		  * @pre El flujo contiene una imagen en formato PGM
		  * @pre El flujo debe estar abierto en modo binario
		  * @return Devuelve una referencia al flujo de entrada
		  */
		friend istream & operator >> (istream & in, Imagen &img);
};

#endif

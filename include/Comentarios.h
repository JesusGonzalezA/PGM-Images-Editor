/**
  * @file Comentarios.h
  * @brief Interfaz de la clase `Comentarios`
  *
  */

 #ifndef _COMENTARIOS_H_
 #define _COMENTARIOS_H_

 #include <iostream>
 using namespace std;

/**
  * @class Comentarios
  * @brief Recoge cada operación relevante realizada sobre una Imagen
  *
  */
class Comentarios{
	private:
		/**
 		  * @pre 0 <= num_comentarios
		  */
		int num_comentarios;
		/**
		  * Almacén de comentarios
	   	  */
		string * los_comentarios;
	public:
		/**
		  * @brief Constructor por defecto
		  */
		Comentarios ();

		/**
		  * @brief Constructor de copia
		  * @param otro : Comentarios a copiar
		  */
		Comentarios (const Comentarios &otro);

		/**
		  * @brief Devuelve el número de comentarios guardados
		  * @return Número de comentarios guardados
		  */
		int GetNumComentarios (void) const;

		/**
		  * @brief Operador de asignación
		  * @param otro : Comentarios a copiar
		  * @return Devuelve una referencia al objeto apuntado por this
	 	  */
		Comentarios & operator = (const Comentarios &otro);

		/**
		  * @brief Operador +=
		  * @brief Añade un comentario
		  * @param c : Comentario a añadir
		  * @return Devuelve una referencia al objeto apuntado por this
		  */
		Comentarios & operator += (string c);

		/**
		  * @brief Operador de extracción de flujo
		  * @brief Lee comentarios de un flujo de entrada
		  * @param in : flujo de entrada
		  * @param c : comentarios a leer
		  * @return Devuelve una referencia al flujo de entrada
		  */
		friend istream & operator >> (istream & in, Comentarios &c);

		/**
		  * @brief Operador de inserción en flujo
		  * @brief Escribe los comentarios en un flujo de salida
		  * @param out : flujo de salida
		  * @param c : comentarios a escribir
		  * @return Devuelve una referencia al flujo de salida
		  */
		friend ostream & operator << (ostream & out, Comentarios &c);
};

#endif

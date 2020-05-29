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
		  * @pre num_comentarios < capacidad
		  */
		int num_comentarios;

		/**
		  * @brief Nos permite mantener el control de la estructura
		  * @pre 0 <= capacidad
		  */
		int capacidad;

		/**
		  * @brief Cuánto aumenta la capacidad cuando queremos añadir un
		           nuevo comentario y no tenemos espacio.
	      */
		static const int AUMENTO = 5;
		/**
		  * Almacén de comentarios
	   	  */
		string * los_comentarios;

		/**
		  * @brief Resetea los comentarios
		  */
		void LiberaEspacio ();

		/**
		  * @brief Reserva espacio para guardar comentarios
		  * @param tam : espacio a reservar
		  * @pre `tam` >= 0
		  * @post `num_comentarios` = `tam`
		  * @post `los_comentarios` tiene espacio para `tam` comentarios
		  */
		void ReservaEspacio (const int tam);

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
		  * @brief Destructor
		  */
		~Comentarios (void);

		/**
		  * @brief Devuelve el número de comentarios guardados
		  * @return Número de comentarios guardados
		  */
		int GetNumComentarios (void) const;

		/**
		  * @brief Vacía los comentarios
		  */
		void Limpiar (void);

		/**
		  * @brief Operador de asignación
		  * @param otro : Comentarios a copiar
		  * @return Devuelve una referencia al objeto apuntado por `this`
	 	  */
		Comentarios & operator = (const Comentarios &otro);

		/**
		  * @brief Operador `+=`
		  * @brief Añade un comentario
		  * @param c : Comentario a añadir
		  * @return Devuelve una referencia al objeto apuntado por `this`
		  */
		Comentarios & operator += (string c);

		/**
		  * @brief Inserta un comentario en la lista de comentarios
		  * @param c El comentario a insertar
		  * @param index Índice donde se insertará el comentario.
		  * @pre (index>0) && (index<=num_comentarios+1)
		  * @pre `c` debe empezar por `#`
		  */
		void Inserta (const string c, const int index);

		/**
		  * @brief Operador `[]`
		  * @brief Permite el acceso para consulta
		  * @param index índice del comentario
		  * @pre (index>0) && (index<=num_comentarios)
		  */
		string operator [] (const int index) const;

		/**
		  * @brief Operador de extracción de flujo
		  * @brief Lee comentarios de un flujo de entrada

		  * @brief El formato debe ser:
		   #<comentario 1> <br>
		   #<comentario 2> <br>
		   #	... <br>
		   #<comentario 'num_comentarios' > <br>

		  * @param in : flujo de entrada
		  * @param c : comentarios a leer
		  * @return Devuelve una referencia al flujo de entrada
		  */
		friend istream & operator >> (istream & in, Comentarios &c);

		/**
		  * @brief Operador de inserción en flujo
		  * @brief Escribe los comentarios en un flujo de salida

		  * @brief El formato será:
		   #<comentario 1> <br>
		   #<comentario 2> <br>
		   #	... <br>
		   #<comentario 'num_comentarios' > <br>
		  * @param out : flujo de salida
		  * @param c : comentarios a escribir
		  * @return Devuelve una referencia al flujo de salida
		  */
		friend ostream & operator << (ostream & out, const Comentarios &c);
};

#endif

# MP-ProyectoFinal
[ NOTA ] Puede ver la documentación del proyecto aquí:  https://jesusgonzaleza.github.io/MP-ProyectoFinal/
Proyecto final para la asignatura Metodología de la Programación en la UGR.
El proyecto consiste en la representación de una clase *Imagen*, con la que podremos trabajar fácilmente con archivos *PGM*.

## Uso del proyecto

* Compilación: ``
make
``
* Limpieza: ``make mr.proper``
* Generación de documentación: ``make docs``

>*Para una compilación correcta necesita crear las carpetas vacías: bin lib obj* <br>
>*Para una documentación correcta necesita crear la carpeta doc/html* <br>
>*La documentación se encontrará en doc/html/index.html*

### ./bin/Binariza
``./bin/Binariza <Imagen_PGM> <Valor> <nombre_salida> ``

Convierte la *Imagen_PGM* en una imagen en B/N que se guardará en el fichero *nombre_salida*.
La binarización se realizará a partir del valor del píxel: *Valor*.

### ./bin/Negativo
``./bin/Negativo <Imagen_PGM> (<nombre_salida>)``

Crea la imagen *negativo* de *Imagen_PGM*.
- Si se usa con 2 argumentos, la imagen resultante se guarda en el fichero *nombre_salida*, no alterando la imagen original.
- Si se usa sólo 1 argumento, la imagen original será sustituida por su negativo. Para recuperarla podemos volver a usar este programa sobre la imagen alterada, pero debemos tener en cuenta que se habrán generado comentarios nuevos.

### ./bin/Redimensiona
``./bin/Redimensiona <Imagen_PGM_original> [ <prop> | -f  <filas> | -c <cols> | <filas> <cols> ] <Imagen_PGM_redimensionada>
``

Crea una nueva imagen, guardada en *Imagen_PGM_redimensionada*, que será el resultado de modificar las dimensiones de la imagen *Imagen_PGM_original*. 
>La imagen resultado mantiene la proporción de la imagen original

### ./bin/Estimaciones
``./bin/Estimaciones <fichero_entrada>``

*Fichero_entrada* contiene una lista de rutas a imágenes PGM, cada una en una línea. Estas imágenes tienen la particularidad de que su formato es incompleto: sólo contienen los píxeles de la misma. <br>
El programa seguirá un algoritmo para encontrar las dimensiones que optimicen la vista de la imagen resultante, llegando a generar imágenes PGM completas.

## License
[MIT](https://choosealicense.com/licenses/mit/)

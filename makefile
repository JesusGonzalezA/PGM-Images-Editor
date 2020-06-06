#################################################################
#Jesús González Álvarez
#################################################################

#---------MACROS----------------------
CXX=g++
CXXFLAGS=
#------------
EXE = $(BIN)/Estimaciones $(BIN)/Redimensiona $(BIN)/Binariza $(BIN)/Negativo
#------------
HOMEDIR=.
SRC=$(HOMEDIR)/src
DOC = $(HOMEDIR)/doc
INCLUDE=$(HOMEDIR)/include
OBJ=$(HOMEDIR)/obj
LIB=$(HOMEDIR)/lib
BIN=$(HOMEDIR)/bin
DIRECTORIOS= $(SRC) $(INCLUDE) $(OBJ) $(LIB) $(BIN)

#---------.PHONY----------------------
.PHONY : $(HOMEDIR)/all $(HOMEDIR)/clean $(HOMEDIR)/mr.proper

#################################################################

#----------TOD0-----------------------
all : $(EXE)

#----------EJECUTABLES----------------
$(BIN)/Estimaciones : $(OBJ)/Estimaciones.o $(LIB)/libImagen.a \
					  $(LIB)/libSecuencia.a
	$(CXX) -o $@ $< -L$(LIB) -lImagen -lSecuencia $(CXXFLAGS)

$(BIN)/Redimensiona : $(OBJ)/Redimensiona.o $(LIB)/libImagen.a
	$(CXX) -o $@ $< -L$(LIB) -lImagen $(CXXFLAGS)

$(BIN)/Binariza : $(OBJ)/Binariza.o $(LIB)/libImagen.a
	$(CXX) -o $@ $< -L$(LIB) -lImagen $(CXXFLAGS)

$(BIN)/Negativo : $(OBJ)/Negativo.o $(LIB)/libImagen.a
	$(CXX) -o $@ $< -L$(LIB) -lImagen $(CXXFLAGS)

#----------OBJETOS--------------------
$(OBJ)/Estimaciones.o : $(SRC)/Estimaciones.cpp \
				  $(INCLUDE)/Imagen.h $(INCLUDE)/UtilidadesFicheros.h
	$(CXX) -o $@ -c $< -I$(INCLUDE) $(CXXFLAGS)

$(OBJ)/Redimensiona.o : $(SRC)/Redimensiona.cpp \
				  $(INCLUDE)/Imagen.h $(INCLUDE)/UtilidadesFicheros.h
	$(CXX) -o $@ -c $< -I$(INCLUDE) $(CXXFLAGS)

$(OBJ)/Binariza.o : $(SRC)/Binariza.cpp \
				  $(INCLUDE)/Imagen.h $(INCLUDE)/UtilidadesFicheros.h
	$(CXX) -o $@ -c $< -I$(INCLUDE) $(CXXFLAGS)

$(OBJ)/Negativo.o : $(SRC)/Negativo.cpp \
				  $(INCLUDE)/Imagen.h $(INCLUDE)/UtilidadesFicheros.h
	$(CXX) -o $@ -c $< -I$(INCLUDE) $(CXXFLAGS)

$(OBJ)/Imagen.o : $(SRC)/Imagen.cpp \
				  $(INCLUDE)/Imagen.h $(INCLUDE)/Comentarios.h
	$(CXX) -c -o $@ $< -I$(INCLUDE)

$(OBJ)/Comentarios.o : $(SRC)/Comentarios.cpp $(INCLUDE)/Comentarios.h
	$(CXX) -c -o $@ $< -I$(INCLUDE)


#-----------------------OBJ auxiliares
$(OBJ)/UtilidadesFicheros.o : $(SRC)/UtilidadesFicheros.cpp \
							  $(INCLUDE)/UtilidadesFicheros.h
	$(CXX) -c -o $@ $< -I$(INCLUDE) $(CXXFLAGS)

#----------BIBLIOTECAS----------------
$(LIB)/libImagen.a : $(OBJ)/UtilidadesFicheros.o $(OBJ)/Comentarios.o \
					$(OBJ)/Imagen.o $(OBJ)/Secuencia.o
	ar rvs $@ $^

# (Secuencia) ........................

$(OBJ)/Secuencia.o : $(SRC)/Secuencia.cpp \
                     $(INCLUDE)/Secuencia.h $(INCLUDE)/TipoBase_Secuencia.h
	@echo
	@echo Creando objeto: Secuencia.o
	@echo
	g++ -c -o $(OBJ)/Secuencia.o  $(SRC)/Secuencia.cpp \
       -I$(INCLUDE) -std=c++11

$(LIB)/libSecuencia.a : $(OBJ)/Secuencia.o
	@echo
	@echo Creando biblioteca: libSecuencia.a
	@echo
	ar rvs $(LIB)/libSecuencia.a  $(OBJ)/Secuencia.o




#----------LIMPIEZA-------------------
mr.proper : clean clean-bins

clean: clean-objs clean-libs

clean-objs:

	@echo Borrando objetos

	-rm $(OBJ)/*

	@echo ...Borrados objetos
	@echo


clean-libs:
	@echo Borrando bibliotecas

	-rm $(LIB)/*

	@echo ...Borradas bibliotecas
	@echo

clean-bins :
	@echo Borrando ejecutables

	-rm $(BIN)/*

	@echo ...Borrados ejecutables

# ************ Generación de documentación ******************
docs:
	@doxygen $(DOC)/doxys/Doxyfile
	@echo "-- Documentación disponible en $(DOC)/html --"

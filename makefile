#################################################################
#Jesús González Álvarez
#################################################################

#---------MACROS----------------------
CXX=g++
CXXFLAGS=
#------------
EXE = $(BIN)/Prueba
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
$(BIN)/Prueba : $(SRC)/Prueba.cpp $(OBJ)/Imagen.o $(OBJ)/Comentarios.o
	$(CXX) -o $@ $^ -I$(INCLUDE) $(CXXFLAGS)

#----------OBJETOS--------------------
$(OBJ)/Imagen.o : $(SRC)/Imagen.cpp $(INCLUDE)/Imagen.h
	$(CXX) -c -o $@ $< -I$(INCLUDE)

$(OBJ)/Comentarios.o : $(SRC)/Comentarios.cpp $(INCLUDE)/Comentarios.h
	$(CXX) -c -o $@ $< -I$(INCLUDE)


#-----------------------OBJ auxiliares


#----------BIBLIOTECAS----------------


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

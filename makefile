#################################################################
#Jesús González Álvarez
#################################################################

#---------MACROS----------------------
CXX=g++
CXXFLAGS=
#------------
EXE =
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


#----------OBJETOS--------------------


#-----------------------OBJ auxiliares


#----------BIBLIOTECAS----------------


#----------LIMPIEZA-------------------
mr.proper : clean clean-bins

clean: clean-objs clean-libs

clean-objs: clean-objetos-bibliotecas

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

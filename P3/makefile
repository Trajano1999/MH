# compilador
CC = g++

# compiler flags:
#	-g    : añade información de depuración al ejecutable
#	-Wall : activa avisos en el compilador
#	-O2   : opción de compilación eficiente
CFLAGS  = -Wall -g -O2

# carpetas																						   # cambiar carpetas
BIN = bin
SRC = src
OBJ = obj
INC = include

# archivos																						   # modificar nombre del ejecutable y archivos de entrada
EJECUTABLE = practica3
SOURCES = $(wildcard $(SRC)/*.cpp)
OBJECTS = $(addprefix $(OBJ)/, $(notdir $(SOURCES:.cpp=.o)))
RUTA_ARCHIVOS_ENTRADA = /home/juanma/GitHub/MH/P3/datos_MDD
RUTA_ARCHIVO_EJECUCION = /home/juanma/GitHub/MH/P3/ejecucion_completa.sh

all: $(BIN)/$(EJECUTABLE)

# ejecutable
$(BIN)/$(EJECUTABLE): $(OBJECTS)
	$(CC) $(CFLAGS) $(OBJECTS) -o $@

# objeto main																			   		   # añadir dependencias
$(OBJ)/main.o: src/main.cpp include/problema.h
	$(CC) $(CFLAGS) -c $< -o $@ -I ./$(INC)

# objetos
$(OBJ)/%.o: $(SRC)/%.cpp $(INC)/%.h
	$(CC) $(CFLAGS) -c $< -o $@ -I ./$(INC)

# limpieza
clear:
	rm $(OBJ)/* $(BIN)/*

# ejecución	de un archivo																		   # alterar opciones de ejecución
exec: $(BIN)/$(EJECUTABLE)
	./$< $(RUTA_ARCHIVOS_ENTRADA)/GKD-b_08_n25_m7.txt

# ejecución completa
exec_total: $(BIN)/$(EJECUTABLE)
	bash $(RUTA_ARCHIVO_EJECUCION)
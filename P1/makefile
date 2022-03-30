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

# archivos																						   # modificar nombre del ejecutable
EJECUTABLE = practica1
SOURCES = $(wildcard $(SRC)/*.cpp)
OBJECTS = $(addprefix $(OBJ)/, $(notdir $(SOURCES:.cpp=.o)))

all: $(BIN)/$(EJECUTABLE)

# ejecutable
$(BIN)/$(EJECUTABLE): $(OBJECTS)
	$(CC) $(CFLAGS) $(OBJECTS) -o $@

# objeto main																			   		   # añadir dependencias
$(OBJ)/main.o: src/main.cpp include/problema.h
	$(CC) $(CFLAGS) -c $< -o $@ -I ./include

# objetos
$(OBJ)/%.o: $(SRC)/%.cpp $(INC)/%.h
	$(CC) $(CFLAGS) -c $< -o $@ -I ./$(INC)

# limpieza
clear:
	rm $(OBJ)/* $(BIN)/*

# ejecución																						   # alterar opciones de ejecución
exec: $(BIN)/$(EJECUTABLE)
	./$< /home/juanma/Escritorio/Uni/Segundo_Cuatri/MH/P1/datos_MDD/GKD-b_10_n25_m7.txt

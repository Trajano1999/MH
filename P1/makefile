# compilador
CC = g++

# compiler flags:
#	-g    : añade información de depuración al ejecutable
#	-Wall : activa avisos en el compilador
#	-O2   : opción de compilación eficiente
CFLAGS  = -Wall -g -O2

# carpetas
BIN = bin
SRC = src
OBJ = obj

# archivos
EJECUTABLE = practica1
SOURCES = $(wildcard $(SRC)/*.cpp)
OBJECTS = $(addprefix $(OBJ)/, $(notdir $(SOURCES:.cpp=.o)))

all: $(BIN)/$(EJECUTABLE)

$(BIN)/$(EJECUTABLE): $(OBJECTS)
	$(CC) $(CFLAGS) $(OBJECTS) -o $@

$(OBJ)/%.o: $(SRC)/%.cpp
	$(CC) $(CFLAGS) -c $< -o $@

clear:
	rm $(OBJ)/* $(BIN)/*

exec: $(BIN)/$(EJECUTABLE)
	./$< /home/juanma/Escritorio/Uni/Segundo_Cuatri/MH/P1/datos_MDD/GKD-b_10_n25_m7.txt
# compilador
CC = g++

# compiler flags:
#  -g    : añade información de depuración al ejecutable
#  -Wall : activa avisos en el compilador
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
	./$<
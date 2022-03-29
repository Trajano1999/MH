# compilador
CC = g++

# compiler flags:
#  -g    : añade información de depuración al ejecutable
#  -Wall : activa avisos en el compilador
CFLAGS  = -g -Wall -O2

# carpetas
SRC = src
OBJ = obj

# archivos
EJECUTABLE = practica1
SOURCES = main.cpp prueba.cpp
OBJECTS = $(SOURCES:.cpp=.o)

all: $(EJECUTABLE)


$(EJECUTABLE): $(OBJECTS)
	$(CC) $(CFLAGS) -o $@ $(OBJ)/*

$(OBJECTS):
	$(CC) $(CFLAGS) -c $(SRC)/*
	mv *.o $(OBJ)/

clear:
	rm $(OBJ)/*.o $(EJECUTABLE)

exec: $(EJECUTABLE)
	./$<
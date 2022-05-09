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
EJECUTABLE = practica1
SOURCES = $(wildcard $(SRC)/*.cpp)
OBJECTS = $(addprefix $(OBJ)/, $(notdir $(SOURCES:.cpp=.o)))
RUTA_ARCHIVOS_ENTRADA = /home/juanma/Escritorio/Uni/Segundo_Cuatri/MH/P1/datos_MDD

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
	./$< $(RUTA_ARCHIVOS_ENTRADA)/GKD-b_1_n25_m2.txt

#	$(RUTA_ARCHIVOS_ENTRADA)/GKD-b_2_n25_m2.txt 				\
	$(RUTA_ARCHIVOS_ENTRADA)/GKD-b_3_n25_m2.txt 				\
	$(RUTA_ARCHIVOS_ENTRADA)/GKD-b_4_n25_m2.txt 				\
	$(RUTA_ARCHIVOS_ENTRADA)/GKD-b_5_n25_m2.txt 				\
	$(RUTA_ARCHIVOS_ENTRADA)/GKD-b_6_n25_m7.txt 				\
	$(RUTA_ARCHIVOS_ENTRADA)/GKD-b_7_n25_m7.txt 				\
	$(RUTA_ARCHIVOS_ENTRADA)/GKD-b_8_n25_m7.txt 				\
	$(RUTA_ARCHIVOS_ENTRADA)/GKD-b_9_n25_m7.txt 				\
	$(RUTA_ARCHIVOS_ENTRADA)/GKD-b_10_n25_m7.txt 				\
	$(RUTA_ARCHIVOS_ENTRADA)/GKD-b_11_n50_m5.txt 				\
	$(RUTA_ARCHIVOS_ENTRADA)/GKD-b_12_n50_m5.txt 				\
	$(RUTA_ARCHIVOS_ENTRADA)/GKD-b_13_n50_m5.txt 				\
	$(RUTA_ARCHIVOS_ENTRADA)/GKD-b_14_n50_m5.txt 				\
	$(RUTA_ARCHIVOS_ENTRADA)/GKD-b_15_n50_m5.txt 				\
	$(RUTA_ARCHIVOS_ENTRADA)/GKD-b_16_n50_m15.txt				\
	$(RUTA_ARCHIVOS_ENTRADA)/GKD-b_17_n50_m15.txt				\
	$(RUTA_ARCHIVOS_ENTRADA)/GKD-b_18_n50_m15.txt				\
	$(RUTA_ARCHIVOS_ENTRADA)/GKD-b_19_n50_m15.txt 			    \
	$(RUTA_ARCHIVOS_ENTRADA)/GKD-b_20_n50_m15.txt				\
	$(RUTA_ARCHIVOS_ENTRADA)/GKD-b_21_n100_m10.txt			   	\
	$(RUTA_ARCHIVOS_ENTRADA)/GKD-b_22_n100_m10.txt			   	\
	$(RUTA_ARCHIVOS_ENTRADA)/GKD-b_23_n100_m10.txt			    \
	$(RUTA_ARCHIVOS_ENTRADA)/GKD-b_24_n100_m10.txt       		\
	$(RUTA_ARCHIVOS_ENTRADA)/GKD-b_25_n100_m10.txt   	    	\
	$(RUTA_ARCHIVOS_ENTRADA)/GKD-b_26_n100_m30.txt			   	\
	$(RUTA_ARCHIVOS_ENTRADA)/GKD-b_27_n100_m30.txt			   	\
	$(RUTA_ARCHIVOS_ENTRADA)/GKD-b_28_n100_m30.txt			   	\
	$(RUTA_ARCHIVOS_ENTRADA)/GKD-b_29_n100_m30.txt			   	\
	$(RUTA_ARCHIVOS_ENTRADA)/GKD-b_30_n100_m30.txt			   	\
	$(RUTA_ARCHIVOS_ENTRADA)/GKD-b_31_n125_m12.txt			   	\
	$(RUTA_ARCHIVOS_ENTRADA)/GKD-b_32_n125_m12.txt			   	\
	$(RUTA_ARCHIVOS_ENTRADA)/GKD-b_33_n125_m12.txt			   	\
	$(RUTA_ARCHIVOS_ENTRADA)/GKD-b_34_n125_m12.txt			   	\
	$(RUTA_ARCHIVOS_ENTRADA)/GKD-b_35_n125_m12.txt			   	\
	$(RUTA_ARCHIVOS_ENTRADA)/GKD-b_36_n125_m37.txt    		   	\
	$(RUTA_ARCHIVOS_ENTRADA)/GKD-b_37_n125_m37.txt			   	\
	$(RUTA_ARCHIVOS_ENTRADA)/GKD-b_38_n125_m37.txt				\
	$(RUTA_ARCHIVOS_ENTRADA)/GKD-b_39_n125_m37.txt			   	\
	$(RUTA_ARCHIVOS_ENTRADA)/GKD-b_40_n125_m37.txt			   	\
	$(RUTA_ARCHIVOS_ENTRADA)/GKD-b_41_n150_m15.txt			   	\
	$(RUTA_ARCHIVOS_ENTRADA)/GKD-b_42_n150_m15.txt			   	\
	$(RUTA_ARCHIVOS_ENTRADA)/GKD-b_43_n150_m15.txt			   	\
	$(RUTA_ARCHIVOS_ENTRADA)/GKD-b_44_n150_m15.txt    		   	\
	$(RUTA_ARCHIVOS_ENTRADA)/GKD-b_45_n150_m15.txt			   	\
	$(RUTA_ARCHIVOS_ENTRADA)/GKD-b_46_n150_m45.txt			   	\
	$(RUTA_ARCHIVOS_ENTRADA)/GKD-b_47_n150_m45.txt			   	\
	$(RUTA_ARCHIVOS_ENTRADA)/GKD-b_48_n150_m45.txt			   	\
	$(RUTA_ARCHIVOS_ENTRADA)/GKD-b_49_n150_m45.txt			   	\
	$(RUTA_ARCHIVOS_ENTRADA)/GKD-b_50_n150_m45.txt			   
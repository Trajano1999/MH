//-------------------------------------------------------------------------------------------------
//  Universidad de Granada
//  Escuela Superior de Inegeniería Informática y Telecomunicaciones 
//  Curso 2021/2022 
//  
//  Metaheurísticas
//  Práctica 1:
//  Técnicas de Búsqueda Local y Algoritmos Greedy para el Problema de la Mínima Dispersión Diferencial
//
//  Juan Manuel Mateos Pérez
//-------------------------------------------------------------------------------------------------

#ifndef PROBLEMA_HPP
#define PROBLEMA_HPP

# include <iostream>
# include <fstream>

class Problema {
    private:
        int num_filas, num_columnas;
        int **matriz;

    public:
        Problema(const int & num_filas, const int & num_columnas);
        Problema(const ifstream & fichero);
        ~Problema();
        int** getMatriz();
        int getNumFilas();
        int getNumColumnas();
};

# endif
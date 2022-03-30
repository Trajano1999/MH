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

# include "problema.h"

Problema::Problema(const int & num_filas, const int & num_columnas){
    matriz = new int*[num_filas];
    for(int i=0; i<num_filas; ++i){
        matriz[i] = new int*[num_columnas];
    }

}
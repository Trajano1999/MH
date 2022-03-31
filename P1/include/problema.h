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

# ifndef _PROBLEMA_H_
# define _PROBLEMA_H_

# include <iostream>
# include <fstream>
# include <vector>
# include <ctime>

using namespace std;

class Problema {
    private:
        int elem_sel;
        vector<vector<double> > matriz;

        int aleatorio(int min, int max);

    public:
        Problema(const char * dir_fich);
        vector<vector<double> > getMatriz();

        // métodos para resolver el problema
        vector<int> greedysolution();
};

# endif
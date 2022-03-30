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

# ifndef _PROBLEMA_HPP_
# define _PROBLEMA_HPP_

# include <iostream>
# include <fstream>
# include <vector>

using namespace std;

class Problema {
    private:
        vector<vector<int> > matriz;

    public:
        Problema(ifstream dir_fich);
        vector<vector<int> > getMatriz();
};

# endif
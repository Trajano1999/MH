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
        unsigned int elem_sel, semilla;
        vector<vector<double> > matriz;

        int aleatorio(int min, int max);
        double dispersion(vector<int> & v, int elem);

    public:
        Problema(unsigned int sem, const char * dir_fich);
        vector<vector<double> > getMatriz();

        // métodos para resolver el problema
        vector<int> solucionGreedy();
};

# endif
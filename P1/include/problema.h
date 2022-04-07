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

        // métodos privados para Greedy
        int aleatorio(int min, int max);
        double dispersion2(vector<int> & v, int elem);

        vector<double> sigmaNoSeleccionados(const vector<int> & cand, const vector<int> & sol);
        vector<double> sigmaSeleccionados(const vector<int> & sol);
        int elementoMenorDispersion(const vector<int> & candidatos, const vector<int> & sol);

        // métodos privados para BL
        void intercambio(vector<int> & v, int valor1, int valor2);

    public:
        Problema(unsigned int sem, const char * dir_fich);
        vector<vector<double> > getMatriz();

        // métodos para resolver el problema
        vector<int> solucionGreedy();
        vector<int> solucionBusquedaLocal();
};

/*
double Problema::dispersion2(vector<int> & v, int elem){
    double suma = 0,
           valor_max = 0,
           valor_min = VALOR_GRANDE;

    // añadimos el elemento
    v.push_back(elem);
    
    // calculamos la dispersión con el elemento añadido
    for(unsigned i=0; i<v.size(); ++i){
        suma = 0;

        for(unsigned j=0; j<v.size(); ++j){
            if(v[i] != v[j])
                suma += matriz[v[i]][v[j]] == 0 ? matriz[v[j]][v[i]] : matriz[v[i]][v[j]];
        }

        if(suma > valor_max)
            valor_max = suma;

        if(suma < valor_min)
            valor_min = suma;
    }

    // eliminamos el elemento
    v.pop_back();

    return v.size() > 2 ? valor_max - valor_min : valor_max;
}
*/

# endif
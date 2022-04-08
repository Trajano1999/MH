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
# include <set>
# include <ctime>

using namespace std;

class Problema {
    private:
        unsigned elem_sel, semilla;
        vector<vector<double> > matriz;

        // métodos privados para Greedy
        int randomGreedy(unsigned sem, int min, int max);
        double valorMaximo(const vector<double> & v);
        double valorMinimo(const vector<double> & v);
        int posicionMinima(const vector<double> & v);
        vector<double> sigmaNoSeleccionados(const vector<int> & cand, const vector<int> & sol);
        vector<double> sigmaSeleccionados(const vector<int> & sol);
        int elementoMenorDispersion(const vector<int> & candidatos, const vector<int> & sol);

        // métodos privados para BL
        bool comprobarValor(const vector<int> & v, int valor);
        set<int> randomBL(int min, int max);
        void intercambio(vector<int> & v, int valor1, int valor2);
        double coste(const vector<int> & v);

    public:
        Problema(unsigned sem, const char * dir_fich);
        vector<vector<double> > getMatriz();

        // métodos para resolver el problema
        vector<int> solucionGreedy();
        vector<int> solucionBusquedaLocal();
};

# endif
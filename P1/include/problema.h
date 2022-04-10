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

            // devuelve un valor aleatorio entre los parámetros recibidos
            int randomGreedy(unsigned sem, int min, int max);
            
            // devuelve el mayor valor de un vector
            double valorMaximo(const vector<double> & v);
        
            // devuelve el menor valor estrictamente positivo de un vector 
            double valorMinimo(const vector<double> & v);
        
            // devuelve la posición del menor valor estrictamente positivo de un vector 
            int posicionMinima(const vector<double> & v);
            
            // calcula el vector donde cada posición tiene la suma de distancias
            // del elemento no seleccionados i, a todos los seleccionados
            vector<double> sigmaNoSeleccionados(const vector<int> & cand, const vector<int> & sol);
            
            // calcula el vector donde cada posición tiene la suma de distancias
            // del elemento seleccionado i, a todos los demás
            vector<double> sigmaSeleccionados(const vector<int> & sol);
            
            // calcula el elemento con menor dispersión
            int elementoMenorDispersion(const vector<int> & candidatos, const vector<int> & sol);

        // métodos privados para BL

            // intercambia los elementos con valor1 de un vector por valor2
            void intercambio(vector<int> & v, int valor1, int valor2);

            // devuelve m valores aleatorios distintos entre los parámetros recibidos (teniendo en cuenta la semilla)
            set<int> randomBL(int min, int max);

            // calcula la primera posición de un valor en un vector
            int calcularPosicion(const vector<int> & v, int elem);

            // calcula la dispersion de un vector en el que se intercambian dos valores
            double dispersionIntercambiarElementos(const vector<int> & sol, int elem_eliminar, int elem_aniadir);

    public: 
        // constructor
        Problema(unsigned sem, const char * dir_fich);

        // observadores
        unsigned getSemilla();
        unsigned getElementosSeleccionados();
        vector<vector<double> > getMatriz();

        // modificadores
        void setSemilla(unsigned sem);
        void setMatriz(const char * dir_fich);

        // calcula la dispersión de un vector
        double dispersion(const vector<int> & v);

        // métodos para resolver el problema
        vector<int> solucionGreedy();
        vector<int> solucionBusquedaLocal();
};

# endif
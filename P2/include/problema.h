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

        // metodos privados generales

            // devuelve el mayor valor de un vector
            double valorMaximo(const vector<double> & v);
        
            // devuelve el menor valor estrictamente positivo de un vector 
            double valorMinimoPositivo(const vector<double> & v);
        
            // devuelve la posición del menor valor estrictamente positivo de un vector 
            int posicionMinimoPositivo(const vector<double> & v);

            // intercambia los elementos con valor1 de un vector por valor2
            void intercambio(vector<int> & v, int valor1, int valor2);

            // calcula la primera posición de un valor en un vector
            int calcularPosicion(const vector<int> & v, int elem);

            // genera un vector del tamaño indicado, con valores 0 y 1 en posiciones aleatorias, con exactamente m 1s
            vector<int> generarVectorAleatorio(unsigned tamanio_vector);

        // métodos privados para Greedy

            // devuelve un valor aleatorio entre los parámetros recibidos
            int randomGreedy(unsigned sem, int min, int max);
            
            // calcula el vector donde cada posición tiene la suma de distancias
            // del elemento no seleccionado i, a todos los seleccionados
            vector<double> sigmaNoSeleccionados(const vector<int> & cand, const vector<int> & sol);
            
            // calcula el vector donde cada posición tiene la suma de distancias
            // del elemento seleccionado i, a todos los demás
            vector<double> sigmaSeleccionados(const vector<int> & sol);
            
            // calcula el elemento con menor dispersión
            int elementoMenorDispersion(const vector<int> & candidatos, const vector<int> & sol);

        // métodos privados para BL

            // devuelve m valores aleatorios distintos entre los parámetros recibidos (teniendo en cuenta la semilla)
            set<int> randomBL(int min, int max);

            // calcula la dispersion de un vector en el que se intercambian dos valores
            double dispersionIntercambiarElementos(const vector<int> & sol, int elem_eliminar, int elem_aniadir);

        // métodos privados para AGs // jjj

            // genera la población de padres para AG Uniformes (del mismo tamaño que la población genética)

            // selecciona los ganadores de num_torneos torneos binarios arbitrarios 
            vector<vector<int> > seleccion(const vector<vector<int> > & poblacion, unsigned num_torneos);

            // realiza el cruce uniforme con probabilidad PROBABILIDAD_CRUCE
            // jjj no se si son cruces distintos o solo cambia la probabilidad
            void cruceUniforme(vector<vector<int> > poblacion);
            void crucePosicion(vector<vector<int> > poblacion);

            // se encarga de mutar la población con una probabilidad de PROBABILIDAD_MUTACION
            void mutacion();

            // escoge el mejor hijo
            void reemplazamiento(vector<vector<int> > poblacion, vector<vector<int> > poblacion_hijos);
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

        // métodos públicos
        double dispersion(const vector<int> & v);

        // métodos para resolver el problema

            // P1
            vector<int> solucionGreedy();
            vector<int> solucionBusquedaLocal();
            
            // P2  

                // AGGs 
                vector<int> solucionAGGUniforme();
                vector<int> solucionAGGPosicion();
            
                // AGEs
                vector<int> solucionAGEUniforme();
                vector<int> solucionAGEPosicion();

                // AMs
                // jjj
                            vector<vector<int> > creacionPoblacion(unsigned tamanio_poblacion);

};

# endif
//-------------------------------------------------------------------------------------------------
//  Universidad de Granada
//  Escuela Superior de Ingeniería Informática y Telecomunicaciones 
//  Curso 2021/2022 
//  
//  Metaheurísticas. Práctica Alternativa
//  Análisis de una metaheurística : Algoritmo Big Bang-Big Crunch
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
# include <random>
# include <iomanip>
# include <utility>
# include <algorithm>

using namespace std;

class Problema 
{
    private:
        unsigned elem_tot, 
                 elem_sel, 
                 semilla;
        vector<vector<double> > matriz;

        // metodos privados generales

            // devuelve el mayor valor de un vector
            double valorMaximoPositivo(const vector<double> & v);
        
            // devuelve el menor valor estrictamente positivo de un vector 
            double valorMinimoPositivo(const vector<double> & v);
        
            // devuelve la posición del mayor valor estrictamente positivo de un vector 
            int posicionMayorPositivo(const vector<double> & v);

            // devuelve la posición del menor valor estrictamente positivo de un vector 
            int posicionMinimoPositivo(const vector<double> & v);

            // indica si un elemento está en el vector
            bool estaEnVector(vector<int> vector, int valor);

            // calcula la primera posición de un valor en un vector
            int calcularPosicion(const vector<int> & v, int elem);

            // genera un vector población del tamaño indicado, con valores 0 y 1 en posiciones aleatorias, con exactamente m 1s
            vector<int> generarVectorPoblacionAleatorio(unsigned tamanio_vector);

            // calcula la media de un vector de distancias
            double mediaElementosPositivosVector(const vector<double> & distancias);

        // métodos privados para Greedy

            // devuelve un valor aleatorio entre los parámetros recibidos positivos o cero
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

            // calcula la dispersion de un vector en el que se intercambian dos valores
            double dispersionIntercambiarElementos(const vector<int> & sol, int elem_eliminar, int elem_aniadir);

        // métodos privados para AGs

            // calcula la dispersion de una poblacion (que es un vector de vectores {0,1,1,0})
            vector<double> dispersionPoblacion(const vector<vector<int> > & poblacion);

            // calcula la dispersion de una poblacion de vectores pueblo (que son vectores {2,3,5})
            vector<double> dispersionPoblacionPueblo(const vector<vector<int> > & poblacion);

            // ajusta el números de 1s tras aplicar el cruceUniforme
            void reparacion(vector<int> & hijo);

            // calcula el vector con menor dispersión de una población dada
            vector<int> mejorVectorPoblacion(const vector<vector<int> > & poblacion);

            // calcula el vector con mayor dispersión de una población dada
            vector<int> peorVectorPoblacion(const vector<vector<int> > & poblacion);

            // transforma un vector_poblacion {0,1,1} en un vector_pueblos {1,2}
            vector<int> transformacionVectorPueblos(const vector<int> & vector_poblacion);

            // transforma un vector_pueblos {1,2} en un vector_poblacion {0,1,1} 
            vector<int> transformacionVectorPoblacion(const vector<int> & vector_pueblos);

            // genera la población de padres para AG Uniformes (del mismo tamaño que la población genética)
            vector<vector<int> > creacionPoblacion(unsigned tamanio_poblacion);

            // selecciona los ganadores de población de num_torneos torneos binarios arbitrarios 
            vector<vector<int> > seleccion(const vector<vector<int> > & poblacion, const vector<double> & dispersion_poblacion, unsigned num_torneos);

            // realiza el cruce uniforme con la probabilidad asociada
            void cruceUniforme(vector<vector<int> > & poblacion_hijos, unsigned tamanio_cruce, double probabilidad);
            
            // realiza el cruce de posición con la probabilidad asociada
            void crucePosicion(vector<vector<int> > & poblacion_hijos, unsigned tamanio_cruce, double probabilidad);

            // se encarga de mutar la población generacional
            void mutacionGeneracional(vector<vector<int> > & poblacion_hijos, double probabilidad);

            // se encarga de mutar la población generacional
            void mutacionEstacionaria(vector<vector<int> > & poblacion_hijos, double probabilidad);

            // aplica el reemplazamiento generacional explicado
            void reemplazamientoGeneracional(vector<vector<int> > & poblacion, const vector<vector<int> > & poblacion_hijos);

            // aplica el reemplazamiento estacionario explicado
            void reemplazamientoEstacionario(vector<vector<int> > & poblacion, const vector<vector<int> > & poblacion_hijos);

        // métodos privados para AMs

            // aplicamos BL a un vector de pueblos recibido y el resultado proporcionado también es un vector de pueblos
            vector<int> busquedaLocalP2(const vector<int> & vector_inicio, unsigned max_evaluaciones, unsigned & num_evaluaciones);

        // métodos privados para ILS

            // intercambiamos t elementos de la solución por t elementos que no lo sean
            vector<int> mutacion(const vector<int> & solucion, unsigned t);

        // métodos privados para ES

            // generamos un valor real aleatorio entre min y max
            double generarAleatorioReal(int min, int max);

            // generamos un nuevo vecino aplicandole una mutación
            vector<int> generarNuevoVecino(const vector<int> & original, double & coste_vecino);   

            // enfriamos usando el esquema de Cauchy modificado 
            double enfriamiento(double temp_inicial, double temperatura, double temp_final, unsigned iteraciones);

        // métodos privados para Práctica Alternativa

            // generamos un valor real aleatorio uniforme entre min y max
            double generarValorRealUniforme(int min, int max);

            // genera nuevos candidatos
            vector<vector<int> > generarNuevosCandidatos(const vector<int> & mejor_sol, unsigned eval);

    public: 
        // constructor
        Problema(unsigned sem, const char * dir_fich);

        // observadores
        unsigned getSemilla();
        unsigned getElementosTotales();
        unsigned getElementosSeleccionados();
        vector<vector<double> > getMatriz();

        // modificadores
        void setSemilla(unsigned sem);
        void setMatriz(const char * dir_fich);

        // métodos públicos
            
            // calcula la dispersion de un vector de pueblos solución
            double dispersion(const vector<int> & v);
            
            // genera un vector de pueblos del tamaño indicado, con exactamente m valores naturales
            vector<int> generarVectorPueblosAleatorio();

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
                vector<int> solucionAM1();
                vector<int> solucionAM2();
                vector<int> solucionAM3();
            
            // P3
            vector<int> solucionEnfriamientoSimulado(const vector<int> & sol_recibida);
            vector<int> solucionBusquedaMultiarranque();
            vector<int> solucionILS();
            vector<int> solucionILS_ES();

            // Práctica Alternativa
            vector<int> solucionBB_BC();
            vector<int> solucionBB_BC_Memetico();
};

# endif

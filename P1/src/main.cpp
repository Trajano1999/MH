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

using namespace std;

//-------------------------------------------------------------------------------------------------
// CONSTANTES GLOBALES
//-------------------------------------------------------------------------------------------------

const unsigned EJECUCIONES_POR_PROBLEMA = 5;
const string DIR_FICHERO_SALIDA = "/home/juanma/Escritorio/datos.txt";

//-------------------------------------------------------------------------------------------------
// FUNCIONES
//-------------------------------------------------------------------------------------------------

// muestra una matriz
void mostrarMatriz(const vector<vector<double> > & m){
    for(unsigned i=0; i<m.size(); ++i){
        cout << "( ";
        for(unsigned j=0; j<m[i].size(); ++j){
            cout << m[i][j] << " ";
        }
        cout << ")" << endl;
    }
}

// muestra un vector
void mostrarVector(const vector<int> & v){
    cout << "( ";
    for(unsigned i=0; i<v.size(); ++i)
        cout << v[i] << " ";
    cout << ")"; 
}

//-------------------------------------------------------------------------------------------------
// MAIN
//-------------------------------------------------------------------------------------------------

int main(int narg, char * arg[]){
    unsigned random_semilla = 0,
             tiempo_antes_greedy,
             tiempo_despues_greedy,
             tiempo_antes_BL,
             tiempo_despues_BL;
    double tiempo_final_greedy = 0.0,
           tiempo_final_BL = 0.0;
    const char * dir_fichero = arg[1];
    string nombre_fichero;
    
    // mensajes por pantalla
    string peticion_semilla = "\nIntroduzca la semilla : ",
           solucion_greedy  = "\nSolución por Greedy         : ",
           solucion_BL      = "\nSolución por Búsqueda Local : ";

    // guardamos los datos en un fichero
    ofstream fichero(DIR_FICHERO_SALIDA);
    if(!fichero.is_open())
        cerr << "Error al abrir " << DIR_FICHERO_SALIDA << endl;
    fichero << "Documento " << "Tiempo_Greedy " << "Tiempo_BL" << endl;

    Problema problema(random_semilla, dir_fichero);

    for(int i=1; i<narg; ++i){
        dir_fichero = arg[i];
        problema.setMatriz(dir_fichero);

        for(unsigned j=0; j<EJECUCIONES_POR_PROBLEMA; ++j){
            random_semilla = j+1;
            problema.setSemilla(random_semilla);

            tiempo_antes_greedy = clock();
            problema.solucionGreedy();
            tiempo_despues_greedy = clock();

            tiempo_final_greedy += double(tiempo_despues_greedy-tiempo_antes_greedy) / CLOCKS_PER_SEC;

            tiempo_antes_BL = clock();
            problema.solucionBusquedaLocal();
            tiempo_despues_BL = clock();

            tiempo_final_BL += double(tiempo_despues_BL-tiempo_antes_BL) / CLOCKS_PER_SEC;
        }
        
        tiempo_final_greedy = tiempo_final_greedy / EJECUCIONES_POR_PROBLEMA;
        tiempo_final_BL = tiempo_final_BL / EJECUCIONES_POR_PROBLEMA;

        fichero << arg[i] << " " << tiempo_final_greedy << " " << tiempo_final_BL << endl;

        tiempo_final_greedy = 0;
        tiempo_final_BL = 0;
    }
    
    /*random_semilla = 1; jjj

    // solución por Greedy
    cout << solucion_greedy;
    mostrarVector(problema.solucionGreedy());

    // solución por Búsqueda Local
    cout << solucion_BL;
    mostrarVector(problema.solucionBusquedaLocal());*/

    cout << endl;
}
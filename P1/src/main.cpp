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
    unsigned random_semilla;
    const char * dir_fichero = arg[1];

    // mensajes por pantalla
    string peticion_semilla = "\nIntroduzca la semilla : ",
           solucion_greedy  = "\nSolución por Greedy         : ",
           solucion_BL      = "\nSolución por Búsqueda Local : ";

    // lectura de semilla
    cout << peticion_semilla; 
    cin >> random_semilla;

    Problema problema(random_semilla, dir_fichero);
    //jjj mostrarMatriz(problema.getMatriz());

    // solución por Greedy
    cout << solucion_greedy;
    mostrarVector(problema.solucionGreedy());

    // solución por Búsqueda Local
    cout << solucion_BL;
    mostrarVector(problema.solucionBusquedaLocal());

    cout << endl;
}
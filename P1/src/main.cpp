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

// muestra una matriz
void mostrarMatriz(const vector<vector<double> > & m){
    for(unsigned int i=0; i<m.size(); ++i){
        cout << "( ";
        for(unsigned int j=0; j<m[i].size(); ++j){
            cout << m[i][j] << " ";
        }
        cout << ")" << endl;
    }
}

// muestra un vector
void mostrarVector(const vector<int> & v){
    cout << "( ";
    for(unsigned int i=0; i<v.size(); ++i)
        cout << v[i] << " ";
    cout << ")"; 
}

int main(int narg, char * arg[]){
    unsigned int random_semilla;
    const char * dir_fichero = arg[1];

    // mensajes por pantalla
    string solucion_greedy = "\nSolución por Greedy :\n";
    string peticion_semilla = "\nIntroduzca la semilla :\n";

    // lectura de semilla
    cout << peticion_semilla; 
    cin >> random_semilla;

    Problema problema(random_semilla, dir_fichero);
    mostrarMatriz(problema.getMatriz());

    // solución Greedy
    cout << solucion_greedy;
    mostrarVector(problema.greedysolution());

    cout << endl;
}
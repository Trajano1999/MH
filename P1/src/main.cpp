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

# include <iostream>

# include "problema.h"

using namespace std;

// muestra una matriz
void MostrarMatriz(const vector<vector<double> > & m){
    for(unsigned int i=0; i<m.size(); ++i){
        cout << "( ";
        for(unsigned int j=0; j<m[i].size(); ++j){
            cout << m[i][j] << " ";
        }
        cout << ")" << endl;
    }
}

int main(int narg, char * arg[]){
    cout << endl;

    const char * dir_fichero = arg[1];

    Problema problema(dir_fichero);

    vector<vector<double> > mat_prob = problema.getMatriz();
    MostrarMatriz(mat_prob);

    cout << endl;
}
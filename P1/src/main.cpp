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

void MostrarInicio(){
    cout << endl;
}

void MostrarMatriz(const vector<vector<int> > & m){
    for(unsigned int i=0; i<m.size(); ++i){
        for(unsigned int j=0; j<m[i].size(); ++j){
            cout << m[i][j] << " ";
        }
        cout << endl;
    }
}

int main(int narg, char * arg[]){
    MostrarInicio();
    const char * dir_fichero = arg[1];

    Problema problema(dir_fichero);

    vector<vector<int> > ma;

    ma.push_back({ 0, 0, 0 });
    ma.push_back({ 0, 0, 0 });
    ma.push_back({ 0, 0, 0 });

    MostrarMatriz(ma);
}
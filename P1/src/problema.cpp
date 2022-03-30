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

/*Problema::Problema(){
    for(int i=0; i<vector.size(); ++i){
        for(int j=0; j<vector[i].size(); ++j){
            matriz[i][j] = 0;
        }
    }
}*/

Problema::Problema(const char * dir_fich){
    int elem_tot, elem_sel;

    // abrimos el fichero
    ifstream fichero(dir_fich);
    if(!fichero.is_open())
        cerr << "Error al abrir " << dir_fich << endl;

    fichero >> elem_tot;
    fichero >> elem_sel;

    cout << "Elem tot : " << elem_tot << endl;
    cout << "Elem sel : " << elem_sel << endl;
}

vector<vector<int> > Problema::getMatriz(){
    return matriz;
}
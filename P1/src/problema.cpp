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

Problema::Problema(const char * dir_fich){
    int elem_tot, elem_sel;

    // abrimos el fichero
    ifstream fichero(dir_fich);
    if(!fichero.is_open())
        cerr << "Error al abrir " << dir_fich << endl;

    // leemos los primeros valores del fichero
    fichero >> elem_tot;
    fichero >> elem_sel;
    cout << "Elem tot : " << elem_tot << endl;
    cout << "Elem sel : " << elem_sel << endl;

    // redimensionamos la matriz
    vector<vector<double> > aux(elem_tot, vector<double>(elem_tot)); 
    matriz = aux;

    int num_lineas = (elem_tot * (elem_tot-1)) / 2;
    double pueblo1,
           pueblo2,
           distancia;

    // rellenamos la matriz con el resto de valores del fichero
    for(int i=0; i<num_lineas; ++i){
        fichero >> pueblo1;
        fichero >> pueblo2;
        fichero >> distancia;
        matriz[pueblo1][pueblo2] = distancia;
    }
}

vector<vector<double> > Problema::getMatriz(){
    return matriz;
}
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

// jjj
int Problema::aleatorio(int min, int max){
    // utilizamos srand() y time() para modificar la semilla cada vez,
    // ya que time() devuelve los segundos trasncurridos desde el 1 Enero de 1970
    srand(time(NULL));
    return rand() % (max-min+1) + min;
}

Problema::Problema(const char * dir_fich){
    int elem_totales;

    // abrimos el fichero
    ifstream fichero(dir_fich);
    if(!fichero.is_open())
        cerr << "Error al abrir " << dir_fich << endl;

    // leemos los primeros valores del fichero
    fichero >> elem_totales;
    fichero >> elem_sel;

    // jjj
    cout << "Elem tot : " << elem_totales << endl;
    cout << "Elem sel : " << elem_sel << endl;

    // redimensionamos la matriz
    vector<vector<double> > aux(elem_totales, vector<double>(elem_totales)); 
    matriz = aux;

    int num_lineas = (elem_totales * (elem_totales-1)) / 2;
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

// jjj
vector<int> Problema::greedysolution(){
    vector<int> sol;
    
    int n_pueblos = matriz.size(),
        candidato = aleatorio(1, n_pueblos);

    sol.push_back(candidato);
    while((int)sol.size() < elem_sel){
        candidato = 0;
        sol.push_back(candidato);
    }
    
    return sol;
}
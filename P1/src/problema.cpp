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
    // utilizamos srand() para modificar la semilla
    srand(semilla);
    return rand() % (max-min+1) + min;
}

Problema::Problema(unsigned int sem, const char * dir_fich){
    int elem_totales;

    // almacenamos la semilla
    semilla = sem;

    // abrimos el fichero
    ifstream fichero(dir_fich);
    if(!fichero.is_open())
        cerr << "Error al abrir " << dir_fich << endl;

    // leemos los primeros valores del fichero
    fichero >> elem_totales;
    fichero >> elem_sel;

    // jjj
    cout << endl;
    cout << "Elem tot : " << elem_totales << endl;
    cout << "Elem sel : " << elem_sel << endl << endl;

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
    int n_pueblos = matriz.size(),
        mejor_candidato = aleatorio(0, n_pueblos-1);
    //double distancia, mejor_distancia;
    vector<int> sol, candidatos;
    
    // rellenamos el vector de candidatos con todos los valores
    for(int i=0; i<n_pueblos; ++i)
        candidatos.push_back(i);

    // mostramos el vector de candidatos
    cout << "\tVector de candidatos : ";
    cout << "( ";
    for(int i=0; i<n_pueblos; ++i){
        cout << candidatos[i] << " ";
    }
    cout << ")" << endl;

    // añadimos el primer valor aleatorio
    sol.push_back(mejor_candidato);
    candidatos[mejor_candidato] = -1;

    while(sol.size() < elem_sel){
        mejor_candidato = 1;
        /*// valor inicial a mejor_distancia;
        mejor_distancia = 100000000;

        for(unsigned i=0; i<candidatos.size() && candidatos[i] != -1; ++i){ 
            // calculo distancia
            distancia = 10;
        
            // almaceno mejor distancia
            if(distancia < mejor_distancia){
                mejor_distancia = distancia;
                mejor_candidato = i;
            }
        }*/

        sol.push_back(mejor_candidato);
        candidatos[mejor_candidato] = -1;
    }
    
    return sol;
}
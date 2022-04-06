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

// máximo valor de un double en c++
const double VALOR_GRANDE = 1.7976931348623158e+308;

// jjj
int Problema::aleatorio(int min, int max){
    // utilizamos srand() para modificar la semilla
    srand(semilla);
    return rand() % (max-min+1) + min;
}

double Problema::dispersion(vector<int> & v, int elem){
    double suma = 0, 
           valor_max = 0, 
           valor_min = VALOR_GRANDE;

    // añadimos el elemento
    v.push_back(elem);
    
    // calculamos la dispersión con el elemento añadido
    for(unsigned i=0; i<v.size(); ++i){
        suma = 0;

        for(unsigned j=0; j<v.size(); ++j){
            if(v[i] != v[j])
                suma += matriz[v[i]][v[j]] == 0 ? matriz[v[j]][v[i]] : matriz[v[i]][v[j]];
        }

        if(suma > valor_max)
            valor_max = suma;

        if(suma < valor_min)
            valor_min = suma;
    }

    // eliminamos el elemento
    v.pop_back();

    return v.size() > 2 ? valor_max - valor_min : valor_max;
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

    // redimensionamos la matriz
    vector<vector<double> > aux(elem_totales, vector<double>(elem_totales)); 
    matriz = aux;

    int num_lineas = (elem_totales * (elem_totales-1)) / 2;
    int pueblo1,
        pueblo2;
    double distancia;

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

// jjj se puede hacer un un list para que sea más eficiente al eliminar un elemento del vector, en vez de poner el elemento a -1
vector<int> Problema::solucionGreedy(){
    int n_pueblos = matriz.size(),
        mejor_candidato = aleatorio(0, n_pueblos-1);
    vector<int> sol, candidatos;

    double una_dispersion,
           mejor_dispersion = 0.0;
    
    // rellenamos el vector de candidatos
    for(int i=0; i<n_pueblos; ++i)
        candidatos.push_back(i);

    // añadimos el primer valor aleatorio
    sol.push_back(mejor_candidato);
    candidatos[mejor_candidato] = -1;

    while(sol.size() < elem_sel){   
        mejor_dispersion = VALOR_GRANDE;
          
        // recorremos los pueblos aún no seleccionados
        for(unsigned i=0; i<candidatos.size(); ++i){
            if(candidatos[i] != -1){
                // calculamos la dispersión de añadir el pueblo i
                una_dispersion = dispersion(sol, i);
                
                // comparamos las dispersiones obtenidas
                if( una_dispersion < mejor_dispersion){
                    mejor_dispersion = una_dispersion;
                    mejor_candidato = i;
                }
            }
        }

        // actualizamos los valores
        sol.push_back(mejor_candidato);
        candidatos[mejor_candidato] = -1;
    }

    cout << "\tVector de candidatos : ";
    cout << "( ";
    for(int i=0; i<n_pueblos; ++i){
        cout << candidatos[i] << " ";
    }
    cout << ")" << endl;
    
    return sol;
}
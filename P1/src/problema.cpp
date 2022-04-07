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

//-------------------------------------------------------------------------------------------------
// CONSTANTES GLOBALES
//-------------------------------------------------------------------------------------------------

// máximo valor de un double en c++
const double VALOR_GRANDE = 1.7976931348623158e+308;

//-------------------------------------------------------------------------------------------------
// MÉTODOS PRIVADOS
//-------------------------------------------------------------------------------------------------

// jjj
int Problema::aleatorio(int min, int max){
    // utilizamos srand() para modificar la semilla
    srand(semilla);
    return rand() % (max-min+1) + min;
}

vector<double> Problema::sigmaNoSeleccionados(const vector<int> & cand, const vector<int> & sol){
    unsigned tamanio_cand = cand.size(),
             tamanio_sol = sol.size();
    double suma = 0.0;
    vector<double> res (tamanio_cand, 0.0);

    for(unsigned i=0; i<tamanio_cand; ++i)
        if(cand[i] != -1){
            for(unsigned j=0; j<tamanio_sol; ++j)
                suma += matriz[sol[j]][cand[i]] == 0 ? matriz[sol[j]][cand[i]] : matriz[sol[j]][cand[i]];
            
            res[i] = suma;
            suma = 0.0;
        }
    
    return res;
}

vector<double> Problema::sigmaSeleccionados(const vector<int> & sol){
    unsigned tamanio_sol = sol.size();
    double suma = 0.0;
    vector<double> res (tamanio_sol, 0.0);
    
    for(unsigned i=0; i<tamanio_sol; ++i){
        for(unsigned j=0; j<tamanio_sol; ++j){
            if(i != j) 
                suma += matriz[sol[i]][sol[j]] == 0 ? matriz[sol[j]][sol[i]] : matriz[sol[i]][sol[j]];
        }

        res[i] = suma;
        suma = 0.0;
    }

    return res;
}

int Problema::elementoMenorDispersion(const vector<int> & cand, const vector<int> & sol){
    double distancia;
    unsigned tamanio_cand = cand.size(),
             tamanio_sol = sol.size();
    vector<double> sigma (tamanio_sol, 0.0);

    // calculamos el vector de la suma de distancias de cada elemento no seleccionado a los seleccionados
    vector<double> sigma_no_seleccionados = sigmaNoSeleccionados(cand, sol);

    // calculamos el vector de la suma de distancias de cada elemento seleccionado al resto
    vector<double> sigma_seleccionados = sigmaSeleccionados(sol);

    for(unsigned i=0; i<tamanio_cand; ++i)
        if(cand[i] != -1){
            // calculamos el vector de la suma de distancias de los sigma seleccionados 
            // con la distancia de añadir un elemento no seleccionado i
            for(unsigned j=0; j<tamanio_sol; ++j){
                distancia = matriz[sol[j]][cand[i]] == 0 ? matriz[cand[i]][sol[j]] : matriz[sol[j]][cand[i]];
                sigma[j] = sigma_seleccionados[j] + distancia;
            }

            // calculamos el max y min de sigma
        }

    return 1;
}

void Problema::intercambio(vector<int> & v, int valor1, int valor2){
    for(unsigned i=0; i<v.size(); ++i)
        if(v[i] == valor1)
            v[i] = valor2;
}

//-------------------------------------------------------------------------------------------------
// CONSTRUCTOR
//-------------------------------------------------------------------------------------------------

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

//-------------------------------------------------------------------------------------------------
// MÉTODOS PÚBLICOS
//-------------------------------------------------------------------------------------------------

vector<vector<double> > Problema::getMatriz(){
    return matriz;
}

// jjj se puede hacer un un list para que sea más eficiente al eliminar un elemento del vector, en vez de poner el elemento a -1
vector<int> Problema::solucionGreedy(){
    int n_pueblos = matriz.size(),
        mejor_candidato = aleatorio(0, n_pueblos-1);
    vector<int> sol, candidatos;
    
    // rellenamos el vector de candidatos
    for(int i=0; i<n_pueblos; ++i)
        candidatos.push_back(i);

    // añadimos el primer valor aleatorio
    sol.push_back(mejor_candidato);
    candidatos[mejor_candidato] = -1;

    // añadimos los demás pueblos
    while(sol.size() < elem_sel){             
        mejor_candidato = elementoMenorDispersion(candidatos, sol);
        sol.push_back(mejor_candidato);
        candidatos[mejor_candidato] = -1;
    }
    
    return sol;
}

vector<int> Problema::solucionBusquedaLocal(){
    vector<int> res = {1};
    return res;
}